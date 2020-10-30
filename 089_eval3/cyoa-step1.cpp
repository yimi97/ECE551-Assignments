#include "rand_story.hpp"
using namespace std;
int main(int argc, char ** argv) {
  /*
  Choice c1(1, "test");
  Choice c2(2, "AAA");
  Choice c3(3, "CCC");
  vector<Choice *> v1;
  v1.push_back(&c1);
  v1.push_back(&c2);
  v1.push_back(&c3);
  Page p("The page text", v1, false, false);
  p.printPage();
  */

  string line;
  vector<Choice *> vector_choice;
  ifstream ifs;
  vector<string> text;
  bool WIN = false;
  bool LOSE = false;
  ifs.open(argv[1], ifstream::in);
  if (ifs.fail()) {
    cerr << "Bad input.\n" << endl;
    exit(EXIT_FAILURE);
  }
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE);
  }
  ifs.close();
  // cout << vector_choice.size();

  //    vector_choice[0]->printChoice();
  //vector_choice[1]->printChoice();
  //vector_choice[2]->printChoice();
  Page p(text, vector_choice, WIN, LOSE);
  p.printPage();

  return EXIT_SUCCESS;
}
