#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class vector {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 public:
  // Construct
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);

  // Dest
  ~vector();

  // Iter
  iterator begin();
  iterator end();
  iterator insert(iterator pos, const_reference value);

  // Operator
  vector &operator=(const vector &v) noexcept;
  vector &operator=(vector &&v) noexcept;
  reference operator[](size_type pos);


  // Func-s
  reference at(size_type pos);  
  const_reference front();  
  const_reference back();  
  T *data();  
  bool empty(); 
  size_type size();
  size_type max_size(); 
  void reserve(size_type size); 
  size_type capacity();
  void shrink_to_fit();
  void clear();
  void erase(iterator pos); //delete by pos
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
//fields
 private:
  size_type size_ = 0;
  size_type buf_ = 0;
  value_type *vector_ = nullptr;
};
}  // namespace s21

#endif  // _VECTOR_H_