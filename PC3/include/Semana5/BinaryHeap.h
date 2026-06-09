#pragma once

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ods {

template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
 public:
  BinaryHeap() = default;

  explicit BinaryHeap(const std::vector<T>& values) : data_(values) {
    heapify();
  }

  explicit BinaryHeap(std::vector<T>&& values) : data_(std::move(values)) {
    heapify();
  }

  static int left(int i) { return 2 * i + 1; }
  static int right(int i) { return 2 * i + 2; }
  static int parent(int i) { return (i - 1) / 2; }

  bool empty() const { return data_.empty(); }
  std::size_t size() const { return data_.size(); }

  const T& top() const {
    if (data_.empty()) {
      throw std::out_of_range("Heap vacio");
    }
    return data_.front();
  }

  const std::vector<T>& data() const { return data_; }

  bool add(const T& value) {
    data_.push_back(value);
    bubbleUp(static_cast<int>(data_.size()) - 1);
    return true;
  }

  T remove() {
    if (data_.empty()) {
      throw std::out_of_range("Heap vacio");
    }
    T out = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (!data_.empty()) {
      trickleDown(0);
    }
    return out;
  }

  void clear() { data_.clear(); }

  void bubbleUp(int i) {
    while (i > 0) {
      int p = parent(i);
      if (!comp_(data_[i], data_[p])) {
        break;
      }
      std::swap(data_[i], data_[p]);
      i = p;
    }
  }

  void trickleDown(int i) {
    while (true) {
      int best = i;
      int l = left(i);
      int r = right(i);

      if (l < static_cast<int>(data_.size()) && comp_(data_[l], data_[best])) {
        best = l;
      }
      if (r < static_cast<int>(data_.size()) && comp_(data_[r], data_[best])) {
        best = r;
      }
      if (best == i) {
        break;
      }
      std::swap(data_[i], data_[best]);
      i = best;
    }
  }

  void heapify() {
    for (int i = static_cast<int>(data_.size()) / 2 - 1; i >= 0; --i) {
      trickleDown(i);
    }
  }

  bool isHeap() const {
    return isHeapArray(data_, comp_);
  }

  static bool isHeapArray(const std::vector<T>& data, Compare comp = Compare{}) {
    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
      const int l = left(i);
      const int r = right(i);
      if (l < static_cast<int>(data.size()) && comp(data[l], data[i])) {
        return false;
      }
      if (r < static_cast<int>(data.size()) && comp(data[r], data[i])) {
        return false;
      }
    }
    return true;
  }

 private:
  std::vector<T> data_{};
  Compare comp_{};
};

}  // namespace ods
