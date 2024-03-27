//
// Created by bulatruslanovich on 27/03/2024.
//

#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H

#include <iostream>
#include <initializer_list>
#include <utility>



template <typename T>
class List {
private:
  struct ListIterator;
  struct ListConstIterator;
  struct Node;
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = const ListConstIterator;
  using size_type = std::size_t;

  List() : _head(new value_type{}), _size(0U) {};

//  List(size_type n) : _head(new value_type{}), _size(n) {};
//
//  List(std::initializer_list<value_type> const &items);
//  List(const List &l);
//  List(List &&l);
//  ~List();
//
//  List& operator=(List&& l) {
//    return *this;
//  }

  const_reference front() const noexcept { return *begin(); }
  reference front() noexcept { return *begin(); }

  const_reference back() const noexcept { return *std::prev(end()); };
  reference back()  noexcept { return *std::prev(end()); };

  iterator begin() noexcept { return iterator {_head->_next}; }
  const_iterator begin() const noexcept {return const_iterator {_head->_next}; }

  iterator end() noexcept { return iterator {_head}; }
  const_iterator end() const noexcept { return const_iterator {_head}; }

  bool empty() {
      return _size == 0;
  }

  size_type size() {
    return _size;
  }

//  size_type max_size();
//  void clear();
//  iterator insert(iterator pos, const_reference _value);
//  void erase(iterator pos);
//  void push_back(const_reference _value);
//  void pop_back();
//  void push_front(const_reference _value);
//  void pop_front();
//  void swap(List &other);
//  void merge(List &other);
//  void splice(const_iterator pos, List &other);
//  void reverse();
//  void unique();
//  void sort();


private:
  struct Node {
    value_type *_value;
    Node *_next;
    Node *_prev;

    Node() : _value(0), _next(nullptr), _prev(nullptr) {}
    explicit Node(reference value) : _value(value), _next(nullptr), _prev(nullptr) {}
    explicit Node(value_type&& value) : _value(std::move(value)), _next(nullptr), _prev(nullptr) {}

    void linkPrev(Node* newNode) {
      newNode->_next = this;
      _prev->_next = newNode;
      newNode->_prev = _prev;
      _prev = newNode;
    }

    void UnLink() {
      _prev->_next = this->_next;
      _next->_prev = this->_prev;
      this->_prev = nullptr;
      this->_next = nullptr;
    }

    void ValueSwap(Node* other) {
      std::swap(this->_value, other->_value);
    }

    void PrevNextSwap() {
      std::swap(_prev, _next);
    }
  };

  struct ListIterator {
    ListIterator() = delete;
    explicit ListIterator(Node* node) noexcept : _node(node) {};
    Node& operator*() const noexcept { return _node->_value; }

    iterator& operator++() noexcept {
      _node = _node->_next;
      return *this;
    }

    iterator& operator--() noexcept {
      _node = _node->_prev;
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator temp {_node};
      ++(*this);
      return temp;
    }

    iterator operator--(int) noexcept {
      iterator temp {_node};
      --(*this);
      return temp;
    }

    bool operator==(const iterator& other) noexcept {
        return this->_node == other->_node;
    }

    bool operator!=(const iterator& other) noexcept {
        return !this->operator==(other);
    }

    Node* _node;
  };

  struct ListConstIterator {
    ListConstIterator() = delete;
    explicit ListConstIterator(const Node* node) noexcept : _node(node) {};
    ListConstIterator(const iterator& it) : _node(it->node) {};

    const Node& operator*() const noexcept { return _node->_value; }

    const_iterator& operator++() noexcept {
      _node = _node->_next;
      return *this;
    }

    const_iterator& operator--() noexcept {
      _node = _node->_prev;
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator temp {_node};
      ++(*this);
      return temp;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp {_node};
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) noexcept {
      return this->_node == other->_node;
    }

    bool operator!=(const const_iterator& other) noexcept {
      return !this->operator==(other);
    }

    const Node* _node;
  };

  Node* _head;
  size_type _size;
};


#endif // SRC_S21_LIST_H
