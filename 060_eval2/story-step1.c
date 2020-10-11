#include "rand_story.h"
int main(int argc, char ** argv) {
  /*
  if (argc != 3) {
    perror("Wrong input. \n");
    exit(EXIT_FAILURE);
  }
  */
  // ptr or copy?  catarray_t * cat = argv[2];
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file. \n");
    exit(EXIT_FAILURE);
  }

  // DO STH
  char * story = parseTemplate(f);

  printf("%s\n", story);
  free(story);
  if (fclose(f) != 0) {
    perror("Failed to close the input file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
