#include <stdlib.h>
#include <stdio.h>

#include "Tree.h"

#define bool int
#define false 0
#define true 1

typedef struct node Node;

struct node {
    int info;
    void * b;
    Node * right;
    Node * left;
};

//Public
Node * newNode(int info, void * b, Node * r, Node * l) {
    Node * node = (Node *) malloc(sizeof(struct node));
    node->b = b;
    node->info = info;
    node->left = l;
    node->right = r;

    return node;
}

//Public
void * getBin(Node * n) {
	return n->b;
}

//Public
void setRight(Node * root, Node * n) {
    root->right = n;
}

//Public
void setLeft(Node * root, Node * n){
    root->left = n;
}

//Public
Node * getRight(Node * n) {
    return n->right;
}

//Public
Node * getLeft(Node * n) {
    return n->left;
}

//Public
void printInOrdem(Node * root) {
    if(root != NULL) {
        printInOrdem(root->left);
        printf("%c ",root->info);
        printInOrdem(root->right);
    }
}

//Public
bool isLeaf(Node * node) {
    return node->left == NULL && node->right == NULL;
}

void cleanTree(Node * node) {
	if(node != NULL) {
		cleanTree(node->left);
		cleanTree(node->right);
		free(node->b);
		free(node);
	}
}




