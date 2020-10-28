#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class myException : public std::exception {
 public:
  virtual const char * what() const throw() { return "Not valid!\n"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(T d) : data(d), next(NULL), prev(NULL) {}
    ~Node() {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (int i = 0; i < rhs.getSize(); i++) {
      addBack(rhs[i]);
    }
    /*
    Node * ptr = rhs.tail;
    while (ptr != NULL) {
      this->addFront(ptr->data);
      ptr = ptr->prev;
      }*/
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * ptr = head->next;
      delete head;
      head = ptr;
    }
    tail = NULL;
    size = 0;
  };
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * ptr = head->next;
        delete head;
        head = ptr;
      }
      tail = NULL;  // ?
      size = 0;

      for (int i = 0; i < rhs.getSize(); i++) {
        addBack(rhs[i]);
      }
      /*
      Node * ptr = rhs.tail;
      while (ptr != NULL) {
        this->addFront(ptr->data);
        ptr = ptr->prev;
      }
      */
      size = rhs.getSize();
      /*
      LinkedList temp(rhs);
      std::swap(temp.tail, tail);
      std::swap(temp.head, head);
      std::swap(temp.size, size);
      */
    }
    return *this;
  }

  void addFront(const T & item) {
    Node * ptr = new Node(item);
    ptr->next = head;
    head = ptr;
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    /*    Node * ptr = new Node(item);
    if (head == NULL) {
      head = ptr;
      tail = ptr;
      size = 1;
    }
    else {
      Node * temp = tail;
      tail = ptr;
      ptr->prev = temp;
      temp->next = ptr;
      size++;
      }*/
    Node * ptr = new Node(item);
    ptr->prev = tail;
    tail = ptr;
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  int find(const T & item) const {
    /*
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
    */
    Node * ptr = head;
    int i = 0;
    while (ptr != NULL) {
      if (ptr->data == item) {
        return i;
      }
      ptr = ptr->next;
      i++;
    }
    return -1;
  }

  bool remove(const T & item) {
    int f = find(item);
    if (f == -1) {
      return false;
    }
    Node * ptr = head;
    for (int i = 0; i < f; i++) {
      ptr = ptr->next;
    }
    Node * r_prev = ptr->prev;
    Node * r_next = ptr->next;
    if (r_prev == NULL && r_next == NULL) {
      delete ptr;
      size--;
      return true;
    }

    if (r_prev == NULL) {
      r_next->prev = NULL;
    }
    else if (r_next == NULL) {
      r_prev->next = NULL;
    }
    else {
      r_prev->next = r_next;
      r_next->prev = r_prev;
    }
    delete ptr;
    size--;
    return true;
  }

  int getSize() const { return size; }

  T & operator[](int index) {
    if (size == 0 || index >= size || index < 0) {
      throw myException();
    }
    else {
      Node * ptr = head;
      for (int i = 0; i < size; i++) {
        ptr = ptr->next;
      }
      return ptr->data;
    }
  }

  const T & operator[](int index) const {
    if (index >= size || index < 0) {
      throw myException();
    }
    else {
      Node * ptr = head;
      for (int i = 0; i < size; i++) {
        ptr = ptr->next;
      }
      return ptr->data;
    }
  }
};

#endif
