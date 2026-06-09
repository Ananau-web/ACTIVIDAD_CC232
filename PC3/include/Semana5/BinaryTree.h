#pragma once

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "BinTree.h" // se escarga de la gestión estructural de la memoria y el árbol(insertar, borrar, unir subárboles, etc)
namespace ods {
// BinaryTree se enfoca en 
template <typename T> // hereda de BinTree<T> para aprovechar su funcionalidad básica de árbol binario
class BinaryTree : public BinTree<T> {
 public:
  using Node = typename BinTree<T>::Node;
  using BinTree<T>::root_;

  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator() = default;
    explicit iterator(Node* node) : current_(node) {}

    reference operator*() const { return current_->data; }
    pointer operator->() const { return &current_->data; }

    iterator& operator++() {
      current_ = (current_ == nullptr) ? nullptr : current_->succ();
      return *this;
    }

    iterator operator++(int) {
      iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const { return current_ == other.current_; }
    bool operator!=(const iterator& other) const { return !(*this == other); }

   private:
    Node* current_{nullptr};
  };

  class node_iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Node*;
    using difference_type = std::ptrdiff_t;
    using pointer = Node**;
    using reference = Node*&;

    node_iterator() = default;
    explicit node_iterator(Node* node) : current_(node) {}

    Node* operator*() const { return current_; }

    node_iterator& operator++() {
      current_ = (current_ == nullptr) ? nullptr : current_->succ();
      return *this;
    }

    bool operator==(const node_iterator& other) const { return current_ == other.current_; }
    bool operator!=(const node_iterator& other) const { return !(*this == other); }

   private:
    Node* current_{nullptr};
  };

  int depth(const Node* node) const {
    int d = 0;
    while (node != nullptr && node != root_) {
      node = node->parent;
      ++d;
    }
    return d;
  }

  int height(const Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    const int lh = height(node->left);
    const int rh = height(node->right);
    return 1 + (lh > rh ? lh : rh);
  }

  int height() const { return height(root_); }

  std::size_t subtreeSize(const Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    return 1 + subtreeSize(node->left) + subtreeSize(node->right);
  }

  Node* firstNode() const {
    return root_ == nullptr ? nullptr : root_->leftmost();
  }

  Node* lastNode() const {
    return root_ == nullptr ? nullptr : root_->rightmost();
  }

  Node* nextNode(Node* node) const {
    return node == nullptr ? nullptr : node->succ();
  }

  Node* prevNode(Node* node) const {
    return node == nullptr ? nullptr : node->pred();
  }

  iterator begin() const { return iterator(firstNode()); }
  iterator end() const { return iterator(nullptr); }

  node_iterator nodesBegin() const { return node_iterator(firstNode()); }
  node_iterator nodesEnd() const { return node_iterator(nullptr); }

  std::vector<T> traverseInorder(InorderStrategy strategy = InorderStrategy::Recursive) {
    return this->inorder(strategy);
  }

  std::vector<T> traverseBreadthFirst() {
    return this->levelOrder();
  }

  std::vector<T> iterateBySuccessor() const {
    std::vector<T> out;
    for (Node* u = firstNode(); u != nullptr; u = nextNode(u)) {
      out.push_back(u->data);
    }
    return out;
  }

  std::vector<T> iterateByPredecessor() const {
    std::vector<T> out;
    for (Node* u = lastNode(); u != nullptr; u = prevNode(u)) {
      out.push_back(u->data);
    }
    return out;
  }

  std::string asciiArt() const {
    if (root_ == nullptr) {
      return "(arbol vacio)\n";
    }
    std::vector<std::string> lines;
    buildAscii(root_, "", true, lines);
    std::ostringstream out;
    for (const auto& line : lines) {
      out << line << '\n';
    }
    return out.str();
  }

 private:
  static std::string nodeLabel(const T& value) {
    std::ostringstream out;
    out << value;
    return out.str();
  }

  static void buildAscii(const Node* node, const std::string& prefix, bool isTail,
                         std::vector<std::string>& lines) {
    if (node == nullptr) {
      return;
    }
    if (node->right != nullptr) {
      buildAscii(node->right, prefix + (isTail ? "│   " : "    "), false, lines);
    }
    lines.push_back(prefix + (isTail ? "└── " : "┌── ") + nodeLabel(node->data));
    if (node->left != nullptr) {
      buildAscii(node->left, prefix + (isTail ? "    " : "│   "), true, lines);
    }
  }
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const BinaryTree<T>& tree) {
  out << tree.asciiArt();
  return out;
}

}  // namespace ods
