#ifndef arvB_H
#define arvB_H

typedef struct no {
    char v;
    struct no* di;
    struct no* es;
    int alt;
} no;

typedef struct {
    no* raiz;
    int alt;
    int nNos;
} t_binary_tree;

t_binary_tree* create (char* txt);

char* inOrder (t_binary_tree* arv);

char* preOrder (t_binary_tree* arv);

char* posOrder (t_binary_tree* arv);

void print (t_binary_tree* arv);

int compStr(char* str1, char* str2);

void freeArv (t_binary_tree* arv);

void ajustarSTR (char* str);

#endif