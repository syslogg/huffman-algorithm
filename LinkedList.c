#include <stdio.h>
#include <stdlib.h>

#include "List.h"

typedef struct list List;
typedef struct node Node;

struct node {
    void * b;
    Node * next;
};

struct list {
    Node * first;
    Node * last;
    int len;
};

//Declaring
Node * createNode(void * item);

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
    listClean(l);
    free(l);
}

//Public
void listClean(List * l) {
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
void listAdd(List * l, void * item) {
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
void listRemove(List * l, int i) {
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

    free(aux);
    
    l->len--;
}

//Public
void * getValue(List * l, int index) {
	if (index >= l->len){
		printf("Error: Index passou do limite");
		return NULL;	
	}
	
	Node * aux = l->first;
	int count = 0;
	while (aux != NULL) {
		if(index == count) {
			return aux->b;
		}
		count++;
		aux = aux->next;
	}
}

//Public
int getValueInt(List * l, int index) {
	void * value = getValue(l,index);
	if(value != NULL) {
		return * (int *) value;
	}
	return -1;
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

//Public
void * * getAllList(List * l) {
	void * * listArray = (void * *) malloc(l->len * sizeof(struct node));
	//void * listArray[l->len];
	int i;
	Node * aux = l->first;
	for (i = 0; i < l->len; i++) {
		listArray[i] = aux->b;
		aux = aux->next;
	}
	return listArray;
}

//Public
void * get(List * l, int i) {

}

//Private
Node * createNode(void * item) {
    Node * n = (Node *) malloc(sizeof(struct node));
    n->next = NULL;
    n->b = item;
    return n;
}







