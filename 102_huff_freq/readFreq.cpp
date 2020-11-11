#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream ifs;
  ifs.open(fname, std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "Fail to open the file\n"
              << "\n";
  }
  uint64_t * res = new uint64_t[257]();
  int c;
  while ((c = ifs.get()) != EOF) {
    res[c]++;
  }
  res[256]++;
  ifs.close();
  return res;
}
