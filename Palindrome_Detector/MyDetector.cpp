

/**
 * TODO: Complete these class definitions
 */

/// Starter includes (YW)
#include "MyDetector.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"
#include <cctype>
#include <iostream>

//
namespace CPSC131::PalindromeDetector
{
	/// YOUR WELCOME
	MyDetector::MyDetector() {}
	
	//
	bool MyDetector::isPalindrome(std::string s)
	{
		//	TODO: Your code here
	   MyQueue<char> queue;
	   MyStack<char> stack;

	   for(size_t x = 0; x < s.size(); x++) {
		if(isalpha(s.at(x)) != 0) {
			queue.enqueue(tolower(s.at(x)));
			stack.push(tolower(s.at(x)));
		}
	   }

	   for(size_t i = 0; i < queue.size(); i++) {
		if(stack.top() != queue.front()) {
			return false;
		}
		else if(stack.top() == queue.front()) {
			stack.pop();
			queue.dequeue();
		}
	   }
		return true;
	}
}












