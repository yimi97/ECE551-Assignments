#include "rand_story.cpp"
using namespace std;
bool all_reachable(vector<Page *> & vector_page, set<int> & page_num);
bool equal_set(set<int> & s1, set<int> & s2);
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

  if (!validate_page(page_num, choice_num, page_win, page_lose)) {
    cerr << "ERROR: pages are not valid!\n";
    exit(EXIT_FAILURE);
  }
  else if (!all_reachable(vector_page, page_num)) {
    cerr << "Not";
    exit(EXIT_FAILURE);
  }
  else {
    if (DEBUG)
      cout << "DEBUG: pages are valid.\n";
    execute(vector_page);
  }
  return EXIT_SUCCESS;
}

bool all_reachable(vector<Page *> & vector_page, set<int> & page_num) {
  vector<int> check_vec;
  //set<int> check_set;
  set<int> reachable;
  check_vec.push_back(1);
  reachable.insert(1);
  while (!check_vec.empty()) {
    int p = check_vec[0];
    //    cout << "DEBUG: page number " << p << endl;
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
  if (equal_set(page_num, reachable)) {
    return true;
  }
  else {
    return false;
  }
}

bool equal_set(set<int> & s1, set<int> & s2) {
  return s1.size() == s2.size() && equal(s1.begin(), s1.end(), s2.begin());
}
