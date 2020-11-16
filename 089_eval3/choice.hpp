#ifndef __CHOICE_HPP__
#define __CHOICE_HPP__

#include "headers.hpp"
class Choice {
 private:
  int num;
  std::string c;

 public:
  Choice() : num(0), c(NULL) {}
  Choice(int n, std::string str) : num(n), c(str) {}
  ~Choice() {}
  Choice & operator=(const Choice & rhs);
  int getNum() const { return num; }
  void testChoice() const { std::cout << "Choice is: " << c << "\n"; }
  void printChoice() const { std::cout << c << "\n"; }
};

#endif
