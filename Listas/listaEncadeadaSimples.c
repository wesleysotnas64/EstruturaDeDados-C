#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO  *prox;
};


NO *criaNO(int chave); //1 - Existe | 2 - Não existe
int buscar(int chave, NO *ptInicio);
void addNOInicio(int chave, NO **ptInicio, NO **ptFim);
void addNOFim(int chave, NO **ptInicio, NO **ptFim);

void imprimeLista(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    //printf("%d\n", buscar(42, ptInicio)); 

    addNOInicio(10, &ptInicio, &ptFim);
    addNOInicio(42, &ptInicio, &ptFim);

    addNOInicio(10, &ptInicio, &ptFim);

    addNOFim(10, &ptInicio, &ptFim);
    addNOFim(15, &ptInicio, &ptFim);

    imprimeLista(ptInicio);

    //printf("%d\n", buscar(42, ptInicio)); 

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;

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

void addNOInicio(int chave, NO **ptInicio, NO **ptFim){ // Add Inicio - O(1)
    printf("ADD_INICIO. CHAVE = %d\n", chave);
    if(buscar(chave, (*ptInicio)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        //Direcionando o ponteiro fim. Caso seja o primeiro elemento.
        if((*ptInicio) == NULL && (*ptFim) == NULL) (*ptFim) = (*no);

        (*no)->prox = (*ptInicio);
        (*ptInicio) = (*no);

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void addNOFim(int chave, NO **ptInicio, NO **ptFim){ // Add Fim - O(1)
    printf("ADD_FIM. CHAVE = %d\n", chave);
    if(buscar(chave, (*ptInicio)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        //Direcionando o ponteiro inicio. Caso seja o primeiro elemento.
        if((*ptInicio) == NULL && (*ptFim) == NULL) (*ptInicio) = (*no);

        (*ptFim)->prox = (*no);
        (*ptFim)       = (*no);

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void imprimeLista(NO *ptInicio){ //Lista elementos - O(n)
    if(ptInicio != NULL){
        printf("[%d]\n", ptInicio->chave);
        if(ptInicio->prox !=NULL) imprimeLista(ptInicio->prox);
    } else printf("Fim da lista...\n");
}