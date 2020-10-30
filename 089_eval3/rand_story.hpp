#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Choice {
 private:
  int num;
  string c;

 public:
  Choice() : num(0), c(NULL){};
  Choice(int n, string str) : num(n), c(str) {}
  ~Choice(){};
  Choice & operator=(const Choice & rhs) {
    if (this != &rhs) {
      num = rhs.num;
      c = rhs.c;
    }
    return *this;
  }
  void testNum() { cout << "Choice number is: " << num << "\n"; }
  void testChoice() { cout << "Choice is: " << c << "\n"; }
  void printChoice() { cout << c << "\n"; }
};

class Page {
 private:
  vector<string> text;
  vector<Choice *> choices;
  //string comment;
  bool win;
  bool lose;

 public:
  Page() : text(), choices(), win(false), lose(false) {}
  Page(vector<string> & t, vector<Choice *> & c, bool w, bool l) :
      text(t),
      choices(),
      win(w),
      lose(l) {
    for (size_t i = 0; i < c.size(); i++) {
      choices.push_back(c[i]);
    }
  }
  ~Page() {
    for (size_t i = 0; i < choices.size(); i++) {
      delete choices[i];
    }
  }
  void printText() {
    for (vector<string>::iterator it = text.begin(); it != text.end(); ++it) {
      cout << *it << "\n";
    }
  }
  void printPage() {
    printText();
    if (win) {
      cout << "\n";
      cout << "Congratulations! You have won. Hooray!\n";
    }
    else if (lose) {
      cout << "\n";
      cout << "Sorry, you have lost. Better luck next time!\n";
    }
    else {
      cout << "\n"
           << "What would you like to do?\n\n";
      if (!choices.empty()) {
        int i = 1;
        for (vector<Choice *>::iterator it = choices.begin(); it != choices.end(); ++it) {
          cout << " " << i << ". ";
          (*it)->printChoice();
          i++;
        }
      }  //else wrong
    }
  }
};

void parseLine(string & line,
               vector<Choice *> & vector_choice,
               vector<string> & text,
               bool & win,
               bool & lose) {
  // choice / win / lose / # / text
  // remember to check error!
  if ((line.find(':') != string::npos) && isdigit(line[0])) {
    //found a choice
    size_t pos = line.find(':');
    string n = line.substr(0, pos);
    //size_t dot = line.find('.');
    //  string c = line.substr(pos + 1, dot - pos - 1);
    string c = line.substr(pos + 1);
    Choice * cho = new Choice(atoi(n.c_str()), c);
    vector_choice.push_back(cho);
  }
  else if (line.find("WIN") == 0) {
    win = true;
  }
  else if (line.find("LOSE") == 0) {
    lose = true;
  }
  else if (line.find('#') == 0) {
    return;
  }
  else {
    text.push_back(line);
  }
}
