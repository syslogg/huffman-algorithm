/* Criacao de estrutura de arvore, Trabalho de Estrutura de Dados 2 */

/* setting */
typedef struct node Node;

Node * newNode(int info, void * b, Node * r, Node * l);

void setRight(Node * root, Node * n);
void setLeft(Node * root, Node * n);

Node * getRight(Node * n);
Node * getLeft(Node * n);
void * getBin(Node * n);

void printInOrdem(Node * root);

void cleanTree(Node * node);
