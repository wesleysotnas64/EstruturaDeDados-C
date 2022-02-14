#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO *prox;
};

NO *criaNO(int chave);
int tamanho(NO *ptInicio);
int buscar(int chave, NO *ptInicio);
void addNOInicio(int chave, NO **ptInicio);

void imprimeListaRecursiva(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;

    addNOInicio(12, &ptInicio);
    addNOInicio(11, &ptInicio);
    addNOInicio(10, &ptInicio);
    addNOInicio(9, &ptInicio);
    addNOInicio(8, &ptInicio);
    addNOInicio(7, &ptInicio);
    addNOInicio(6, &ptInicio);
    addNOInicio(5, &ptInicio);
    addNOInicio(4, &ptInicio);
    addNOInicio(3, &ptInicio);
    addNOInicio(2, &ptInicio);
    addNOInicio(1, &ptInicio);
    

    //imprimeListaRecursiva(ptInicio);

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;

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

void addNOInicio(int chave, NO **ptInicio){ //O(1)
    printf("-----------------------\n");
    printf("ADD_INICIO. CHAVE = %d\n", chave);

    if(buscar(chave, (*ptInicio)) == 0){
        
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if(tamanho((*ptInicio)) == 0){
            (*ptInicio) = (*no);
            (*no)->prox = (*ptInicio);
        } else{
            
            NO *ptAux = (*ptInicio)->prox;
            while(1){
                if(ptAux->prox == (*ptInicio)) break;
                else ptAux = ptAux->prox;
            }
            (*no)->prox = (*ptInicio);
            (*ptInicio) = (*no);
            ptAux->prox = (*ptInicio);
        }

        

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void imprimeListaRecursiva(NO *ptInicio){
    if(ptInicio != NULL){
        printf("[%2d] -> %2d\n",ptInicio->chave, ptInicio->prox->chave);
        if(ptInicio->prox != ptInicio) imprimeListaRecursiva(ptInicio->prox);
    } 
}