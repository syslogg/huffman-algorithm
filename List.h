/* Criacao de estrutura de lista, Trabalho de Estrutura de Dados 2 */

/* setting */
typedef struct list List;

List * list();
void destroyList();

void listAdd(List * l, void * item);
void listRemove(List * l, int i);

void listClean(List * l);

void push(List * l, void * item);
void pop(List * l);

void * getValue(List * l, int index);
int getValueInt(List * l, int index);

int length(List * l);

void * * getAllList(List * l);