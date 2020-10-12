#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addWord(catarray_t * catarray, char * curr) {
  char * colon = strchr(curr, ':');
  if (colon == NULL) {
    fprintf(stderr, "No colon.\n");
    exit(EXIT_FAILURE);
  }
  char * cat = strndup(curr, colon - curr);
  char * w = strndup(colon + 1, strlen(curr) - (colon - curr + 1));
  char * ptr = w;
  while (*ptr != '\0' && *ptr != '\n') {
    ptr++;
  }
  *ptr = '\0';
  int exist = 0;
  for (size_t i = 0; i < catarray->n; i++) {
    if (strcmp(catarray->arr[i].name, cat) == 0) {
      free(cat);
      exist = 1;
      catarray->arr[i].n_words += 1;
      catarray->arr[i].words =
          realloc(catarray->arr[i].words,
                  ((catarray->arr[i].n_words) * sizeof(*catarray->arr[i].words)));
      catarray->arr[i].words[catarray->arr[i].n_words - 1] = w;
      break;
    }
  }
  if (exist == 0) {
    catarray->n += 1;
    catarray->arr = realloc(catarray->arr, (catarray->n) * sizeof(*catarray->arr));
    catarray->arr[catarray->n - 1].name = cat;
    catarray->arr[catarray->n - 1].n_words = 1;
    catarray->arr[catarray->n - 1].words =
        malloc(sizeof(*catarray->arr[catarray->n - 1].words));
    catarray->arr[catarray->n - 1].words[0] = w;
  }
  free(curr);
}

catarray_t * parseWord(FILE * f) {
  char * curr = NULL;
  size_t sz;
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  while (getline(&curr, &sz, f) >= 0) {
    addWord(catarray, curr);
    curr = NULL;
  }
  free(curr);
  return catarray;
}

char * parseLine(char * line, catarray_t * cats) {
  char * head = line;
  char *start, *end;
  char word[50];
  char buffer[strlen(line)];
  char res[3 * strlen(line)];
  *res = '\0';
  start = strchr(head, '_');
  while (start != NULL) {
    end = strchr(start + 1, '_');
    if (end == NULL) {
      perror("No mataching underscore.\n");
      exit(EXIT_FAILURE);
    }
    strncpy(buffer, head, start - head);
    buffer[start - head] = '\0';  //non-terminated
    strncpy(word, start + 1, end - start - 1);
    word[end - start - 1] = '\0';
    int pre = atoi(word);
    if (pre > 0) {
      //      strcat(buffer, findPre(pre, ref));  //
    }
    else {
      strcat(buffer, chooseWord(word, cats));  // do wee need to free chooseword?
    }
    strcat(res, buffer);
    head = end + 1;
    start = strchr(head, '_');
  }
  strcat(res, head);
  char * str = strdup(res);
  return str;
}

void parseTemplate(FILE * f, catarray_t * cats) {
  char * curr = NULL;
  size_t sz;
  char * temp;
  while (getline(&curr, &sz, f) >= 0) {
    temp = parseLine(curr, cats);
    printf("%s", temp);
    free(curr);
    free(temp);
    curr = NULL;
  }
  free(curr);
}
