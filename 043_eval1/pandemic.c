#include "pandemic.h"

#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  if (line == NULL) {
    // error msg
    exit(EXIT_FAILURE);
  }

  // if wrong type, error msg

  country_t ans;
  // ans.name[0] = '\0';
  // ans.population = 0;
  char * ptr = line;
  char pop[100];
  char myname[64];
  int i = 0;
  while (*ptr != ',') {
    myname[i] = *ptr;
    ptr++;
    i++;
  }
  myname[i] = '\0';
  ptr++;
  i = 0;
  while (*ptr != '\0') {
    pop[i] = *ptr;
    ptr++;
    i++;
  }

  // ans.name = myname;
  strcpy(ans.name, myname);
  ans.population = atoi(pop);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
