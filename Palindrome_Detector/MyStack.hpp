#ifndef CPSC131_MYSTACK_HPP
#define CPSC131_MYSTACK_HPP




//
#include <forward_list>
#include <stdexcept>


//
namespace CPSC131
{
	template <class T>
	class MyStack
	{
		//
		public:
			
			/// YOUR WELCOME
			MyStack() {}
			
			/**
			 * push()
			 * 
			 * Takes an item and pushes it onto the stack.
			 */
			void push(const T& item)
			{
				list.push_front(item);
				size_++;
				
			}
			
			/**
			 * Removes the next item from the stack
			 * 
			 * Does not return a value
			 * 
			 * If the stack is empty: throw an std::range_error
			 */
			void pop()
			{
				if(list.empty() == true) {
					throw std::range_error("List is empty");
				}
				list.pop_front();
				size_--;
			}
			
			/**
			 * Peek at the top of the stack
			 * 
			 * Does not remove anything.
			 * 
			 * If the stack is empty: throw an std::range_error
			 */
			T& top()
			{
			if(list.empty() == true) { throw std::range_error("List is empty"); }
			return list.front();
			}
			
			/**
			 * Remove all items from the stack
			 */
			void clear()
			{
				list.clear();
				size_ = 0;
			}
			
			/**
			 * Return the number of items in the stack
			 */
			size_t size()
			{
				return size_;
			}
			
			/**
			 * Return true if the stack is empty, false otherwise
			 */
			bool empty()
			{
				if(size_ == 0) { return true; }
				return false;
			}
			
		//
		private:
			

			std::forward_list<T> list;
			size_t size_ = 0;
			/******************************/
	};
}







#endif
