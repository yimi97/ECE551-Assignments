#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("wrong input\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file.\n");
    exit(EXIT_FAILURE);
  }

  catarray_t * c = parseWord(f);
  for (size_t i = 0; i < c->n; i++) {
    printf("%s:\n", c->arr[i].name);
    for (size_t j = 0; j < c->arr[i].n_words; j++) {
      printf("  %s\n", c->arr[i].words[j]);
    }
  }
  for (size_t i = 0; i < c->n; i++) {
    free(c->arr[i].name);
    for (size_t j = 0; j < c->arr[i].n_words; j++) {
      free(c->arr[i].words[j]);
    }
    free(c->arr[i].words);
  }
  free(c->arr);
  free(c);

  if (fclose(f) != 0) {
    perror("Failed to close the file.\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
