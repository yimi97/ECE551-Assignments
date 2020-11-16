//#include "rand_story.cpp"
#include "rand_story.hpp"
//using namespace std;
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "USAGE: ./cyoa-step1 page.txt\n";
    exit(EXIT_FAILURE);
  }
  std::string line;
  std::vector<Choice *> vector_choice;
  std::ifstream ifs;
  std::vector<std::string> text;
  bool WIN = false;
  bool LOSE = false;
  bool pond = false;
  ifs.open(argv[1], std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "Bad input." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (!validate_format(ifs)) {
    ifs.close();
    exit(EXIT_FAILURE);
  }
  ifs.close();
  ifs.open(argv[1], std::ifstream::in);
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE, pond);
  }
  ifs.close();
  Page p(0, text, vector_choice, WIN, LOSE);
  p.printPage();

  return EXIT_SUCCESS;
}
