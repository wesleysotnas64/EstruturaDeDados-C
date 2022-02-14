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
void addNOInicio(int chave, NO **ptInicio, NO **ptFim);
void addNOFim(int chave, NO **ptInicio, NO **ptFim);
void rmvNOInicio(NO **ptInicio, NO **ptFim);
void rmvNOFim(NO **ptInicio, NO **ptFim);
void rmvNOMeio(int chave, NO **ptInicio);
void rmv(int chave, NO **ptInicio, NO **ptFim);
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

    rmvNOInicio(&ptInicio, &ptFim);
    rmvNOFim(&ptInicio, &ptFim);
    rmvNOMeio(3, &ptInicio);
    rmv(4, &ptInicio, &ptFim);
    imprimeListaIterativa(ptInicio);

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
        } else{
            (*no)->prox = (*ptInicio);
            (*ptInicio) = (*no);
            (*ptFim)->prox = (*ptInicio);
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
        } else{
            (*ptFim)->prox = (*no);
            (*ptFim) = (*no);
            (*no)->prox = (*ptInicio);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void rmvNOInicio(NO **ptInicio, NO **ptFim){//O(1)
    printf("-----------------------\n");
    printf("RMV_INICIO. CHAVE = %d\n", (*ptInicio)->chave);
    if((*ptInicio) != NULL){

        NO *lixo = (*ptInicio);

        (*ptInicio) = lixo->prox;
        (*ptFim)->prox = (*ptInicio);
        
        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_INICIO FALHOU!\n");
        printf("-----------------------\n");
    }
}

void rmvNOFim(NO **ptInicio, NO **ptFim){//O(n)
    printf("-----------------------\n");
    printf("RMV_FIM. CHAVE = %d\n", (*ptFim)->chave);
    if((*ptInicio) != NULL){

        NO *lixo = NULL;
        NO *ptAux = (*ptInicio);

        while(1){
            if(ptAux->prox == (*ptFim)) break;
            else ptAux = ptAux->prox;
        }

        lixo = (*ptFim);
        (*ptFim) = ptAux;
        (*ptFim)->prox = (*ptInicio);
        
        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_FIM FALHOU!\n");
        printf("-----------------------\n");
    }
}

void rmvNOMeio(int chave, NO **ptInicio){ //O(n)
    printf("-----------------------\n");
    printf("RMV_MEIO. CHAVE = %d\n", chave);
    if((*ptInicio) != NULL){

        if(buscar(chave, (*ptInicio)) == 1){
            NO *lixo = (*ptInicio);
            NO *ptAux = (*ptInicio);

            while(1){
                if(ptAux->prox->chave == chave) break;
                else ptAux = ptAux->prox;
            }

            lixo = ptAux->prox;
            ptAux->prox = lixo->prox;
            
            int miniBuff = lixo->chave;
            free(lixo);

            printf("Chave %d removida!\n", miniBuff);
            printf("-----------------------\n");
        } else{
            printf("RMV_MEIO FALHOU!\n");
            printf("-----------------------\n");
        } 
    } else{
        
        printf("RMV_MEIO FALHOU!\n");
        printf("-----------------------\n");
    }
}

void rmv(int chave, NO **ptInicio, NO **ptFim){
    if(chave == (*ptInicio)->chave) rmvNOInicio(&(*ptInicio), &(*ptFim));
    else if(chave == (*ptFim)->chave) rmvNOFim(&(*ptInicio), &(*ptFim));
    else rmvNOMeio(chave, &(*ptInicio));
}

void imprimeListaIterativa(NO *ptInicio){//O(n)
    if(ptInicio != NULL){
        NO *ptAux = ptInicio;
        do{
            printf("[%2d] -> %2d\n",ptAux->chave, ptAux->prox->chave);
            ptAux = ptAux->prox;
            if(ptAux == ptInicio) break;
        }while(1);
    } 
}
