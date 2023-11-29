#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void testesTrabalho(int escolha, int modo);

int main() {
    int op = 0, op1 = 0;

    while (1) {
        system("cls");
        printf("Insira o numero de uma das seguintes opcoes\n\n"
               "Opcao 1: Realizar os 10 testes do trabalho\n"
               "Opcao 2: Realizar um teste especifico\n"
               "Opcao 3: Sair\n"
               "Opcao: ");
        scanf("%d", &op);

        if (op == 3)
            break;

        switch (op) {
            case 1:
                system("cls");
                printf("Insira o numero de uma das seguintes opcoes\n\n"
                       "Opcao 1: Resultado das expressoes\n"
                       "Opcao 2: Traducao das expressoes para notacao pre-fixada\n"
                       "Opcao: ");
                scanf("%d", &op1);
                testesTrabalho(op, op1);
                break;
            case 2:
                system("cls");
                printf("Insira o numero de uma das seguintes opcoes\n\n"
                       "Opcao 1: Resultado da expressao\n"
                       "Opcao 2: Traducao da expressao para notacao pre-fixada\n"
                       "Opcao: ");
                scanf("%d", &op1);
                testesTrabalho(op, op1);
                break;

            default:
                system("cls");
                printf("Opcao invalida\n\n");
                system("pause");
                break;
        }
    }

    return 0;
}

void testesTrabalho(int escolha, int modo) {
    char expressaoEspecifica[100];
    char* expressao[10] = {
        "3 4 + 5 *",         // 1
        "7 2 * 4 +",         // 2
        "8 5 2 4 + * +",     // 3
        "6 2 / 3 + 4 *",     // 4
        "9 5 2 8 * 4 + * +", // 5
        "2 3 + log 5 /",     // 6
        "10 log 3 ^ 2 + ",   // 7
        "45 60 + 30 cos *",  // 8
        "0.5 45 sen 2 ^ +",  // 9
        "3 4 + 5 tan *"      // 10
    };

    system("cls");

    switch (escolha) {
        case 1:
            switch (modo) {
                case 1:
                    system("cls");
                    printf("Resultados:\n");
                    for (int i = 0; i < 10; i++) {
                        printf("Resultado %d: %.3f\n", i + 1, avaliarExpressaoPosfixada(expressao[i]));
                    }
                    printf("\n");
                    system("pause");
                    break;

                case 2:
                    system("cls");
                    printf("Traducoes:\n");
                    for (int i = 0; i < 10; i++) {
                        printf("traducao %i: %s\n", i + 1, posParaPre(expressao[i]));
                    }
                    system("pause");
                    break;

                default:
                    system("cls");
                    printf("Modo invalido\n\n");
                    system("pause");
                    break;
            }
            break;

        case 2:
            switch (modo) {
                case 1:
                    system("cls");
                    printf("Insira a expressao: ");
                    fflush(stdin);
                    fgets(expressaoEspecifica, sizeof(expressaoEspecifica), stdin);

                    size_t len = strlen(expressaoEspecifica);
                    if (len > 0 && expressaoEspecifica[len - 1] == '\n') {
                        expressaoEspecifica[len - 1] = '\0';
                    }

                    printf("Resultado: %.3f\n\n", avaliarExpressaoPosfixada(expressaoEspecifica));
                    system("pause");
                    break;

                case 2:
                    system("cls");
                    printf("Insira a expressao: ");
                    fflush(stdin);
                    gets(expressaoEspecifica);

                    printf("Traducao: %s\n\n", posParaPre(expressaoEspecifica));
                    system("pause");
                    break;

                default:
                    system("cls");
                    printf("Modo invalido\n\n");
                    system("pause");
                    break;
            }
            break;
    }
}
