#include "rand_story.h"

void execute(int numCategory, int numTemplate, char ** argv, int noUsed) {
  FILE * f_category = fopen(argv[numCategory], "r");
  if (f_category == NULL) {
    perror("Could not open category file.\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * c = parseWord(f_category);
  if (fclose(f_category) != 0) {
    perror("Failed to close category file.\n");
    freeCatarray(c);
    exit(EXIT_FAILURE);
  }

  FILE * f_template = fopen(argv[numTemplate], "r");
  if (f_template == NULL) {
    perror("Could not open template file.\n");
    exit(EXIT_FAILURE);
  }
  parseTemplate(f_template, c, noUsed);
  freeCatarray(c);
  if (fclose(f_template) != 0) {
    perror("Failed to close template file.\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if ((argc != 3 && argc != 4) || (argc == 4 && (strcmp(argv[1], "-n") != 0))) {
    fprintf(stderr, "Wrong input.\n");
    exit(EXIT_FAILURE);
  }
  if (argc == 3) {
    int noUsed = 0;
    execute(1, 2, argv, noUsed);
  }
  else {
    int noUsed = 1;
    execute(2, 3, argv, noUsed);
  }
  return EXIT_SUCCESS;
}
