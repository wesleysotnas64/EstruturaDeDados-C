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
void addNOInicio(int chave, NO **ptInicio, NO **ptFim);
void addNOFim(int chave, NO **ptInicio, NO **ptFim);

void imprimeListaIterativa(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    addNOInicio(3, &ptInicio, &ptFim);
    addNOInicio(2, &ptInicio, &ptFim);
    addNOInicio(1, &ptInicio, &ptFim);

    addNOFim(4, &ptInicio, &ptFim);
    addNOFim(5, &ptInicio, &ptFim);
    addNOFim(6, &ptInicio, &ptFim);

    imprimeListaIterativa(ptInicio);

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

void addNOInicio(int chave, NO **ptInicio, NO **ptFim){ //O(1)
    printf("-----------------------\n");
    printf("ADD_INICIO. CHAVE = %d\n", chave);

    if(buscar(chave, (*ptInicio)) == 0){
        
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if(tamanho((*ptInicio)) == 0){
            (*ptInicio) = (*no);
            (*ptFim)    = (*no);
            (*no)->prox = (*no);
            (*no)->ante = (*no);
        } else{
            (*no)->prox = (*ptInicio);
            (*no)->ante = (*ptFim);
            (*ptInicio)->ante = (*no);
            (*ptFim)->prox    = (*no);
            (*ptInicio) = (*no);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void addNOFim(int chave, NO **ptInicio, NO **ptFim){ //O(1)
    printf("-----------------------\n");
    printf("ADD_FIM. CHAVE = %d\n", chave);

    if(buscar(chave, (*ptInicio)) == 0){
        
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if(tamanho((*ptInicio)) == 0){
            (*ptInicio) = (*no);
            (*ptFim)    = (*no);
            (*no)->prox = (*no);
            (*no)->ante = (*no);
        } else{
            (*no)->prox = (*ptInicio);
            (*no)->ante = (*ptFim);
            (*ptInicio)->ante = (*no);
            (*ptFim)->prox    = (*no);
            (*ptFim) = (*no);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void imprimeListaIterativa(NO *ptInicio){//O(n)
    if(ptInicio != NULL){
        NO *ptAux = ptInicio;
        do{
            printf("%2d <- [%2d] -> %2d\n", ptAux->ante->chave, ptAux->chave, ptAux->prox->chave);
            ptAux = ptAux->prox;
            if(ptAux == ptInicio) break;
        }while(1);
    } 
}
