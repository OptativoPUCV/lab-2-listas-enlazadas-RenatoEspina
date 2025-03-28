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
    Node* new=createNode(data);
    if(list->head==NULL){
        list->head=new;
        list->tail=new;
        return;
    }
    if(list->current==NULL) return;
    Node* actual=list->current;
    Node* siguiente=list->current->next;
    actual->next=new;
    new->prev=actual;
    siguiente->prev=new;
    new->next=siguiente;
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
    if(list->head->next!=NULL){
        Node* prev=list->current->prev;
        Node* next=list->current->next;
        prev->next=next;
        next->prev=prev;
        void* dato= list->current->data;
        free(list->current);
        list->current=next;
        return dato;
    }
    void* dato= list->current->data;
    free(list->current);
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}