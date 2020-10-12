#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// Step 2
void freeCatarray(catarray_t * c);
void addWord(FILE * f, catarray_t * catarray, char * curr);
catarray_t * parseWord(FILE * f);

// Step1
void parseTemplate(FILE * f, catarray_t * cats);
char * parseLine(FILE * f, char * line, catarray_t * cats);

struct word_tag {
  char * word;
  int blank;
};

typedef struct word_tag word_t;

struct template_tag {
  word_t * word_arr;
  //  char ** word_arr;
  //  size_t * blank_arr;
  size_t word_sz;
  //  size_t blank_sz;
};

typedef struct template_tag template_t;

//template_t * parseTemplate(FILE * f);

#endif
