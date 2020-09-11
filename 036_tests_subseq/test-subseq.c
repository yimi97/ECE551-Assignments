#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t exp_ans) {
  size_t ans = maxSeq(array, n);
  printf("Test case: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  if (ans != exp_ans) {
    printf("ERROR: the maxSeq gets %ld but the correct ans is %ld \n", ans, exp_ans);
    exit(EXIT_FAILURE);
  }
  return;
}

int main(void) {
  int arr1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int arr2[] = {1, 2, 1, 3, 5, 6, 7, 2, 4, 6, 9};
  int arr3[] = {1};
  int arr4[] = {1, 2};
  int arr5[] = {1, 2, 3, 4, 5, 4, 3, 2};
  int arr6[] = {1, 1, 1};
  int arr7[] = {3, 2, 1};
  int arr8[] = {0};
  int arr9[6] = {1, 2, 3};
  // an array can not have zero size
  // int arr10[] = {};
  int arr11[] = {-1};
  int arr12[] = {352436664};
  int arr13[] = {1, 2, 3, 4, 4, 6, 7, 8};
  int arr14[] = {-4, -3, -2, 1, 3, 2};
  // char arr12[] = {'a'};
  int x = 3;
  int * p = &x;
  run_check(p, 1, 1);
  run_check(NULL, 0, 0);
  run_check(arr1, 10, 4);
  run_check(arr2, 11, 5);
  run_check(arr3, 1, 1);
  run_check(arr4, 2, 2);
  run_check(arr5, 8, 5);
  run_check(arr6, 3, 1);
  run_check(arr7, 3, 1);
  run_check(arr8, 1, 1);
  run_check(arr9, 6, 3);
  // run_check(arr10, 0, 0);
  run_check(arr11, 1, 1);
  run_check(arr12, 1, 1);
  run_check(arr13, 8, 4);
  run_check(arr14, 6, 5);
  // run_check(arr12, 1, 0);
  return EXIT_SUCCESS;
}
