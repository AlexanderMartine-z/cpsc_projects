
#include <iostream>
#include <string>
#include "syntax.hpp"
 using namespace std;

int main() {
    string line;
    getline(cin, line);
    BASICFUNC calc;
    calc.isSyntax(line);
 
    return 0; 
}