#ifndef STACK_HPP
#define STACK_HPP
#include "syntax.hpp"
#include <stack>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;
class POSTTOPRE : public BASICFUNC
{

public:
    POSTTOPRE() {};
    int Precedence(char x)
    {
        switch (x)
        {
        case '^':
            return 4;

        case '*':
        case '/':
            return 3;

        case '+':
        case '-':
            return 1;
        
        }
        return 0;
    }

    string convert(string line)
    {
        string line_ = rmvWhiteSpace(line);
        line_ = "(" + line_ + ")";
        reverse(line_.begin(), line_.end());
        stack<char> conv;
        string result = "";

        for (int i = 0; i < line_.size(); i++)
        {
            
            if (isdigit(line_[i]))
            {
                result.push_back(line_[i]);
                continue;
            } 
 
            // if closed parantheses push open parantheses
            if (line_[i] == ')')
            {
                conv.push(')');
            } 

            // if incoming op. < op. in stack 
            if (operators(line_[i]))
            {
                while (!conv.empty() && Precedence(line_[i]) < Precedence(conv.top()))
                {
                    result.push_back(conv.top());
                    conv.pop();
                    conv.push(line_[i]);
                }
                    conv.push(line_[i]);
            }
            else if (line_[i] == '(')
            {

                while(!conv.empty() && conv.top() != ')') 
                {
                    result.push_back(conv.top());
                    conv.pop();
                }
                if(!conv.empty()) { conv.pop(); }
            }
        }

        while(!conv.empty()) 
        {
            result.push_back(conv.top());
            conv.pop(); 
        } 
        reverse(result.begin(), result.end());
        cout << endl << "result: " << result << endl;
        return result;
    }
    private:
    };

#endif
