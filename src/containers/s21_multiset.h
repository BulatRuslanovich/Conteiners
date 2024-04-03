#ifndef CONTAINERS_S21_MULTISET_H
#define CONTAINERS_S21_MULTISET_H

#include "s21_red_black_tree.h"

namespace s21 {
template <class Key> class Multiset {
public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using treeType = RBTree<value_type>;
  using iterator = typename treeType::iterator;
  using const_iterator = typename treeType::constIterator;
  using size_type = std::size_t;
private:
  treeType *tree;
public:

  Multiset() : tree(new treeType{}) {}

  Multiset(std::initializer_list<value_type> const &items) : Multiset() {
    for (auto item : items) {
      insert(item);
    }
  }

  Multiset(const Multiset &other) : tree(new treeType(*other.tree)) {}

  Multiset(Multiset &&other) noexcept
      : tree(new treeType(std::move(*other.tree))) {}

  Multiset &operator=(const Multiset &other) {
    *tree = *other.tree;
    return *this;
  }

  Multiset &operator=(Multiset &&other) noexcept {
    *tree = std::move(*other.tree);
    return *this;
  }

  ~Multiset() {
    delete tree;
    tree = nullptr;
  }

  iterator begin() noexcept { return tree->Begin(); }
  const_iterator begin() const noexcept { return tree->Begin(); }
  iterator end() noexcept { return tree->End(); }
  const_iterator end() const noexcept { return tree->End(); }
  [[nodiscard]] bool empty() const noexcept { return tree->Empty(); }
  [[nodiscard]] size_type size() const noexcept { return tree->Size(); }
  [[nodiscard]] size_type max_size() const noexcept { return tree->MaxSize(); }
  void clear() noexcept { tree->Clear(); }
  iterator insert(const value_type &value) {
    return tree->Insert(value);
  }
  void erase(iterator pos) noexcept { tree->Erase(pos); }
  void swap(Multiset &other) noexcept { tree->Swap(*other.tree); }
  void merge(Multiset &other) noexcept { tree->Merge(*other.tree); }
  size_type count(const key_type &key) const {
    auto lowerIt = lower_bound(key);

    if (*lowerIt != key) {
      return 0;
    }

    auto endIt = end();
    size_type resultCount = 0;

    while (lowerIt != endIt && *lowerIt == key) {
      ++resultCount;
      ++lowerIt;
    }

    return resultCount;
  }

  iterator find(const key_type &key) noexcept { return tree->Find(key); }
  const_iterator find(const key_type &key) const noexcept {
    return tree->Find(key);
  }

  bool contains(const key_type &key) const noexcept {
    return tree->Find(key) != tree->End();
  }

  std::pair<iterator, iterator> equal_range(const key_type &key) noexcept {
    iterator first = lower_bound(key);
    iterator second = upper_bound(key);

    return std::pair<iterator, iterator>{first, second};
  }

  std::pair<const_iterator, const_iterator> equal_range(const key_type &key) const noexcept {
    const_iterator first = lower_bound(key);
    const_iterator second = upper_bound(key);

    return std::pair<const_iterator, const_iterator>{first, second};
  }

  iterator lower_bound(const key_type &key) noexcept {
    return tree->LowerBound(key);
  }

  const_iterator lower_bound(const key_type &key) const {
    return tree->LowerBound(key);
  }

  iterator upper_bound(const key_type &key) noexcept {
    return tree->UpperBound(key);
  }

  const_iterator upper_bound(const key_type &key) const {
    return tree->UpperBound(key);
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    return tree->Emplace(std::forward<Args>(args)...);
  }


};
}
#endif // CONTAINERS_S21_MULTISET_H
