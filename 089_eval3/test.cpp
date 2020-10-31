#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
bool check_number(string s) {
  string::iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) {
    ++it;
  }
  return !s.empty() && it == s.end();
}
int main() {
  set<int> s = {1, 3, 4, 5};
  if (s.find(7) == s.end()) {
    cout << "not exist\n";
  }
  //  unique_ptr<int> p;
  /*
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
  string str = "kk";
  cout << num << ":" << str << "\n";
  string n = "12sdfb";
  if (check_number(n)) {
    cout << "is number\n";
  }
  else {
    cout << "not a number\n";
  }
  int a = atoi(n.c_str());
  cout << a << "\n";

  set<int> s1;
  s1.insert(1);
  s1.insert(2);
  */
  //  string s = "test memory leak";
  //exit(EXIT_FAILURE);
  /*
  deque<int> q;
  q.push_back(1);
  q.push_back(2);
  q.push_back(4);
  q.pop_front();
  */
  return EXIT_SUCCESS;
}
