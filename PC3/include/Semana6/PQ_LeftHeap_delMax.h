#pragma once

#include "PQ_LeftHeap.h"

namespace ods {

template <class T, class Compare>
T leftHeapDelMax(PQ_LeftHeap<T, Compare>& h) {
  return h.delMax();
}

}  // namespace ods
