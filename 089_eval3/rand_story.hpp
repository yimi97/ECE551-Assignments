#include <iostream>
#include <string>
#include <vector>
class Choice {
 private:
  int num;
  const char * c;

 public:
  Choice() : num(0), c(NULL){};
  Choice(std::string line) {
    std::size_t pos = line.find(':');
    std::string n = line.substr(0, pos - '0');
    c = (line.substr(pos)).c_str();
    num = std::atoi(n);
  }
  ~Choice(){};
};

class Page {
 private:
  const char * text;
  std::vector<Choice> * choices;
  bool win;
  bool lose;

 public:
  Page() : text(NULL), choices(NULL), win(false), lose(false) {}
  Page(const char * t, std::vector<Choice> * c, bool w, bool l) :
      text(t),
      choices(c),
      win(w),
      lose(l) {}
  ~Page() {}
};
