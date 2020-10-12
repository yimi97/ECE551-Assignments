#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================================== Step 3 ========================================= */

/*
int pre = atoi(word);
if (pre > 0){findRef}
else {cw=chooseWord(), addRef}
*/

/* ======================================== Step 2 ========================================= */

/*
 *@a function used to free a catarray_t struct.  
 *@param c: The struct going to be freed.
 *@return void.
*/
void freeCatarray(catarray_t * c) {
  for (size_t i = 0; i < c->n; i++) {
    free(c->arr[i].name);
    for (size_t j = 0; j < c->arr[i].n_words; j++) {
      free(c->arr[i].words[j]);
    }
    free(c->arr[i].words);
  }
  free(c->arr);
  free(c);
}

/*
 *@a function used to parse and store each line from word input file.  
 *@param f: The file read, in case we have to close it.
 *@param catarray : A pointer pointing to a cataray_t created before. 
 *@param curr : A pointer pointing to each line from getline().
 *@return void.
*/
void addWord(FILE * f, catarray_t * catarray, char * curr) {
  char * colon = strchr(curr, ':');
  if (colon == NULL) {
    fprintf(stderr, "No colon.\n");
    free(curr);
    freeCatarray(catarray);
    fclose(f);
    exit(EXIT_FAILURE);
  }
  char * cat = strndup(curr, colon - curr);
  char * w = strndup(colon + 1, strlen(curr) - (colon - curr + 1));
  char * ptr = w;
  // remove '\n'
  while (*ptr != '\0' && *ptr != '\n') {
    ptr++;
  }
  *ptr = '\0';
  int exist = 0;  // used to check if the newly parsed cat is already stored before
  for (size_t i = 0; i < catarray->n; i++) {
    // if the cat is inside our array, store the word into its struct
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
  // if not, create a new category struct, store cat and word, resize arr
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

/*
 *@a function used to read word input file and add words.  
 *@param f : A word input file containing cat:word lines. 
 *@return catarray_t.
*/
catarray_t * parseWord(FILE * f) {
  char * curr = NULL;
  size_t sz;
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  while (getline(&curr, &sz, f) >= 0) {
    // parse and add words to catarray
    addWord(f, catarray, curr);
    curr = NULL;
  }
  free(curr);
  return catarray;
}

/* ======================================== Step 1 ========================================= */

/*
 *@a function used to parse each line from story template file and print.  
 *@param f: The file read, in case we have to close it.
 *@param line : A pointer pointing to a each line from getline() inside parseTemplate. 
 *@param cat : A pointer pointing to a catarray_t struct storing cat and words.
 *@return void.
*/
void parseLine(FILE * f, char * line, catarray_t * cats) {
  char * ptr = line;
  char * second;
  while (*ptr != '\0') {
    if (*ptr == '_') {
      second = strchr(ptr + 1, '_');
      if (second == NULL) {
        //free
        free(line);
        fclose(f);
        fprintf(stderr, "ERROR: No mathing underscore in template.\n");
        exit(EXIT_FAILURE);
      }
      char newWord[second - ptr];
      for (size_t i = 0; i < second - ptr - 1; i++) {
        newWord[i] = ptr[1];
      }
      newWord[second - ptr - 1] = '\0';
      fprintf(stdout, "%s", chooseWord(newWord, cats));
      ptr = second + 1;
    }
    else {
      fprintf(stdout, "%c", *ptr);
      ptr++;
    }
  }
}

/*
 *@a function used to read and parse a story template file.  
 *@param f : A story template file. 
 *@param cats : A pointer pointing to a catarray_t struct storing cat and words.
 *@return void.
*/
void parseTemplate(FILE * f, catarray_t * cats) {
  char * curr = NULL;
  size_t sz;
  while (getline(&curr, &sz, f) >= 0) {
    parseLine(f, curr, cats);
    free(curr);
    curr = NULL;
  }
  free(curr);
}
