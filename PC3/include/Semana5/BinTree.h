#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "BinNode.h"

namespace ods {

template <typename T>
class BinTree {
 public:
  using Node = BinNode<T>;

  BinTree() = default;

  BinTree(const BinTree&) = delete;
  BinTree& operator=(const BinTree&) = delete;

  BinTree(BinTree&& other) noexcept { swap(other); }

  BinTree& operator=(BinTree&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  virtual ~BinTree() { clear(); }

  std::size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  Node* root() const { return root_; }

  Node* insertAsRoot(const T& value) {
    clear();
    root_ = new Node(value);
    size_ = 1;
    return root_;
  }

  Node* insertAsLC(Node* parent, const T& value) {
    if (parent == nullptr) {
      throw std::invalid_argument("El padre no puede ser null");
    }
    Node* child = parent->insertAsLC(value);
    ++size_;
    updateHeightAbove(parent);
    return child;
  }

  Node* insertAsRC(Node* parent, const T& value) {
    if (parent == nullptr) {
      throw std::invalid_argument("El padre no puede ser null");
    }
    Node* child = parent->insertAsRC(value);
    ++size_;
    updateHeightAbove(parent);
    return child;
  }

  int updateHeight(Node* node) {
    if (node == nullptr) {
      return -1;
    }
    node->height = 1 + std::max(stature(node->left), stature(node->right));
    return node->height;
  }

  void updateHeightAbove(Node* node) {
    while (node != nullptr) {
      updateHeight(node);
      node = node->parent;
    }
  }

  Node* attachAsLC(Node* parent, BinTree<T>& subtree) {
    if (parent == nullptr) {
      throw std::invalid_argument("El padre no puede ser null");
    }
    if (parent->left != nullptr) {
      throw std::logic_error("El padre ya tiene hijo izquierdo");
    }
    if (subtree.root_ == nullptr) {
      return nullptr;
    }
    parent->left = subtree.root_;
    subtree.root_->parent = parent;
    size_ += subtree.size_;
    updateHeightAbove(parent);
    Node* attached = parent->left;
    subtree.root_ = nullptr;
    subtree.size_ = 0;
    return attached;
  }

  Node* attachAsRC(Node* parent, BinTree<T>& subtree) {
    if (parent == nullptr) {
      throw std::invalid_argument("El padre no puede ser null");
    }
    if (parent->right != nullptr) {
      throw std::logic_error("El padre ya tiene hijo derecho");
    }
    if (subtree.root_ == nullptr) {
      return nullptr;
    }
    parent->right = subtree.root_;
    subtree.root_->parent = parent;
    size_ += subtree.size_;
    updateHeightAbove(parent);
    Node* attached = parent->right;
    subtree.root_ = nullptr;
    subtree.size_ = 0;
    return attached;
  }

  std::size_t removeSubtree(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    std::size_t removed = node->size();
    Node* parent = node->parent;
    Node*& link = fromParentTo(node);
    link = nullptr;
    node->parent = nullptr;
    destroy(node);
    size_ -= removed;
    updateHeightAbove(parent);
    return removed;
  }

  BinTree<T> secede(Node* node) {
    BinTree<T> out;
    if (node == nullptr) {
      return out;
    }
    std::size_t detached = node->size();
    Node* parent = node->parent;
    Node*& link = fromParentTo(node);
    link = nullptr;
    node->parent = nullptr;
    out.root_ = node;
    out.size_ = detached;
    size_ -= detached;
    updateHeightAbove(parent);
    return out;
  }

  template <typename Visit>
  void travPre(Visit visit) {
    if (root_ != nullptr) {
      root_->travPre(visit);
    }
  }

  template <typename Visit>
  void travPreIterative(Visit visit) {
    if (root_ != nullptr) {
      root_->travPreIterative2(visit);
    }
  }

  template <typename Visit>
  void travIn(Visit visit, InorderStrategy strategy = InorderStrategy::Recursive) {
    if (root_ != nullptr) {
      root_->travIn(visit, strategy);
    }
  }

  template <typename Visit>
  void travPost(Visit visit) {
    if (root_ != nullptr) {
      root_->travPost(visit);
    }
  }

  template <typename Visit>
  void travPostIterative(Visit visit) {
    if (root_ != nullptr) {
      root_->travPostIterative(visit);
    }
  }

  template <typename Visit>
  void travLevel(Visit visit) {
    if (root_ != nullptr) {
      root_->travLevel(visit);
    }
  }

  std::vector<T> preorder() { return preorderValues(root_); }
  std::vector<T> preorderIterative() { return preorderValuesIterative(root_); }

  std::vector<T> inorder(InorderStrategy strategy = InorderStrategy::Recursive) {
    return inorderValues(root_, strategy);
  }

  std::vector<T> postorder() { return postorderValues(root_); }
  std::vector<T> postorderIterative() { return postorderValuesIterative(root_); }
  std::vector<T> levelOrder() { return levelOrderValues(root_); }

  bool checkParentLinks() const {
    return checkParentLinks(root_, nullptr);
  }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

 protected:
  std::size_t size_{0};
  Node* root_{nullptr};

  static void destroy(Node* node) {
    if (node == nullptr) {
      return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  Node*& fromParentTo(Node* node) {
    if (node->parent == nullptr) {
      return root_;
    }
    return node->isLeftChild() ? node->parent->left : node->parent->right;
  }

  static bool checkParentLinks(const Node* node, const Node* parent) {
    if (node == nullptr) {
      return true;
    }
    if (node->parent != parent) {
      return false;
    }
    return checkParentLinks(node->left, node) && checkParentLinks(node->right, node);
  }

  void swap(BinTree& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
};

}  // namespace ods
