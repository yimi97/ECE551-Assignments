
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
#include "search.cpp"
//int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class NegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class PosFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }
};

class LinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned max_num;
  if (high > low) {
    max_num = log2(high - low) + 1;
  }
  else {
    max_num = 1;
  }
  CountedIntFn * c = new CountedIntFn(max_num, f, mesg);
  int ans = binarySearchForZero(c, low, high);
  if (expected_ans != ans) {
    std::cerr << mesg << "\n";
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  SinFunction * sf = new SinFunction();
  PosFunction * pf = new PosFunction();
  NegFunction * nf = new NegFunction();
  LinFunction * lf = new LinFunction();
  check(sf, 0, 150000, 52359, "SinFunction");
  check(pf, 1, 15, 1, "Pos / pos range");
  check(pf, -15, -1, -15, "Pos / neg range");
  check(pf, -15, 15, -15, "Pos / cross range");
  check(nf, 1, 15, 14, "Neg / pos range");
  check(nf, -15, -1, -2, "Neg / neg range");
  check(nf, -15, 15, 14, "Neg / cross range");
  check(lf, 1, 100, 1, "Lin / pos range");
  check(lf, -100, -1, -2, "Lin / neg range");
  check(lf, -100, 100, 0, "Lin / cross range");
  check(lf, -1, 10, 0, "Lin / cross range 2");  // ?
  return EXIT_SUCCESS;
}
