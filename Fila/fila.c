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
void add(int chave, NO **ptInicio, NO **ptFim);
void rmv(NO **ptInicio, NO **ptFim);
void imprimeFilaIterativa(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    printf("TAMANHO = %d\n", tamanho(ptInicio));

    add(1, &ptInicio, &ptFim);
    add(2, &ptInicio, &ptFim);
    add(3, &ptInicio, &ptFim);
    add(4, &ptInicio, &ptFim);
    add(5, &ptInicio, &ptFim);
    add(6, &ptInicio, &ptFim);

    imprimeFilaIterativa(ptInicio);
    printf("TAMANHO = %d\n", tamanho(ptInicio));

    rmv(&ptInicio, &ptFim);
    rmv(&ptInicio, &ptFim);
    rmv(&ptInicio, &ptFim);
    rmv(&ptInicio, &ptFim);
    rmv(&ptInicio, &ptFim);
    rmv(&ptInicio, &ptFim);

    imprimeFilaIterativa(ptInicio);
    printf("TAMANHO = %d\n", tamanho(ptInicio));

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
            if(ptAux->prox == NULL) break;
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
        } while(ptAux != NULL);    
    }

    printf("Chave %d não encontrado!\n", chave);
    return 0;
}

void add(int chave, NO **ptInicio, NO **ptFim){//O(1)
    printf("-----------------------\n");
    printf("ADD_FIM_DA_FILA. CHAVE = %d\n", chave);
    
    if(buscar(chave, (*ptInicio)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if(tamanho((*ptInicio)) == 0){
            (*ptInicio) = (*no);
            (*ptFim) = (*no);
        } else{
            (*no)->ante = (*ptFim);
            (*ptFim)->prox = (*no);
            (*ptFim) = (*no);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void rmv(NO **ptInicio, NO **ptFim){//O(1)
    printf("-----------------------\n");
    if((*ptInicio) != NULL){
        printf("RMV_INICIO_DA_FILA. CHAVE = %d\n", (*ptInicio)->chave);
        NO *lixo = (*ptInicio);

        if((*ptInicio) == (*ptFim)){
            (*ptInicio) == NULL;
            (*ptFim) == NULL;
        } else{
            (*ptInicio) = (*ptInicio)->prox;
            (*ptInicio)->ante = NULL;
        }

        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV FALHOU!\n");
        printf("-----------------------\n");
    }
}

void imprimeFilaIterativa(NO *ptInicio){//O(n)
    if(ptInicio != NULL){
        NO *ptAux = ptInicio;
        do{
            printf("[%2d]\n",ptAux->chave);
            ptAux = ptAux->prox;
            if(ptAux == NULL) break;
        }while(1);
    } 
}
