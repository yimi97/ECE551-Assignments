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
//unsigned * substring(unsigned * array, size_t start, size_t sub_length, size_t n){
//unsigned * sub_arr[sub_length];
//for(size_t i =0;i<sub_length;i++){
//sub_arr[i] = array[i+start];
//}
//}

double cal_avg(unsigned * array, size_t n, unsigned * start, size_t days) {
  int sum = 0;
  for (int i = 0; i < days; i++) {
    sum += *start;
    start++;
  }
  double avg = (double)sum / days;
  return avg;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  unsigned * ptr = data;
  double average;
  int cycle = 0;
  for (int i = 0; i < n_days; i += 7) {
    if (n_days - i < 7) {
      average = cal_avg(data, n_days, ptr, n_days - i);
      cycle = n_days / 7;
      avg[cycle] = average;
      break;
    }
    else {
      average = cal_avg(data, n_days, ptr, 7);
      ptr += 7;
      cycle = i / 7;
      avg[cycle] = average;
    }
  }
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
