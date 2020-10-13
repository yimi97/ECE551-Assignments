#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================================== Step 3 ========================================= */
int checkExist(char * word, catarray_t * c) {
  for (size_t i = 0; i < c->n; i++) {
    if (strcmp(c->arr[i].name, word) == 0) {
      return 1;
    }
  }
  return 0;
}

void addRef(const char * word, category_t * cat) {
  cat->n_words += 1;
  cat->words = realloc(cat->words, cat->n_words * sizeof(*cat->words));
  cat->words[cat->n_words - 1] = strdup(word);
}

void freeCategory(category_t * c) {
  if (c == NULL) {
    return;
  }
  for (size_t i = 0; i < c->n_words; i++) {
    free(c->words[i]);
  }
  free(c->words);
  free(c);
}

void freeAll(char * line, FILE * f, catarray_t * cats, category_t * wordRef) {
  free(line);
  fclose(f);
  freeCatarray(cats);
  freeCategory(wordRef);
}

/* ======================================== Step 2 ========================================= */

/*
 *@a function used to free a catarray_t struct.  
 *@param c: The struct going to be freed.
 *@return void.
*/
void freeCatarray(catarray_t * c) {
  if (c == NULL) {
    return;
  }
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
    fprintf(stderr, "ERROR: No colon.\n");
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
void parseLine(FILE * f, char * line, catarray_t * cats, category_t * wordRef) {
  char * ptr = line;
  char * second;
  while (*ptr != '\0') {
    if (*ptr == '_') {
      second = strchr(ptr + 1, '_');
      if (second == NULL) {
        fprintf(stderr, "ERROR: No mathing underscore in template.\n");
        freeAll(line, f, cats, wordRef);
        exit(EXIT_FAILURE);
      }
      char newWord[second - ptr];
      for (size_t i = 0; i < second - ptr - 1; i++) {
        newWord[i] = ptr[i + 1];
      }
      newWord[second - ptr - 1] = '\0';

      //      printf("%s\n", newWord);
      int num = atoi(newWord);
      if (cats == NULL) {  // step1
        fprintf(stdout, "%s", chooseWord(newWord, NULL));
      }
      else {            // step3
        if (num > 0) {  // integer: replace word using word reference
          if (num > wordRef->n_words) {
            fprintf(stderr, "ERROR: [%d] out of range.\n", num);
            freeAll(line, f, cats, wordRef);
            exit(EXIT_FAILURE);
          }
          char * replace = wordRef->words[wordRef->n_words - num];
          fprintf(stdout, "%s", replace);
          addRef(replace, wordRef);
        }
        else {  // category: replace word using chooseWord()
          if (checkExist(newWord, cats) == 1) {  // if exit word
            const char * replace = chooseWord(newWord, cats);
            fprintf(stdout, "%s", replace);
            addRef(replace, wordRef);
          }
          else {
            fprintf(stderr, "ERROR: [%s] is not an integer or category.\n", newWord);
            freeAll(line, f, cats, wordRef);
            exit(EXIT_FAILURE);
          }
        }
      }
      // fprintf(stdout, "%s", chooseWord(newWord, cats)); // step1 init
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
  //
  category_t * wordRef = malloc(sizeof(*wordRef));
  wordRef->n_words = 0;
  wordRef->words = NULL;
  //
  while (getline(&curr, &sz, f) >= 0) {
    parseLine(f, curr, cats, wordRef);
    free(curr);
    curr = NULL;
  }
  free(curr);
  freeCategory(wordRef);
}
