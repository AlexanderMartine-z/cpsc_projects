// Alexander Martinez
// CPSC 120-07
// 2022-09-27
// alex_m007@csu.fullerton.edu
// @alex3809
//
// Lab 08-01
// Partners: @emilyk123
//
// Read files and print out words that are a palindrome
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool IsPalindrome(const std::string& word) {
  std::string revered_word{word.rbegin(), word.rend()};
  return word == revered_word;
}

int main(int argc, char const* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  if (arguments.size() < 2) {
    std::cout << "Please provide a path to a file";
    return 1;
  }
  std::string input_file_name{arguments.at(1)};
  std::ifstream input_file_stream{input_file_name};
  if (!input_file_stream.is_open()) {
    std::cout << "Could not open the file " << input_file_name
              << ". Exiting.\n";
    return 42;
  }
  while (input_file_stream.good()) {
    std::string line_buffer;
    std::getline(input_file_stream, line_buffer);
    if (IsPalindrome(line_buffer) && line_buffer.size() > 3) {
      std::cout << line_buffer << "\n";
    }
  }
  input_file_stream.close();
  return 0;
}
