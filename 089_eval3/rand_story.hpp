#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool DEBUG = false;
//
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
  int getNum() { return num; }
  void testChoice() { cout << "Choice is: " << c << "\n"; }
  void printChoice() { cout << c << "\n"; }
};

class Page {
 private:
  int num;
  vector<string> text;
  vector<Choice *> choices;
  bool win;
  bool lose;

 public:
  Page() : num(), text(), choices(), win(false), lose(false) {}
  Page(int n, vector<string> & t, vector<Choice *> & c, bool w, bool l) :
      num(n),
      text(t),
      choices(),
      win(w),
      lose(l) {
    for (size_t i = 0; i < c.size(); i++) {
      choices.push_back(c[i]);
    }
  }
  ~Page() {
    for (int i = 0; i < getChoiceNum(); i++) {
      delete choices[i];
    }
  }
  Page & operator=(const Page & rhs) {
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
  bool getWin() const { return win; }
  bool getLose() const { return lose; }
  int getNum() const { return num; }
  vector<string> getText() const { return text; }
  int getChoiceNum() const { return choices.size(); }
  vector<Choice *> getChoice() const { return choices; }
  vector<int> getChoiceVec() {  // TODO: should be const
    vector<int> v;
    for (vector<Choice *>::iterator it = choices.begin(); it != choices.end(); ++it) {
      v.push_back((*it)->getNum());
    }
    return v;
  }
  void printText() {
    for (vector<string>::iterator it = text.begin(); it != text.end(); ++it) {
      cout << *it << "\n";
    }
  }
  void printPage() {
    //    cout << "DEBUG: " << getNum() << "\n";
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
          if (DEBUG) {
            cout << "DEBUG: "
                 << " " << i << ". "
                 << "(" << (*it)->getNum() << ")";
          }
          (*it)->printChoice();
          i++;
        }
      }  //else wrong
    }
  }
};
// ================================== step4 ================================ //
void make_path(map<int, map<int, int> > & parent, int & win);
void make_parent(map<int, vector<int> > & child, map<int, map<int, int> > & parent);
void make_child(vector<Page *> & vector_page, set<int> & reachable);

// ================================== step3 ================================ //
bool all_reachable(vector<Page *> & vector_page, set<int> & page_num, vector<int> & diff);
bool equal_set(set<int> & s1, set<int> & s2, vector<int> & diff);

// ================================== step2 ================================ //
void read_pages(string & dir,
                vector<Page *> & vector_page,
                set<int> & page_num,
                set<int> & choice_num,
                bool & page_win,
                bool & page_lose);
bool validate_page(set<int> & page_num, set<int> & choice_num, bool win, bool lose);
bool compare_set(set<int> & set1, set<int> & set2);
bool check_number(string s);
bool check_number_valid(string s, Page * p);
bool check_exit(Page * p);
void execute(vector<Page *> & page);
void free_page(vector<Page *> & page);

// ================================== step1 ================================ //
bool line_choice(const string & line);
bool validate_format(ifstream & ifs);
void parseLine(string & line,
               vector<Choice *> & vector_choice,
               vector<string> & text,
               bool & win,
               bool & lose,
               bool & pond);
