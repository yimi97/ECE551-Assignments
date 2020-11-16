
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

bool DEBUG = false;

class Choice {
 private:
  int num;        // the number of a choice
  std::string c;  // the text of a choice

 public:
  Choice() : num(0), c(NULL) {}
  Choice(int n, std::string str) : num(n), c(str) {}
  ~Choice() {}
  Choice & operator=(const Choice & rhs);
  // return the number of the choice
  int getNum() const { return num; }
  // print the choice text with prefix, used for debug
  void testChoice() const { std::cout << "Choice is: " << c << "\n"; }
  // print the choice text
  void printChoice() const { std::cout << c << "\n"; }
};

class Page {
 private:
  int num;                        // the number of the page
  std::vector<std::string> text;  // the text of the page
  std::vector<Choice *> choices;  // the vector of choice of the page
  bool win;                       // the win flag
  bool lose;                      // the lose flag

 public:
  Page() : num(), text(), choices(), win(false), lose(false) {}
  Page(int n, std::vector<std::string> & t, std::vector<Choice *> & c, bool w, bool l);
  ~Page();
  Page & operator=(const Page & rhs);
  // return win flag
  bool getWin() const { return win; }
  // return lose flag
  bool getLose() const { return lose; }
  // return page number
  int getNum() const { return num; }
  // return page text
  std::vector<std::string> getText() const { return text; }
  // return how many numbers hold by the page
  int getChoiceNum() const { return choices.size(); }
  // return the choice vector
  std::vector<Choice *> getChoice() const { return choices; }
  // return the vector of choice number
  std::vector<int> getChoiceVec() const;
  // print the text, used for debug
  void printText() const;
  // print the whole page
  void printPage() const;
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

bool validate_format(std::ifstream & ifs, std::vector<std::string> & myfile);
int line_choice(const std::string & line);
bool validate_format(std::ifstream & ifs);
void parseLine(std::string & line,
               std::vector<Choice *> & vector_choice,
               std::vector<std::string> & text,
               bool & win,
               bool & lose,
               bool & pond);
