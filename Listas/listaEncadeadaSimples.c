#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO  *prox;
};

NO *criaNO(int chave); 
int buscar(int chave, NO *ptInicio); //1 - Existe | 2 - Não existe
void addNOInicio(int chave, NO **ptInicio, NO **ptFim);
void addNOFim(int chave, NO **ptInicio, NO **ptFim);
void rmvNOInicio(NO **ptInicio, NO **ptFim);
void rmvNOFim(NO **ptInicio, NO **ptFim);
void rmvNOMeio(int chave, NO **ptInicio, NO **ptFim);
void rmv(int chave, NO **ptInicio, NO **ptFim);

void imprimeLista(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    addNOInicio(10, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

    addNOInicio(42, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

    addNOInicio(10, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

    addNOFim(15, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

    addNOInicio(99, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

    rmv(10, &ptInicio, &ptFim);
    imprimeLista(ptInicio);

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

void rmvNOInicio(NO **ptInicio, NO **ptFim){
    if((*ptInicio) != NULL){
        printf("RMV_INICIO. CHAVE = %d\n", (*ptInicio)->chave);

        NO *lixo;
        lixo = (*ptInicio);
        
        if((*ptInicio) == (*ptFim)){ //Se existir apenas um elemento para ser removido
            (*ptInicio) = NULL;
            (*ptFim) = NULL;
        }  else (*ptInicio) = (*ptInicio)->prox;


        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_INICIO FALHOU! Lista vazia!\n");
        printf("-----------------------\n");
    } 
    
}

void rmvNOFim(NO **ptInicio, NO **ptFim){//O(n) pois tem que referenciar o penultimo
    if((*ptFim) != NULL){
        printf("RMV_FIM. CHAVE = %d\n", (*ptInicio)->chave);

        NO *lixo;
        lixo = (*ptFim);
        
        if((*ptInicio) == (*ptFim)){ //Se existir apenas um elemento para ser removido
            (*ptInicio) = NULL;
            (*ptFim) = NULL;
        }  else{ // Se não, tem que pegar o penultimo 'O(n)' e referenciar
            NO *aux = (*ptInicio);

            while (1){
                if(aux->prox == (*ptFim)) break;
                else aux = aux->prox;
            }

            (*ptFim) = aux;
            (*ptFim)->prox = NULL;
        } 


        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_INICIO FALHOU! Lista vazia!\n");
        printf("-----------------------\n");
    } 
}

void rmvNOMeio(int chave, NO **ptInicio, NO **ptFim){ //O(n)
    if((*ptInicio) !=  NULL){
        printf("RMV_MEIO. CHAVE = %d\n", chave);

        NO *aux;
        aux = (*ptInicio);

        NO *lixo;
        while(1){
            if(aux->prox->chave == chave){
                lixo = aux->prox;
                aux->prox = aux->prox->prox;
                break;
            } else aux = aux->prox;
        }

        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_MEIO FALHOU! Lista vazia!\n");
        printf("-----------------------\n");
    }
}

void rmv(int chave, NO **ptInicio, NO **ptFim){
    if(chave == (*ptInicio)->chave) rmvNOInicio(&(*ptInicio), &(*ptFim));
    else if(chave == (*ptFim)->chave) rmvNOFim(&(*ptInicio), &(*ptFim));
    else rmvNOMeio(chave, &(*ptInicio), &(*ptFim));
}

void imprimeLista(NO *ptInicio){ //Lista elementos - O(n)
    if(ptInicio != NULL){
        printf("[%d]\n", ptInicio->chave);
        if(ptInicio->prox !=NULL) imprimeLista(ptInicio->prox);
    } else printf("Fim da lista...\n");
}