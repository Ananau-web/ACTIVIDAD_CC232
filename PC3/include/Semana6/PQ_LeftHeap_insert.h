#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
void leftHeapInsert(PQ_LeftHeap<T, Compare>& h, const T& e) {
  h.insert(e);
}

}  // namespace ods
