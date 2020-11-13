#include "rand_story.hpp"
// ====================================== step4 =================================== //
void make_path(map<int, map<int, int> > & parent, int & win) {
  vector<vector<int> > path;
  vector<int> vec;
  vec.push_back(win);
  path.push_back(vec);
  int key = win;
  while (key != 1) {
    int k = parent[key].begin()->first;
    int v = parent[key].begin()->second;
    vector<int> vec;
    vec.push_back(k);
    vec.push_back(v);
    path.push_back(vec);
    key = k;
  }
  for (size_t i = path.size() - 1; i >= 1; i--) {
    cout << "Page " << path[i][0] << " Choice " << path[i][1] << endl;
  }
  cout << "Page " << path[0][0] << " WIN" << endl;
}

void make_parent(map<int, vector<int> > & child, map<int, map<int, int> > & parent) {
  for (map<int, vector<int> >::iterator it = child.begin(); it != child.end(); ++it) {
    for (size_t i = 0; i < it->second.size(); i++) {
      int key = it->second[i];
      if (parent.find(key) == parent.end()) {
        map<int, int> value;
        // it->first: its parent; i+1: its index
        value.insert(pair<int, int>(it->first, i + 1));
        parent.insert(pair<int, map<int, int> >(key, value));
      }
      else {
        parent[key].insert((pair<int, int>(it->first, i + 1)));
      }
    }
  }
}

void make_child(vector<Page *> & vector_page, set<int> & reachable) {
  int win_num = -1;
  map<int, vector<int> > child;
  for (set<int>::iterator it = reachable.begin(); it != reachable.end(); ++it) {
    Page * p = vector_page[*it - 1];
    if (p->getChoiceNum() != 0) {
      child.insert(pair<int, vector<int> >(p->getNum(), p->getChoiceVec()));
    }
    // update winning page
    if (p->getWin()) {
      win_num = p->getNum();
    }
  }
  if (win_num == -1) {
    cerr << "There is no way to win\n";
    free_page(vector_page);
    exit(EXIT_FAILURE);
  }
  map<int, map<int, int> > parent;
  make_parent(child, parent);
  make_path(parent, win_num);
}

// ====================================== step3 =================================== //
bool all_reachable(vector<Page *> & vector_page,
                   set<int> & page_num,
                   vector<int> & diff) {
  vector<int> check_vec;
  set<int> reachable;
  check_vec.push_back(1);
  reachable.insert(1);
  while (!check_vec.empty()) {
    int p = check_vec[0];
    if (DEBUG)
      cout << "DEBUG: page " << p << " can be reached.\n";
    check_vec.erase(check_vec.begin());
    vector<Choice *> c = vector_page[p - 1]->getChoice();
    if (!c.empty()) {
      for (vector<Choice *>::iterator it = c.begin(); it != c.end(); ++it) {
        int n = (*it)->getNum();
        if (reachable.find(n) == reachable.end()) {
          check_vec.push_back(n);
          reachable.insert(n);
        }
      }
    }
  }
  if (equal_set(page_num, reachable, diff)) {
    return true;
  }
  else {
    return false;
  }
}

bool equal_set(set<int> & s1, set<int> & s2, vector<int> & diff) {
  if (s1.size() == s2.size() && equal(s1.begin(), s1.end(), s2.begin())) {
    return true;
  }
  else {
    set_symmetric_difference(
        s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(diff));
    return false;
  }
}

// ====================================== step2 =================================== //
void read_single_page(ifstream & ifs,
                      int i,
                      vector<Page *> & vector_page,
                      set<int> & page_num,
                      set<int> & choice_num,
                      bool & page_win,
                      bool & page_lose) {
  string line;
  vector<Choice *> vector_choice;
  vector<string> text;
  bool WIN = false;
  bool LOSE = false;
  bool pond = false;
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE, pond);
  }
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
}

void read_pages(string & dir,
                vector<Page *> & vector_page,
                set<int> & page_num,
                set<int> & choice_num,
                bool & page_win,
                bool & page_lose) {
  ifstream ifs;
  int i = 1;
  while (true) {
    string page = dir;
    stringstream ss;
    ss << i;
    page.append(ss.str()).append(".txt");
    ifs.open(page.c_str(), ifstream::in);
    if (ifs.fail()) {
      break;
    }
    if (!validate_format(ifs)) {
      ifs.close();
      free_page(vector_page);
      exit(EXIT_FAILURE);
    }
    ifs.close();
    ifs.open(page.c_str(), ifstream::in);
    read_single_page(ifs, i, vector_page, page_num, choice_num, page_win, page_lose);
    ifs.close();
    i++;
  }
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
  return (diff.size() == 1 && diff[0] == 1) || (diff.size() == 0);
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
      return;
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
    delete page[i];
  }
  page.clear();
}

// ====================================== step1 =================================== //
bool line_choice(const string & line) {
  if (line.find(':') == std::string::npos) {
    return false;
  }
  size_t pos = line.find(':');
  std::string num = line.substr(0, pos);
  const char * ptr = num.c_str();
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      return false;
    }
    ptr++;
  }
  return true;
}

bool validate_format(ifstream & ifs) {
  std::string line;
  bool haveChoice = false;
  bool win = false;
  bool lose = false;
  bool pond = false;
  while (getline(ifs, line)) {
    if (!pond) {
      if (line_choice(line)) {
        if (win || lose) {
          std::cerr << "ERROR: read choice then lose or win\n";
          return false;
        }
        haveChoice = true;
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: win&&haveChocie or win&&win or win&&lose\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: lose&&haveChocie or lose&&lose or win&&lose\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          std::cerr << "ERROR: no section 1\n";
          return false;
        }
        pond = true;
      }
      else {
        std::cerr << "ERROR: other invalid lines between setion 1 and 2\n";
        return false;
      }
    }
  }
  return true;
}

void parseLine(string & line,
               vector<Choice *> & vector_choice,
               vector<string> & text,
               bool & win,
               bool & lose,
               bool & pond) {
  if (!pond && line_choice(line)) {
    size_t pos = line.find(':');
    string n = line.substr(0, pos);
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
    pond = true;
  }
  else {
    text.push_back(line);
  }
}
