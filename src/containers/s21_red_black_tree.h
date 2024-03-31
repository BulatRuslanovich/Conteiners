#ifndef CONTEINERS_S21_RED_BLACK_TREE_H
#define CONTEINERS_S21_RED_BLACK_TREE_H

#include <functional>
#include <limits>
#include <vector>

namespace s21 {
enum RBTreeColor { Black, Red };

template <typename Key, typename Comparator=std::less<Key>>
class RBTree {
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
  constIterator Begin() noexcept { return constIterator(MostLittle()); }

  iterator End() noexcept { return iterator(root); }
  constIterator End() noexcept { return constIterator(root); }

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
  std::vector<std::pair<iterator , bool>> Emplace(Args && ...args) {
    std::vector<std::pair<iterator , bool>> result;
    result.reserve(sizeof ...(args));
    
    for (auto item : {std::forward<Args>(args)...}) {
      treeNode *newNode = new treeNode (std::move(item));
      std::pair<iterator , bool> resultInsert = Insert(Root(), newNode, false);
      result.push_back(resultInsert);
    }
    
    return result;
  }
  
  template <typename... Args>
  std::vector<std::pair<iterator , bool>> EmplaceUnique(Args && ...args) {
    std::vector<std::pair<iterator , bool>> result;
    result.reserve(sizeof ...(args));
    
    for (auto item : {std::forward<Args>(args)...}) {
      treeNode *newNode = new treeNode (std::move(item));
      std::pair<iterator , bool> resultInsert = Insert(Root(), newNode, true);
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
     treeNode *copy = new treeNode {node->key, node->color};
     
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
   
   treeNode *&Root() {return root->parent; }
   const treeNode *Root() const {return root->parent; }
   treeNode *& MostLittle()  { return root->left; }
   const treeNode * MostLittle() const { return root->left; }
   treeNode *& MostBig()  { return root->right; }

   std::pair<iterator, bool> Insert(treeNode *origin, treeNode *newNode, bool unique) {
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
     //Father
     treeNode *parent = node->parent;

     while (node != Root() && parent == Red) {
       //Grandpa
       treeNode *grand = parent->parent;

       if (grand->left == parent) {
         treeNode *uncle = grand->right;

         if (uncle != nullptr && uncle->color == Red) {
           //first case
           parent->color = Black;
           uncle->color = Black;
           grand->color = Red;

           node = grand;
           parent = node->parent;
         } else {
           //second case
           if (parent->right == node) {
             RotateLeft(parent);
             std::swap(parent, node);
           }

           //third case
           RotateRight(grand);
           grand->color = Red;
           parent->color = Black;
           break;
         }
       } else {
         treeNode *uncle = grand->left;

         if (uncle != nullptr && uncle->color == Red) {
           //first case
           parent->color = Black;
           uncle->color = Black;
           grand->color = Red;

           node = grand;
           parent = node->parent;
         } else {
           //second case
           if (parent->left == node) {
             RotateRight(parent);
             std::swap(parent, node);
           }

           //third case
           RotateLeft(grand);
           grand->color = Red;
           parent->color = Black;
           break;
         }
       }
     }

     Root()->color = Black;
   }

   void RotateRight(treeNode *node ) noexcept {
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

   void RotateLeft(treeNode *node ) noexcept {
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


   
  
};
}


#endif // CONTEINERS_S21_RED_BLACK_TREE_H
