#include "rand_story.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: ./cyoa-step2 dir_name\n";
    exit(EXIT_FAILURE);
  }
  // read page 1
  std::ifstream ifs;
  std::string page1 = argv[1];
  page1.append("/page1.txt");
  if (DEBUG)
    std::cout << "DEBUG: page1 is " << page1 << std::endl;
  ifs.open(page1.c_str(), std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "ERROR: Cannot open page1.\n";
    exit(EXIT_FAILURE);
  }
  ifs.close();
  page1.clear();
  // read other pages
  std::string dir = argv[1];
  dir.append("/page");
  std::set<int> page_num;
  std::set<int> choice_num;
  bool page_win = false;
  bool page_lose = false;
  std::vector<Page *> vector_page;

  read_pages(dir, vector_page, page_num, choice_num, page_win, page_lose);

  if (!validate_page(page_num, choice_num, page_win, page_lose)) {
    std::cerr << "ERROR: pages are not valid!\n";
    free_page(vector_page);
    exit(EXIT_FAILURE);
  }
  else {
    if (DEBUG)
      std::cout << "DEBUG: pages are valid.\n";
    execute(vector_page);
  }
  free_page(vector_page);
  return EXIT_SUCCESS;
}
