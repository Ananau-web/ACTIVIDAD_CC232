#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
void leftHeapMerge(PQ_LeftHeap<T, Compare>& a, PQ_LeftHeap<T, Compare>& b) {
  a.merge(b);
}

}  // namespace ods
