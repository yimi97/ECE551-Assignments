#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================================== Step 4 ========================================= */

/*
 *@a function used to remove the word used from catarray_t. 
 *@param cats: A pointer pointing to the catarray_t struct.
 *@param newWord: A pointer pointing to the replaced word string.
 *@param replace: A pointer pointing to the replacing word string.
 *@return void.
*/
void removeWord(catarray_t * cats, char * newWord, const char * replace) {
  for (size_t i = 0; i < cats->n; i++) {
    // find category name
    if (strcmp(cats->arr[i].name, newWord) == 0) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        // find replaced word
        if (strcmp(cats->arr[i].words[j], replace) == 0) {
          free(cats->arr[i].words[j]);
          for (size_t k = j; k < cats->arr[i].n_words - 1; k++) {
            cats->arr[i].words[k] = cats->arr[i].words[k + 1];
          }
          cats->arr[i].n_words -= 1;
          // if no words exists in this category
          // if (cats->arr[i].n_words == 0) {
          // printf("no words!!!\n");
          //}
          cats->arr[i].words = realloc(
              cats->arr[i].words, cats->arr[i].n_words * sizeof(*cats->arr[i].words));
          return;
        }
      }
    }
  }
}

/* ======================================== Step 3 ========================================= */

/*
 *@a function used to replace the blanks with words. 
 *@param newWord: A pointer pointing to the word string waiting to be replaces.
 *@param f: A pointer pointing to the file need to be closed.
 *@param line: A pointer pointing to the line read by getline().
 *@param cats: A pointer pointing to the catarray_t struct.
 *@param wordRef: A pointer pointing to the category_t struct used to record word reference.
 *@param noUsed: A int used to check if we can use the used words.
 *@return void.
*/
void replaceWord(char * newWord,
                 FILE * f,
                 char * line,
                 catarray_t * cats,
                 category_t * wordRef,
                 int noUsed) {
  int num = atoi(newWord);
  if (num > 0) {  // integer: replace word using word reference
    if (num > wordRef->n_words) {
      fprintf(stderr, "ERROR: [%d] is out of range.\n", num);
      freeAll(line, f, cats, wordRef);
      exit(EXIT_FAILURE);
    }
    char * replace = wordRef->words[wordRef->n_words - num];
    fprintf(stdout, "%s", replace);
    addRef(replace, wordRef);
  }
  else {                                   // category: replace word using chooseWord()
    if (checkExist(newWord, cats) == 1) {  // if word exists
      const char * replace = chooseWord(newWord, cats);
      fprintf(stdout, "%s", replace);
      addRef(replace, wordRef);
      if (noUsed == 1) {
        removeWord(cats, newWord, replace);
      }
    }
    else {
      fprintf(stderr, "ERROR: [%s] is not an integer or category.\n", newWord);
      freeAll(line, f, cats, wordRef);
      exit(EXIT_FAILURE);
    }
  }
}

/*
 *@a function used to check if the word inside the catarray. 
 *@param word: A pointer pointing to the word string.
 *@param cats: A pointer pointing to the catarray_t struct.
 *@return int: if exists return 1, otherwise return 0.
*/
int checkExist(char * word, catarray_t * c) {
  for (size_t i = 0; i < c->n; i++) {
    if (strcmp(c->arr[i].name, word) == 0 && c->arr[i].n_words > 0) {
      return 1;
    }
  }
  return 0;
}

/*
 *@a function used to add the word into word reference.  
 *@param word: A pointer pointing to the word string.
 *@param cats: A pointer pointing to the category_t struct.
 *@return void.
*/
void addRef(const char * word, category_t * cat) {
  cat->n_words += 1;
  cat->words = realloc(cat->words, cat->n_words * sizeof(*cat->words));
  cat->words[cat->n_words - 1] = strdup(word);
}
/*
 *@a function used to free a category_t struct.
 *@param cats: A pointer pointing to the category_t struct.
 *@return void.
*/
void freeCategory(category_t * c) {
  if (c == NULL) {
    return;
  }
  if (c->name != NULL) {
    free(c->name);
  }
  for (size_t i = 0; i < c->n_words; i++) {
    free(c->words[i]);
  }
  free(c->words);
  free(c);
}

/*
 *@a function used to free several kinds of memory blocks while encountering an error.  
 *@param line: A pointer pointing to the line read by getline().
 *@param f: A pointer pointing to the file need to be closed.
 *@param cats: A pointer pointing to the catarray_t struct.
 *@param wordRef: A pointer pointing to the category_t struct used to record word reference.
 *@return void.
*/
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
 *@param wordRef: A pointer pointing to a category_t sturct, storing words used.
 *@param noUsed: An integer used to check if we can use the used words.
 *@return void.
*/
void parseLine(FILE * f,
               char * line,
               catarray_t * cats,
               category_t * wordRef,
               int noUsed) {
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

      if (cats == NULL) {  // step1
        fprintf(stdout, "%s", chooseWord(newWord, NULL));
      }
      else {  // step3
        replaceWord(newWord, f, line, cats, wordRef, noUsed);
      }
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
 *@param noUsed: An integer used to check if we can use the used words.
 *@return void.
*/
void parseTemplate(FILE * f, catarray_t * cats, int noUsed) {
  char * curr = NULL;
  size_t sz;
  // init a word reference to store the words usef previously
  category_t * wordRef = malloc(sizeof(*wordRef));
  wordRef->n_words = 0;
  wordRef->words = NULL;
  wordRef->name = NULL;
  while (getline(&curr, &sz, f) >= 0) {
    parseLine(f, curr, cats, wordRef, noUsed);
    free(curr);
    curr = NULL;
  }
  free(curr);
  freeCategory(wordRef);
}
