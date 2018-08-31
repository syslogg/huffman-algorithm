#include <stdio.h>
#include <stdlib.h>

#include "List.h"

typedef struct list List;
typedef struct node Node;

struct list {
    Node * first;
    Node * last;
    int len;
};

struct node {
    void * b;
    Node * next;
};

//Public
List * list() {
    List * l = (List *) malloc(sizeof(struct list));
    l->first = NULL;
    l->last = NULL;
    l->len = 0;

    return l;
}

//Public
void destroyList(List * l) {
    cleanList(l);
    free(l);
}

//Public
void cleanList(List * l) {
    Node * aux = l->first;
    while (aux != NULL) {
        Node * aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    l->first = NULL;
    l->last = NULL;
    l->len = 0;
}

//Public
void add(List * l, void * item) {
    Node * newNode = createNode(item);
    
    if(l->first == NULL) {
        l->first = newNode;
    } else {
        l->last->next = newNode;
    }

    l->last = newNode;
    l->len++;
}

//Public
void * remove(List * l, int i) {
    Node * aux = l->first;
    Node * prev = NULL;

    if(i >= l->len) {
        printf("Error");
        return;
    }

    int count = 0;
    for (count=0; i != count; count++) {
        prev = aux;
        aux = aux->next;
    }

    if(i == 0) {
        l->first = aux->next;
    } else if (i == l->len-1) {
        l->last = prev;
        prev->next = NULL;
    } else {
        prev->next = aux->next;
    }

    free(aux->b);
    free(aux);
    
    l->len--;
}

//Public
void cleanList(List * l){
    Node * aux = l->first;
    while (aux != NULL) {
        Node * next = aux->next;
        free (aux);
        aux = next;
    }
    l->first = NULL;
    l->last = NULL;
    l->len = 0;
}

//Public
void push(List * l, void * item) {
    Node * newNode = createNode(item);
    l->last->next = newNode;
    l->last = newNode;
    l->len++;
}

//Public
void pop(List * l) {
    Node * aux = l->first;
    Node * prev = NULL;

    while (aux->next != NULL) {
        prev = aux;
        aux = aux->next;
    }
    free(aux);
}

//Public
int length(List * l) {
    return l->len;
}

//Private
Node * createNode(void * item) {
    Node * n = (Node *) malloc(sizeof(struct node));
    n->next = NULL;
    n->b = item;
    return n;
}