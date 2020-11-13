#include "rand_story.cpp"
using namespace std;

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: ./cyoa-step3 dir_name\n";
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
  else if (!all_reachable(vector_page, page_num, diff)) {
    if (DEBUG)
      cout << "DEBUG: Not all reachable!\n";
    for (size_t i = 0; i < diff.size(); i++) {
      cout << "Page " << diff[i] << " is not reachable\n";
    }
    free_page(vector_page);
    exit(EXIT_FAILURE);
  }
  else {
    if (DEBUG)
      cout << "DEBUG: pages are valid.\n";
    free_page(vector_page);
  }
  return EXIT_SUCCESS;
}
