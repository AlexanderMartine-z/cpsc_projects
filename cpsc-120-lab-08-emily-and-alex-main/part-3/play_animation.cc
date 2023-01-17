// Alexander Martinez
// CPSC 120-07
// 2022-09-27
// alex_m007@csu.fullerton.edu
// @alex3809
//
// Lab 08-02
// Partners: @emilyk123
//
// ANSI & ASCII Animation
//

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main(int argc, char const* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  if (arguments.size() < 2) {
    std::cout << "please provide a path to a file";
    return 1;
  }
  std::string input_file_name{arguments.at(1)};
  std::ifstream input_file_stream{input_file_name};
  if (!input_file_stream.is_open()) {
    std::cout << "Could not open the file " << input_file_name << "\n";
    return 42;
  }
  char letter{0};
  while (input_file_stream.get(letter)) {
    std::cout << letter;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  input_file_stream.close();

  return 0;
}
