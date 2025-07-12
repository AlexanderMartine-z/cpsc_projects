cmake_minimum_required(VERSION 3.10)
project(cv_proj01 LANGUAGES CXX CUDA)

#Specifies which C++ version to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) # use strict c++ 17, no gnu extensions by default
set(CMAKE_POSITION_INDEPENDENT_CODE OFF) #ensures position-independent code for shared libraries on Linux

#Find opencv
find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc videoio cudaarithm cudaimgproc dnn)

#Find cuda
find_package (CUDA REQUIRED)
#Path to the ONNX Runtime build directory
set(ONNX_RUNTIME_LIB_DIR /home/JuiceBox/onnxruntime/build/Linux/Release) #location for onnxruntime.so
set(ONNX_RUNTIME_PUBLIC_INCLUDE_DIR /home/JuiceBox/onnxruntime/include/onnxruntime/core/session)
set(ONNX_PROTO_INCLUDE_DIR /home/JuiceBox/onnxruntime/build/Linux/Release/_deps/onnx-build) #For ONNX proto headers

#Included Directories
include_directories(${OpenCV_INCLUDE_DIRS})
# Include ONNX Runtime Headers
include_directories(${ONNX_RUNTIME_PUBLIC_INCLUDE_DIR})
include_directories(${ONNX_PROTO_INCLUDE_DIR}) # For ONNX Proto Headers
include_directories(${CUDA_INCLUDE_DIRS})
include_directories("/home/JuiceBox/onnxruntime/include")
#Src Files
add_executable(main src/main.cpp)

#Linking OpenCV libraries
link_directories("/home/JuiceBox/onnxruntime/build/Linux/Release")
target_link_libraries(main ${OpenCV_LIBS})
target_link_libraries(main /home/JuiceBox/onnxruntime/build/Linux/Release/libonnxruntime.so)
target_link_libraries(main ${CUDA_LIBRARIES})

#ONNX Runtime Librarr must be found at runtime
#Add to the library path to the RPATH so executable finds the .so file
set_property(TARGET main PROPERTY CMAKE_INSTALL_RPATH "${ONNX_RUNTIME_LIB_DIR}:${OpenCV_LIB_DIRS}:${CUDA_TOOLKIT_ROOT_DIR}/lib64")
set_property(TARGET main PROPERTY CMAKE_BUILD_RPATH "${ONNX_RUNTIME_LIB_DIR}:${OpenCV_LIB_DIRS}:${CUDA_TOOLKIT_ROOT_DIR}/lib64")

