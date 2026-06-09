#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <ostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ods {

template <class T, class Compare = std::less<T>>
class Treap {
 public:
  struct Node {
    T key{};
    std::uint64_t priority{0};
    Node* parent{nullptr};
    Node* left{nullptr};
    Node* right{nullptr};

    Node() = default;
    Node(const T& value, std::uint64_t p, Node* par = nullptr)
        : key(value), priority(p), parent(par) {}

    bool isLeftChild() const { return parent != nullptr && parent->left == this; }
    bool isRightChild() const { return parent != nullptr && parent->right == this; }
  };

  Treap() : rng_(232) {}
  explicit Treap(std::uint64_t seed) : rng_(seed) {}
  explicit Treap(Compare comp, std::uint64_t seed = 232) : comp_(std::move(comp)), rng_(seed) {}

  Treap(const Treap&) = delete;
  Treap& operator=(const Treap&) = delete;

  Treap(Treap&& other) noexcept { swap(other); }
  Treap& operator=(Treap&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  ~Treap() { clear(); }

  void clear() {
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
  }

  void swap(Treap& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
    std::swap(rng_, other.rng_);
    std::swap(priorityCounter_, other.priorityCounter_);
  }

  Node* root() const noexcept { return root_; }
  std::size_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  Node* findLast(const T& x) const {
    Node* w = root_;
    Node* prev = nullptr;
    while (w != nullptr) {
      prev = w;
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return prev;
  }

  Node* findEQ(const T& x) const {
    Node* w = root_;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return nullptr;
  }

  Node* lowerBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else if (comp_(w->key, x)) {
        w = w->right;
      } else {
        return w;
      }
    }
    return candidate;
  }

  Node* upperBound(const T& x) const {
    Node* w = root_;
    Node* candidate = nullptr;
    while (w != nullptr) {
      if (comp_(x, w->key)) {
        candidate = w;
        w = w->left;
      } else {
        w = w->right;
      }
    }
    return candidate;
  }

  bool contains(const T& x) const { return findEQ(x) != nullptr; }

  bool add(const T& x) { return addWithPriority(x, nextPriority()); }

  bool addWithPriority(const T& x, std::uint64_t priority) {
    Node* u = new Node(x, priority);
    if (!addNode(u)) {
      delete u;
      return false;
    }
    bubbleUp(u);
    return true;
  }

  bool remove(const T& x) {
    Node* u = findEQ(x);
    if (!u) return false;
    trickleDown(u);
    splice(u);
    delete u;
    return true;
  }

  void rotateLeft(Node* u) {
    if (!u || !u->right) return;
    Node* w = u->right;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->right = w->left;
    if (u->right) u->right->parent = u;
    w->left = u;
    u->parent = w;
  }

  void rotateRight(Node* u) {
    if (!u || !u->left) return;
    Node* w = u->left;
    w->parent = u->parent;
    if (!u->parent) {
      root_ = w;
    } else if (u->isLeftChild()) {
      u->parent->left = w;
    } else {
      u->parent->right = w;
    }
    u->left = w->right;
    if (u->left) u->left->parent = u;
    w->right = u;
    u->parent = w;
  }

  void bubbleUp(Node* u) {
    while (u->parent && u->parent->priority > u->priority) {
      if (u->isRightChild()) {
        rotateLeft(u->parent);
      } else {
        rotateRight(u->parent);
      }
    }
    if (!u->parent) root_ = u;
  }

  void trickleDown(Node* u) {
    while (u->left || u->right) {
      if (!u->left) {
        rotateLeft(u);
      } else if (!u->right) {
        rotateRight(u);
      } else if (u->left->priority < u->right->priority) {
        rotateRight(u);
      } else {
        rotateLeft(u);
      }
      if (root_ == u) root_ = u->parent;
    }
  }

  std::vector<T> inorderKeys() const {
    std::vector<T> out;
    inorder(root_, out);
    return out;
  }

  std::vector<T> levelOrderKeys() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->key);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  std::string asciiArt() const {
    if (!root_) return "(treap vacio)\n";
    std::vector<std::string> lines;
    buildAscii(root_, "", true, lines);
    std::ostringstream out;
    for (const auto& line : lines) out << line << '\n';
    return out.str();
  }

  bool isBST() const { return isBST(root_, nullptr, nullptr) && checkParents(root_, nullptr); }
  bool isHeapByPriority() const { return isHeapByPriority(root_); }
  bool isTreap() const { return isBST() && isHeapByPriority(); }

 private:
  Node* root_{nullptr};
  std::size_t size_{0};
  Compare comp_{};
  std::mt19937_64 rng_;
  std::uint64_t priorityCounter_{0};

  std::uint64_t nextPriority() {
    std::uint64_t raw = rng_();
    return (raw << 16) ^ (++priorityCounter_);
  }

  bool addNode(Node* u) {
    u->left = nullptr;
    u->right = nullptr;
    Node* p = findLast(u->key);
    if (!p) {
      root_ = u;
      u->parent = nullptr;
      ++size_;
      return true;
    }
    if (comp_(u->key, p->key)) {
      if (p->left) return false;
      p->left = u;
    } else if (comp_(p->key, u->key)) {
      if (p->right) return false;
      p->right = u;
    } else {
      return false;
    }
    u->parent = p;
    ++size_;
    return true;
  }

  void splice(Node* u) {
    Node* s = u->left ? u->left : u->right;
    if (u == root_) {
      root_ = s;
    } else if (u->isLeftChild()) {
      u->parent->left = s;
    } else {
      u->parent->right = s;
    }
    if (s) s->parent = u->parent;
    --size_;
  }

  static void destroy(Node* u) {
    if (!u) return;
    destroy(u->left);
    destroy(u->right);
    delete u;
  }

  static void inorder(Node* u, std::vector<T>& out) {
    if (!u) return;
    inorder(u->left, out);
    out.push_back(u->key);
    inorder(u->right, out);
  }

  bool isBST(Node* u, const T* low, const T* high) const {
    if (!u) return true;
    if (low && !comp_(*low, u->key)) return false;
    if (high && !comp_(u->key, *high)) return false;
    return isBST(u->left, low, &u->key) && isBST(u->right, &u->key, high);
  }

  static bool checkParents(Node* u, Node* parent) {
    if (!u) return true;
    if (u->parent != parent) return false;
    return checkParents(u->left, u) && checkParents(u->right, u);
  }

  static bool isHeapByPriority(Node* u) {
    if (!u) return true;
    if (u->left && u->left->priority < u->priority) return false;
    if (u->right && u->right->priority < u->priority) return false;
    return isHeapByPriority(u->left) && isHeapByPriority(u->right);
  }

  static std::string nodeLabel(const Node* u) {
    std::ostringstream out;
    out << u->key << "|p=" << u->priority;
    return out.str();
  }

  static void buildAscii(const Node* node, const std::string& prefix, bool isTail,
                         std::vector<std::string>& lines) {
    if (!node) return;
    if (node->right) {
      buildAscii(node->right, prefix + (isTail ? "│   " : "    "), false, lines);
    }
    lines.push_back(prefix + (isTail ? "└── " : "┌── ") + nodeLabel(node));
    if (node->left) {
      buildAscii(node->left, prefix + (isTail ? "    " : "│   "), true, lines);
    }
  }
};

template <class T, class Compare>
inline std::ostream& operator<<(std::ostream& out, const Treap<T, Compare>& t) {
  out << t.asciiArt();
  return out;
}

}  // namespace ods
