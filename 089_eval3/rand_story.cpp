#include "rand_story.hpp"
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
        cout << "That is not a valid choice, please try again\n";
      }
    }
  }
}

void free_page(vector<Page *> & page) {
  for (size_t i = 0; i < page.size(); i++) {
    if (DEBUG)
      cout << "DEBUG: free page.\n";
    delete page[i];
  }
  page.clear();
}