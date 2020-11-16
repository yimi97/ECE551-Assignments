#include "page.hpp"

Page::Page(int n,
           std::vector<std::string> & t,
           std::vector<Choice *> & c,
           bool w,
           bool l) :
    num(n),
    text(t),
    choices(),
    win(w),
    lose(l) {
  for (size_t i = 0; i < c.size(); i++) {
    choices.push_back(c[i]);
  }
}

Page::~Page() {
  for (int i = 0; i < getChoiceNum(); i++) {
    delete choices[i];
  }
}

Page & Page::operator=(const Page & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < getChoiceNum(); i++) {
      delete choices[i];
    }
    num = rhs.getNum();  //private??? rhs.num; or rhs.getNum();?
    text = rhs.getText();
    win = rhs.getWin();
    lose = rhs.getLose();
    for (int i = 0; i < rhs.getChoiceNum(); i++) {
      choices.push_back(rhs.getChoice()[i]);
    }
  }
  return *this;
}

std::vector<int> Page::getChoiceVec() const {
  std::vector<int> v;
  for (std::vector<Choice *>::const_iterator it = choices.begin(); it != choi\
ces.end();
       ++it) {
    v.push_back((*it)->getNum());
  }
  return v;
}

void Page::printText() const {
  for (std::vector<std::string>::const_iterator it = text.begin(); it != text.end();
       ++it) {
    std::cout << *it << "\n";
  }
}

void Page::printPage() const {
  printText();
  if (win) {
    std::cout << "\n"
              << "Congratulations! You have won. Hooray!\n";
  }
  else if (lose) {
    std::cout << "\n";
    std::cout << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    std::cout << "\n"
              << "What would you like to do?\n\n";
    if (!choices.empty()) {
      int i = 1;
      for (std::vector<Choice *>::const_iterator it = choices.begin();
           it != choices.end();
           ++it) {
        std::cout << " " << i << ". ";
        if (DEBUG) {
          std::cout << "DEBUG: "
                    << " " << i << ". "
                    << "(" << (*it)->getNum() << ")";
        }
        (*it)->printChoice();
        i++;
      }
    }  //else wrong
  }
}
