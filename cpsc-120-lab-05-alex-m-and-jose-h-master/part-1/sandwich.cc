// Alexander Martinez
// CPSC 120-01
// 2022-10-04
// alex_m007@csu.fullerton.edu
// @alex3809
// Partners: @Josehernandez503, @EthLo-deimos
//
// Lab 05-01
//
// Print out a description of a sandwich. Validates if the number of arguments is correct.
// Validates if the number of arguments is correct.
// 

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);

if (arguments.size() !=4) {
  std::cout << "Error, you must supply 3 arguments\n";
  return 1;
}

std::string command{arguments.at(0)};
std::string protein{arguments.at(1)};
std::string bread{arguments.at(2)};
std::string condiment{arguments.at(3)};

std::cout << "Your order: A " << protein << " sandwich on "
          << bread << " with " << condiment << ".\n";

  return 0;
}
