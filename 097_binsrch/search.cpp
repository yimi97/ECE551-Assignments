#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int res = f->invoke(mid);
    if (res == 0) {
      return mid;
    }
    else if (res < 0) {
      low = mid;
    }
    else {
      high = mid;
    }
  }
  return low;
}
