#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO *prox;
    NO *ante;
};

NO *criaNO(int chave);
int tamanho(NO *ptInicio);
int buscar(int chave, NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;
    novo->ante  = NULL;

    return novo;
}

int tamanho(NO *ptInicio){
    int contador = 0;
    if(ptInicio != NULL){
        NO *ptAux = ptInicio;
        
        while (1){
            contador++;
            if(ptAux->prox == ptInicio) break;
            else ptAux = ptAux->prox;
        }
    }
    return contador;
}

int buscar(int chave, NO *ptInicio){ //O(n)
    if(ptInicio != NULL){
        
        NO *ptAux = ptInicio;

        do{
            if(ptAux->chave == chave) return 1;
            else ptAux = ptAux->prox;
        } while(ptAux != ptInicio);    
    }

    printf("Chave %d não encontrado!\n", chave);
    return 0;
}


