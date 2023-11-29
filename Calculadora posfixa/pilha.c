#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (!p) {
        printf("Erro: Falha ao alocar memória para a pilha.\n");
        exit(EXIT_FAILURE);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

int estaVazia(Pilha* p) {
    return p->topo == NULL;
}

Item* criarItem(double dado) {
    Item* novoItem = (Item*)malloc(sizeof(Item));
    if (!novoItem) {
        printf("Erro: Falha ao alocar memória para o item.\n");
        exit(EXIT_FAILURE);
    }
    novoItem->dado = dado;
    novoItem->proximo = NULL;
    return novoItem;
}

void push(Pilha* p, double dado) {
    Item* novoItem = criarItem(dado);
    novoItem->proximo = p->topo;
    p->topo = novoItem;
    p->tamanho = p->tamanho + 1;
}

double pop(Pilha* p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia, não é possível desempilhar.\n");
        exit(EXIT_FAILURE);
    }
    Item* temp = p->topo;
    double dado = temp->dado;
    p->topo = temp->proximo;
    free(temp);
    p->tamanho = p->tamanho - 1;
    return dado;
}

double topo(Pilha* p) {
    if (estaVazia(p)) {
        printf("Erro: Pilha vazia, não há elementos para visualizar.\n");
        exit(EXIT_FAILURE);
    }
    return p->topo->dado;
}

void liberarPilha(Pilha* p) {
    while (!estaVazia(p)) {
        pop(p);
    }
    free(p);
}

double avaliarExpressaoPosfixada(char* expressao) {
    Pilha* p = criarPilha();
    double operando1;
    double operando2;
    char temp[100];
    int controle = 0;

    for (int i = 0; expressao[i] != '\0'; i++) {
        for(int i = 0; i < 100; i++) {
            temp[i] = ' ';
        }
        controle = 0;
        if (isdigit(expressao[i])) {
            for(int j = i; expressao[j] != ' '; j++) {
                temp[controle] = expressao[j];
                i++;
                controle++;
            }
            push(p, strtof(temp, NULL));
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            continue;
        } else {
            if(expressao[i]=='l'
            || expressao[i]=='r' 
            || expressao[i]=='c' 
            || expressao[i]=='s' 
            || expressao[i]=='t'){
                operando1 = pop(p);
            }else {
                operando1 = pop(p);
                operando2 = pop(p); 
            }
        
            switch (expressao[i]) {
                case '+':
                    push(p, operando2 + operando1);
                    break;
                case '-':
                    push(p, operando2 - operando1);
                    break;
                case '*':
                    push(p, operando2 * operando1);
                    break;
                case '/':
                    if (operando2 != 0.0) {
                        push(p, operando2 / operando1);
                    } else {
                        printf("Erro: Divisão por zero\n");
                        return 1;
                    }
                    break;
                case '^':
                    push(p, pow(operando1, operando2));
                    break;
                case 'r':
                    push(p, sqrt(operando1));
                    break;
                case 'l':
                    if((expressao[i] + expressao[i+1] + expressao[i+2]) == ('l' + 'o' + 'g')) {
                        push(p,((double)log10(operando1)));
                        i += 2;
                    }else {
                        printf("Erro: Operador inválido | log\n");
                    }
                    break;
                case 'c':
                    if((expressao[i] + expressao[i+1] + expressao[i+2]) == ('c' + 'o' + 's')) {
                        push(p,((double)cos(operando1)));
                        i += 2;
                    }else {
                        printf("Erro: Operador inválido | cos\n");
                    }
                    break;
                case 's':
                    if((expressao[i] + expressao[i+1] + expressao[i+2]) == ('s' + 'e' + 'n')) {
                        push(p,((double)sin(operando1)));
                        i += 2;
                    }else {
                        printf("Erro: Operador inválido | sen\n");
                    }
                    break;
                case 't':
                    if((expressao[i] + expressao[i+1] + expressao[i+2]) == ('t' + 'a' + 'n')) {
                        push(p,((double)tan(operando1)));
                        i += 2;
                    }else {
                        printf("Erro: Operador inválido | tan\n");
                    }
                    break;
                default:
                    printf("Erro: Operador inválido | padrao\n");
                    return 1;
            }
        }
    }
    return pop(p);
}

char* posParaPre(char* expressao) {
    int tam = 0, controle = 0;

    while (expressao[tam] != '\0') {
        tam++;
    }

    char* expressaoInvertida = malloc(tam + 1);
    expressaoInvertida[tam] = '\0';

    char temp[tam + 1];

    for(int i = tam - 1, j = 0; i >= 0; i--, j++) {
        if(isdigit(expressao[i])) {
            for(int k = i; isdigit(expressao[k]); k--, i--, controle++) {
                if(expressao[k - 1] == '.') {
                    temp[controle] = expressao[k];
                    temp[controle + 1] = expressao[k - 1];
                    controle++;
                    k--;
                    i--;
                } else {
                    temp[controle] = expressao[k];
                }
            }
            i++;
            for(int l = controle - 1; l >= 0; l--, j++) {
                expressaoInvertida[j] = temp[l];
            }
            j--; 
            controle = 0;  
        } else {
            if(expressao[i] == ' ' 
            || expressao[i] == '+' 
            || expressao[i] == '-' 
            || expressao[i] == '*'
            || expressao[i] == '/'
            || expressao[i] == 'r'
            || expressao[i] == '^') {
                expressaoInvertida[j] = expressao[i];
            } else {
                if(expressao[i] == 'g' 
                || expressao[i] == 'n' 
                || expressao[i] == 's') {
                    expressaoInvertida[j] = expressao[i-2];
                    j++;
                    expressaoInvertida[j] = expressao[i-1];
                    j++;
                    expressaoInvertida[j] = expressao[i];
                    i -= 2;
                }
            }
        }
    }

    return expressaoInvertida;

}
