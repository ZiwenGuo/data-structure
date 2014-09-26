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

//typedef Node * ListType;

// Solution to get arround with printAll const problem--
// we pass the pointer to the list by value here.
// Note that pointer is small here, but is powerful;
// Java pass by reference, cpp pass by pointer.
// However, if you want to modify the pointer of the object
// you still need to pass *&

//Node *lookupNode(const Node *&list, const string &key);
static Node *lookupNode(Node *list, const string &key);

//Node *lookupNodePrev(const Node *&list, const string &key, Node *&prevNode);
static Node *lookupNodePrev(Node *list, const string &key, Node *&prevNode);

static bool removeNode(Node *&list, const string &key);

static void insertFront(Node *&list, const string &key, int val);

static void printList(Node *list);

static int listLength(Node *list);


//*************************************************************************


Table::Table() {
  hashSize = HASH_SIZE;
  hashEntries = new Node*[hashSize];
  numEntries = 0;
    
  for (int i = 0; i < hashSize; i++) {
    hashEntries[i] = NULL;
  }
}

Table::Table(unsigned int hSize) {
  hashSize = hSize;
  hashEntries = new Node*[hashSize]; // allocate an array of 100 pointers to Node
  numEntries = 0;
    
  for (int i = 0; i < hashSize; i++) {
    hashEntries[i] = NULL; // this expression is type Node*
  }
}

int * Table::lookup(const string &key) {
  Node *n = lookupNode(hashEntries[hashCode(key)], key);
  if (n) {
    return &(n->value);
  } else {
    return NULL;
  }
}


bool Table::remove(const string &key) {
  if (removeNode(hashEntries[hashCode(key)], key)) {
    numEntries--;
    return true;
  } else {
    return false;
  }
}

bool Table::insert(const string &key, int value) {
  int index = hashCode(key);
  if (!lookupNode(hashEntries[index], key)) {
    insertFront(hashEntries[index], key, value);
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
    if (hashEntries[i] != NULL) {
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
    int curLength = listLength(hashEntries[i]);
    length = (curLength > length) ? curLength : length; 
  }
  return length; 
}

void Table::printAll() const{
  for (int i = 0; i < hashSize; i++) {
    printList(hashEntries[i]);
  }
}

void Table::hashStats(ostream &out) const {
  out << "number of buckets: " << getHashSize() << endl;
  out << "number of entries: " << getNumEntries() << endl;
  out << "number of non-empty buckets: " << getNumNonEmptyBuckets() << endl;
  out << "longest chain: " << getLongestChain() << endl;
}


// add definitions for your private methods here

//Node *lookupNode(const Node *&list, const string &key) {
static Node *lookupNode(Node *list, const string &key) {
  Node * p;
  for (p = list; p != NULL; p = p->next) {
    if (p->key == key) {
      return p;
    }
  }
  return NULL;   
}

//Node *lookupNodePrev(const Node *&list, const string &key, Node *&prevNode) {
static Node *lookupNodePrev(Node *list, const string &key, Node *&prevNode) {
  Node * p = list;
  if (!p) { // empty list
    prevNode = NULL;
    return NULL;
  }
  
  if (p->key == key) { // first element
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

static bool removeNode(Node *&list, const string &key) {
  Node *prevNode = NULL;
  Node *p = lookupNodePrev(list, key, prevNode);
  if (p == NULL) {
    return false;
  }
    
  if (prevNode == NULL) { // void removeFront(Node *&list)
    // if (p->next == NULL) {
    //   delete p;
    //   list = NULL;
    // } else {
    //   Node * tmp = p->next;
    //   *p = *(p->next);
    //   delete tmp;
    // }     
    Node *rest = list->next;
    delete list;
    list = rest;
  } else {  // remove non-front
    prevNode->next = p->next;
    delete p;
  }
  return true;
}

static void insertFront(Node *&list, const string &key, int val) {
  list = new Node(key, val, list);
}

static void printList(Node *list) {
  if (!list) {
    cout << "<empty>" << endl;
    return;
  }

  for (Node *p = list; p != NULL; p = p->next) {
    cout << "(" << p->key << "," << p->value << ") ";
  }
  cout << endl; 
}

static int listLength(Node *list) {
  if (!list) {
    return 0;
  } 

  int length = 0;
  for (Node *p = list; p != NULL; p = p->next) {
    length++;
  }
  return length;

}
