// some linked list routines and a test program for CS 455 lab

#include <iostream>
#include <cctype>
#include <cassert>
#include <string>

using namespace std;


//*************************************************************************
struct Node {
    int data;
    Node *next;

    Node(int item);
    Node(int item, Node *n);
};

Node::Node(int item) {
    data = item;
    next = NULL;
}

Node::Node(int item, Node *n) {
    data = item;
    next = n;
}


//*************************************************************************
// utility functions used by this code
// these functions are defined at the bottom of the file

// inserts val at the front of list
// PRE: list is a well-formed list
void insertFront(Node *&list, int val);

void removeFront(Node * &list);

void removeLast(Node * &list);

// makes list into an empty list
//   reclaiming memory used by nodes 
// PRE: list is a well-formed list
// POST: list is NULL
void clearList(Node * &list);

// prints list elements, space separated, ending with '\n'
// prints emty list as "<empty>"
// PRE: list is a well-formed list
void printList(Node *list);


//*************************************************************************

// PRE: list is a well-formed list
// POST: returns sum of elements in list
int sumList (Node *list)
{
    int sum = 0;

    for (Node *p = list; p != NULL; p = p->next) {
        sum += p->data; 
    }

    return sum;
}


// PRE: list is a well-formed list
// POST: list' is same as list, but with item appended
void append (Node * &list, int item)
{
    if (list == NULL) {
        insertFront(list, item);
        return;
    }

    Node *p = list;
    while (p->next != NULL) {
        p = p->next;  
    }
    p->next = new Node(item);
}


// printEveryOther: prints 1st, 3rd, 5th, ... elements in a list
// PRE: list is a well-formed linked list
void printEveryOther(Node * list)
{
    if (list == NULL) {
        cout << "<empty>" << endl;
        return ;
    }

    Node *p = list; 
    while (1) {
        cout << p->data << " ";

        p = p->next;
        if (p == NULL) {
            break;
        }
        p = p->next;
        if (p == NULL) {
            break;
        }
    }

    cout << endl;
}


/*
 * promptForInt: Prompts for and reads an integer.
 */
int promptForInt (string prompt)
{
    int value;

    cout << prompt << ": ";
    cin >> value;
    return value;
}


// skips over non-digits, non eoln in input stream
void skip()
{
    int ch = cin.peek();
    while ((ch != '\n') && (!isdigit(ch))) {
        cin.get();
        ch = cin.peek();
    }  
}

void printCmdSummary() {
      cout<< "Valid commands are b(build new list), i(insert), a(append), " 
	  << endl;
      cout << "         s(sum of elmts) , p(print every other), h(help), q(quit)." 
	   << endl;
}


// buildList: reads numbers from one line, prepends them to the list
// in reverse order.
// User must enter at least one number, and terminate sequence of
// numbers with a newline.
// PRE: theList is a well-formed list
void buildList(Node * & theList)
{
    int i;

    do {
        cin >> i;
        insertFront(theList, i);
        skip();
    } while (cin.peek() != '\n');

    cin.get();     // consume the newline
}


/* a little test program */

int main ()
{

  char c;
  bool keepgoing = true;
  int  v;
  Node *thelist = NULL;

  printCmdSummary();

  do {
    cout << "\nPlease enter a command [b, i, a, s, p, h, q]: ";
    cin >> c;

    if (cin.fail()) {
      cout << "ERROR: input stream failed." << endl;
      keepgoing = false;
    }
    else {
      switch (c) {
      case 'b':
	clearList(thelist);
	cout << "Please enter a sequence of ints followed by <nl> (e.g:1 2 3): ";
	buildList(thelist);
	break;
      case 'i':
	v = promptForInt ("Value to insert");
	insertFront (thelist, v);
	break;
      case 'a':
	v = promptForInt ("Value to append");
	append (thelist, v);
	break;
      case 's':
	cout << "Sum of elements in list is " << sumList(thelist) << endl;
	break;
      case 'p':
	cout << "Print every other: " << endl;
	printEveryOther(thelist); cout << endl;
	break;
      case 'q':
	keepgoing = false;
	break;
      default:
	printCmdSummary();
	break;
      }
      cout << "The list: ";
      printList (thelist);

    }
    
    
  } while (keepgoing);

  return 0;
}


void insertFront(Node *&list, int val) {
    list = new Node(val, list);
}

void removeFront(Node * &list) {
    if (list == NULL) {
        return;
    }

    Node rest = list->next;
    delete list;
    list = rest;
}

void removeLast(Node * &list) {
    if (list == NULL) {
        return;
    }

    if (list->next == NULL) {
        delete list;
        list = NULL; // must do this delete() will not invalidate the reference
    }

    Node *p = list;
    while (p->next->next != NULL) {
        p = p->next;
    }
    delete p->next;
    p->next = NULL;
}

void printList(Node *list) {
    if (list == NULL) {
        cout << "<empty>";
    }

    Node *p = list;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
}


void clearList(Node *&list) {
    Node *rest = list;

    while (list != NULL) {
        rest = list->next;  // rest is all but the first element
        delete list;  // reclaims one node only
        list = rest;
    }
}

