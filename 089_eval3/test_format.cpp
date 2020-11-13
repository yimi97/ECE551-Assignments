#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

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
  int num_int = atoi(num.c_str());
  return true;
}

bool validate_page(std::ifstream & ifs) {
  std::string line;
  bool haveChoice = false;
  bool win = false;
  bool lose = false;
  bool pond = false;
  while (getline(ifs, line)) {
    if (!pond) {
      if (line_choice(line)) {
        if (win || lose) {
          std::cerr << "invalid section1: case 1\n";
          return false;
        }
        haveChoice = true;
      }
      else if (line.find("WIN") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "invalid section1: case 2\n";
          return false;
        }
        win = true;
      }
      else if (line.find("LOSE") == 0) {
        if (haveChoice || lose || win) {
          std::cerr << "invalid section1: case 3\n";
          return false;
        }
        lose = true;
      }
      else if (line.find('#') == 0) {
        if (!haveChoice && !win && !lose) {
          std::cerr << "no chocie or win or lose\n";
          return false;
        }
        pond = true;
      }
      else {
        std::cerr << "invalid line in section1 or section2\n";
        return false;
      }
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
  if (validate_page(ifs)) {
    std::cout << "valid\n";
  }
  else {
    std::cout << "not valid\n";
  }
  ifs.close();

  return EXIT_SUCCESS;
}
