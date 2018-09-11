#include <stdio.h>
#include <stdlib.h>

#include "../List.h"

typedef struct list List;
typedef struct nodeList NodeList;

struct nodeList {
    void * b;
    NodeList * next;
};

struct list {
    NodeList * first;
    NodeList * last;
    int len;
};

//Declaring
NodeList * createNode(void * item);

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
    NodeList * aux = l->first;
    while (aux != NULL) {
        NodeList * aux2 = aux->next;
        free(aux);
        aux = aux2;
    }
    l->first = NULL;
    l->last = NULL;
    l->len = 0;
}

//Public
void listAdd(List * l, void * item) {
    NodeList * newNode = createNode(item);
    
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
    NodeList * aux = l->first;
    NodeList * prev = NULL;

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
void setItem(List * l, int i, void * item) {
    if (i >= l->len){
		printf("Error: Index passou do limite");
		return;	
	}

    int count = 0;

    if(l != NULL) {
        NodeList * aux = l->first;
        while (aux != NULL) {
		if(i == count) {
			aux->b = item;
		}
		count++;
		aux = aux->next;
	}

    }
}

//Public
void * getValue(List * l, int index) {
	if (index >= l->len){
		printf("Error: Index passou do limite");
		return NULL;	
	}
	
	NodeList * aux = l->first;
	int count = 0;
	while (aux != NULL) {
		if(index == count) {
			return aux->b;
		}
		count++;
		aux = aux->next;
	}

    return NULL;
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
    NodeList * newNode = createNode(item);
    l->last->next = newNode;
    l->last = newNode;
    l->len++;
}

//Public
void pop(List * l) {
    NodeList * aux = l->first;
    NodeList * prev = NULL;

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
	void * * listArray = (void * *) malloc(l->len * sizeof(struct nodeList));
	//void * listArray[l->len];
	int i;
	NodeList * aux = l->first;
	for (i = 0; i < l->len; i++) {
		listArray[i] = aux->b;
		aux = aux->next;
	}
	return listArray;
}

//Private
NodeList * createNode(void * item) {
    NodeList * n = (NodeList *) malloc(sizeof(struct nodeList));
    n->next = NULL;
    n->b = item;
    return n;
}







