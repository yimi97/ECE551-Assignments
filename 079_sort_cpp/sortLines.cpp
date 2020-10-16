#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void sortLine(vector<string> lines) {
  sort(lines.begin(), lines.end());
  for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << "\n";
  }
}

int main(int argc, char ** argv) {
  string s;
  vector<string> lines;
  if (argc == 1) {
    while (getline(cin, s)) {
      lines.push_back(s);
    }
    sortLine(lines);
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream ifs(argv[i], ifstream::in);
      while (getline(ifs, s)) {
        lines.push_back(s);
      }
      sortLine(lines);
      ifs.close();
    }
  }
  return EXIT_SUCCESS;
}
