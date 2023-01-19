// Alexander Martinez
// CPSC 120-01
// 2022-11-29
// alex_m007@csu.fullerton.edu
// @alex3809
//
// Lab 12-01
// Partners: @ahernandez09
//
// Made Animation

#include <Magick++.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "animated_gradient_functions.h"

const int kImageWidth{512};

const int kImageHeight{512};

const int kNumberOfImages = 10;

int main(int argc, char* argv[]) {
  Magick::InitializeMagick(*argv);

  std::vector<std::string> arguments(argv, argv + argc);
  if (arguments.size() < 2) {
    std::cout << "Please provide a path to a file";
    return 1;
  }

  std::string output_file_name{arguments.at(1)};

  std::string image_format(".gif");
  if (!HasMatchingFileExtension(output_file_name, image_format)) {
    std::cout << arguments.at(1) << " is missing the required file extension "
              << image_format << ".\n";
    return 1;
  }

  std::vector<double> sine_lookup_table = BuildSineLookupTable(kImageWidth);

  Magick::ColorRGB white(1, 1, 1);

  std::vector<Magick::Image> images;

  double blue_step = M_PI / double(kNumberOfImages);

  int row_col_step{kImageWidth / kNumberOfImages};

  for (int current_image = 0; current_image < kNumberOfImages;
       current_image++) {
    Magick::Image image(Magick::Geometry(kImageWidth, kImageHeight), white);

    std::cerr << "Image " << current_image + 1 << "...";
    double blue = sin(blue_step * current_image);

    for (int column = 0; column < image.columns(); column++) {
      for (int row = 0; row < image.rows(); row++) {
        int current_step(current_image * row_col_step);
        double red = sine_lookup_table.at((row + current_step) % kImageWidth);
        double green =
            sine_lookup_table.at((column + current_step) % kImageHeight);
        Magick::ColorRGB color(red, green, blue);
        image.pixelColor(row, column, color);
      }
    }

    images.push_back(image);
    std::cerr << "completed.\n";
  }
  Magick::writeImages(images.begin(), images.end(), output_file_name);

  return 0;
}
