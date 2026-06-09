#pragma once

#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

template <class T, class Compare>
void complHeapHeapifyFloyd(std::vector<T>& a, Compare comp) {
  if (a.size() < 2) {
    return;
  }
  for (std::size_t i = a.size() / 2; i-- > 0;) {
    complHeapPercolateDown(a, a.size(), i, comp);
  }
}

}  // namespace ods
