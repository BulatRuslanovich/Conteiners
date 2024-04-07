#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = T *;
  using const_iteratir = const T *;

 private:
  value_type array_[N] = {};
  size_type size_;

 public:
  array() : size_(N) {}

  array(std::initializer_list<value_type> const &items) : array() {
    int i = 0;
    for (auto item : items) {
      if ((size_t)i < N) {
        array_[i] = item;
        ++i;
      }
    }
  }

  array(const array &a) : array() {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = a.array_[i];
    }
  }

  array(array &&a) : array() {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = std::move(a.array_[i]);
    }
  }

  ~array() { size_ = 0; }

  iterator data() { return N > 0 ? array_ : 0; }

  iterator begin() { return N > 0 ? array_ : 0; }

  iterator end() { return N > 0 ? array_ + N : 0; }

  array &operator=(const array &a) noexcept {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = a.array_[i];
    }

    return *this;
  }

  array &operator=(array &&a) noexcept {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = std::move(a.array_[i]);
    }

    return *this;
  }

  reference operator[](size_type pos) { return at(pos); }

  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("Out of range");
    }

    return array_[pos];
  }

  const_reference front() {
    if (empty()) {
      throw std::out_of_range("Array is empty");
    }

    return array_[0];
  }
  const_reference back() {
    if (empty()) {
      throw std::out_of_range("Array is empty");
    }

    return array_[N - 1];
  }

  bool empty() { return begin() == end(); }

  size_type size() { return N; }

  size_type max_size() { return std::distance(begin(), end()); }

  void swap(array &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
  }

  void fill(const_reference value) {
    for (size_t i = 0; i < N; ++i) {
      array_[i] = value;
    }
  }
};
}  // namespace s21

#endif