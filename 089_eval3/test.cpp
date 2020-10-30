#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
  vector<int> v1 = {1, 2, 3};
  vector<int> v2 = v1;
  for (int n : v2) {
    cout << n << "\n";
  }
  vector<int> v3(v1);
  for (int n : v3) {
    cout << n << "\n";
  }
  vector<int> v4;
  if (v4.empty()) {
    cout << "empty vector"
         << "\n";
  }
  int num = 1;
  string str = "fk";
  cout << num << ":" << str << "\n";
  return EXIT_SUCCESS;
}
