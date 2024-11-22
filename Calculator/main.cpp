
#include <iostream>
#include <string>
#include "syntax.hpp"
#include "conversion.hpp"
 using namespace std;

int main() {
    string line;
    getline(cin, line);
    POSTTOPRE converted;
    converted.convert(line);
    return 0; 
}