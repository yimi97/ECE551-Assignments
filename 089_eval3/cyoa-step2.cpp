#include "rand_story.cpp"
using namespace std;

int main(int argc, char ** argv) {
  // TODO: check argc
  // read page1
  ifstream ifs;
  string page1 = argv[1];
  page1.append("/page1.txt");
  if (DEBUG)
    cout << "DEBUG: page1 is " << page1 << endl;
  ifs.open(page1.c_str(), ifstream::in);
  if (ifs.fail()) {
    cerr << "ERROR: Cannot open page1.\n";
    //    exit(EXIT_FAILURE);
    return EXIT_FAILURE;
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
    free_page(vector_page);
    //exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
  else {
    if (DEBUG)
      cout << "DEBUG: pages are valid.\n";
    execute(vector_page);
  }
  return EXIT_SUCCESS;
}
