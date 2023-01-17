// Alexander Martinez
// CPSC 120-07
// 2022-09-27
// alex_m007@csu.fullerton.edu
// @alex3809
//
// Lab 08-02
// Partners: @emilyk123
//
// Read files and print out words that are a palindrome
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void Prompt() {
  std::cout
      << "What's a secret message that you'd like to write into a file?\n";
  std::cout
      << "Type your message out and when you're done press return or enter.\n";
}

int main(int argc, char* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);
  if (arguments.size() < 2) {
    std::cout << "please provide a path to a file";
    return 1;
  }
  std::string output_file_name{arguments.at(1)};
  std::ofstream output_file_stream{output_file_name};
  if (!output_file_stream.is_open()) {
    std::cout << "Could not open the file " << output_file_name << "\n";
    return 42;
  }
  std::string secret_message;
  Prompt();
  std::getline(std::cin, secret_message);
  output_file_stream << secret_message << "\n";
  std::cout << "Your secret message was saved into " << output_file_name
            << "\n";
  output_file_stream.close();

  return 0;
}
