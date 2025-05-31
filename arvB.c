#include <stdlib.h>
#include "arvB.h"

#include <stdio.h>


int letra (char x) {
    return (x >= 'A' && x<= 'Z') || (x >= 'a' && x<= 'z');
}

//(A,(B,(),()),(C,(F,(),()),()))
t_binary_tree* create (char* txt) {
    t_binary_tree* arv = malloc(sizeof(t_binary_tree));
    arv->raiz = NULL;
    arv->alt = 0;
    arv->nNos = 0;

    int I = 0, Cabe = 0, Cesp = 1;
    char ant = '\0';
    
    no** pilha = malloc(sizeof(no*) * 200);
    int size = 0;

    while (txt[I] != '\0') {

        if (txt[I] != ' ') {
            
            if (txt[I] == '(') {
                if (ant != ',' && ant != '\0') {
                    return NULL;
                }

                Cabe++;
                Cesp--;

            } else if (letra(txt[I])) {

                if (ant != '(') {
                    return NULL;
                }

                pilha[size] = malloc(sizeof(no));
                pilha[size]->v = txt[I];
                pilha[size]->di = NULL;
                pilha[size]->es = NULL;

                pilha[size + 1] = pilha[size];

                if (arv->raiz == NULL) {
                    arv->raiz = pilha[size];
                    pilha[size]->alt = 1;
                    
                } else {
                    if (size > 1 && pilha[size - 1]->v == pilha[size - 2]->v ) {
                        pilha[size - 1]->es = pilha[size];
                    } else {
                        pilha[size - 1]->di = pilha[size];
                    }
                    pilha[size]->alt = pilha[size - 1]->alt + 1;
                }
                if (pilha[size]->alt > arv->alt) {
                    arv->alt = pilha[size]->alt;
                }
                
                arv->nNos += 1;

                size += 2;
                Cesp += 2;

            } else if (txt[I] == ',') {

                if (ant != ')' && !letra(ant)) {
                    return NULL;
                }

            } else if (txt[I] == ')') {

                if (ant != '(' && ant != ')') {
                    return NULL;
                }

                size--;
                Cabe--;

            } else {
                return NULL;
            }

            ant = txt[I];
        }

        I++;
    }

    if (Cabe != 0 || Cesp != 0) {
        return NULL;
    }

    return arv;
}

void recIn (no* no, char* txt, int* fim) {
    if (no != NULL) {
        recIn(no->es, txt, fim);
        txt[*fim] = no->v;
        *fim += 1;
        recIn(no->di, txt, fim);
    }
}

char* inOrder (t_binary_tree* arv) {
    char* seq = malloc(sizeof(char) * 100);
    int fim = 0;

    recIn (arv->raiz, seq, &fim);
    return seq;
}

void recPre (no* no, char* txt, int* fim) {
    if (no != NULL) {
        txt[*fim] = no->v;
        *fim += 1;
        recPre(no->es, txt, fim);
        recPre(no->di, txt, fim);
    }
}

char* preOrder (t_binary_tree* arv) {
    char* seq = malloc(sizeof(char) * 100);
    int fim = 0;

    recPre (arv->raiz, seq, &fim);
    return seq;
}

void recPos (no* no, char* txt, int* fim) {
    if (no != NULL) {
        recPos(no->es, txt, fim);
        recPos(no->di, txt, fim);
        txt[*fim] = no->v;
        *fim += 1;
    }
}

char* posOrder (t_binary_tree* arv) {
    char* seq = malloc(sizeof(char) * 100);
    int fim = 0;

    recPos (arv->raiz, seq, &fim);
    return seq;
}

void recInPrin (no* no, int* esp, int* fim) {
    if (no != NULL) {
        int espa = 0;
        recInPrin(no->es, esp, fim);

        espa += 1 + esp[*fim - 1];
        esp[*fim] = espa;
        *fim += 1;

        recInPrin(no->di, esp, fim);
    }
}

void recInPrin2 (no* no, int* espacos, int* I, char** saida, int* sizes) {
    if (no != NULL) {
        recInPrin2(no->es, espacos, I, saida, sizes);
        
        while (sizes[no->alt - 1] < espacos[*I]) {
            saida[no->alt - 1][sizes[no->alt - 1]] = ' ';
            sizes[no->alt - 1] += 1;
        }
        saida[no->alt - 1][sizes[no->alt - 1]] = no->v;
        sizes[no->alt - 1] += 1;

        *I += 1;

        recInPrin2(no->di, espacos, I, saida, sizes);
    }
}

void print (t_binary_tree* arv) {
    if (arv->raiz == NULL) {
        return;
    }

    // dois percursos in order, o primeiro calcula o número de espaços e salva em um vetor,
    // o seugundo vai adicionar os espaços e as letras a saida.

    int espacos[arv->nNos + 1];
    espacos[0] = -1;
    int size = 1;
    recInPrin(arv->raiz, espacos, &size);

    char** saida = malloc(sizeof(char*) * arv->alt);
    for (int I = 0; I < arv->alt; I++) {
        saida[I] = malloc(sizeof(char) * arv->nNos);
    }

    int sizes[arv->alt];
    for (int I = 0; I < arv->alt; I++) {
        sizes[I] = 0;
    }

    int um = 1;
    recInPrin2(arv->raiz, espacos, &um, (char**)saida, sizes);
   
    for (int I = 0; I < arv->alt; I++) {
        saida[I][sizes[I]] = '\0';
        printf("%s\n", saida[I]);
        free(saida[I]);
    }
    free(saida);
}
  
int compStr(char* str1, char* str2) {
    int I = 0;
    while (str1[I] != '\0' && str2[I] != '\0') {
        if (str1[I] != str2[I]) {
            return 0;
        }
        I++;
    }
    if (str1[I] != str2[I]) {
        return 0;
    }
    return 1;
}

void ajustarSTR (char* str) {
    int I = 0;
    while (str[I] !='\n') {
        I++;   
    }
    str[I] = '\0';
}

void recFree (no* no) {
    if (no != NULL) {
        recFree(no->es);
        recFree(no->di);
        free(no);
    }
}

void freeArv (t_binary_tree* arv) {
    if (arv != NULL) {
        recFree(arv->raiz);
        free(arv);
    }
}

