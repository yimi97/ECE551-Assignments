#include "rand_story.cpp"
using namespace std;
bool all_reachable(vector<Page *> & vector_page, set<int> & page_num, vector<int> & diff);
bool equal_set(set<int> & s1, set<int> & s2, vector<int> & diff);

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
        value.insert(pair<int, int>(it->first, i + 1));
        parent.insert(pair<int, map<int, int> >(key, value));
      }
      else {
        parent[key].insert((pair<int, int>(it->first, i + 1)));
      }
    }
  }
}

void find_path(vector<Page *> & vector_page, set<int> & reachable) {
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
    //    return EXIT_FAILURE;
    //    return;
  }
  map<int, map<int, int> > parent;
  make_parent(child, parent);
  make_path(parent, win_num);
  /*
  for (map<int, vector<int> >::iterator it = parent.begin(); it != parent.end(); ++it) {
    cout << "DEBUG: key is " << it->first << endl;
    cout << "DEBUG: value is ";
    for (size_t i = 0; i < it->second.size(); i++) {
      cout << it->second[i] << " ";
    }
    cout << endl;
  }
  cout << "DEBUG: winning page is " << win_num << endl;
  */
}

int main(int argc, char ** argv) {
  // read page1
  ifstream ifs;
  string page1 = argv[1];
  page1.append("/page1.txt");
  ifs.open(page1.c_str(), ifstream::in);
  if (ifs.fail()) {
    cerr << "ERROR: Cannot open page1.\n";
    exit(EXIT_FAILURE);
  }
  ifs.close();
  // read other pages
  string dir = argv[1];
  dir.append("/page");
  set<int> page_num;
  set<int> choice_num;
  bool page_win = false;
  bool page_lose = false;
  vector<Page *> vector_page;

  read_pages(dir, vector_page, page_num, choice_num, page_win, page_lose);
  vector<int> diff;
  if (!validate_page(page_num, choice_num, page_win, page_lose)) {
    if (DEBUG)
      cout << "DEBUG: pages are not valid!\n";
    exit(EXIT_FAILURE);
  }

  all_reachable(vector_page, page_num, diff);
  set<int> reachable = page_num;
  for (size_t i = 0; i < diff.size(); i++) {
    reachable.erase(diff[i]);
  }
  if (DEBUG) {
    cout << "DEBUG: reachable pages include ";
    for (set<int>::iterator it = reachable.begin(); it != reachable.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }
  find_path(vector_page, reachable);
  free_page(vector_page);
  return EXIT_SUCCESS;
}

bool all_reachable(vector<Page *> & vector_page,
                   set<int> & page_num,
                   vector<int> & diff) {
  vector<int> check_vec;
  //set<int> check_set;
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