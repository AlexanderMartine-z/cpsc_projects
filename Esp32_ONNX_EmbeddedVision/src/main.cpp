// #include "opencv2/video/tracking.hpp" //for optical flow algo
#include "opencv2/highgui.hpp" // high level GUI
#include "opencv2/imgproc.hpp" //for image processing
#include "opencv2/videoio.hpp" //video I/O
#include <ctype.h>
#include <iostream>
#include <onnxruntime_cxx_api.h> // ONNX Runtime C++ API
#include <opencv2/opencv.hpp>    // OpenCV library
#include <string>
#include <vector>

int main(int argc, char **argv) {
  // Using OpenCV to open camera and capture frame
  cv::VideoCapture cap;
  cv::CommandLineParser parser(argc, argv, "{@input|0|}");
  //@input default value is 0 which is value for opening default webcam
  std::string input = parser.get<std::string>("@input");
  if ((input.size() == 1) && (isdigit(input[0]))) {
    cap.open(input[0] - '0');
  } else {
    cap.open(input);
  }

  const std::string window_name = "Sign Language Recognition";
  cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

  // ONNX Model Loading and Session Creation
  /* Ort Env should be created once and reused across program
      Required base for most ONNX runtime constructors, may throw so use a try
     catch
  */
  // use a try catch because it may throw a runtime error
  try {
    // Must first initialize Ort::Env object because it starts the ONNX runtime
    // evironemnt It holds all the logging state and logging configuration for
    // all operations
    Ort::Env environment_o(ORT_LOGGING_LEVEL_WARNING,
                           "Sign_Language_Detection");

    // Defines the path to your ONNX file
    const ORTCHAR_T *model_path_ =
        "../models/mediapipe_hand-handlandmarkdetector.onnx";

    //
    Ort::SessionOptions session_opt;

    /* Specifies we want to use the GPU for inference via CUDA
     * this is the key step to enable gpu acceleration for much faster
     * performance
     */
    OrtCUDAProviderOptions cuda_options{};
    session_opt.AppendExecutionProvider_CUDA(cuda_options);
    session_opt.SetGraphOptimizationLevel(
        GraphOptimizationLevel::ORT_ENABLE_ALL);
    // session_ is the main inference engine object that holds the loaded model
    auto session_ = Ort::Session(environment_o, model_path_, session_opt);
    std::cout << "ONNX Runtime session created" << std::endl;

    // Phase 2: Inspect Model Inputs

    // Gets an instance of the default ONNX Runtime allocator.
    // Some session methods, particularly those that return strings (like names)
    // naeed an allocator to manage the memory for the object session_
    // information
    Ort::AllocatorWithDefaultOptions allocator;

    // Gets the number of Input Nodes for the model, (like a math function the
    // input the nodes represent the parameters) In this case of CV it is only 1
    // because we are only processing the image, used to confirm our models
    // structure
    size_t num_input_nodes = session_.GetInputCount();
    std::cout << "# of Model Inputs: " << num_input_nodes << std::endl;

    // We need this name so later when we run the model we can tell the session
    //"Here is my image, and i want you to feed it into the input node names
    // input" Gets the name of the first input node Need this name to associate
    // our input tensor with the correct model input when we run inference.
    Ort::AllocatedStringPtr input_name_ptr =
        session_.GetInputNameAllocated(0, allocator);
    const char *input_name = input_name_ptr.get();
    std::cout << "Input[0] name is: " << input_name << std::endl;

    // Gets the type information for the first input mode
    // This object contains details about the inputs type (tensor, sequence ...)
    Ort::TypeInfo input_type_info = session_.GetInputTypeInfo(0);

    // This is a request from the object, we are expecting a tensor type, gives
    // info like its shape and element type If the input was of other type like
    // a map the try catch block will handle the error
    auto input_tensor_info = input_type_info.GetTensorTypeAndShapeInfo();

    // Gets the shape of the input tensor as a vector of integers
    // Critical: Tells us the exact dimensions we need to resize our image to.
    std::vector<int64_t> input_dims = input_tensor_info.GetShape();

    // Used in neural networks, batch size refers to how many images will be
    // processed at the same time
    // A model can be designed flexible and is signaled using -1 in ONNX
    // This piece of code handles models with dynamic batch size and says we
    // will only process one image at the same time
    if (input_dims[0] < 0) {
      input_dims[1] = 1;
    }
	
    std::vector<const char *> output_names;
    for (size_t i = 0; i < session_.GetOutputCount(); i++) {
      Ort::AllocatedStringPtr name_ptr =
          session_.GetOutputNameAllocated(i, allocator);
      output_names.push_back(name_ptr.get());
    }

    const std::vector<std::pair<int, int>> hand_connections = {
        {0, 1},   {1, 2},   {2, 3},   {3, 4},   {5, 6},   {6, 7},   {7, 8},
        {9, 10},  {10, 11}, {11, 12}, {13, 14}, {14, 15}, {15, 16}, {17, 18},
        {18, 19}, {19, 20}, {0, 5},   {5, 9},   {9, 13},  {13, 17}, {0, 17},
    };

    cv::Mat frame;

	std::cout << "Initialized the environment " << std::endl;

    while (1) {
      cap >> frame;
      if (frame.empty()) {
        break;
      }
      // return {"image": ((batch_size, 3, 256, 256), "float32")} python code
      // for input resize image to specification of the onnx model
      cv::Mat resized_image;
      cv::resize(frame, resized_image, cv::Size(input_dims[2], input_dims[3]));

      // Converts to RGB and normalize to [0,1]
      // OpenCV captures frames in BGR, so we need to convert back to RGB for
      // onnx model as seen in python code example input, the image has to be of
      // type 32bit float using .convertTO to change the data type of pixel
      // Model expects float type data, 0.0 to 1.0, raw image is integer 0 - 255
      // The convertTo function multiplies every pixel value in the image by
      // that scaling factor. EX 255* (1.0/255.0) = 1.0
      cv::Mat float_image;
      cv::cvtColor(resized_image, float_image, cv::COLOR_BGR2RGB);
      float_image.convertTo(float_image, CV_32F, 1.0 / 255.0);

      //      Convert from HWC to CHW format.
      //    - What it does: Rearranges the image data from Height-Width-Channel
      //    to Channel-Height-Width.
      //    - Why: Most deep learning frameworks, including the one this model
      //    was trained in, expect the
      //      channel data to be first. `cv::dnn::blobFromImage` is a convenient
      //      OpenCV function that handles this conversion efficiently.
      //    The blob is a 4D matrix with the shape [1, 3, 256, 256].
      cv::Mat input_blob = cv::dnn::blobFromImage(float_image);

      // Create Input Tensor & Run Inference
      // Create a a memory info object that that describes where the input
      // tensor data is located Tells the ONNX Runtime that the data for our
      // tensor is in standard CPU memory not GPU OrtArenaAllocator is standard
      // efficient allocator, OrtMemTypeCPU is the default for CPU
      Ort::MemoryInfo memory_info =
          Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeCPU);
	std::cout << "Created Input Tensor and Run Inference" << std::endl;
      // Create the input tensor object
      // Wraps preprocessed image data (input_blob) in an Ort::Value object,
      // which is the format the ONNX runtime understands This is a zero copy
      // operation, meaning the data is not duplicated memory_info is the memory
      // description we just created (float*)input_blob.data, a pointer to the
      //actual image data inside the openCV blob input_blob.total() The total
      // number of float values in the blob (1 * 3 * 256 * 256)
      // input_dims.data(), a pointer to our input_dims vector which holds the
      // shape [1,3,256,256] input_dims,size(), total number of dimernsions
      // which is 4
      Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
          memory_info, (float *)input_blob.data, input_blob.total(),
          input_dims.data(), input_dims.size());
	std::cout << "Created Input Tensor Object " << std::endl;
      // Run session, providing the input and requesting all three outputs by
      // name
      auto output_tensors =
          session_.Run(Ort::RunOptions(nullptr), &input_name, &input_tensor, 1,
                       output_names.data(), output_names.size());
	std::cout << "Session has started to run " << std::endl;
      // -- Process Output --
      // The landmark data is in the 3rd output tensor (index 2)
      float *landmark_data = output_tensors[2].GetTensorMutableData<float>();
      auto landmark_shape =
          output_tensors[2].GetTensorTypeAndShapeInfo().GetShape();
      int num_landmarks = landmark_shape[1]; // should be 21
      int landmark_dims = landmark_shape[2]; // (x,y,z)

      // The model outputs normalized coordinates (values between 0 and 1).
      // We must scale them by the original frame's width and height to get
      // pixel coordinates. The landmark data is a flat array, so we access the
      // coordinates for the i-th landmark like this: x = data at index (i * 3 + 0) y = data at index (i * 3 + 1) z = data at index (i * 3 + 2)
      // ignore z for 2D drawing.
      std::vector<cv::Point> landmark_points;
      for (int i = 0; i < num_landmarks; i++) {
        float x = landmark_data[i * landmark_dims + 0] * frame.cols;
        float y = landmark_data[i * landmark_dims + 1] * frame.rows;
        landmark_points.push_back(
            cv::Point(static_cast<int>(x), static_cast<int>(y)));
      };

      //Display the results 
	//Loop through hand_connections list, tells us which pair of points to connect 
	//Draws a pruple line with a thickness of 2 pixels
	for(const auto& conn : hand_connections) {
		cv::line(frame, landmark_points[conn.first], landmark_points[conn.second], cv::Scalar(128,0,128), 2);
	}
	
	//Draw the points/landmarks as circles 
	//diameter of 10 pix, red circle, -1 means filled cicrcle not outline
	for(const auto & points_ : landmark_points) {
		cv::circle(frame, points_, 5, cv::Scalar(0,0,255), -1);
	}
	
	imshow(window_name, frame);

      char c = (char)cv::waitKey(10);
      if (c == 27) {
        break;
      } // 27 means ESC in ASCII
    }

  } catch (const Ort::Exception &e) {
    std::cerr << "ONNX Runtime Error " << e.what() << std::endl;
    return -1;
  }

  return 0;
};
