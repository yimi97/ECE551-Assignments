#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance;
  balance = initial;
  for (int mo = 0; mo < working.months; mo++) {
    int age = startAge / 12;
    int month = startAge % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance += balance * working.rate_of_return + working.contribution;
    startAge++;
  }
  for (int mo = 0; mo < retired.months; mo++) {
    int age = startAge / 12;
    int month = startAge % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balance);
    balance += balance * retired.rate_of_return + retired.contribution;
    startAge++;
  }
}

//double calculate(int age, retire_info info, double balance) {
//}

int main(void) {
  retire_info working;
  retire_info retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return EXIT_SUCCESS;
}
