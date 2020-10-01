#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * myCount = malloc(sizeof(*myCount));
  myCount->arr = NULL;
  myCount->sz = 0;
  return myCount;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->count_unknown++;
  }
  else {
    if (c->arr == NULL) {
      c->arr = malloc(sizeof(*c->arr));
      c->sz++;
      c->arr->str = malloc((strlen(name) + 1) * sizeof(*c->arr->str));
      strcpy(c->arr->str, name);
      c->arr->count = 1;
    }
    else {
      one_count_t * ptr = c->arr;
      for (size_t i = 0; i < c->sz; i++) {
        if (strcmp(name, ptr->str) == 0) {
          ptr->count++;
          //          return EXIT_SUCCESS;
          return;
        }
        ptr++;
      }
      if (ptr == c->arr + c->sz) {
        c->arr = realloc(c->arr, (c->sz + 1) * sizeof(*c->arr));
        c->sz++;
        c->arr[c->sz - 1].str = malloc((strlen(name) + 1) * sizeof(*c->arr->str));
        strcpy(c->arr[c->sz - 1].str, name);
        c->arr[c->sz - 1].count = 1;
      }
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  one_count_t * ptr = c->arr;
  for (size_t i = 0; i < c->sz; i++) {
    // print to the FILE outFile
    fprintf(outFile, "%s: %ld\n", ptr->str, ptr->count);
    ptr++;
  }
  if (c->count_unknown != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->count_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  one_count_t * ptr = c->arr;
  for (size_t i = 0; i < c->sz; i++) {
    free(ptr->str);
    ptr++;
  }
  free(c->arr);
  free(c);
}
