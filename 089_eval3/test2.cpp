#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

bool check_number(string & s) {
  const char * x = s.c_str();
  const char * ptr = x;
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      return false;
    }
    ptr++;
  }
  return true;
}

int main() {
  string s = "  123";
  int a = atoi(s.c_str());
  if (check_number(s))
    cout << "TRUE" << endl;
  else
    cout << "FALSE" << endl;
  cout << s.c_str() << endl;
  cout << a << endl;
  return EXIT_SUCCESS;
}
