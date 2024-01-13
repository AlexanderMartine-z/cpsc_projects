#ifndef CPSC131_PALINDROMEDETECTOR_MYQUEUE_HPP
#define CPSC131_PALINDROMEDETECTOR_MYQUEUE_HPP


/**
 * You do not need to edit this file,
 * though you may add helper methods if you wish.
 */


/// Starter includes
#include "MyQueue.hpp"
#include "MyStack.hpp"
//
#include <string>


//
namespace CPSC131::PalindromeDetector
{
	//
	class MyDetector
	{
		//
		public:
			
			///	Your welcome
			MyDetector();
			
			/**
			 * Receive an std::string
			 * 
			 * Return true if the string is a palindrome
			 * Return false otherwise
			 */
			bool isPalindrome(std::string s);
			
		//
		private:
			
			//	Do not add Stack/Queue as member variable; It will make your class non-thread-safe.
	};
}









#endif
