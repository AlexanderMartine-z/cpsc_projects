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

#include "animated_gradient_functions.h"

#include <cmath>
#include <iostream>

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  return (file_name.size() >= extension.size() &&
          (file_name.compare(file_name.size() - extension.size(),
                             extension.size(), extension) == 0));
}

std::vector<double> BuildSineLookupTable(int image_width) {
  std::vector<double> lookup_table;
  double radian_step = M_PI / double(image_width);
  for (int column = 0; column < image_width; column++) {
    double value = sin(radian_step * column);
    lookup_table.push_back(value);
  }

  return lookup_table;
}
