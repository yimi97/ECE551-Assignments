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

int main(int argc, char ** argv) {
  if (argc < 1) {  //==1
    printf("Enter a string?/n");
    getchar();
    printf("sss");
    exit(EXIT_SUCCESS);
  }
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  FILE * f;
  for (int numOfFiles = 1; numOfFiles < argc; i++) {
    f = fopen(argv[numOfFiles], "r");
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
    //   lines = NULL;
    //curr = NULL;
    i = 0;
  }
  // FILE * f = fopen("name.txt", "r");

  return EXIT_SUCCESS;
}
