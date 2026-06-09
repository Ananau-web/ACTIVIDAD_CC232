#pragma once

#include <cstddef>

namespace ods {

template <class T>
class PQ {
 public:
  virtual ~PQ() = default;
  virtual void insert(const T& e) = 0;
  virtual T delMax() = 0;
  virtual const T& getMax() const = 0;
  virtual bool empty() const noexcept = 0;
  virtual std::size_t size() const noexcept = 0;
};

}  // namespace ods
