#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "rand_story.cpp"
/*
bool line_choice(const std::string & line) {
  if (line.find(':') == std::string::npos) {
    return false;
  }
  size_t pos = line.find(':');
  std::string num = line.substr(0, pos);
  const char * ptr = num.c_str();
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      return false;
    }
    ptr++;
  }
  return true;
}
*/
void freeChoice(std::vector<Choice *> & vector_choice) {
  for (size_t i = 0; i < vector_choice.size(); i++) {
    delete vector_choice[i];
  }
  vector_choice.clear();
}

bool read_page(std::ifstream & ifs,
               std::vector<Choice *> & vector_choice,
               std::vector<std::string> & text,
               bool & win,
               bool & lose,
               bool & pond) {
  std::string line;
  bool haveChoice = false;
  while (getline(ifs, line)) {
    if (!pond) {
      if (line_choice(line)) {  // const
        if (win || lose) {
          // free choice;
          freeChoice(vector_choice);
          std::cerr << "invalid section1: case 1\n";
          return false;
        }
        haveChoice = true;
        size_t pos = line.find(':');
        std::string n = line.substr(0, pos);
        std::string c = line.substr(pos + 1);
        Choice * cho = new Choice(atoi(n.c_str()), c);
        vector_choice.push_back(cho);
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          // free choice
          freeChoice(vector_choice);
          std::cerr << "invalid section1: case 2\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          // free chocie
          freeChoice(vector_choice);
          std::cerr << "invalid section1: case 3\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          // free choice
          freeChoice(vector_choice);
          std::cerr << "no chocie or win or lose\n";
          return false;
        }
        pond = true;
      }
      else {
        // free choice
        freeChoice(vector_choice);
        std::cerr << "invalid line in section1 or section2\n";
        return false;
      }
    }
    else {
      text.push_back(line);
    }
  }
  return true;
}

int main(int argc, char ** argv) {
  std::ifstream ifs;

  ifs.open(argv[1], std::ifstream::in);
  if (ifs.fail()) {
    std::cerr << "fail to open"
              << "\n";
    exit(EXIT_FAILURE);
  }
  std::vector<Choice *> vector_choice;
  std::vector<std::string> text;
  bool win = false;
  bool lose = false;
  bool pond = false;
  bool ifValid = read_page(ifs, vector_choice, text, win, lose, pond);
  ifs.close();
  if (!ifValid) {
    exit(EXIT_FAILURE);
  }
  Page p(0, text, vector_choice, win, lose);
  p.printPage();
  return EXIT_SUCCESS;
}
