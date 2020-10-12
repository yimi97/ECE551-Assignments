#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  /*
  char * str = "_ABC_ abc abc _qwe_.";
  char buffer[100];
  strncpy(buffer, str, 0);
  buffer[strlen(buffer)] = '\0';
  printf("%s", buffer);
  char * word = "happy";
  strcat(buffer, word);
  printf("%s\n", buffer);
  printf("%ld\n", strlen(buffer));
  char * res = "";
  strcat(res, buffer);
  printf("%s\n", res);
  */
  char * s = "abs";
  int x = atoi(s);
  printf("%d", x);
  return EXIT_SUCCESS;
}
