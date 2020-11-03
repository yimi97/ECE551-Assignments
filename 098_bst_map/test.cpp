#include <cstdlib>
#include <iostream>
#include <string>

#include "bstmap.h"
int main(void) {
  BstMap<int, std::string> myTree;
  myTree.add(6, "hello");
  myTree.add(1, "world");
  myTree.add(5, "bye");
  myTree.add(4, "test");
  std::cout << "find 6 " << myTree.lookup(6) << "\n";
  std::cout << "find 1 " << myTree.lookup(1) << "\n";
  std::cout << "find 5 " << myTree.lookup(5) << "\n";
  //  std::cout << "find 7 " << myTree.lookup(7) << "\n";
  // myTree.remove(3);
  myTree.remove(6);
  return EXIT_SUCCESS;
}
