#ifndef SRC_S21_LIST_H
#define SRC_S21_LIST_H


#include <initializer_list>
#include <limits>
#include <iterator>
#include <iostream>

namespace s21 {
template <typename T> class List {
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

  List() : _head(new Node{}), _size(0U){};

  explicit List(size_type n) : List() {
    for (int i = 0; i < n; ++i) {
      push_back(value_type{});
    }
  }

  List(std::initializer_list<value_type> const &items) : List() {
    for (auto item : items) {
      push_back(item);
    }
  }

  List(const List &l) : List() {
    for (auto item : l) {
      push_back(item);
    }
  }

  List(List &&l) noexcept : List()  { splice(begin(), l); }

  ~List() {
    clear();
    delete _head;
    _head = nullptr;
  }

  List &operator=(const List &other) noexcept {
    if (this != &other) {
      iterator ourBegin = begin();
      iterator ourEnd = end();
      iterator otherBegin = other.begin();
      iterator otherEnd = other.end();

      while (ourBegin != ourEnd && otherBegin != otherEnd) {
        *ourBegin = *otherBegin;
        ++ourBegin;
        ++otherBegin;
      }

      while (ourBegin != ourEnd) {
        iterator temp = ourBegin;
        ++ourBegin;
        erase(temp);
      }

      while (otherBegin != otherEnd) {
        push_back(otherBegin);
        ++otherBegin;
      }
    }

    return *this;
  }

  List &operator=(List &&l) noexcept {
    if (this != &l) {
      clear();
      splice(begin(), l);
    }

    return *this;
  }

  const_reference front() const noexcept { return *begin(); }
  reference front() noexcept { return *begin(); }

  const_reference back() const noexcept { return *std::prev(end()); };
  reference back() noexcept { return *std::prev(end()); };

  iterator begin() noexcept { return iterator{_head->_next}; }
  const_iterator begin() const noexcept { return const_iterator{_head->_next}; }

  iterator end() noexcept { return iterator{_head}; }
  const_iterator end() const noexcept { return const_iterator{_head}; }

  bool empty() { return _size == 0; }

  size_type size() { return _size; }

  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / 2) / sizeof(Node) - 1;
  }

  void clear() {
    while (_size > 0) {
      erase(begin());
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node *newNode = new Node(value);
    pos._node->linkPrev(newNode);
    ++_size;

    return iterator(newNode);
  }

  void erase(iterator pos) noexcept {
    if (pos != end()) {
      pos._node->UnLink();
      delete pos._node;
      --_size;
    }
  }
  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(--end()); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }
  void swap(List &other) {
    if (this != &other) {
      std::swap(this->_head, other._head);
      std::swap(this->_size, other._size);
    }
  }

  void merge(List &other) {
    if (this != &other) {
      iterator ourBegin = begin();
      iterator ourEnd = end();
      iterator otherBegin = other.begin();
      iterator otherEnd = other.end();

      while (ourBegin != ourEnd && otherBegin != otherEnd) {
        if (*otherBegin < *ourBegin) {
          Node *tmp = otherBegin._node;
          ++otherBegin;
          tmp->UnLink();
          --other._size;
          ourBegin._node->linkPrev(tmp);
          ++_size;
        } else {
          ++ourBegin;
        }
      }


      splice(end(), other);
    }
  }

  void splice(const_iterator pos, List &other) noexcept {
    if (!other.empty()) {
      iterator itCurrent{const_cast<Node *>(pos._node)};
      iterator itOther = other.end();

      itOther._node->_next->_prev = itCurrent._node->_prev;
      itOther._node->_prev->_next = itCurrent._node->_next;

      itCurrent._node->_prev->_next = itOther._node->_next;
      itCurrent._node->_prev = itOther._node->_prev;

      _size += other.size();
      other._head->_next = other._head;
      other._head->_prev = other._head;
    }
  }

  void reverse() {
    iterator beginIt = begin();
    iterator endIt = end();

    while (beginIt != endIt) {
      beginIt._node->SwapChains();
      --beginIt;
    }

    _head->SwapChains();
  }

  void unique() {
    iterator beginIt = begin();
    iterator endIt = end();
    iterator prevIt = begin();

    ++beginIt;

    while (beginIt != endIt) {
      if (*beginIt == *prevIt) {
        erase(beginIt);
        prevIt = beginIt;
      } else {
        ++prevIt;
      }

      ++beginIt;
    }
  }

  void sort() { quickSort(begin(), --end(), _size); }

private:
  void quickSort(iterator left, iterator right, size_type size) {
    if (left != right && size > 1) {
      iterator swapIt = left;
      iterator pivotIt = left;
      iterator tempRight = right;
      iterator tempLeft = left;
      --swapIt;
      --pivotIt;
      size_type shift = 0;

      while (shift < size / 2) {
        ++pivotIt;
        ++shift;
      }

      value_type pivot = *pivotIt;
      shift = 0;

      pivotIt._node->SwapValue(right._node);

      while (tempLeft != tempRight) {
        if (*tempLeft < pivot) {
          ++swapIt;
          ++shift;
          tempLeft._node->SwapValue(swapIt._node);
          ++tempLeft;
        } else if (*tempLeft == pivot) {
          --tempRight;
          tempLeft._node->SwapValue(tempRight._node);
        } else {
          ++tempLeft;
        }
      }

      iterator nextLeft = swapIt;
      size_type nextRightSize = size - shift - 1;
      size_type nextLeftSize = shift;

      ++swapIt;
      while (tempRight != right) {
        swapIt._node->SwapValue(tempRight._node);
        ++swapIt;
        ++tempRight;
        --nextRightSize;
      }

      swapIt._node->SwapValue(right._node);
      ++swapIt;

      iterator nextRight = swapIt;

      quickSort(left, nextLeft, nextLeftSize);
      quickSort(nextRight, right, nextRightSize);
    }
  }


  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it{const_cast<Node *>(pos._node)};
    Node *newNode;

    for (auto item : {std::forward<Args>(args)...}) {
      newNode = new Node(std::move(item));
      it._node->linkPrev(newNode);
      ++_size;
    }

    return iterator(newNode);
  }

  template <typename... Args> void emplace_back(Args &&...args) {
    emplace(end(), std::forward<Args>(args)...);
  }

  template <typename... Args> void emplace_front(Args &&...args) {
    emplace(begin(), std::forward<Args>(args)...);
  }

  struct Node {
    value_type _value;
    Node *_next;
    Node *_prev;

    Node() noexcept : _value(value_type{}), _next(this), _prev(this) {}
    explicit Node(const_reference value)
        : _value(value), _next(nullptr), _prev(nullptr) {}
    explicit Node(value_type &&value) noexcept
        : _value(std::move(value)), _next(nullptr), _prev(nullptr) {}

    void linkPrev(Node *newNode) {
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

    void SwapValue(Node *other) { std::swap(this->_value, other->_value); }

    void SwapChains() { std::swap(_prev, _next); }
  };

  struct ListIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::value_type;
    using pointer = value_type*;
    using reference = value_type&;

    Node *_node;
    ListIterator() = delete;
    explicit ListIterator(Node *node) noexcept : _node(node) {};
    reference operator*() const noexcept { return _node->_value; }

    iterator &operator++() noexcept {
      _node = _node->_next;
      return *this;
    }

    iterator &operator--() noexcept {
      _node = _node->_prev;
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator temp{_node};
      ++(*this);
      return temp;
    }

    iterator operator--(int) noexcept {
      iterator temp{_node};
      --(*this);
      return temp;
    }

    bool operator==(const iterator &other) const noexcept {
      return _node == other._node;
    }

    bool operator!=(const iterator &other) const noexcept {
      return _node != other._node;
    }
  };

  struct ListConstIterator {
    // это что-то типа наследования от интерфейса
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::value_type;
    using pointer = const value_type*;
    using reference = const value_type&;

    const Node *_node;
    ListConstIterator() = delete;
    explicit ListConstIterator(const Node *node) noexcept : _node(node){};
    ListConstIterator(const iterator &it) : _node(it._node){};
    reference operator*() const noexcept { return _node->_value; }

    const_iterator &operator++() noexcept {
      _node = _node->_next;
      return *this;
    }

    const_iterator &operator--() noexcept {
      _node = _node->_prev;
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator temp{_node};
      ++(*this);
      return temp;
    }

    const_iterator operator--(int) noexcept {
      const_iterator temp{_node};
      --(*this);
      return temp;
    }

    // TODO: понять почему с friend работает merge
    friend bool operator==(const const_iterator &it1, const const_iterator &it2) noexcept {
      return it1._node == it2._node;
    }

    friend bool operator!=(const const_iterator &it1, const const_iterator &it2) noexcept {
      return it1._node != it2._node;
    }
  };

private:
  Node *_head;
  size_type _size;
};

};

#endif // SRC_S21_LIST_H
