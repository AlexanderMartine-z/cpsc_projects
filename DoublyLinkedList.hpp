#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


//
#include <stdlib.h>

#include <iostream>
#include <stdexcept>


namespace CPSC131 {

namespace DoublyLinkedList {

template <class T>
class DoublyLinkedList {
 public:
  /**
   * Node class, representing a single item in our linked list
   */

  class Node {
   public:
    /// CTORS
    Node() : prev_(nullptr), next_(nullptr) {}
    Node(T element) : element_(element), prev_(nullptr), next_(nullptr) {}
    Node(T element, Node* prev, Node* next)
        : element_(element), prev_(prev), next_(next) {}

    void setPrevious(Node* prev) { prev_ = prev; }

    void setPrev(Node* prev) { prev_ = prev; }

    Node* getPrevious() { return prev_; }

    Node* getPrev() { return prev_; }

    void setNext(Node* next) { next_ = next; }


    Node* getNext() { return next_; }


    void setElement(T element) { element_ = element; }

 
    T& getElement() { return this->element_; }


    T& operator*() { return this->element_; }

   private:
    T element_;
    Node* prev_;
    Node* next_;
  };

  /**
   * Nested Iterator class.
   */
  class Iterator {
   public:
    
    Iterator() {
    
    }

    Iterator(Node* head, Node* tail) : head_(head), tail_(tail) {
      this->cursor_ = this->end();
    }

    Iterator(Node* head, Node* tail, Node* cursor)
        : head_(head), tail_(tail), cursor_(cursor) {}

    Node* begin() {
      return head_;
    }


    Node* end() {

      return nullptr;
    }

    Node* getCursor() {

      return cursor_;
    }

    
    Iterator& operator=(const Iterator& other) {
      this->cursor_ = other.cursor_;
      this->head_ = other.head_;
      this->tail_ = other.tail_;
      return *this;
    }

    bool operator==(const Iterator& other) {
      if (cursor_ == other.cursor_) {
        return true;
      }

      return false;
    }

    bool operator!=(const Iterator& other) {
      if (cursor_ != other.cursor_) {
        return true;
      }
      return false;
    }


    Iterator& operator++() {
      this->cursor_ = cursor_->getNext();

      return *this;
    }

    
    Iterator operator++(int) {
      auto before = *this;
      cursor_ = this->cursor_->getNext();
      return before;
    }

   
    Iterator& operator--() {
      this->cursor_ = this->cursor_->getPrev();
      return *this;
    }

    
    Iterator operator--(int) {
      auto before = *this;
      cursor_ = cursor_->getPrev();

      return before;
    }


    Iterator operator+=(size_t add) {
      for (size_t i = 0; i < add; i++) {
        this->cursor_ = cursor_->getNext();
      }
      return *this;
    }
    

    Iterator operator-=(size_t add) {
      if (add > 0) {
        for (size_t i = 0; i < add; i++) {
          this->cursor_ = this->cursor_->prev_;
          this->head_ = this->head_->prev_;
          this->tail_ = this->tail_->prev_;
        }
      }
 

      return *this;
    }


    Iterator operator+=(int add) {
      int i = 0;
      if (add > 0) {
        while (i < add && cursor_ != nullptr) {
          cursor_ = cursor_->getNext();
          i++;
        }
      } else if (add < 0) {
        while (i > add && cursor_ != nullptr) {
          cursor_ = cursor_->getPrev();
          i++;
        }
      }
      return *this;
    }


    Iterator operator-=(int subtract) {
      int i = 0;
      //	TODO: Your code here
      if (subtract < 0)
        while (i > subtract && cursor_ != nullptr) {
          cursor_ = cursor_->getPrev();
          i--;
        }
      else if (subtract > 0) {
        while (i < subtract && cursor_ != nullptr) {
          cursor_ = cursor_->getPrev();
          i++;
        }
      }
      return *this;
    }


    T& operator*() {
      return this->cursor_->getElement();
    }

   private:
    Node* head_ = nullptr;

    Node* tail_ = nullptr;

    Node* cursor_ = nullptr;

    friend class DoublyLinkedList;
  };

  DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  DoublyLinkedList(const DoublyLinkedList& other) {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
    for (Iterator itr = other.begin(); itr != other.end(); itr++) {
      push_back(*itr);
    }

  }

  ~DoublyLinkedList() {
    clear();
  }


  void assign(size_t count, const T& value) {
    clear();
    Node* node = new Node();
    node->setNext(nullptr);
    node->setPrev(nullptr);
    node->setElement(value);
    head_ = node;
    tail_ = node;

    for (size_t i = 1; i < count; i++) {
      node = new Node();
      node->setElement(value);
      node->setNext(nullptr);
      node->setPrev(tail_);
      tail_->setNext(node);
      tail_ = node;
    }
    size_ = count;
  }


  void assign(Iterator first, Iterator last) {
    clear();
    if (first.getCursor() <= last.getCursor()) {
      for (Node* node = first.getCursor(); node != first.end(); node++) {
        push_back(node->getElement());
      }
    } else {
      for (Node* node = first.getCursor(); node != last.getCursor(); node++) {
        push_back(node->getElement());
      }
    }
  }

  Node* head() const {

    return head_;
  }

  Node* tail() const {

    return tail_;
  }

  Iterator begin() const {

    return Iterator(head_, tail_, head_);
  }


  Iterator last() const {

    return Iterator(head_, tail_, tail_);
  }


  Iterator end() const {

    return Iterator(head_, tail_, nullptr);
  }


  bool empty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }


  size_t size() const {

    return size_;
  }


  void clear() {
    while (head_ != nullptr) {
      Node* x = head_;
      head_ = head_->getNext();
      delete x;
    }
    tail_ = nullptr;
    size_ = 0;
  }


  Iterator insert_after(Iterator pos, const T& value) {
    if (size_ == 0) {
      Node* node = new Node();
      node->setNext(nullptr);
      node->setPrev(nullptr);
      node->setElement(value);
      head_ = node;
      tail_ = node;
      size_++;
    } else if (pos == this->end()) {
      return push_back(value);
    }
    Node* node = new Node();
    node->setElement(value);
    node->setNext(pos.getCursor()->getNext());
    node->setPrev(pos.getCursor());
    pos.getCursor()->setNext(node);
    size_++;
    return Iterator(node, head_, tail_);
  }

 
  Iterator insert_after(size_t pos, const T& value) {
    Iterator itr = begin();
    for (size_t i = 0; i < pos; i++) {
      itr++;
    }
    Iterator iter = insert_after(itr, value);
    return Iterator(iter.getCursor(), head_, tail_);
  }

  
  Iterator erase(Iterator pos) {
    if (pos.getCursor() == nullptr) {
      throw std::range_error("Out of range");
    }
    Node* del = nullptr;
    Node* temp = head_;
    Node* current = head_;
    while (current != nullptr && current != pos.getCursor()) {
      temp = current;
      current = current->getNext();
      if (current == tail_) {
        delete tail_;
        return this->end();
      }
      del = current;
      current->setNext(current->getNext());
      temp->setNext(current);
      delete del;
    }
    return Iterator(head_, tail_, current);
  }


  Iterator push_after(Iterator pos, const T& value) {
    //	TODO: Your code here
    if (pos == this->end()) {
      throw std::range_error("Out of range");
    }
    Node* node = new Node();
    node->setElement(value);
    node->setNext(pos.getCursor()->getNext());
    node->setPrev(pos.getCursor());
    pos.getCursor()->setNext(node);
    size_++;
    return Iterator(head_, tail_, node);
  }

 
  void push_front(const T& value) {
    //	TODO: Your code here
    if (size_ == 0) {
      push_back(value);
    } else {
      Node* node = new Node();
      node->setElement(value);
      node->setNext(head_);
      node->setPrev(tail_);
      head_->setPrev(node);
      head_ = node;
      size_++;
    }
  }

  Iterator push_back(const T& value) {
    Node* node = new Node();
    node->setElement(value);
    if (tail_ == nullptr) {
      head_ = node;
      tail_ = node;
    } else {
      node->setNext(nullptr);
      node->setPrev(tail_);
      tail_->setNext(node);
      tail_ = node;
    }
    size_++;
    return Iterator(head_, tail_, tail_);
  }

  void pop_front() {
    if (size_ == 0) {
      throw std::logic_error("Our list is empty sir/maam");
    }
    Node* del = head_;
    head_ = head_->getNext();
    delete del;

    //	TODO: Your code here
    size_--;
  }


  void pop_back() {
    if (size_ <= 0) {
      throw std::logic_error("Empty in the DLL");
    }
    if (size_ == 1) {
      Node* del = tail_;
      tail_ = tail_->getPrev();
      delete del;
      tail_ = nullptr;
      head_ = nullptr;
      size_ = 0;
    } else if (size_ > 1) {
      Node* del = tail_;
      tail_ = tail_->getPrev();
      delete del;
      size_--;
    }
  }

  T& front() {
    if (size_ <= 0) {
      throw std::logic_error("Empty in the DLL");
    }
    return head_->getElement();
  }


  T& back() {
    if (size_ <= 0) {
      throw std::logic_error("Empty in the DLL");
    }
    return tail_->getElement();
  }

  
  T& at(size_t index) {
    Node* x = head_;
    if (index < 0 || size_ <= index) {
      throw std::range_error("Index out of bounds");
    }

    for (size_t i = 0; i < index; i++) {
      x = x->getNext();
    }

    return x->getElement();
  }


  void reverse() {
    DoublyLinkedList<T> temp;
    for (size_t i = 0; i < size_; i++) {
      temp.push_front(at(i));
    }

    clear();

    for (size_t i = 0; i < temp.size(); i++) {
      push_back(temp.at(i));
    }

    temp.clear();
  }



  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) {
    clear();

    assign(other.begin(), other.end());
    return *this;
  }


  bool operator==(DoublyLinkedList<T>& other) {
    Node* node = head_;
    Iterator rhs(head_, tail_, node);
    if (other.size_ == size_) {
      for (size_t i = 0; i < other.size(); i++) {
        if (other.at(i) == rhs.getCursor()->getElement()) {
          rhs++;
          return true;
        }
      }
    }
    return false;
  }


  bool operator!=(DoublyLinkedList<T>& other) {
    if (operator==(other) == false) {
      return true;
    }
    return false;
  }

 private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;
};
}  // namespace DoublyLinkedList
}  // namespace CPSC131

#endif
