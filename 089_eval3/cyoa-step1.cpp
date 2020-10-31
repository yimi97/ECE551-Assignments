#include "rand_story.hpp"
using namespace std;
int main(int argc, char ** argv) {
  string line;
  vector<Choice *> vector_choice;
  ifstream ifs;
  vector<string> text;
  bool WIN = false;
  bool LOSE = false;
  ifs.open(argv[1], ifstream::in);
  if (ifs.fail()) {
    cerr << "Bad input." << endl;
    exit(EXIT_FAILURE);
  }
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE);
  }
  ifs.close();
  Page p(0, text, vector_choice, WIN, LOSE);
  p.printPage();

  return EXIT_SUCCESS;
}
