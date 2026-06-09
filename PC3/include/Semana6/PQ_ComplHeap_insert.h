#pragma once

#include <vector>

#include "PQ_ComplHeap_percolateUp.h"

namespace ods {

template <class T, class Compare>
void complHeapInsert(std::vector<T>& a, const T& e, Compare comp) {
  a.push_back(e);
  complHeapPercolateUp(a, a.size() - 1, comp);
}

}  // namespace ods
