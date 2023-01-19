// Alexander Martinez
// CPSC 120-01
// 2022-10-04
// alex_m007@csu.fullerton.edu
// @alex3809
// Partners: @Josehernandez503, @EthLo-deimos 
//
// Lab 05-02
//
// Finds the Arithmetic Mean of the values inputted.

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  std::vector<std::string> arguments(argv, argv + argc);

  // TODO: Validate that there is at least one command line argument.
  // If not, print an error message and return a non-zero value.
if (arguments.size() < 2) {
  std::cout << "Error, you must supply at least one number\n";
  return 1;
}
  // TODO: Write a for-each loop to sum (add up) all of the command line
  // arguments.
  // Use a double or float type so that your program preserves fractional
  // values.
  // The loop needs to skip over the command name, which is the first element
  // of the arguments vector.
  // Each argument is a std::string. You will need to convert each string into
  // a number with the std::stod or std::stof function. 
int i{0};
int average{0};
bool first{true};
for (const std::string& argument : arguments) {
  if (first) {
    first = false;
    continue;
  }
  int value(std::stoi(argument));
  average += value;
  i++;

}

average /= i;
std::cout << "Average = " << average << std::endl;

  // TODO: After the loop has finished summing the arguments, calculate the
  // average of the values. Recall that the average is the total value divided
  // by the number of values.

  // TODO: Use cout to print out a message of the form
  // average = *AVERAGE*
  // on its own line.

  return 0;
}
