#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO  *prox;
};


NO *criaNO(int chave);
void addNO(int chave, NO **ptInicio);

void imprimeLista(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;

    addNO(10, &ptInicio);
    addNO(42, &ptInicio);

    imprimeLista(ptInicio);

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;

    return novo;
}

void addNO(int chave, NO **ptInicio){ // Add Inicio - O(1)
    NO **no  = malloc(sizeof(NO*));
    (*no) = criaNO(chave);

    (*no)->prox = (*ptInicio);
    (*ptInicio) = (*no);
}

void imprimeLista(NO *ptInicio){ //Lista elementos - O(n)
    if(ptInicio != NULL){
        printf("[%d]\n", ptInicio->chave);
        if(ptInicio->prox !=NULL) imprimeLista(ptInicio->prox);
    } else printf("Fim da lista...\n");
}