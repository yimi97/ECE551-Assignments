#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
// Step 4
void removeWord(catarray_t * cats, char * newWord, const char * replace);

// Step 3
void replaceWord(char * newWord,
                 FILE * f,
                 char * line,
                 catarray_t * cats,
                 category_t * wordRef,
                 int noUsed);
int checkExist(char * word, catarray_t * c);
void addRef(const char * word, category_t * cat);
void freeCategory(category_t * c);
void freeAll(char * line, FILE * f, catarray_t * cats, category_t * wordRef);

// Step 2
void freeCatarray(catarray_t * c);
void addWord(FILE * f, catarray_t * catarray, char * curr);
catarray_t * parseWord(FILE * f);

// Step1
void parseLine(FILE * f,
               char * line,
               catarray_t * cats,
               category_t * wordRef,
               int noUsed);
void parseTemplate(FILE * f, catarray_t * cats, int noUsed);
#endif
