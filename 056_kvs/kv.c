#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t parseLine(char * curr) {
  char * ptr = curr;
  kvpair_t kv;
  kv.key = NULL;
  kv.value = NULL;
  size_t i = 0;
  while (*ptr != '=') {
    kv.key = realloc(kv.key, (i + 1) * sizeof(*kv.key));
    kv.key[i] = *ptr;
    ptr++;
    i++;
  }
  kv.key = realloc(kv.key, (i + 1) * sizeof(*kv.key));
  kv.key[i] = '\0';
  i = 0;
  ptr++;
  while ((*ptr != '\0') && (*ptr != '\n')) {
    kv.value = realloc(kv.value, (i + 1) * sizeof(*kv.value));
    kv.value[i] = *ptr;
    ptr++;
    i++;
  }
  kv.value = realloc(kv.value, (i + 1) * sizeof(*kv.value));
  kv.value[i] = '\0';
  free(curr);  // why!!!
  return kv;
}

void readFile(FILE * f, kvarray_t * arr) {
  arr->pair = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    arr->pair = realloc(arr->pair, (i + 1) * sizeof(*arr->pair));
    arr->pair[i] = parseLine(curr);
    curr = NULL;
    i++;
  }
  arr->length = i;
  free(curr);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file. \n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * arr = malloc(sizeof(*arr));
  readFile(f, arr);
  if (fclose(f) != 0) {
    perror("Failed to close the input file. \n");
    exit(EXIT_FAILURE);
  }
  return arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * ptr = pairs->pair;
  for (size_t i = 0; i < pairs->length; i++) {
    free(ptr->key);
    free(ptr->value);
    ptr++;
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t * ptr = pairs->pair;
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", ptr->key, ptr->value);
    ptr++;
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pair[i].key, key) == 0) {
      return pairs->pair[i].value;
    }
  }
  return NULL;
}
