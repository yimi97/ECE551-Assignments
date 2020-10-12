#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input. \n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file. \n");
    exit(EXIT_FAILURE);
  }

  parseTemplate(f, NULL);

  if (fclose(f) != 0) {
    perror("Failed to close the input file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
