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
void parseLine(FILE * f, char * line, catarray_t * cats);

#endif
