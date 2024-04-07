#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue() : front_(nullptr), tail_(nullptr), size_(0) {}

  bool empty() const noexcept { return size_ == 0; }

  void push(const_reference value) {
    Node* new_node = new Node(value);
    new_node->next_ = nullptr;

    if (empty()) {
      front_ = tail_ = new_node;
    } else {
      tail_->next_ = new_node;
      tail_ = new_node;
    }

    size_++;
  }

  queue(std::initializer_list<value_type> const& items)
      : front_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& item : items) {
      push(item);
    }
  }

  queue(queue&& q) noexcept : front_(q.front_), tail_(q.tail_), size_(q.size_) {
    q.front_ = q.tail_ = nullptr;
    q.size_ = 0;
  }

  queue(const queue& q) : front_(nullptr), tail_(nullptr), size_(0) {
    Node* curr = q.front_;
    while (curr) {
      push(curr->value_);
      curr = curr->next_;
    }
  }

  ~queue() { clear(); }

  void clear() noexcept {
    while (front_) {
      Node* temp = front_;
      front_ = front_->next_;
      delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
  }

  queue& operator=(const queue& q) {
    if (this != &q) {
      clear();
      Node* curr = q.front_;
      while (curr) {
        push(curr->value_);
        curr = curr->next_;
      }
    }
    return *this;
  }

  const_reference front() const {
    if (empty()) throw std::out_of_range("Queue is empty. Mistake by Front()");
    return front_->value_;
  }

  const_reference back() const {
    if (empty()) throw std::out_of_range("Queue is empty. Mistake by Back()");
    return tail_->value_;
  }

  size_type size() const noexcept { return size_; }

  void pop() {
    if (empty()) throw std::out_of_range("Queue is empty. Mistake by Pop");

    Node* temp = front_;
    front_ = front_->next_;
    delete temp;

    if (empty()) {
      tail_ = nullptr;
    }
    --size_;
  }

  void swap(queue& other) noexcept {
    if (this != &other) {
      std::swap(front_, other.front_);
      std::swap(tail_, other.tail_);
      std::swap(size_, other.size_);
    }
  }


  template <typename... Args>
    void insert_many_back(Args&&... args) {
        (push(std::forward<Args>(args)), ...);
    }

  private:
  struct Node {
    value_type value_;
    Node* next_;

    Node(const value_type& value) : value_(value), next_(nullptr) {}
  };

  Node* front_;
  Node* tail_;
  size_type size_;
};
}  // namespace s21

#endif  // SRC_S21_QUEUE_H
