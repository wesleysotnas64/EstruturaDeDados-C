#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO  *prox;
    NO  *ante;
};

NO *criaNO(int chave);
int buscar(int chave, NO *ptInicio); //1 - Existe | 2 - Não existe

int main(){

    NO *ptInicio;
    NO *ptFim;

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;
    novo->ante  = NULL;

    return novo;
}

int buscar(int chave, NO *ptInicio){
    if(ptInicio != NULL){
        if(ptInicio->chave == chave) return 1;
        else return buscar(chave, ptInicio->prox);
    } else{
        printf("Chave %d não encontrado!\n", chave);
        return 0;
    } 
}