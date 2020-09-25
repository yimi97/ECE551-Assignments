#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
// This function will read a file and print the sorted lines.
void readAFile(FILE * f) {
  if (f == NULL) {
    perror("Could not open file./n");
    exit(EXIT_FAILURE);
  }
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
  if (fclose(f) != 0) {
    perror("Failed to close the input file.\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  FILE * f;
  if (argc == 1) {
    printf("Enter a lines:\n");
    f = stdin;
    /*
    if (f == NULL) {
      perror("Could not open file./n");
      exit(EXIT_FAILURE);
    }
    */
    readAFile(f);
    /*
    if (fclose(f) != 0) {
      perror("Failed to close the input file.\n");
      exit(EXIT_FAILURE);
    }
    */
    exit(EXIT_SUCCESS);
  }

  for (int numOfFiles = 1; numOfFiles < argc; numOfFiles++) {
    f = fopen(argv[numOfFiles], "r");
    /*
    if (f == NULL) {
      perror("Could not open file./n");
      exit(EXIT_FAILURE);
    }
    */
    readAFile(f);
    /*
    if (fclose(f) != 0) {
      perror("Failed to close the input file.\n");
      exit(EXIT_FAILURE);
    }
    */
  }

  return EXIT_SUCCESS;
}
