
#ifndef BASICFUNC_HPP
#define BASICFUNC_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class BASICFUNC
{

public:

        BASICFUNC() {};

        string rmvWhiteSpace(string line) {
          line.erase(remove(line.begin(), line.end(), ' '), line.end());
          return line;
        }

        void invalid() 
        { 
          cout << "INVALID NOTATION\n"; 
          exit(1);
        }

        bool operators(char c) {
              switch(c) {
                case '*': 
                return true;

                case '/':
                return true;
                
                case '+':
                return true;

                case '-':
                return true;

                case '^':
                return true;

                case '.':
                return true;
              }
            return false;
        }
        
        void isSyntax(string line) {
                line = rmvWhiteSpace(line);
                
                int x = 0;
                int y = 0;

                for(int i = 0; i < line.size(); i++) {
                  if(isdigit(line[i]))
                  { 
                    goto jmp;
                  }

                  if((true == operators(line[i])) && (true == operators(line[i+1]))) 
                  { invalid(); }

                  switch(line[i]) 
                  {
                   case ')':
                   x += 1;
                   break;

                   case '(':
                   y += 1;
                   break;
                  }
                  jmp:;
            }
            if( x != y ) { invalid(); }
            cout<< "NICE NOTATION\n";
        }

private:


};

#endif