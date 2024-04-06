#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 public:
  vector() : size_(0), buf_(0) {}


  vector(size_type n) {
    vector_ = new value_type[n];
    size_ = n;
    buf_ = n;
  }

  vector(std::initializer_list<value_type> const &items) {
    for (auto item : items) {
      push_back(item);
    }
  }

  vector(const vector &v) {
    vector_ = new value_type[v.buf_];
    *this = v;
  }

  vector(vector &&v) {
    *this = std::move(v);
  }

  ~vector() {
    delete[] vector_;
    size_ = 0;
    buf_ = 0;
    vector_ = nullptr;
  }

  vector &operator=(const vector &v) noexcept {
    std::copy(v.vector_, v.vector_ + v.size_, vector_);
    size_ = v.size_;
    buf_ = v.buf_;
    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      for (size_t i = 0; i < v.size(); ++i) {
        push_back(v.vector_[i]);
        v.vector_[i] = 0;
      }
      v.size_ = 0, v.buf_ = 0;
      delete[] v.vector_;
      v.vector_ = nullptr;
    }
    return *this;
  }

  reference operator[](size_type pos) {
    return vector_[pos];
  }


  iterator begin() {
    return size_ > 0 ? &vector_[0] : 0;
  }

  iterator end() {
    return size_ > 0 ? &vector_[size_] : 0;
  }

  iterator insert(iterator pos, const_reference value) {
    size_type position = pos - &vector_[0];
    vector_[position] = value;
    return &vector_[position];
  }

  reference at(size_type pos) {
    if (pos >= buf_) throw std::out_of_range("Current element outside the array");
    return vector_[pos];
  }

  const_reference front() {
    if (empty()) {
      throw std::out_of_range("Array is empty");
    }

    return vector_[0];
  }

  const_reference back() {
    if (empty()) {
      throw std::out_of_range("Array is empty");
    }

    return vector_[size_ - 1];
  }

  T *data() {
    if (empty()) {
      throw std::out_of_range("Array is empty");
    }

    return &vector_[0];
  }

  bool empty() {
    return vector_ == nullptr;
  }

  size_type size() {
    return size_;
  }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size > buf_) {
      value_type *new_vector_ = new value_type[size];
      std::copy(vector_, vector_ + size_, new_vector_);
      delete[] vector_;
      vector_ = new_vector_;
      buf_ = size;
    }
  }

  size_type capacity() {
    return buf_;
  }

  void shrink_to_fit() {
    value_type *new_vector_ = new value_type[size_];
    std::copy(vector_, vector_ + size_, new_vector_);
    delete[] vector_;
    vector_ = new_vector_;
    buf_ = size_;
  }

  void clear() {
    size_ = 0;
  }

  void erase(iterator pos) {
    if (pos > end()) pos = end();
    if (pos < begin()) pos = begin();
    for (iterator i = pos; i < end(); ++i) {
      *i = *(i + 1);
    }
    size_--;
  }

  void push_back(const_reference value) {
    if (size_ == buf_) {
      reserve(buf_ ? buf_ * 2 : 1);
    }

    vector_[size_++] = value;
  }

  void pop_back() {
    size_--;
  }

  void swap(vector &other) {
    std::swap(vector_, other.vector_);
    std::swap(size_, other.size_);
    std::swap(buf_, other.buf_);
  }

 private:
  size_type size_ = 0;
  size_type buf_ = 0;
  value_type *vector_ = nullptr;
  // qwefrgtfhfgdrsewrqefre
  //(исторический момент) НЕ УДАЛЯТЬ!

};
}  // namespace s21
#endif  // _VECTOR_H_