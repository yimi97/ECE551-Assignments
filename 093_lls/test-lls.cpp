#include <assert.h>

#include <cstdlib>
#include <vector>

#include "ll.h"

void testList(void) {
  LinkedList<int> t1;
  assert(t1.head == NULL && t1.tail == NULL && t1.size == 0 && t1.getSize() == 0);
  assert(t1.remove(0) == false);

  LinkedList<int> t2;
  t2 = t1;
  assert(t2.head == NULL && t2.tail == NULL && t2.size == 0 && t2.getSize() == 0);

  LinkedList<int> t2b(t1);
  assert(t2b.head == NULL && t2b.tail == NULL && t2b.size == 0 && t2b.getSize() == 0);

  t1.addFront(1);
  assert(t1.head->data == 1 && t1.tail->data == 1);
  assert(t1.head != NULL && t1.tail == t1.head && t1.size == 1 && t1.getSize() == 1);
  assert(t1[0] == 1);
  assert(t1.find(1) == 0);
  assert(t1.find(2) == -1);
  assert(t1.remove(2) == false);
  assert(t1.head != NULL && t1.tail == t1.head && t1.size == 1 && t1.getSize() == 1);
  assert(t1.head->next == NULL && t1.tail->prev == NULL);
  // t1: 1

  t2.addBack(2);
  assert(t2.head->data == 2 && t2.tail->data == 2);
  assert(t2.head != NULL && t2.tail == t2.head && t2.size == 1 && t2.getSize() == 1);
  assert(t2[0] == 2);
  assert(t2.find(2) == 0);
  assert(t2.find(1) == -1);
  assert(t2.head->next == NULL && t2.tail->prev == NULL);
  assert(t2.remove(2) == true);
  assert(t2.head == NULL && t2.tail == NULL && t2.size == 0 && t2.getSize() == 0);
  // t2: NULL

  LinkedList<int> t3(t1);
  assert(t1.head != t3.head && t1.tail != t3.tail);
  assert(t3.head != NULL && t3.tail == t3.head && t3.size == 1 && t3.getSize() == 1);
  assert(t3.head->data == 1);
  t3.addFront(3);
  assert(t3.head->next == t3.tail && t3.tail->prev == t3.head);
  assert(t3.head->next->prev == t3.head);
  assert(t3.head->data == 3);
  assert(t3.tail->data == 1);
  assert(t3.size == 2 && t3.getSize() == 2);
  assert(t3[0] == 3 && t3[1] == 1);
  assert(t3.find(3) == 0 && t3.find(1) == 1);
  assert(t3.find(2) == -1);
  assert(t3.remove(2) == false);
  t3.addFront(4);
  assert(t3.remove(4) == true);
  assert(t3.head != NULL && t3.tail != NULL && t3.size == 2 && t3.getSize() == 2);
  // t3: 3->1

  LinkedList<int> t4(t1);
  t4.addBack(3);  //1->3
  assert(t4.head->next == t4.tail && t4.tail->prev == t4.head);
  assert(t4.head->data == 1);
  assert(t4.tail->data == 3);
  assert(t4.size == 2 && t4.getSize() == 2);
  assert(t4[0] == 1 && t4[1] == 3);
  assert(t4.find(3) == 1 && t4.find(1) == 0);
  assert(t4.find(2) == -1);
  assert(t4.remove(2) == false);
  t4.addBack(4);
  assert(t4.remove(4) == true);
  assert(t4.head != NULL && t4.tail != NULL && t4.size == 2 && t4.getSize() == 2);
  // t4: 1->3

  t2.addBack(5);  // t2: 5
  t3 = t2;
  assert(t3.head != NULL && t3.tail == t3.head && t2.size == 1 && t2.getSize() == 1);
  // t3: 5

  // test duplicated num remove
  assert(t4.find(1) == 0);
  t4.addFront(1);
  assert(t4.find(1) == 0);
  t4.remove(1);
  assert(t4.find(1) == 0);
  assert(t4.size == 2 && t4.getSize() == 2);
  assert(t4[0] == 1 && t4[1] == 3);
  assert(t4.find(3) == 1 && t4.find(1) == 0);

  // test remove all
  t4.remove(1);
  t4.remove(3);
  assert(t4.head == NULL && t4.tail == NULL && t4.size == 0 && t4.getSize() == 0);

  // test 2-digit num
  t4.addFront(1);
  t4.addBack(11);
  assert(t4.size == 2 && t4.getSize() == 2);
  assert(t4[0] == 1 && t4[1] == 11);
  assert(t4.find(1) == 0 && t4.find(11) == 1);

  // test addFront and addBack
  t4.addFront(5);
  t4.addBack(6);
  t4.addFront(7);
  t4.addBack(8);
  assert(t4[0] == 7 && t4[5] == 8);
  assert(t4.size == 6);

  //
  t4.addFront(8);
  assert(t4.find(8) == 0);

  //
  t4 = t2b;
  assert(t4.head == NULL && t4.tail == NULL && t4.size == 0 && t4.getSize() == 0);
  t2b = t3;
  assert(t2b.head == t2b.tail && t2b.tail->next == NULL && t2b.size == 1);

  //
  assert(t2b[0] == 5);

  //
  LinkedList<int> t11 = LinkedList<int>();
  assert(t11.size == 0 && t11.getSize() == 0 && t11.head == NULL && t11.tail == NULL);
  t11.addFront(1);
  assert(t11.size == 1 && t11.getSize() == 1 && t11.head == t11.tail &&
         t11.head->data == 1);
  assert(t11.find(1) == 0 && t11.find(2) == -1 && t11[0] == 1);
  assert(t11.remove(0) == false && t11.remove(1) == true);
  t11.addFront(1);
  t11.addFront(2);
  assert(t11.size == 2 && t11.getSize() == 2);
  assert(t11.head->data == 2 && t11.head->next == t11.tail && t11.head->prev == NULL);
  assert(t11.tail->data == 1 && t11.tail->prev == t11.head && t11.tail->next == NULL);
  assert(t11[0] == 2 && t11[1] == 1 && t11.find(1) == 1 && t11.find(2) == 0);
  LinkedList<int> t21 = LinkedList<int>(t11);
  LinkedList<int> t31 = LinkedList<int>();
  t31 = t21;
  assert(t31.size == 2 && t31.getSize() == 2 && t31[0] == 2 && t31[1] == 1);
  LinkedList<int> t41 = LinkedList<int>();
  t21 = t41;
  assert(t21.size == 0 && t21.getSize() == 0 && t21.head == NULL && t21.tail == NULL);
  t11.addBack(3);
  assert(t11.size == 3 && t11.getSize() == 3);
  assert(t11.head->data == 2 && t11.head->next->next == t11.tail &&
         t11.head->prev == NULL);
  assert(t11.tail->data == 3 && t11.tail->prev->prev == t11.head &&
         t11.tail->next == NULL);
  assert(t11[0] == 2 && t11[2] == 3 && t11.find(3) == 2 && t11.find(2) == 0);
  assert(t11.remove(1) == true && t11.remove(4) == false);
  assert(t11.size == 2);
  assert(t11.head->prev == NULL && t11.tail->next == NULL && t11.tail->prev == t11.head &&
         t11.head->next == t11.tail);
  assert(t11.head->next->data == 3 && t11[0] == 2 && t11[1] == 3);
}
/*
void testList() {
  IntList t1 = IntList();
  assert(t1.size == 0 && t1.getSize() == 0 && t1.head == NULL && t1.tail == NULL);
  t1.addFront(1);
  assert(t1.size == 1 && t1.getSize() == 1 && t1.head == t1.tail && t1.head->data == 1);
  assert(t1.find(1) == 0 && t1.find(2) == -1 && t1[0] == 1);
  assert(t1.remove(0) == false && t1.remove(1) == true);
  t1.addFront(1);
  t1.addFront(2);
  assert(t1.size == 2 && t1.getSize() == 2);
  assert(t1.head->data == 2 && t1.head->next == t1.tail && t1.head->prev == NULL);
  assert(t1.tail->data == 1 && t1.tail->prev == t1.head && t1.tail->next == NULL);
  assert(t1[0] == 2 && t1[1] == 1 && t1.find(1) == 1 && t1.find(2) == 0);
  IntList t2 = IntList(t1);
  IntList t3 = IntList();
  t3 = t2;
  assert(t3.size == 2 && t3.getSize() == 2 && t3[0] == 2 && t3[1] == 1);
  IntList t4 = IntList();
  t2 = t4;
  assert(t2.size == 0 && t2.getSize() == 0 && t2.head == NULL && t2.tail == NULL);
  t1.addBack(3);
  assert(t1.size == 3 && t1.getSize() == 3);
  assert(t1.head->data == 2 && t1.head->next->next == t1.tail && t1.head->prev == NULL);
  assert(t1.tail->data == 3 && t1.tail->prev->prev == t1.head && t1.tail->next == NULL);
  assert(t1[0] == 2 && t1[2] == 3 && t1.find(3) == 2 && t1.find(2) == 0);
  assert(t1.remove(1) == true && t1.remove(4) == false);
  assert(t1.size == 2);
  assert(t1.head->next->next == NULL);
}
*/
int main(void) {
  testList();
  return EXIT_SUCCESS;
}
