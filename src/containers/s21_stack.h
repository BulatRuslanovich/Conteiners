#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T>
class stack {
 private:
  struct Node;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack() : head_(nullptr), size_(0U) {}

  stack(std::initializer_list<value_type> const &items) : stack() {
    for (auto item : items) {
      push(item);
    }
  }

  stack(const stack &s) : stack() {
    if (s.head_ == nullptr) {
      head_ = nullptr;
      return;
    }
    value_type array[s.size()];
    int i = 0;
    Node *temp = s.head_;

    while (temp) {
      array[i] = temp->value_;
      temp = temp->prev_;
      i++;
    }

    while (i > 0) {
      push(array[i - 1]);
      i--;
    }
  }

  stack(stack &&s) noexcept {
    head_ = s.head_;
    size_ = s.size_;
    s.head_ = nullptr;
    s.size_ = 0;
  }

  ~stack() {
    while (!this->empty()) {
      this->pop();
    }
  }

  const_reference top() {
    if (this->empty()) {
      throw std::out_of_range("Stack is empty");
    }

    return head_->value_;
  }

  bool empty() { return size_ == 0; }

  [[nodiscard]] size_type size() const { return size_; }

  void push(const_reference value) {
    Node *ptr = new Node(value);
    if (head_) {
      ptr->prev_ = head_;
      head_ = ptr;
    } else
      head_ = ptr;
    ++size_;
  }

  void pop() {
    if (head_ != nullptr) {
      Node *ptr = head_->prev_;
      delete head_;
      head_ = ptr;
      --size_;
    }
  }

  void swap(stack &other) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      this->~stack();
      head_ = s.head_;
      size_ = s.size_;
      s.head_ = nullptr;
      s.size_ = 0;
    }
    return *this;
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (auto item : {std::forward<Args>(args)...}) {
      push(item);
    }
  }

 private:
  struct Node {
    value_type value_;
    Node *prev_;

    explicit Node(const T &value = 0) : value_(value), prev_(nullptr) {}

    Node *head_ = nullptr;
    size_type size_ = 0;
  };

  Node *head_;
  size_type size_;
};
}  // namespace s21

#endif  // S21_STACK_H_
