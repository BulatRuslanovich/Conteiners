#ifndef CONTAINERS_S21_MAP_H
#define CONTAINERS_S21_MAP_H

#include <stdexcept>

#include "s21_red_black_tree.h"

namespace s21 {
template <class Key, class Type>
class map {
 public:
  using key_type = Key;
  using mapped_type = Type;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  struct MapValueComparator {
    bool operator()(const_reference value1,
                    const_reference value2) const noexcept {
      return value1.first < value2.first;
    }
  };

  using treeType = RBTree<value_type, MapValueComparator>;
  using iterator = typename treeType::iterator;
  using const_iterator = typename treeType::constIterator;
  using size_type = std::size_t;

  map() : tree(new treeType{}) {}

  map(std::initializer_list<value_type> const &items) : map() {
    for (auto item : items) {
      insert(item);
    }
  }

  map(const map &other) : tree(new treeType(*other.tree)) {}

  map(map &&other) noexcept : tree(new treeType(std::move(*other.tree))) {}

  map &operator=(const map &other) noexcept {
    *tree = *other.tree;
    return *this;
  }

  map &operator=(map &&other) noexcept {
    *tree = std::move(*other.tree);
    return *this;
  }

  ~map() {
    delete tree;
    tree = nullptr;
  }

  mapped_type &at(const key_type &key) {
    value_type search_pair(key, mapped_type{});
    iterator it = tree->Find(search_pair);

    if (it == end()) {
      throw std::out_of_range("s21::map::at: Element is not exists");
    } else {
      return (*it).second;
    }
  }

  const mapped_type &at(const key_type &key) const {
    return const_cast<map<Key, Type> *>(this)->at(key);
  }

  mapped_type &operator[](const key_type &key) {
    value_type search_pair(key, mapped_type{});
    iterator it = tree->Find(search_pair);

    if (it == end()) {
      std::pair<iterator, bool> result = tree->InsertUnique(search_pair);
      return (*result.first).second;
    } else {
      return (*it).second;
    }
  }

  iterator begin() noexcept { return tree->Begin(); }
  const_iterator begin() const noexcept { return tree->Begin(); }

  iterator end() noexcept { return tree->End(); }
  const_iterator end() const noexcept { return tree->End(); }

  [[nodiscard]] bool empty() const noexcept { return tree->Empty(); }
  [[nodiscard]] size_type size() const noexcept { return tree->Size(); }
  [[nodiscard]] size_type max_size() const noexcept { return tree->MaxSize(); }
  void clear() noexcept { tree->Clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree->InsertUnique(value);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    return tree->InsertUnique(value_type{key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    iterator res = tree->Find(value_type{key, obj});

    if (res == end()) {
      return tree->InsertUnique(value_type{key, obj});
    }
    (*res).second = obj;

    return {res, false};
  }

  void erase(iterator pos) noexcept { tree->Erase(pos); }

  void swap(map &other) noexcept { tree->Swap(*other.tree); }

  void merge(map &other) noexcept { tree->MergeUnique(*other.tree); }

  bool contains(const key_type &key) const noexcept {
    value_type search_pair(key, mapped_type{});
    iterator it = tree->Find(search_pair);
    return end() != it;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree->EmplaceUnique(std::forward<Args>(args)...);
  }

 private:
  treeType *tree;
};

}  // namespace s21

#endif  // CONTAINERS_S21_MAP_H
