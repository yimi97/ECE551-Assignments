#include "choice.hpp"

Choice & Choice::operator=(const Choice & rhs) {
  if (this != &rhs) {
    num = rhs.num;
    c = rhs.c;
  }
  return *this;
}
