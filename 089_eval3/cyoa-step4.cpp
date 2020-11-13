#include "rand_story.cpp"
using namespace std;

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: ./cyoa-step4 dir_name\n";
    exit(EXIT_FAILURE);
  }
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
  make_child(vector_page, reachable);
  free_page(vector_page);
  return EXIT_SUCCESS;
}
