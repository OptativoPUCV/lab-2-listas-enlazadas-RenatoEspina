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
    List* new=(List*)malloc(sizeof(List));
    if(new==NULL){
        exit(EXIT_FAILURE);
    }
    new->head=NULL;
    new->tail=NULL;
    new->current=NULL;
    return new;
}

void * firstList(List * list) {
    if(list->head==NULL) return NULL;
    list->current=list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list->current==NULL) return NULL;
    if(list->current->next==NULL) return NULL;
    list->current=list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail==NULL) return NULL;
    list->current=list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current==NULL) return NULL;
    if(list->current->prev==NULL) return NULL;
    list->current=list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* new=createNode(data);
    if(list->head!=NULL) list->head->prev=new;
    else list->tail=new;
    Node* next=list->head;
    list->head=new;
    list->head->next=next;
    return;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* new = createNode(data);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
        return;
    }
    if (list->current == NULL) return;
    Node* actual = list->current;
    Node* siguiente = list->current->next;
    actual->next = new;
    new->prev = actual;
    new->next = siguiente;
    if (siguiente != NULL)
        siguiente->prev = new;
    else
        list->tail = new;
    return;
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
    if (list->current == NULL) return NULL;
    Node *node = list->current;
    void *data = node->data;
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } 
    else {
        list->head = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
        list->current = node->next;
    } 
    else {
        list->tail = node->prev;
        list->current = node->prev;
    }
    free(node);
    return data;
    }

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}