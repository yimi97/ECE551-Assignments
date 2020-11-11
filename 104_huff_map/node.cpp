#include "node.h"

void buildMapHelper(BitString b, std::map<unsigned, BitString> & theMap, Node * curr) {
  if (curr == NULL) {
    return;
  }
  if (curr->sym != NO_SYM) {
    assert(curr->left == NULL && curr->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(curr->sym, b));
  }
  else {
    buildMapHelper(b.plusZero(), theMap, curr->left);
    buildMapHelper(b.plusOne(), theMap, curr->right);
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  buildMapHelper(b.plusZero(), theMap, left);
  buildMapHelper(b.plusOne(), theMap, right);
}
