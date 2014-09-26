// Table.cpp  Table class implementation
// CSCI 455 PA5
// Name: Hefang Li
// Loginid: hefangli

/*
 * Modified 11/22/11 by CMB
 *   changed name of constructor formal parameter to match .h file
 */

#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>

//*************************************************************************
// Node class definition and member functions
//     You don't need to add or change anything in this section

// Note: we define the Node in the implementation file, because it's only
// used by the Table class; not by any Table client code.

struct Node {
  string key;
  int value;

  Node *next;

  Node(const string &theKey, int theValue);

  Node(const string &theKey, int theValue, Node *n);
};

Node::Node(const string &theKey, int theValue) {
  key = theKey;
  value = theValue;
  next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
  key = theKey;
  value = theValue;
  next = n;
}

typedef Node * ListType;

class My455List {
public:

  My455List();

  // returns the address of the node or null if key is not present
  Node *lookupNode(const string &key) const;

  // returns the address of the node or null if key is not present
  // set prevNode to the address of the preceding node
  Node *lookupPrevNode(const string &key, Node *&prevNode) const;

  // remove an element
  // false iff element wasn't present
  bool removeNode(const string &key);

  // insert element at the front of list
  void insertFront(const string &key, int value);

  // prints list elements, space separated, ending with '\n'
  // prints emty list as "<empty>"
  void printList() const;

  // return the length of the list
  int getNumNodes() const;

private:

  int numNodes;
  Node * head;
};

My455List::My455List() {
  numNodes = 0;
  head = NULL;
}

//*************************************************************************


Table::Table() {
  hashSize = HASH_SIZE;
  hashEntries = new My455List[hashSize];
  numEntries = 0;
}

Table::Table(unsigned int hSize) {
  hashSize = hSize;
  hashEntries = new My455List[hashSize];
  numEntries = 0;
}

int * Table::lookup(const string &key){
  My455List entry = hashEntries[hashCode(key)];
  Node *n = entry.lookupNode(key);
  if (!n) {
    return NULL;
  } else {
    return &(n->value);
  }
}

bool Table::remove(const string &key) {
  if (hashEntries[hashCode(key)].removeNode(key)) {
    numEntries--;
    return true;
  } else {
    return false;
  }
}

bool Table::insert(const string &key, int value) {
    My455List *l = hashEntries[hashCode(key)];
  if (!l->lookupNode(key)) {
    l->insertFront(key, value);
    // "=": initialization by copy constructor 
    // different from java reference
    numEntries++;
    return true;
  } else {
    return false;
  }
}

int Table::getNumEntries() const {
  return numEntries;
}

int Table::getNumNonEmptyBuckets() const { 
  int num = 0;
  for (int i = 0; i < hashSize; i++) {
    if (hashEntries[i].getNumNodes() != 0) {
      num++;
    }
  }
  return num;     
}

int Table::getHashSize() const { 
  return hashSize;
}

int Table::getLongestChain() const { 
  int length = 0;
  for (int i = 0; i < hashSize; i++) {
    int curLength = hashEntries[i].getNumNodes();
    length = (curLength > length) ? curLength : length; 
  }
  return length; 
}

void Table::printAll() const{
  for (int i = 0; i < hashSize; i++) {
    hashEntries[i].printList();
  }
}

void Table::hashStats(ostream &out) const{
  out << "number of buckets: " << getHashSize() << endl;
  out << "number of entries: " << getNumEntries() << endl;
  out << "number of non-empty buckets: " << getNumNonEmptyBuckets() << endl;
  out << "longest chain: " << getLongestChain() << endl;
}


// add definitions for your private methods here

Node * My455List::lookupNode(const string &key) const{
  for (Node * p = head; p != NULL; p = p->next) {
    if (p->key == key) {
      return p;
    }
  }
  return NULL;   
}

Node * My455List::lookupPrevNode(const string &key, Node *&prevNode) const{
  Node * p = head;
  if (!p) { // empty list
    prevNode = NULL;
    return NULL;
  }

  if (p->key == key) { // it is the first element
    prevNode = NULL;
    return p;
  }

  for (; p->next != NULL; p = p->next) {
    if (p->next->key == key) {
      prevNode = p;
      return p->next;
    }
  }

  prevNode = NULL; // not found
  return NULL;
}

bool My455List::removeNode(const string &key) {
  Node *prevNode = NULL;
  Node *p = lookupPrevNode(key, prevNode);

  if (!p) {
    return false; // false iff element wasn't present
  } 

  if (!prevNode) { // it is the first element (there are other ways to do so
                   // please refer to version 2
    if (p->next == NULL) { // it has no succeding element
      delete p;
      head = NULL;
    } else {
      Node *tmp = p->next; // very important
      *p = *(p->next);
      // p->key = p->next->key.c_str(); // this can do deep copy of strings
      delete tmp;
    }
  } else { // has preNode
    prevNode->next = p->next;
    delete p;
  }

  numNodes--;
  return true;
}

void My455List::insertFront(const string &key, int value) {
  head = new Node(key, value, head);
    // new(), dynamic allocation, don't want any local variable here
    // hopefully, you will get a warning
  numNodes++;
}

void My455List::printList() const{
  if (numNodes == 0) {
    cout << "<empty>" << endl;
    return;
  }

  for (Node *p = head; p != NULL; p = p->next) {
    cout << "(" << p->key << "," << p->value << ") ";
  }
  cout << endl;
}

int My455List::getNumNodes() const{
  return numNodes;
}

