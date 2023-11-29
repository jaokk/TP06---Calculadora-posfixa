#ifndef PILHA_H
#define PILHA_H

typedef struct {
    double dado;
    struct Item* proximo;
} Item;

typedef struct {
    Item* topo;
    int tamanho;
} Pilha;

Pilha* criarPilha();
int estaVazia(Pilha* p);
Item* criarItem(double dado);
void push(Pilha* p, double dado);
double pop(Pilha* p);
double topo(Pilha* p);
void liberarPilha(Pilha* p);
double avaliarExpressaoPosfixada(char* expressao);
char* posParaPre(char* expressao);

#endif
