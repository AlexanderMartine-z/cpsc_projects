#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


#include <forward_list>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


namespace CPSC131::MyHashTable {
//
template <class VTYPE> class MyHashTable {
  //
public:
  //
  static constexpr size_t DEFAULT_CAPACITY = 1024;
  static constexpr size_t ULLONG_WRAP_AT = 4294967295;


  MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY) {
    setCapacity(capacity);
  }


  MyHashTable(const MyHashTable &other) {
    capacity_ = other.capacity();
    size_ = other.size();
    n_collisions_ = other.n_collisions();
    table_ = new std::forward_list<std::pair<std::string, VTYPE>>[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
      for (auto &x : other.table_[i]) {
        table_[i].emplace_front(x);
      }
    }
  }


  ~MyHashTable() {
    clear();
    if (table_ != nullptr) {
      delete[] table_;
      table_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      n_collisions_ = 0;
    }
  }


  size_t capacity() const { return capacity_; }


  size_t size() const { return size_; }

 
  bool empty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }


  size_t n_collisions() const { return n_collisions_; }


  void setCapacity(size_t c) {
    auto temp = table_;
    size_t old = capacity_;
    capacity_ = c;
    n_collisions_ = 0;

    table_ = new std::forward_list<std::pair<std::string, VTYPE>>[capacity_];

    if (temp != nullptr) {
      for (size_t i = 0; i < old; i++) {
        for (auto &x : temp[i]) {
          auto index = midSquareHash(x.first);
          if (table_[index].empty() == false) {
            n_collisions_++;
          }
          table_[index].emplace_front(x.first, x.second);
        }
      }
    }
    delete[] temp;
  }

  unsigned long long int hash(std::string key) const {
    return this->midSquareHash(key);
  }

  
  unsigned long long int midSquareHash(std::string key) const {
    unsigned long long sum = 1;
    for (char char_ : key) {
      auto rep = static_cast<unsigned long long>(char_);
      sum = sum * rep;
      if (sum > 4294967295) {
        sum = sum % 4294967295;
      }
    }

    sum = sum * sum;

    std::string sum_string = std::to_string(sum);
    if (sum_string.empty() == true) {
      return 0;
    }

    size_t pos = sum_string.size() / 4;
    size_t length = sum_string.size() / 2;
    std::string sub = sum_string.substr(pos, length);
    std::string x = sub;

    unsigned long long sum_num = std::stoull(x);
    if (capacity() == 0) {
      return 0;
    }
    sum_num = sum_num % capacity();
    return sum_num;
  }

  

  bool exists(std::string key) const {
    if (table_ == nullptr) {
      return false;
    }
    auto index = midSquareHash(key);
    for (auto &i : table_[index]) {
      if (i.first == key) {
        return true;
      }
    }
    return false;
  }


  void add(std::string key, VTYPE value) {
    if (exists(key) == true) {
      throw std::runtime_error("The key already exists: " + key);
    }
    auto index = midSquareHash(key);

    if (table_[index].empty() == false) {
      n_collisions_++;
    }
    table_[index].emplace_front(key, value);
    size_++;
  }

  VTYPE &get(std::string key) const {
    auto index = midSquareHash(key);
    if (table_[index].empty()) {
      table_[index].front().second;
    }
    for (auto &i : table_[index]) {
      if (i.first == key) {
        return i.second;
      }
    }
    throw std::runtime_error(
        "Cannot get value for key because it doesn't exist: " + key);
  }


  std::forward_list<std::string> getAllKeys(bool sorted = false) const {
    std::forward_list<std::string> keys;

    if (size_ == 0) {
      return keys;
    }

    for (size_t i = 0; i < capacity_; ++i) {
      for (auto &index : table_[i]) {
        keys.push_front(index.first);
      }
    }
    if (sorted == true) {
      keys.sort();
      sorted = false;
    }
    return keys;
  }

 
  void remove(std::string key) {
    if (exists(key) == false) {
      throw std::runtime_error(
          "Cannot remove value for key because it doesn't exist: " + key);
    }

    auto index = midSquareHash(key);
    auto &list = table_[index];
    auto itr = list.before_begin();

    if (table_[index].empty() == false) {
      n_collisions_--;
    }

    for (auto &i : table_[index]) {
      if (i.first == key) {
        list.erase_after(itr);
        size_--;
        break;
      }
      itr++;
    }
  }

  void clear() {
    auto keys = getAllKeys();
    auto key_itr = keys.begin();
    while (key_itr != keys.end()) {
      remove(*key_itr);
      key_itr++;
    }
    size_ = 0;
    n_collisions_ = 0;
  }


  MyHashTable<VTYPE> &operator=(const MyHashTable<VTYPE> &other) {
    delete[] table_;
    table_ =
        new std::forward_list<std::pair<std::string, VTYPE>>[other.capacity()];
    capacity_ = other.capacity();
    n_collisions_ = other.n_collisions_;
    size_ = other.size();

    std::forward_list<std::string> keys = other.getAllKeys();
    for (size_t i = 0; i < capacity_; ++i) {
      table_[i] = other.table_[i];
    }
    return *this;
  }

  
private:

  size_t capacity_ = 0;

  size_t size_ = 0;

  size_t n_collisions_ = 0;


  std::forward_list<std::pair<std::string, VTYPE>> *table_ = nullptr;
};
} 

#endif
