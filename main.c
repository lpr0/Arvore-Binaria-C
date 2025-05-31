#include "arvB.h"
#include <stdlib.h>
#include <stdio.h>

#define verdadeiro ((void*) 1)
#define falso ((void*) 2)

int main () {
    char* input = malloc(sizeof(char) * 100);
    t_binary_tree* arv = NULL;
    char* txt = malloc(sizeof(char) * 500);
    
    while (!compStr(input,"exit")) {
        printf("create\t - Criar a árvore a partir da representação textual em parênteses;\npre\t - Imprimir em pre-ordem;\nin\t - Imprimir em in-ordem;\npost\t - Imprimir em pos-ordem;\nheight\t - Imprime a altura do nó n;\nprint\t - Imprime toda a árvore em modo texto;\nexit\t - Fechar programa.\n");
        scanf("%s", input);
        ajustarSTR(input);

        if (compStr(input, "create\0")) {
            printf("Digite a representação textual da arvore: \n");
            scanf("%s", txt); 
            ajustarSTR(txt);
            arv = create(txt);
            if (arv == NULL) {
                printf("Entrada inválida\n");
            } else {
                printf("Arvore criada\n");
            }
        } else if (compStr(input, "pre")) {
            if (arv == NULL) {
                printf("Crie uma arvore antes.\n");
            } else {
                printf(" %s \n", preOrder(arv));
            }
        } else if (compStr(input, "in")) {
            if (arv == NULL) {
                printf("Crie uma arvore antes.\n");
            } else {
                printf(" %s \n", inOrder(arv));
            }
        } else if (compStr(input, "post")) {
            if (arv == NULL) {
                printf("Crie uma arvore antes.\n");
            } else {
                printf(" %s \n", posOrder(arv));
            }
        } else if (compStr(input, "height")) {
            if (arv == NULL) {
                printf("Crie uma arvore antes.\n");
            } else {
                printf("Altura arvore: %d \n", arv->alt);
            }
        } else if (compStr(input, "print")) {
            if (arv == NULL) {
                printf("Crie uma arvore antes.\n");
            } else {
                print(arv);
            }
        }
    }

    freeArv(arv);
    free(input);
    free(txt);

    return 0;
}