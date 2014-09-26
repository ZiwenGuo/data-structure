#include "cs402.h"
#include "my402list.h"
#include <stdlib.h>

int  
My402ListLength(My402List *L) {
	return L->num_members;
}

int  
My402ListEmpty(My402List *L) {
	if (L->num_members == 0)
		return TRUE;
	else
		return FALSE;
}

/* Returns the first list element or NULL if the list is empty */
My402ListElem *
My402ListFirst(My402List *L) {
	if (L->num_members == 0)
		return NULL;
	else
		return L->anchor.next;
}

/* Returns the last list element or NULL if the list is empty */
My402ListElem *
My402ListLast(My402List *L) {
	if (L->num_members == 0)
		return NULL;
	else
		return L->anchor.prev;
}

/* Returns elem->next or NULL if elem is the last item on the list. 
   Please do not check if elem is on the list */
My402ListElem *
My402ListNext(My402List *L, My402ListElem *E) {
	if (E->next == &L->anchor) 
		return NULL;
	else 
		return E->next;
}

My402ListElem *
My402ListPrev(My402List *L, My402ListElem *E) {
	if (E->prev == &L->anchor) 
		return NULL;
	else 
		return E->prev;
}

int  
My402ListAppend(My402List *L, void *r) {
	My402ListElem *s, *t;	
	s = (My402ListElem *)malloc(sizeof(My402ListElem));
	
	if (s == NULL)
		return FALSE;

	t = L->anchor.prev;
	L->anchor.prev = s;
	t->next = s;
	s->next = &L->anchor;
	s->prev=t;

	s->obj = r;  	
	(L->num_members)++;

	return TRUE;
}

int  
My402ListPrepend(My402List *L, void *r) {
	My402ListElem *s, *t;
	s = (My402ListElem *)malloc(sizeof(My402ListElem));
	if (s == NULL) 
		return FALSE;

	t = L->anchor.next;
	L->anchor.next = s;
	t->prev = s;
	s->prev = &L->anchor;
	s->next = t;

	s->obj = r;  
	(L->num_members)++;

	return TRUE;
}

int  
My402ListInsertAfter(My402List *L, void *r, My402ListElem *E) {
	My402ListElem *s, *m, *n;	
	s = (My402ListElem *)malloc(sizeof(My402ListElem));

	if(s == NULL)
		return FALSE;

	m = E->next;
	n = E->next->prev; 
	E->next->prev = s;
	E->next = s;
	s->next = m;
	s->prev = n;

	s->obj = r;  
	(L->num_members)++;

	return TRUE;
}

int  
My402ListInsertBefore(My402List *L, void *r, My402ListElem *E) {
	My402ListElem *s, *m, *n;
	s = (My402ListElem *)malloc(sizeof(My402ListElem));

	if(s == NULL)
		return FALSE;

	n = E->prev;
	m = E->prev->next; 
	E->prev->next = s;
	E->prev = s;
	s->next = m;
	s->prev = n;

	s->obj = r;  
	(L->num_members)++;

	return TRUE;
}

/* Unlink and delete elem from the list. Please do not delete the object 
   pointed to by elem and do not check if elem is on the list */
void 
My402ListUnlink(My402List *L, My402ListElem *E) {
	E->prev->next = E->next;
	E->next->prev = E->prev;

	free(E);
	(L->num_members)--;
}

/* Unlink and delete all elements from the list and make the list empty. 
   Please do not delete the objects pointed to be the list elements */
void 
My402ListUnlinkAll(My402List *L) {
	My402ListElem *p, *s; 

	if (!My402ListEmpty(L)) {
		for (p = My402ListFirst(L), p->prev->next = NULL; p->next != NULL; p = s) { 
			s = p->next;
			s->prev = NULL;
			free(p); //corresponding to malloc()
		}

		L->num_members = 0;
	}
}

/* Returns the list element elem such that elem->obj == obj. 
   Returns NULL if no such element can be found */
My402ListElem *
My402ListFind(My402List *L, void *r) {
	My402ListElem* p;	
	for (p = My402ListFirst(L); p != &L->anchor; p = p->next) {
		if (p->obj == r) 
			return p;
	}

	return NULL;
}

int 
My402ListInit(My402List *L) {
	L->anchor.next = &L->anchor;
	L->anchor.prev = &L->anchor;
	L->num_members = 0;

	return TRUE;
}
