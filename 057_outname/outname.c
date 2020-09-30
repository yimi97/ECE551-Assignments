#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * count = ".counts";
  size_t length = strlen(inputName) + strlen(count);
  char inputCopy[length + 1];    // +1 for '\0'
  strcpy(inputCopy, inputName);  // will auto add '\0'?
  strcat(inputCopy, count);      // will auto start from '\0' and add '\0' at the end.

  char * newName = malloc((length + 1) * sizeof(*newName));
  for (size_t i = 0; i < length + 1; i++) {
    newName[i] = inputCopy[i];
  }

  return newName;
}
