#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Wrong input. \n");
    exit(EXIT_FAILURE);
  }
  FILE * f_category = fopen(argv[1], "r");
  if (f_category == NULL) {
    perror("Coud not open category file. \n");
    exit(EXIT_FAILURE);
  }

  catarray_t * c = parseWord(f_category);

  if (fclose(f_category) != 0) {
    perror("Failed to close template file. \n");
    exit(EXIT_FAILURE);
  }

  FILE * f_template = fopen(argv[2], "r");
  if (f_template == NULL) {
    perror("Coud not open template file. \n");
    exit(EXIT_FAILURE);
  }

  parseTemplate(f_template, c);
  freeCatarray(c);

  if (fclose(f_template) != 0) {
    perror("Failed to close template file. \n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
