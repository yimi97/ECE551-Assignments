#include "rand_story.hpp"
using namespace std;
bool DEBUG = false;

bool validate_page(set<int> & page_num, set<int> & choice_num, bool win, bool lose);
bool compare_set(set<int> & set1, set<int> & set2);
bool check_number(string s);
bool check_number_valid(string s, Page * p);
bool check_exit(Page * p);
void execute(vector<Page *> & page);
void free_page(vector<Page *> & page);

int main(int argc, char ** argv) {
  ifstream ifs;
  string page1 = argv[1];
  page1.append("/page1.txt");
  if (DEBUG)
    cout << "DEBUG: page1 is " << page1 << endl;
  ifs.open(page1.c_str(), ifstream::in);
  if (ifs.fail()) {
    cerr << "ERROR: Cannot open page1.\n";
    exit(EXIT_FAILURE);
  }
  ifs.close();
  string dir = argv[1];
  dir.append("/page");
  int i = 1;
  set<int> page_num;
  set<int> choice_num;
  bool page_win = false;
  bool page_lose = false;
  vector<Page *> vector_page;
  while (true) {
    string page = dir;
    stringstream ss;
    ss << i;
    page.append(ss.str()).append(".txt");
    //
    ifs.open(page.c_str(), ifstream::in);
    if (ifs.fail()) {
      if (DEBUG)
        cout << "DEBUG: read until " << page << endl;
      break;
    }
    string line;
    vector<Choice *> vector_choice;
    vector<string> text;
    bool WIN = false;
    bool LOSE = false;
    while (getline(ifs, line)) {
      parseLine(line, vector_choice, text, WIN, LOSE);
    }
    ifs.close();
    Page * p = new Page(i, text, vector_choice, WIN, LOSE);
    if (p->getWin()) {
      page_win = true;
    }
    if (p->getLose()) {
      page_lose = true;
    }
    vector_page.push_back(p);
    page_num.insert(i);
    for (size_t j = 0; j < vector_choice.size(); j++) {
      choice_num.insert(vector_choice[j]->getNum());
    }
    i++;
  }
  if (!validate_page(page_num, choice_num, page_win, page_lose)) {
    cerr << "ERROR: pages are not valid!\n";
    exit(EXIT_FAILURE);
  }
  else {
    if (DEBUG)
      cout << "DEBUG: pages are valid.\n";
    execute(vector_page);
  }
  return EXIT_SUCCESS;
}

void execute(vector<Page *> & page) {
  Page * p = page[0];
  while (true) {
    p->printPage();
    if (check_exit(p)) {
      if (DEBUG)
        cout << "DEBUG: exit successfully.\n";
      free_page(page);
      exit(EXIT_SUCCESS);
    }
    string s;
    while (true) {
      getline(cin, s);
      if (check_number_valid(s, p)) {
        int c = atoi(s.c_str());
        int pageNum = p->getChoice()[c - 1]->getNum();
        p = page[pageNum - 1];
        break;
      }
      else {
        cout << "This is not a valid choice, please try again\n";
      }
    }
  }
}

void free_page(vector<Page *> & page) {
  for (size_t i = 0; i < page.size(); i++) {
    delete page[i];
  }
}
bool check_number(string s) {
  string::iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) {
    ++it;
  }
  return !s.empty() && it == s.end();
}

bool check_number_valid(string s, Page * p) {
  if (!check_number(s)) {
    return false;
  }
  int c = atoi(s.c_str());
  if (c >= 1 && c <= p->getChoiceNum()) {
    return true;
  }
  else {
    return false;
  }
}

bool check_exit(Page * p) {
  if (p->getWin() || p->getLose()) {
    return true;
  }
  return false;
}

bool validate_page(set<int> & page_num, set<int> & choice_num, bool win, bool lose) {
  if (compare_set(page_num, choice_num) && win && lose) {
    return true;
  }
  return false;
}

bool compare_set(set<int> & set1, set<int> & set2) {
  if (DEBUG) {
    cout << "DEBUG: page set includes ";
    for (set<int>::iterator it = set1.begin(); it != set1.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
    cout << "DEBUG: choice set includes ";
    for (set<int>::iterator it = set2.begin(); it != set2.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }
  vector<int> diff;
  // TODO: cite
  set_symmetric_difference(
      set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(diff));
  return diff.size() == 1 && diff[0] == 1;
}
