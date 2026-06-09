#pragma once

#include <stdexcept>
#include <vector>

namespace ods {

template <class T>
const T& complHeapGetMax(const std::vector<T>& a) {
  if (a.empty()) {
    throw std::out_of_range("getMax() sobre heap vacio");
  }
  return a.front();
}

}  // namespace ods
