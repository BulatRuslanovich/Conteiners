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

    shrink_to_fit();
  }

  vector(const vector &v) {
    size_ = v.size_;
    buf_ = v.buf_;
    vector_ = nullptr;
    if (size_ > 0) {
      vector_ = new value_type[buf_];
    }

    std::copy(v.begin(), v.end(), vector_);
  }

  vector(vector &&v) { *this = std::move(v); }

  ~vector() {
    delete[] vector_;
    size_ = 0;
    buf_ = 0;
    vector_ = nullptr;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      delete[] vector_;

      if (v.size_ > 0) {
        vector_ = new value_type[v.buf_];
        std::copy(v.begin(), v.end(), vector_);
      }

      size_ = v.size_;
      buf_ = v.buf_;
    }

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

  reference operator[](size_type pos) { return vector_[pos]; }

  iterator begin() { return vector_; }

  iterator end() { return vector_ + size_; }

  const_iterator begin() const { return vector_; }

  const_iterator end() const { return vector_ + size_; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - begin();
    if (index > size_) {
      throw std::out_of_range("Unable to insert into a position");
    }

    if (size_ == buf_) reserve(size_ ? size_ * 2 : 1);

    std::copy(begin() + index, end(), begin() + index + 1);
    *(vector_ + index) = value;

    ++size_;
    return begin() + index;
  }

  reference at(size_type pos) {
    if (pos >= buf_)
      throw std::out_of_range("Current element outside the array");
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

  bool empty() { return vector_ == nullptr; }

  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size <= buf_) return;

    ReallocVec(size);
  }

  size_type capacity() { return buf_; }

  void shrink_to_fit() {
    if (buf_ == size_) return;

    ReallocVec(size_);
  }

  void clear() { size_ = 0; }

  iterator erase(iterator pos) {
    size_type index = pos - begin();
    if (index >= size_) throw std::out_of_range("Unable to erase a position");

    std::copy(begin(), const_cast<iterator>(pos), vector_);
    std::copy(const_cast<iterator>(pos) + 1, end(), vector_ + index);

    --size_;
    return begin() + index;
  }

  void push_back(const_reference value) {
    if (size_ == buf_) {
      reserve(buf_ ? buf_ * 2 : 1);
    }

    vector_[size_++] = value;
  }

  void pop_back() { size_--; }

  void swap(vector &other) {
    std::swap(vector_, other.vector_);
    std::swap(size_, other.size_);
    std::swap(buf_, other.buf_);
  }

  template <typename... Args>
  constexpr iterator insert_many(const_iterator pos, Args &&...args) {
    iterator ret = nullptr;
    auto id = pos - begin();
    reserve(buf_ + sizeof...(args));

    for (auto &&item : {std::forward<Args>(args)...})
      ret = insert(begin() + id, item);

    return ret;
  }

  template <typename... Args>
  constexpr iterator insert_many_back(Args &&...args) {
    for (auto &&item : {std::forward<Args>(args)...}) {
      push_back(item);
    }
    return end() - 1;
  }

 private:
  size_type size_ = 0;
  size_type buf_ = 0;
  value_type *vector_ = nullptr;
  // qwefrgtfhfgdrsewrqefre
  //(исторический момент) НЕ УДАЛЯТЬ!

  void ReallocVec(size_type size) {
    auto tmp = new value_type[size];
    for (size_type i = 0; i < size_; ++i) tmp[i] = std::move(vector_[i]);

    delete[] vector_;
    vector_ = tmp;
    buf_ = size;
  }
};
}  // namespace s21
#endif  // _VECTOR_H_