#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "PQ.h"

namespace ods {

template <class T, class Compare = std::less<T>>
class PQ_LeftHeap : public PQ<T> {
  struct Node {
    T value;
    int npl{1};
    Node* left{nullptr};
    Node* right{nullptr};
    explicit Node(const T& v) : value(v) {}
  };

 public:
  PQ_LeftHeap() = default;

  explicit PQ_LeftHeap(Compare comp) : comp_(std::move(comp)) {}

  PQ_LeftHeap(std::initializer_list<T> xs, Compare comp = Compare{}) : comp_(std::move(comp)) {
    for (const T& x : xs) {
      insert(x);
    }
  }

  template <class InputIt>
  PQ_LeftHeap(InputIt first, InputIt last, Compare comp = Compare{}) : comp_(std::move(comp)) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  ~PQ_LeftHeap() { clear(root_); }

  PQ_LeftHeap(const PQ_LeftHeap&) = delete;
  PQ_LeftHeap& operator=(const PQ_LeftHeap&) = delete;

  PQ_LeftHeap(PQ_LeftHeap&& other) noexcept
      : root_(other.root_), n_(other.n_), comp_(std::move(other.comp_)) {
    other.root_ = nullptr;
    other.n_ = 0;
  }

  PQ_LeftHeap& operator=(PQ_LeftHeap&& other) noexcept {
    if (this != &other) {
      clear(root_);
      root_ = other.root_;
      n_ = other.n_;
      comp_ = std::move(other.comp_);
      other.root_ = nullptr;
      other.n_ = 0;
    }
    return *this;
  }

  bool empty() const noexcept override { return n_ == 0; }
  std::size_t size() const noexcept override { return n_; }

  const T& getMax() const override {
    if (!root_) {
      throw std::out_of_range("getMax() sobre heap izquierdista vacio");
    }
    return root_->value;
  }

  void insert(const T& e) override {
    root_ = mergeNodes(root_, new Node(e));
    ++n_;
  }

  T delMax() override {
    if (!root_) {
      throw std::out_of_range("delMax() sobre heap izquierdista vacio");
    }
    T ans = root_->value;
    Node* old = root_;
    Node* a = root_->left;
    Node* b = root_->right;
    old->left = nullptr;
    old->right = nullptr;
    delete old;
    root_ = mergeNodes(a, b);
    --n_;
    return ans;
  }

  void merge(PQ_LeftHeap& other) {
    if (this == &other) {
      return;
    }
    root_ = mergeNodes(root_, other.root_);
    n_ += other.n_;
    other.root_ = nullptr;
    other.n_ = 0;
  }

  std::vector<T> levelOrder() const {
    std::vector<T> out;
    std::queue<Node*> q;
    if (root_) q.push(root_);
    while (!q.empty()) {
      Node* u = q.front();
      q.pop();
      out.push_back(u->value);
      if (u->left) q.push(u->left);
      if (u->right) q.push(u->right);
    }
    return out;
  }

  bool isLeftistHeap() const { return check(root_).ok; }

 private:
  struct Check {
    bool ok;
    int npl;
  };

  Node* root_{nullptr};
  std::size_t n_{0};
  Compare comp_{};

  static int npl(Node* u) noexcept { return u ? u->npl : 0; }

  Node* mergeNodes(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (comp_(a->value, b->value)) {
      std::swap(a, b);
    }
    a->right = mergeNodes(a->right, b);
    if (npl(a->left) < npl(a->right)) {
      std::swap(a->left, a->right);
    }
    a->npl = npl(a->right) + 1;
    return a;
  }

  Check check(Node* u) const {
    if (!u) return {true, 0};
    const Check l = check(u->left);
    const Check r = check(u->right);
    const bool heapOk = (!u->left || !comp_(u->value, u->left->value)) &&
                        (!u->right || !comp_(u->value, u->right->value));
    const bool leftistOk = npl(u->left) >= npl(u->right) && u->npl == npl(u->right) + 1;
    return {l.ok && r.ok && heapOk && leftistOk, u->npl};
  }

  static void clear(Node* u) noexcept {
    if (!u) return;
    clear(u->left);
    clear(u->right);
    delete u;
  }
};

}  // namespace ods
