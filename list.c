#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List*list=(List*) malloc (sizeof(List));
  list->head = NULL;
  list->tail=NULL;
  list->current=NULL;
  return list;
}

void * firstList(List * list) {
    if (list->head != NULL)
    {
      list->current = list->head;
      return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {

  if (list->current != NULL && list->current->next!=NULL)
  {
    list->current = list->current-> next;
    return list->current->data;
  }
    return NULL ;
}

void * lastList(List * list) {
  if (list->tail != NULL)
  {
    list->current = list->tail;
    return list->tail->data;
  }
    return NULL;
}

void * prevList(List * list) {

  if (list->current != NULL && list->current->prev!=NULL)
  {
    list->current = list->current-> prev;
    return list->current->data;
  }  
  return NULL;

}
void pushFront(List * list, void * data) {
  Node* n= createNode(data);
  n->next= list->head;
  n->prev= NULL;
  if(list->head != NULL)
  {
    list->head->prev = n;
  }
  else
  {
  list->tail = n;
  }
  list->head = n;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current != NULL) {
        Node *n = createNode(data); 

        n->prev = list->current;
        n->next = list->current->next;

        if (list->current->next != NULL) {
            list->current->next->prev = n;
        } else {
            list->tail = n;
        }

        list->current->next = n;
    }
}



void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *n = list->current;
  if(list->current != NULL ){

    if (n->prev !=NULL)
    {
      n->prev->next = n -> next;
    }
    else
    {
      list->head = n->next;
    }
    if (n->next != NULL)
    {
      n->next->prev = n->prev;
    }
    else
    {
      list->tail = n->prev;
    }
  }
  void *data = n->data;
  free(n);
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}