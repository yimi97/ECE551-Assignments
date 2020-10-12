#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int pre = atoi(word);
if (pre > 0){findRef}
else {cw=chooseWord(), addRef}
*/

/*
 *@a function used to parse and store each line from word input file.  
 *@param catarray : A pointer pointing to a cataray_t created before. 
 *@param curr : A pointer pointing to each line from getline().
 *@return void.
*/
void addWord(catarray_t * catarray, char * curr) {
  char * colon = strchr(curr, ':');
  if (colon == NULL) {
    printf("No colon.\n");
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
    addWord(catarray, curr);
    curr = NULL;
  }
  free(curr);
  return catarray;
}

/*
 *@a function used to parse each line from story template file.  
 *@param line : A pointer pointing to a each line from getline() inside parseTemplate. 
 *@param cat : A pointer pointing to a catarray_t struct storing cat and words.
 *@return char* : A pointer pointing to the line parsed.
*/
char * parseLine(char * line, catarray_t * cats) {
  char * head = line;
  char *start, *end;           // start underscore and end undersocre
  char word[50];               // a buffer used to store a replaced word
  char buffer[strlen(line)];   // a buffer used to store a slicing str from head to start
  char res[3 * strlen(line)];  // a buffer to store the result
  *res = '\0';
  start = strchr(head, '_');
  while (start != NULL) {  // keep finding underSocre
    end = strchr(start + 1, '_');
    if (end == NULL) {
      printf("No mataching underscore.\n");
      exit(EXIT_FAILURE);
    }
    strncpy(buffer, head, start - head);
    buffer[start - head] = '\0';  // strncpy is not null-terminated
    strncpy(word, start + 1, end - start - 1);
    word[end - start - 1] = '\0';
    strcat(buffer, chooseWord(word, cats));  // do wee need to free chooseword? why not?
    strcat(res, buffer);
    head = end + 1;
    start = strchr(head, '_');
  }
  // concatenate the rest part to the result
  strcat(res, head);
  char * str = strdup(res);
  return str;
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
