#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void sortLine(vector<string> & lines) {
  sort(lines.begin(), lines.end());
  for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << "\n";
  }
  lines.clear();
}

int main(int argc, char ** argv) {
  string s;
  vector<string> lines;
  ifstream ifs;
  if (argc == 1) {
    while (getline(cin, s)) {
      lines.push_back(s);
    }
    sortLine(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifs.open(argv[i], ifstream::in);
      if (ifs.fail()) {
        cerr << "Bad input." << endl;
        exit(EXIT_FAILURE);
      }
      while (getline(ifs, s)) {
        lines.push_back(s);
      }
      sortLine(lines);
      ifs.close();
    }
  }
  return EXIT_SUCCESS;
}
