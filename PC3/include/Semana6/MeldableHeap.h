#pragma once

#include <cstddef>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>

namespace ods {

template <class T, class Compare = std::less<T>>
class MeldableHeap {
  struct Node {
    T value;
    Node* left{nullptr};
    Node* right{nullptr};
    explicit Node(const T& v) : value(v) {}
  };

 public:
  explicit MeldableHeap(unsigned seed = 232) : rng_(seed) {}
  ~MeldableHeap() { clear(root_); }

  bool add(const T& x) {
    root_ = merge(root_, new Node(x));
    ++n_;
    return true;
  }

  const T& findMin() const {
    if (!root_) throw std::out_of_range("findMin() sobre MeldableHeap vacio");
    return root_->value;
  }

  T remove() {
    if (!root_) throw std::out_of_range("remove() sobre MeldableHeap vacio");
    T y = root_->value;
    Node* old = root_;
    root_ = merge(root_->left, root_->right);
    old->left = nullptr;
    old->right = nullptr;
    delete old;
    --n_;
    return y;
  }

  bool empty() const noexcept { return n_ == 0; }
  std::size_t size() const noexcept { return n_; }

 private:
  Node* root_{nullptr};
  std::size_t n_{0};
  Compare comp_{};
  std::mt19937 rng_;

  Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (comp_(b->value, a->value)) std::swap(a, b);
    if (std::uniform_int_distribution<int>(0, 1)(rng_)) {
      a->left = merge(a->left, b);
    } else {
      a->right = merge(a->right, b);
    }
    return a;
  }

  static void clear(Node* u) noexcept {
    if (!u) return;
    clear(u->left);
    clear(u->right);
    delete u;
  }
};

}  // namespace ods
