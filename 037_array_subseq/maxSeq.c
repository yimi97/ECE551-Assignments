#include <stddef.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  int i = 0;
  int j = 0;
  size_t res = 1;
  while (i < n) {
    while ((j + 1 < n) && (array[j + 1] > array[j])) {
      j++;
    }
    if (j - i + 1 > res) {
      res = j - i + 1;
    }
    j++;
    i = j;
  }
  return res;
}
