#ifndef CONTEINERS_S21_RED_BLACK_TREE_H
#define CONTEINERS_S21_RED_BLACK_TREE_H

#include <functional>
#include <limits>
#include <vector>

namespace s21 {
enum RBTreeColor { Black, Red };

template <typename Key, typename Comparator = std::less<Key>> class RBTree {
private:
  struct RBTreeNode;
  struct RBTreeIterator;
  struct RBTreeConstIterator;

public:
  using keyType = Key;
  using reference = keyType &;
  using constReference = const keyType &;
  using iterator = RBTreeIterator;
  using constIterator = RBTreeConstIterator;
  using sizeType = std::size_t;

  using treeType = RBTree;
  using treeNode = RBTreeNode;
  using treeColor = RBTreeNode;

private:
  treeNode *root;
  sizeType size;
  Comparator cmp;

public:
  RBTree() : root(new treeNode), size(0U) {}

  RBTree(const treeType &other) : RBTree() {
    if (other.Size() > 0) {
      CopyTreeFromOther(other);
    }
  }

  RBTree(treeType &&other) noexcept : RBTree() { Swap(other); }

  ~RBTree() {
    Clear();
    delete root;
    root = nullptr;
  }

  treeType &operator=(const treeType &other) {
    if (this != &other) {
      if (other.Size() > 0) {
        CopyTreeFromOther(other);
      } else {
        Clear();
      }
    }

    return *this;
  }

  treeType &operator=(treeType &&other) noexcept {
    Clear();
    Swap(other);
    return *this;
  }

  void Clear() noexcept {
    Destroy(Root());
    InitRoot();
    size = 0;
  }

  sizeType Size() const noexcept { return size; }

  bool Empty() const noexcept { return size == 0; }

  sizeType MaxSize() const noexcept {
    return ((std::numeric_limits<sizeType>::max() / 2) - 2 * sizeof(treeType)) /
           sizeof(treeType);
  }

  iterator Begin() noexcept { return iterator(MostLittle()); }
  constIterator Begin() const noexcept { return constIterator(MostLittle()); }

  iterator End() noexcept { return iterator(root); }
  constIterator End() const noexcept { return constIterator(root); }

  void Merge(treeType &other) {
    if (this != &other) {
      iterator otherBegin = other.Begin();

      while (!other.Empty()) {
        treeNode *moveNode = otherBegin.node;
        ++otherBegin;

        // TODO: можно будет попробовать убрать
        if (moveNode->left != nullptr) {
          moveNode->left->parent = moveNode->parent;
        }

        if (moveNode->right != nullptr) {
          moveNode->right->parent = moveNode->parent;
        }

        if (moveNode->parent->left == moveNode) {
          moveNode->parent->left = nullptr;
        }

        if (moveNode->parent->right == moveNode) {
          moveNode->parent->right == nullptr;
        }

        moveNode->ToDefault();
        --other.size;
        Insert(Root(), moveNode, false);
      }

      other.InitRoot();
    }
  }

  void MergeUnique(treeType &other) {
    if (this != &other) {
      iterator otherBegin = other.Begin();
      iterator otherEnd = other.End();

      while (otherBegin != otherEnd) {
        iterator result = Find(otherBegin.node->key);

        if (result == End()) {
          iterator temp = otherBegin;
          ++otherBegin;
          treeNode *moveNode = other.ExtractNode(temp);
          Insert(Root(), moveNode, false);
        } else {
          ++otherBegin;
        }
      }
    }
  }

  iterator Insert(constReference key) {
    treeNode *newNode = new treeNode{key};
    return Insert(Root(), newNode, false).first;
  }

  std::pair<iterator, bool> InsertUnique(constReference key) {
    treeNode *newNode = new treeNode{key};
    std::pair<iterator, bool> result = Insert(Root(), newNode, true);

    if (!result.second) {
      delete newNode;
    }

    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> Emplace(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(args));

    for (auto item : {std::forward<Args>(args)...}) {
      treeNode *newNode = new treeNode(std::move(item));
      std::pair<iterator, bool> resultInsert = Insert(Root(), newNode, false);
      result.push_back(resultInsert);
    }

    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> EmplaceUnique(Args &&...args) {
    std::vector<std::pair<iterator, bool>> result;
    result.reserve(sizeof...(args));

    for (auto item : {std::forward<Args>(args)...}) {
      treeNode *newNode = new treeNode(std::move(item));
      std::pair<iterator, bool> resultInsert = Insert(Root(), newNode, true);
      if (!resultInsert.second) {
        delete newNode;
      }

      result.push_back(resultInsert);
    }

    return result;
  }

  iterator Find(constReference key) {
    iterator res = LowerBound(key);

    if (res == End() || cmp(key, *res)) {
      return End();
    }

    return res;
  }

  iterator LowerBound(constReference key) {
    treeNode *origin = Root();
    treeNode *res = End().node;

    while (origin != nullptr) {
      if (!cmp(origin->key, key)) {
        res = origin;
        origin = origin->left;
      } else {
        origin = origin->right;
      }
    }

    return iterator(res);
  }

  iterator UpperBound(constReference key) {
    treeNode *origin = Root();
    treeNode *res = End().node;

    while (origin != nullptr) {
      if (cmp(origin->key, key)) {
        res = origin;
        origin = origin->left;
      } else {
        origin = origin->right;
      }
    }

    return iterator(res);
  }

  void Erase(iterator pos) noexcept {
    treeNode *res = ExtractNode(pos);
    delete res;
  }

  void Swap(treeType &other) noexcept {
    std::swap(root, other.root);
    std::swap(size, other.size);
    std::swap(cmp, other.cmp);
  }

  bool CheckTree() const noexcept {
    if (root->color == Black) {
      return false;
    }

    if (Root() == nullptr) {
      return true;
    }

    if (Root()->color == Red) {
      return false;
    }

    if (!checkRedNodes(Root())) {
      return false;
    }

    if (ComputeBlackHeight(Root()) == -1) {
      return false;
    }

    return true;
  }

private:
  void CopyTreeFromOther(const treeType &other) {
    treeNode *otherCopyRoot = CopyTree(other.Root(), nullptr);
    Clear();
    Root() = otherCopyRoot;
    Root()->parent = root;
    MostLittle() = SearchMin(Root());
    MostBig() = SearchMax(Root());
    size = other.size;
    cmp = other.cmp;
  }

  treeNode *CopyTree(const treeNode *node, treeNode *parent) {
    treeNode *copy = new treeNode{node->key, node->color};

    try {
      if (node->left) {
        copy->left = CopyTree(node->left, copy);
      }

      if (node->right) {
        copy->right = CopyTree(node->right, copy);
      }
    } catch (...) {
      Destroy(copy);
      throw;
    }

    copy->parent = parent;
    return copy;
  }

  void Destroy(treeNode *node) noexcept {
    if (node == nullptr)
      return;

    Destroy(node->left);
    Destroy(node->right);
    delete node;
  }

  void InitRoot() {
    Root() = nullptr;
    MostLittle() = root;
    MostBig() = root;
  }

  treeNode *&Root() { return root->parent; }
  const treeNode *Root() const { return root->parent; }
  treeNode *&MostLittle() { return root->left; }
  const treeNode *MostLittle() const { return root->left; }
  treeNode *&MostBig() { return root->right; }

  std::pair<iterator, bool> Insert(treeNode *origin, treeNode *newNode,
                                   bool unique) {
    treeNode *node = origin;
    treeNode *parent = nullptr;

    while (node != nullptr) {
      parent = node;

      if (cmp(newNode->key, node->key)) {
        node = node->left;
      } else {
        if (!unique ||
            cmp(node->key, newNode->key)) { // TODO: не продуманный участок
          node = node->right;
        } else {
          return {iterator(node), false};
        }
      }
    }

    if (parent != nullptr) {
      newNode->parent = parent;

      if (cmp(newNode->key, parent->key)) {
        parent->left = newNode;
      } else {
        parent->right = newNode;
      }
    } else {
      newNode->color = Black;
      newNode->parent = root;
      Root() = newNode;
    }

    ++size;

    if (MostLittle() == root || MostLittle()->left != nullptr) {
      MostLittle() = newNode;
    }

    if (MostBig() == root || MostBig()->right != nullptr) {
      MostBig() = newNode;
    }

    BalancingInsert(newNode);

    return {iterator(newNode), true};
  }

  void BalancingInsert(treeNode *node) {
    // Father
    treeNode *parent = node->parent;

    while (node != Root() && parent == Red) {
      // Grandpa
      treeNode *grand = parent->parent;

      if (grand->left == parent) {
        treeNode *uncle = grand->right;

        if (uncle != nullptr && uncle->color == Red) {
          // first case
          parent->color = Black;
          uncle->color = Black;
          grand->color = Red;

          node = grand;
          parent = node->parent;
        } else {
          // second case
          if (parent->right == node) {
            RotateLeft(parent);
            std::swap(parent, node);
          }

          // third case
          RotateRight(grand);
          grand->color = Red;
          parent->color = Black;
          break;
        }
      } else {
        treeNode *uncle = grand->left;

        if (uncle != nullptr && uncle->color == Red) {
          // first case
          parent->color = Black;
          uncle->color = Black;
          grand->color = Red;

          node = grand;
          parent = node->parent;
        } else {
          // second case
          if (parent->left == node) {
            RotateRight(parent);
            std::swap(parent, node);
          }

          // third case
          RotateLeft(grand);
          grand->color = Red;
          parent->color = Black;
          break;
        }
      }
    }

    Root()->color = Black;
  }

  void RotateRight(treeNode *node) noexcept {
    const treeNode *pivot = node->left;
    pivot->parent = node->parent;

    if (node == Root()) {
      Root() = pivot;
    } else if (node->parent->left == node) {
      node->parent->left = pivot;
    } else {
      node->parent->right = pivot;
    }

    node->left = pivot->right;

    if (pivot->right != nullptr) {
      pivot->right->parent = node;
    }

    node->parent = pivot;
    pivot->right = node;
  }

  void RotateLeft(treeNode *node) noexcept {
    const treeNode *pivot = node->right;
    pivot->parent = node->parent;

    if (node == Root()) {
      Root() = pivot;
    } else if (node->parent->left == node) {
      node->parent->left = pivot;
    } else {
      node->parent->right = pivot;
    }

    node->right = pivot->left;

    if (pivot->left != nullptr) {
      pivot->left->parent = node;
    }

    node->parent = pivot;
    pivot->right = node;
  }

  treeNode *ExtractNode(iterator pos) noexcept {
    if (pos == End()) {
      return nullptr;
    }

    treeNode *deleteNode = pos.node;

    if (deleteNode->left != nullptr && deleteNode->right != nullptr) {
      treeNode *replace = SearchMininmum(deleteNode->right);
      SwapNodesForErase(deleteNode, replace);
    }

    if (deleteNode->color == Black &&
        ((deleteNode->left == nullptr && deleteNode->right != nullptr) ||
         (deleteNode->left != nullptr && deleteNode->right == nullptr))) {
      treeNode *replace;

      if (deleteNode->left != nullptr) {
        replace = deleteNode->left;
      } else {
        replace = deleteNode->right;
      }

      SwapNodesForErase(deleteNode, replace);
    }

    if (deleteNode->color == Black && deleteNode->left == nullptr &&
        deleteNode->right == nullptr) {
      EraseBalancing(deleteNode);
    }

    if (deleteNode == Root()) {
      InitRoot();
    } else {
      if (deleteNode == deleteNode->parent->left) {
        deleteNode->parent->left = nullptr;
      } else {
        deleteNode->parent->right = nullptr;
      }

      if (MostLittle() == deleteNode) {
        MostLittle() = SearchMin(Root());
      }

      if (MostBig() == deleteNode) {
        MostBig() = SearchMax(Root());
      }
    }

    --size;

    deleteNode->ToDefault();

    return deleteNode;
  }

  void SwapNodesForErase(treeNode *node, treeNode *other) noexcept {
    if (other->parent->left == other) {
      other->parent->left = node;
    } else {
      other->parent->right = node;
    }

    if (node == Root()) {
      Root() = other;
    } else {
      if (node->parent->left == node) {
        node->parent->left = other;
      } else {
        node->parent->right = other;
      }
    }

    std::swap(node->parent, other->parent);
    std::swap(node->left, other->left);
    std::swap(node->right, other->right);
    std::swap(node->color, other->color);

    if (node->left) {
      node->left->parent = node;
    }

    if (node->right) {
      node->right->parent = node;
    }

    if (other->left) {
      other->left->parent = other;
    }

    if (other->right) {
      other->right->parent = other;
    }
  }

  void EraseBalancing(treeNode *deleteNode) noexcept {
    treeNode *checkNode = deleteNode;
    treeNode *parent = deleteNode->parent;

    while (checkNode != Root() && checkNode->color == Black) {
      if (checkNode == parent->left) {
        treeNode *brother = parent->right;

        if (brother->color == Red) {
          std::swap(brother->color, parent->color);
          RotateLeft(parent);
          parent = checkNode->parent;
          brother = parent->right;
        }

        if (brother->color == Black &&
            (brother->left == nullptr || brother->left->color == Black) &&
            (brother->right == nullptr || brother->right->color == Black)) {
          brother->color = Red;

          if (parent->color == Red) {
            parent->color = Black;
            break;
          }

          checkNode = parent;
          parent = checkNode->parent;
        } else {
          if (brother->left != nullptr && brother->left->color == Red &&
              (brother->right == nullptr || brother->right->color == Black)) {
            std::swap(brother->color, brother->left->color);
            RotateRight(brother);
            brother = parent->right;
          }

          brother->right->color = Black;
          brother->color = parent->color;
          parent->color = Black;
          RotateLeft(parent);
          break;
        }
      } else {
        treeNode *brother = parent->left;

        if (brother->color == Red) {
          std::swap(brother->color, parent->color);
          RotateRight(parent);
          parent = checkNode->parent;
          brother = parent->left;
        }

        if (brother->color == Black &&
            (brother->left == nullptr || brother->left->color == Black) &&
            (brother->right == nullptr || brother->right->color == Black)) {
          brother->color = Red;

          if (parent->color == Red) {
            parent->color = Black;
            break;
          }

          checkNode = parent;
          parent = checkNode->parent;
        } else {
          if (brother->right != nullptr && brother->right->color == Red &&
              (brother->left == nullptr || brother->left->color == Black)) {
            std::swap(brother->color, brother->right->color);
            RotateRight(brother);
            brother = parent->left;
          }

          brother->left->color = Black;
          brother->color = parent->color;
          parent->color = Black;
          RotateRight(parent);
          break;
        }
      }
    }
  }

  treeNode *SearchMin(treeNode *node) const noexcept {
    while (node->left != nullptr) {
      node = node->left;
    }

    return node;
  }

  treeNode *SearchMax(treeNode *node) const noexcept {
    while (node->right != nullptr) {
      node = node->right;
    }

    return node;
  }

  int ComputeBlackHeight(const treeNode *node) const noexcept {
    if (node == nullptr) {
      return 0;
    }

    int leftHeight = ComputeBlackHeight(node->left);
    int rightHeight = ComputeBlackHeight(node->right);
    int add = node->color == Black ? 1 : 0;

    if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight) {
      return -1;
    } else {
      return leftHeight + add;
    }
  }

  bool checkRedNodes(const treeNode *node) const noexcept {
    if (node->color == Red) {
      if ((node->left != nullptr && node->left->color == Red) ||
          (node->right != nullptr && node->right->color == Red)) {
        return false;
      }
    }

    if (node->left != nullptr) {
      if (!checkRedNodes(node->left)) {
        return false;
      }
    }

    if (node->right != nullptr) {
      if (!checkRedNodes(node->right)) {
        return false;
      }
    }

    return true;
  }

  struct RBTreeNode {
    treeNode *parent;
    treeNode *left;
    treeNode *right;
    keyType key;
    treeColor color;

    RBTreeNode()
        : parent(nullptr), left(this), right(this), key(keyType{}),
          color(Red){};
    RBTreeNode(const keyType &key)
        : parent(nullptr), left(nullptr), right(nullptr), key(key), color(Red) {
    }
    RBTreeNode(keyType &&key)
        : parent(nullptr), left(nullptr), right(nullptr), key(std::move(key)),
          color(Red) {}
    RBTreeNode(keyType key, treeColor color)
        : parent(nullptr), left(this), right(this), key(key), color(color){};
    void ToDefault() noexcept {
      left = nullptr;
      right = nullptr;
      parent = nullptr;
      color = Red;
    }

    treeNode *NextNode() const noexcept {
      treeNode *node = const_cast<treeNode *>(this);

      if (node->color == Red &&
          (node->parent == nullptr || node->parent->parent == node)) {
        node = node->left;
      } else if (node->right != nullptr) {
        node = node->right;

        while (node->left != nullptr) {
          node = node->left;
        }
      } else {
        treeNode *origin = node->parent;

        while (node == origin->right) {
          node = parent;
          origin = parent->parent;
        }

        if (node->right != parent) {
          node = parent;
        }
      }

      return node;
    }

    treeNode *PrevNode() const noexcept {
      treeNode *node = const_cast<treeNode *>(this);

      if (node->color == Red &&
          (node->parent == nullptr || node->parent->parent == node)) {
        node = node->right;
      } else if (node->right != nullptr) {
        node = node->left;

        while (node->right != nullptr) {
          node = node->right;
        }
      } else {
        treeNode *origin = node->parent;

        while (node == origin->left) {
          node = parent;
          origin = parent->parent;
        }

        if (node->left != parent) {
          node = parent;
        }
      }

      return node;
    }
  };

  struct RBTreeIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = treeType::keyType;
    using pointer = value_type *;
    using reference = value_type &;

    RBTreeIterator() = delete;

    explicit RBTreeIterator(treeNode *node) : node(node) {}

    reference operator*() const noexcept { return node->key; }

    iterator &operator++() noexcept {
      node = node->NextNode();
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator temp{node};
      ++(*this);
      return temp;
    }

    iterator &operator--() noexcept {
      node = node->PrevNode();
      return *this;
    }

    iterator operator--(int) noexcept {
      iterator temp{node};
      --(*this);
      return temp;
    }

    bool operator==(const iterator &other) const noexcept {
      return node == other.node;
    }

    bool operator!=(const iterator &other) const noexcept {
      return node != other.node;
    }

    treeNode *node;
  };

  struct RBTreeConstIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = treeType::keyType;
    using pointer = const value_type *;
    using reference = const value_type &;

    RBTreeConstIterator() = delete;

    explicit RBTreeConstIterator(const treeNode *node) : node(node) {}
    RBTreeConstIterator(const iterator &it) : node(it.node){};

    reference operator*() const noexcept { return node->key; }

    constIterator &operator++() noexcept {
      node = node->NextNode();
      return *this;
    }

    constIterator operator++(int) noexcept {
      constIterator temp{node};
      ++(*this);
      return temp;
    }

    constIterator &operator--() noexcept {
      node = node->PrevNode();
      return *this;
    }

    constIterator operator--(int) noexcept {
      constIterator temp{node};
      --(*this);
      return temp;
    }

    friend bool operator==(const constIterator &it1,
                           const constIterator &it2) noexcept {
      return it1.node == it2.node;
    }

    friend bool operator!=(const constIterator &it1,
                           const constIterator &it2) noexcept {
      return it1.node != it2.node;
    }

    treeNode const *node;
  };
};
};

#endif // CONTEINERS_S21_RED_BLACK_TREE_H
