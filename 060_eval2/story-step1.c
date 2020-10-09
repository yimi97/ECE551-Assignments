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
  template_t * template = parseTemplate(f);
  char printStr[1000] = {0};
  /*  for (size_t i=0;i<template->blank_sz;i++){
    template->word_arr[template->blank_arr[i]]
    }*/
  //size_t b = template->blank_arr[0]; // b must exist?
  for (size_t i = 0; i < template->word_sz; i++) {
    printf("%s\n", template->word_arr[i].word);
    if (template->word_arr[i].blank == 1) {
      strcat(printStr, chooseWord(template->word_arr[i].word, NULL));
    }
    else {
      strcat(printStr, template->word_arr[i].word);
    }
    strcat(printStr, " ");
  }
  printStr[strlen(printStr) - 1] = '.';
  fprintf(stdout, "%s\n", printStr);
  for (size_t j = 0; j < template->word_sz; j++) {
    free(template->word_arr[j].word);
  }
  free(template->word_arr);
  free(template);
  if (fclose(f) != 0) {
    perror("Failed to close the input file. \n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}