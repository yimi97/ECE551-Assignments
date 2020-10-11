#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * parseLine(char * line) {
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
    strcat(buffer, chooseWord(word, NULL));
    strcat(res, buffer);
    // *buffer = '\0';
    head = end + 1;
    start = strchr(head, '_');
  }
  char * ptr = head;
  while (*ptr != '\0' && *ptr != '\n') {
    ptr++;
  }
  *ptr = '\0';
  strcat(res, head);
  char * str = strdup(res);
  return str;
}

char * parseTemplate(FILE * f) {
  char * curr = NULL;
  size_t sz;
  char * temp;
  char str[1000];
  *str = '\0';
  while (getline(&curr, &sz, f) >= 0) {
    temp = parseLine(curr);
    strcat(str, temp);
    free(curr);
    free(temp);
    curr = NULL;
  }
  char * story = strdup(str);
  return story;
}

/*
template_t * parseTemplate(FILE * f) {
  char * curr = NULL;
  size_t sz;
  ssize_t len = getline(&curr, &sz, f);
  if (len == -1) {
    perror("No template. \n");
    exit(EXIT_FAILURE);
  }
  template_t * template = malloc(sizeof(*template));
  template->word_arr = NULL;
  template->word_sz = 0;
  size_t i = 0;
  //  size_t j = 0;
  //  char * str = strdup(curr);
  //char * ptr = str;
  // char * str_head = str;
  char * str = curr;
  char * ptr = curr;
  char * space;
  while ((space = strsep(&str, " ")) != NULL) {
    template->word_arr =
        realloc(template->word_arr, (i + 1) * sizeof(*template->word_arr));
    if (*ptr == '_') {
      if (*(space - 1) != '_') {
        perror("Underscore does not match. \n");
        exit(EXIT_FAILURE);
      }
      template->word_arr[i].word = strndup(ptr + 1, space - ptr - 2);
      template->word_arr[i].blank = 1;
    }
    else {
      template->word_arr[i].word = strndup(ptr, space - ptr);
      template->word_arr[i].blank = 0;
    }
    ptr = space + 1;
    i++;
  }
  template->word_sz = i;
  free(curr);
  return template;
}
*/

/*
template_t * parseTemplate(FILE * f) {
  char * curr = NULL;
  size_t sz;
  ssize_t len = getline(&curr, &sz, f);
  if (len == -1) {
    perror("No template. \n");
    exit(EXIT_FAILURE);
  }
  template_t * template = malloc(sizeof(*template));
  template->word_arr = NULL;
  template->blank_arr = NULL;
  template->word_sz = 0;
  template->blank_sz = 0;
  size_t i = 0;
  size_t j = 0;
  //  char * str = strdup(curr);
  //char * ptr = str;
  // char * str_head = str;
  char * str = curr;
  char * ptr = curr;
  char * space;
  while ((space = strsep(&str, " ")) != NULL || (space = strsep(&str, ".")) != NULL) {
    template->word_arr =
        realloc(template->word_arr, (i + 1) * sizeof(*template->word_arr));
    if (*ptr == "_") {
      if (*(space - 1) != "_") {
        perror("Underscore does not match. \n");
        exit(EXIT_FAILURE);
      }
      template->word_arr[i] = strndup(ptr + 1, space - ptr - 2);
      template->blank_arr =
          realloc(template->blank_arr, (j + 1) * sizeof(*template->blank_arr));
      template->blank_arr[j] = i;
      j++;
    }
    else {
      template->word_arr[i] = strndup(ptr, space - ptr);
    }
    ptr = space + 1;
    i++;
  }

  template->word_sz = i;
  template->blank_sz = j;
  free(curr);
  return template;
  }
*/
