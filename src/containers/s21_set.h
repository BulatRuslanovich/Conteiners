#ifndef CONTAINERS_S21_SET_H
#define CONTAINERS_S21_SET_H
#include <vector>

#include "s21_red_black_tree.h"

namespace s21 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using treeType = RBTree<value_type>;
  using iterator = typename treeType::iterator;
  using const_iterator = typename treeType::constIterator;
  using size_type = std::size_t;

  set() : tree(new treeType{}) {}

  set(std::initializer_list<value_type> const &items) : set() {
    for (auto item : items) {
      insert(item);
    }
  }

  set(const set &other) : tree(new treeType(*other.tree)) {}

  set(set &&other) noexcept : tree(new treeType(std::move(*other.tree))) {}

  set &operator=(const set &other) {
    *tree = *other.tree;
    return *this;
  }

  set &operator=(set &&other) noexcept {
    *tree = std::move(*other.tree);
    return *this;
  }

  ~set() {
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
  std::pair<iterator, bool> insert(const value_type &value) {
    return tree->InsertUnique(value);
  }

  void erase(iterator pos) noexcept { tree->Erase(pos); }
  void swap(set &other) noexcept { tree->Swap(*other.tree); }
  void merge(set &other) noexcept { tree->MergeUnique(*other.tree); }
  iterator find(const key_type &key) noexcept { return tree->Find(key); }
  const_iterator find(const key_type &key) const noexcept {
    return tree->Find(key);
  }

  bool contains(const key_type &key) const noexcept {
    return tree->Find(key) != tree->End();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree->EmplaceUnique(std::forward<Args>(args)...);
  }

 private:
  treeType *tree;
};
}  // namespace s21
#endif  // CONTAINERS_S21_SET_H
