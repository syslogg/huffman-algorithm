/* Criacao de estrutura de lista, Trabalho de Estrutura de Dados 2 */

/* setting */
typedef struct list List;

List * list();
void destroyList();

void add(List * l, void * item);
void * remove(List * l, int i);

void cleanList(List * l);

void push(List * l, void * item);
void pop(List * l);

int length(List * l);