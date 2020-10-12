#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file.\n");
    exit(EXIT_FAILURE);
  }

  catarray_t * c = parseWord(f);
  printWords(c);
  freeCatarray(c);

  if (fclose(f) != 0) {
    perror("Failed to close the file.\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
