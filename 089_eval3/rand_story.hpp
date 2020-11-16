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
//using namespace std;

bool DEBUG = false;

class Choice {
 private:
  int num;
  std::string c;

 public:
  Choice() : num(0), c(NULL){};
  Choice(int n, std::string str) : num(n), c(str) {}
  ~Choice(){};
  Choice & operator=(const Choice & rhs) {
    if (this != &rhs) {
      num = rhs.num;
      c = rhs.c;
    }
    return *this;
  }
  int getNum() const { return num; }
  void testChoice() const { std::cout << "Choice is: " << c << "\n"; }
  void printChoice() const { std::cout << c << "\n"; }
};

class Page {
 private:
  int num;
  std::vector<std::string> text;
  std::vector<Choice *> choices;
  bool win;
  bool lose;

 public:
  Page() : num(), text(), choices(), win(false), lose(false) {}
  Page(int n, std::vector<std::string> & t, std::vector<Choice *> & c, bool w, bool l) :
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
  std::vector<std::string> getText() const { return text; }
  int getChoiceNum() const { return choices.size(); }
  std::vector<Choice *> getChoice() const { return choices; }
  std::vector<int> getChoiceVec() const {  // TODO: should be const
    std::vector<int> v;
    for (std::vector<Choice *>::const_iterator it = choices.begin(); it != choices.end();
         ++it) {
      v.push_back((*it)->getNum());
    }
    return v;
  }
  void printText() const {
    for (std::vector<std::string>::const_iterator it = text.begin(); it != text.end();
         ++it) {
      std::cout << *it << "\n";
    }
  }
  void printPage() const {
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
};
// ================================== step4 ================================ //
void make_path(std::map<int, std::map<int, int> > & parent, int & win);
void make_parent(std::map<int, std::vector<int> > & child,
                 std::map<int, std::map<int, int> > & parent);
void make_child(std::vector<Page *> & vector_page, std::set<int> & reachable);

// ================================== step3 ================================ //
bool all_reachable(std::vector<Page *> & vector_page,
                   std::set<int> & page_num,
                   std::vector<int> & diff);
bool equal_set(std::set<int> & s1, std::set<int> & s2, std::vector<int> & diff);

// ================================== step2 ================================ //
void read_pages(std::string & dir,
                std::vector<Page *> & vector_page,
                std::set<int> & page_num,
                std::set<int> & choice_num,
                bool & page_win,
                bool & page_lose);
bool validate_page(std::set<int> & page_num,
                   std::set<int> & choice_num,
                   bool win,
                   bool lose);
bool compare_set(std::set<int> & set1, std::set<int> & set2);
bool check_number(std::string s);
bool check_number_valid(std::string s, Page * p);
bool check_exit(Page * p);
void execute(std::vector<Page *> & page);
void free_page(std::vector<Page *> & page);

// ================================== step1 ================================ //
bool line_choice(const std::string & line);
bool validate_format(std::ifstream & ifs);
void parseLine(std::string & line,
               std::vector<Choice *> & vector_choice,
               std::vector<std::string> & text,
               bool & win,
               bool & lose,
               bool & pond);
