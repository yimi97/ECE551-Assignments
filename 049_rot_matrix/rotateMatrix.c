#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void rotate(FILE * f) {
  char array[110];
  int c;
  char * ptr = array;
  for (int i = 0; i < 110; i++) {
    c = fgetc(f);
    if (c == EOF) {
      perror("Less lines.\n");
      exit(EXIT_FAILURE);
    }
    array[i] = c;
  }
  if ((c = fgetc(f) != EOF)) {
    perror("More lines.\n");
    exit(EXIT_FAILURE);
  }
  char matrix[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (*ptr == '\n') {
        perror("1 Not 10 chars a line.\n");
        exit(EXIT_FAILURE);
      }
      matrix[i][j] = *ptr;
      ptr++;
    }
    if (*ptr != '\n') {
      perror("2 Not 10 chars a line.\n");
      exit(EXIT_FAILURE);
    }
    ptr++;
  }
  for (int j = 0; j < 10; j++) {
    for (int i = 9; i > -1; i--) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file!");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
