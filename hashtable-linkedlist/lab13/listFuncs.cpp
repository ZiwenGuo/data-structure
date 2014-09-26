/*  
 *  CS 455 Spring 2014
 *
 *  See listFuncs.h for specification of each function.
 */

#include <iostream>

#include <cassert>

#include "listFuncs.h"

using namespace std;


int lastIndexOf(ListType list, int val) {
    int lastIndex = -1;
    int cur = 0;
    for (Node *p = list; p != NULL; p = p->next) {
        if (p->data == val) {
            lastIndex = cur;
        }
        cur++;
    }
    return lastIndex;
}



void removeAdjacentEvens(ListType &list) {
    if (list == NULL || list->next == NULL) {
        return;
    }
    Node *prev = list;
    Node *cur = list->next;
    while (cur != NULL) {
        bool predicate = (prev->data % 2 == 0) && (cur->data % 2 == 0);
        if (predicate) {
            prev->next = cur->next;
            delete cur;
            cur = prev->next;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}



ListType copy(ListType list) {
    if (list == NULL) {
        return NULL;
    }

    Node *p = list;
    //Node *last = newList;
    ListType newList = new Node(p->data);
    Node *last = newList;
    p = p->next;
    while (p != NULL) {
        last->next = new Node(p->data);
        last = last->next;
        p = p->next;
    }
    return newList;
}



void rotateLeft(ListType &list, int k) {
    if (k <= 0 || list == NULL || list->next == NULL) {
        return;
    }

    Node *last;
    int num = 0;
    for (last = list; last->next != NULL; last = last->next) {
        num++;
    }
    if (k >= num + 1) {
        return;
    }

    for (; k != 0; k--) {
        last->next = list;
        list = list->next;
        last = last->next;
        last->next = NULL;
    }

}
