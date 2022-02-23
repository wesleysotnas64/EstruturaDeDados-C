#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO *esq;
    NO *dir;
};

NO *criaNO(int chave);

int main(){
    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->esq  = NULL;
    novo->dir  = NULL;

    return novo;
}