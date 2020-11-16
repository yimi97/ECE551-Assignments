#include "rand_story.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: ./cyoa-step3 dir_name\n";
    exit(EXIT_FAILURE);
  }
  // read page1
  std::ifstream ifs;
  std::string page1 = argv[1];
  page1.append("/page1.txt");
  ifs.open(page1.c_str(), std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "ERROR: Cannot open page1.\n";
    exit(EXIT_FAILURE);
  }
  ifs.close();
  // read other pages
  std::string dir = argv[1];
  dir.append("/page");
  std::set<int> page_num;
  std::set<int> choice_num;
  bool page_win = false;
  bool page_lose = false;
  std::vector<Page *> vector_page;

  read_pages(dir, vector_page, page_num, choice_num, page_win, page_lose);
  std::vector<int> diff;
  if (!validate_page(page_num, choice_num, page_win, page_lose)) {
    std::cerr << "ERROR: pages are not valid as step2's constraint!\n";
    free_page(vector_page);
    exit(EXIT_FAILURE);
  }
  else if (!all_reachable(vector_page, page_num, diff)) {
    for (size_t i = 0; i < diff.size(); i++) {
      std::cout << "Page " << diff[i] << " is not reachable\n";
    }
    free_page(vector_page);
  }
  else {
    free_page(vector_page);
  }
  return EXIT_SUCCESS;
}
