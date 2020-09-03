#include <math.h>
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned power_ans = power(x, y);
  if (power_ans != expected_ans) {
    printf("ERROR: %d to the power %d should be %d, not %d.\n ",
           x,
           y,
           expected_ans,
           power_ans);
    exit(EXIT_FAILURE);
  }
  return;
}

int main(void) {
  run_check(2, 5, 32);
  run_check(7, 7, 823543);
  run_check(0, 0, 1);
  run_check(0, 2, 0);
  run_check(2, 0, 1);
  run_check(2, 1, 2);
  run_check(1, 2, 1);
  run_check(-1, 2, 1);
  run_check(2, -1, 0);
  run_check(-2, -2, 0);
  run_check(4294967295, 0, 1);

  return EXIT_SUCCESS;
}
