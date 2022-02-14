#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO  *prox;
    NO  *ante;
};

NO *criaNO(int chave);
int tamanho(NO *ptInicio);
int buscar(int chave, NO *ptInicio); //1 - Existe | 2 - Não existe
void addNOInicio(int chave, NO **ptInicio, NO **ptFim);
void addNOFim(int chave, NO **ptInicio, NO **ptFim);
void addNOMeio(int chave, int posicao, NO **ptInicio, NO **ptFim);
void rmvNOInicio(NO **ptInicio, NO **ptFim);
void rmvNOFim(NO **ptInicio, NO **ptFim);
void rmvNOMeio(int chave, NO **ptInicio, NO **ptFim);
void rmv(int chave, NO **ptInicio, NO **ptFim);
void rmvPosicao(int posicao, NO **ptInicio, NO **ptFim);
void imprimeListaIterativa(NO *ptInicio);
void imprimeListaRecursiva(NO *ptInicio);

int main(){

    NO *ptInicio = NULL;
    NO *ptFim    = NULL;

    addNOInicio(10, &ptInicio, &ptFim);
    addNOInicio(17, &ptInicio, &ptFim);
    addNOInicio(99, &ptInicio, &ptFim);
    addNOInicio(72, &ptInicio, &ptFim);
    addNOFim   (42, &ptInicio, &ptFim);
    addNOFim   (98, &ptInicio, &ptFim);
    addNOFim   (15, &ptInicio, &ptFim);
    addNOMeio  (37, 3, &ptInicio, &ptFim);

    imprimeListaIterativa(ptInicio);
    printf("Tamanho: %d\n", tamanho(ptInicio));

    rmvNOInicio(&ptInicio, &ptFim);
    imprimeListaRecursiva(ptInicio);
    rmvNOFim(&ptInicio, &ptFim);
    imprimeListaRecursiva(ptInicio);
    rmvNOMeio(42, &ptInicio, &ptFim);
    imprimeListaRecursiva(ptInicio);
    rmv(99, &ptInicio, &ptFim);
    imprimeListaRecursiva(ptInicio);
    rmvPosicao(3, &ptInicio, &ptFim);

    imprimeListaIterativa(ptInicio);
    printf("Tamanho: %d\n", tamanho(ptInicio));

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
    if(ptInicio == NULL) return 0;
    else return 1 + tamanho(ptInicio->prox);
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
    printf("-----------------------\n");
    printf("ADD_INICIO. CHAVE = %d\n", chave);
    if(buscar(chave, (*ptInicio)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        //Direcionando os ponteiros inicio e fim. Caso seja o primeiro elemento.
        if((*ptInicio) == NULL && (*ptFim) == NULL){
            (*ptInicio) = (*no);
            (*ptFim)    = (*no);
        } else{
            (*ptInicio)->ante = (*no);
            (*no)->prox       = (*ptInicio);
            (*ptInicio)       = (*no);
        }
        
        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void addNOFim(int chave, NO **ptInicio, NO **ptFim){ // Add Fim - O(1)
    printf("-----------------------\n");
    printf("ADD_FIM. CHAVE = %d\n", chave);
    if(buscar(chave, (*ptInicio)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        //Direcionando os ponteiros inicio e fim. Caso seja o primeiro elemento.
        if((*ptInicio) == NULL && (*ptFim) == NULL){
            (*ptInicio) = (*no);
            (*ptFim)    = (*no);
        } else{
            (*ptFim)->prox = (*no);
            (*no)->ante    = (*ptFim);
            (*ptFim)       = (*no);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void addNOMeio(int chave, int posicao, NO **ptInicio, NO **ptFim){//O(n). Caso médio = O(n/2) = O(n)
    printf("-----------------------\n");
    printf("ADD_MEIO. CHAVE = %d\n", chave);
    printf("POSICAO: %d\n", posicao);
    if(buscar(chave, (*ptInicio)) == 0){

        int tamanhoLista = tamanho((*ptInicio));

        if(posicao <= 0) addNOInicio(chave, &(*ptInicio), &(*ptFim));
        else if(posicao >= tamanhoLista) addNOFim(chave, &(*ptInicio), &(*ptFim));
        else{
            NO **no = malloc(sizeof(NO*));
            (*no) = criaNO(chave);

            //Procura a posicao. Posição da lista inicia em '0', como em um vetor.
            NO  *ptAux = (*ptInicio);
            for(int i = 0; i < posicao-1; i++) ptAux = ptAux->prox;
            
            (*no)->prox = ptAux->prox;
            (*no)->ante = ptAux;
            ptAux->prox->ante = (*no);
            ptAux->prox = (*no);
            printf("Chave %d adicionada!\n", chave);
        }

    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void rmvNOInicio(NO **ptInicio, NO **ptFim){//O(1)
    printf("-----------------------\n");
    if((*ptInicio) != NULL){
        printf("RMV_INICIO. CHAVE = %d\n", (*ptInicio)->chave);

        NO *lixo;
        lixo = (*ptInicio);
        
        if((*ptInicio) == (*ptFim)){ //Se existir apenas um elemento para ser removido
            (*ptInicio) = NULL;
            (*ptFim) = NULL;
        }  else{
            (*ptInicio) = (*ptInicio)->prox;
            (*ptInicio)->ante = NULL;
        } 


        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_INICIO FALHOU!\n");
        printf("-----------------------\n");
    } 
    
}

void rmvNOFim(NO **ptInicio, NO **ptFim){//O(1) pois há o ptAntes
    printf("-----------------------\n");
    if((*ptFim) != NULL){
        printf("RMV_FIM. CHAVE = %d\n", (*ptFim)->chave);

        NO *lixo;
        lixo = (*ptFim);
        
        if((*ptInicio) == (*ptFim)){ //Se existir apenas um elemento para ser removido
            (*ptInicio) = NULL;
            (*ptFim) = NULL;
        }  else{
            (*ptFim) = (*ptFim)->ante;
            (*ptFim)->prox = NULL;
        } 


        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV_FIM FALHOU!\n");
        printf("-----------------------\n");
    } 
}

//Remove o primeiro 'NO' com a chave igual
void rmvNOMeio(int chave, NO **ptInicio, NO **ptFim){ //O(n)
    printf("-----------------------\n");
    if((*ptInicio) !=  NULL){
        printf("RMV_MEIO. CHAVE = %d\n", chave);

        //Verificar se a chave existe
        if(buscar(chave, (*ptInicio)) == 1){
            NO *aux;
            aux = (*ptInicio);

            NO *lixo;
            while(1){
                if(aux->prox->chave == chave){
                    lixo = aux->prox;
                    aux->prox->prox->ante = aux;
                    aux->prox = aux->prox->prox;
                    break;
                } else aux = aux->prox;
            }

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
    else rmvNOMeio(chave, &(*ptInicio), &(*ptFim));
}

void rmvPosicao(int posicao, NO **ptInicio, NO **ptFim){
    printf("-----------------------\n");
    printf("RMV_POSICAO = %d\n", posicao);
    if(posicao <= 0) rmvNOInicio(&(*ptInicio), &(*ptFim));
    else if(posicao >= tamanho((*ptInicio))-1) rmvNOFim(&(*ptInicio), &(*ptFim));
    else{
        
        NO *lixo  = NULL;
        NO *ptAux = (*ptInicio);

        //pode parar em cima da posição, pois tem referẽncia dos dois lados.
        for(int i = 0; i < posicao; i++) ptAux = ptAux->prox;
        
        lixo = ptAux;
        lixo->ante->prox = lixo->prox;
        lixo->prox->ante = lixo->ante;

        int miniBuff = lixo->chave;

        free(lixo);

        printf("CHAVE %d REMOVINA DA POSICAO %d\n", miniBuff, posicao);
        printf("-----------------------\n");
    }
}

void imprimeListaIterativa(NO *ptInicio){ //O(n)
    NO *ptAux = ptInicio;

    if(ptAux == NULL) printf("NULL <- ptInicio <- ptFim\n");
    else{
        if(tamanho(ptAux) == 1) printf("[%d] <- ptInicio <- ptFim\n", ptAux->chave);
        else{
            printf("[%d] <- Inicio\n", ptAux->chave);
            while(1){
                if(ptAux->prox->prox == NULL){
                    ptAux = ptAux->prox;
                    break;
                } else{
                    ptAux = ptAux->prox;
                    printf("[%d]\n", ptAux->chave);
                }
            }
            printf("[%d] <- ptFim\n", ptAux->chave);
        }
    }
}

void imprimeListaRecursiva(NO *ptInicio){
    if(ptInicio != NULL){
        printf("[%d]\n", ptInicio->chave);
        if(ptInicio->prox !=NULL) imprimeListaRecursiva(ptInicio->prox);
    } else printf("Fim da lista...\n");
}