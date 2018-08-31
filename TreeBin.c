#include <stdlib.h>
#include <stdio.h>

#include "Tree.h"

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
void rmNode(Node * root) {
    if(root != NULL) {
        Node * r = root->right;
        Node * l = root->left;
        free(root->b);
        free(root);
        cleanTree(r);
        cleanTree(l);
    }
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
        printf("%d ",root->info);
        printInOrdem(root->right);
    }
}




