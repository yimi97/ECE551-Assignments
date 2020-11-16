#include "rand_story.cpp"

void freeChoice(std::vector<Choice *> & vector_choice) {
  for (size_t i = 0; i < vector_choice.size(); i++) {
    delete vector_choice[i];
  }
  vector_choice.clear();
}

bool validate_format(std::ifstream & ifs, std::vector<std::string> & myfile) {
  std::string line;
  bool haveChoice = false;
  bool win = false;
  bool lose = false;
  bool pond = false;
  while (getline(ifs, line)) {
    myfile.push_back(line);
    if (!pond) {
      if (line_choice(line)) {
        if (win || lose) {
          std::cerr << "ERROR: read choice then lose or win\n";
          return false;
        }
        haveChoice = true;
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: win&&haveChocie or win&&win or win&&lose\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "ERROR: lose&&haveChocie or lose&&lose or win&&lose\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          std::cerr << "ERROR: no section 1\n";
          return false;
        }
        pond = true;
      }
      else {
        std::cerr << "ERROR: other invalid lines between setion 1 and 2\n";
        return false;
      }
    }
  }
  return true;
}

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

  /*
  while (getline(ifs, line)) {
    parseLine(line, vector_choice, text, WIN, LOSE, pond);
  }
  */
  //
  std::vector<std::string> myfile;
  bool ifv = validate_format(ifs, myfile);
  if (!ifv) {
    //    freeChoice(vector_choice);
    myfile.clear();
    ifs.close();
    //exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
  for (size_t i = 0; i < myfile.size(); i++) {
    parseLine(myfile[i], vector_choice, text, WIN, LOSE, pond);
  }
  //
  ifs.close();
  Page p(0, text, vector_choice, WIN, LOSE);
  p.printPage();

  return EXIT_SUCCESS;
}
