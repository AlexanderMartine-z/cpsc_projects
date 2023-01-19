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

/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#ifndef ANIMAGED_GRADIENT_FUNCTIONS_H
#define ANIMAGED_GRADIENT_FUNCTIONS_H

#include <string>
#include <vector>

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension);

std::vector<double> BuildSineLookupTable(int image_width);

#endif
