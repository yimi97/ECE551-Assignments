#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//

char max(char * arr, size_t n) {
  int max_index = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] > arr[max_index]) {
      max_index = i;
    }
  }
  return 'a' + max_index;
}

int back_solve(char e) {
  int c = e - 'a';
  int key;
  for (int i = 0; i < 26; i++) {
    if ((4 + i) % 26 == c) {
      key = i;
      break;
    }
  }
  return key;
}

void break_encrypt(FILE * f) {
  int c;
  int i;
  char alpha[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      i = c - 97;
      alpha[i] += 1;
    }
  }
  char e = max(alpha, 26);
  int key = back_solve(e);
  fprintf(stdout, "%d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: break_encrypt inputFileNanme\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  break_encrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to clode the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
