#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pandemic.h"

int main(void) {
  char * p = "a  1 23  ";
  char * p1 = "";
  int num = atoi(p1);
  printf("%d", num);
  if (isdigit(*p) == 0) {
    printf("non number");
  }
  return 0;
}
