#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
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
  map<int, vector<int> > m;
  map<int, set<int> > parent;
  m.insert(pair<int, vector<int> >(1, {2, 3, 4}));
  m.insert(pair<int, vector<int> >(2, {5, 6}));
  m.insert(pair<int, vector<int> >(6, {7, 8}));
  m.insert(pair<int, vector<int> >(7, {12, 10}));
  m.insert(pair<int, vector<int> >(8, {11, 4}));
  m.insert(pair<int, vector<int> >(12, {9, 4}));
  map<int, vector<int> >::iterator it;
  for (it = m.begin(); it != m.end(); ++it) {
    cout << it->first << ":";
    for (size_t i = 0; i < it->second.size(); i++) {
      cout << it->second[i] << " ";
      int key = it->second[i];
      if (parent.find(key) == parent.end()) {
        set<int> value = {it->first};
        parent.insert(pair<int, set<int> >(key, value));
      }
      else {
        parent[key].insert(it->first);
      }
    }
    cout << endl;
  }
  int win = 11;
  vector<int> path;
  path.push_back(win);
  int key = win;
  while (key != 1) {
    int next = *parent[key].begin();
    path.push_back(next);
    key = next;
  }
  //  path.push_back(key);
  for (size_t i = 0; i < path.size(); i++) {
    cout << path[i] << " ";
  }
  cout << endl;
  /*
  for (map<int, set<int> >::iterator it = parent.begin(); it != parent.end(); ++it) {
    cout << "DEBUG: key is " << it->first << endl;
    cout << "DEBUG: value is ";
    for (set<int>::iterator i = it->second.begin(); i != it->second.end(); ++i) {
      cout << *i << " ";
    }
    cout << endl;
  }
  */
  /*
  set<int> s = {1, 3, 4, 5};
  if (s.find(7) == s.end()) {
    cout << "not exist\n";
    }*/
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
