#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * @a funtion used to parse a string line to country name and population.
 * @param line : A string need to be parsed.
 * @return country_t.          
 */
country_t parseLine(char * line) {
  // Check first if the pointer pointing to NULL.
  if (line == NULL) {
    printf("Parseline: This line is NULL.\n");
    exit(EXIT_FAILURE);
  }
  if (strchr(line, ',') == NULL) {
    printf("Parseline: No comma. Not correct format.");
    exit(EXIT_FAILURE);
  }
  country_t ans;
  char * ptr = line;
  char pop[100];
  char myname[64];
  int i = 0;  // An index indicating the ith element in myname and pop array.
  // Check if the first chr is comma.
  while (*ptr == ' ') {
    ptr++;
  }
  // Start to record each name char.
  while (*ptr != ',') {
    myname[i] = *ptr;
    ptr++;
    i++;
  }
  if ((i == 0) || (*line == ',')) {
    printf("Parseline: There is no country name information.\n");
    exit(EXIT_FAILURE);
  }
  myname[i] = '\0';
  // Spik the comma.
  ptr++;
  int j = 0;
  if (*ptr == '\0') {
    printf("Parseline: There is no population information");
    exit(EXIT_FAILURE);
  }
  // Start to record each number char.
  while (*ptr != '\0') {
    // Check if the char is punctuation or english letter or space. If yes, exit.
    if (ispunct(*ptr) || isalpha(*ptr)) {
      printf("Parseline: There is non-number inside population.");
      exit(EXIT_FAILURE);
    }
    // Check if there is space inside the number.
    if ((j != 0) && *ptr == ' ') {
      printf("Parseline: There is space inside the number.\n");
      exit(EXIT_FAILURE);
    }
    // If not a space, keep Adding to the pop array.
    if (*ptr != ' ') {
      pop[j] = *ptr;
      j++;
    }
    ptr++;
  }
  // Check if there is no numbers.
  if (j == 0) {
    printf("Parseline: There is no population information.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(ans.name, myname);
  ans.population = atoi(pop);
  return ans;
}

/**
 * @a funtion used to calculate seven-day running average of case data.
 * @param data An array of daily case data.
 * @param n_days The number of days over which the data is measured.
 * @param avg An array of numbers to hold the running average, which should be n_days-7.
 * @return void.          
 */
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  unsigned * start = data;
  unsigned * move;  // A pointer moving from the start date to the seven days behind.
  double average;
  unsigned sum = 0;
  // The length of avg should be n_days-6.
  for (int i = 0; i < n_days - 6; i++) {
    move = start;
    // Move the pointer to get the sum number of cases of seven days.
    for (int j = i; j < i + 7; j++) {
      sum += *move;
      move++;
    }
    average = (double)sum / 7;
    sum = 0;
    avg[i] = average;
    start++;
  }
}

/**
 * @a funtion used to calculate the cumulative number of cases that day per 100,000 people.
 * @param data : An array of daily case data.
 * @param n_days : The number of days over which the data is measured.
 * @param pop : The population of that country.
 * @param cum: An array of doubles cum.
 * @return void.          
 */
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  unsigned * ptr = data;
  unsigned cumulative = 0;
  // Move the ptr to calculate cumulative cases.
  for (int i = 0; i < n_days; i++) {
    cumulative += *ptr;
    cum[i] = (double)cumulative * 100000 / pop;
    ptr++;
  }
}

/**
 * @a funtion used to find the maximum number of daily cases of all countries.
 * @param data : A 2-D array which holds each country's data.
 * @param n_countries: The number of the countries.
 * @param countries: An array of country_t. 
 * @param n_days: The number of days.
 * @return void.          
 */
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned max_cases = 0;  // Store the max cases.
  int country_i;           // Store the country index with the max cases.
  // Iterate the data array.
  for (int i = 0; i < n_countries; i++) {
    for (int j = 0; j < n_days; j++) {
      // Compare the data with max_cases and replace to the max one.
      if (data[i][j] > max_cases) {
        country_i = i;
        max_cases = data[i][j];
      }
    }
  }
  country_t * ptr = countries + country_i;
  printf("%s has the most daily cases with %u\n", ptr->name, max_cases);
}
