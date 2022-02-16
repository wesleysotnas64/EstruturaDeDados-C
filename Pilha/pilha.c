#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO *prox;
};

NO *criaNO(int chave);
int tamanho(NO *ptTopo);
int buscar(int chave, NO *ptTopo);
void add(int chave, NO **ptTopo);
void rmv(NO **ptTopo);
void imprimePilhaIterativa(NO *ptTopo);

int main(){

    NO *ptTopo = NULL;

    add(5, &ptTopo);
    add(4, &ptTopo);
    add(3, &ptTopo);
    add(2, &ptTopo);
    add(1, &ptTopo);

    imprimePilhaIterativa(ptTopo);

    rmv(&ptTopo);
    rmv(&ptTopo);
    rmv(&ptTopo);
    rmv(&ptTopo);
    rmv(&ptTopo);

    imprimePilhaIterativa(ptTopo);

    return 0;
}

NO *criaNO(int chave){
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->prox  = NULL;

    return novo;
}

int tamanho(NO *ptTopo){
    int contador = 0;
    if(ptTopo != NULL){
        NO *ptAux = ptTopo;
        
        while (1){
            contador++;
            if(ptAux->prox == NULL) break;
            else ptAux = ptAux->prox;
        }
    }
    return contador;
}

int buscar(int chave, NO *ptTopo){ //O(n)
    if(ptTopo != NULL){
        
        NO *ptAux = ptTopo;

        do{
            if(ptAux->chave == chave) return 1;
            else ptAux = ptAux->prox;
        } while(ptAux != NULL);    
    }

    printf("Chave %d não encontrado!\n", chave);
    return 0;
}

void add(int chave, NO **ptTopo){//O(1)
    printf("-----------------------\n");
    printf("ADD_TOPO. CHAVE = %d\n", chave);
    
    if(buscar(chave, (*ptTopo)) == 0){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if((*ptTopo) == NULL) (*ptTopo) = (*no);
        else{
            (*no)->prox = (*ptTopo);
            (*ptTopo) = (*no);
        }

        printf("Chave %d adicionada!\n", chave);
    } else printf("Chave %d existe! Não adicionado!\n", chave);
    printf("-----------------------\n");
}

void rmv(NO **ptTopo){//O(1)
    printf("-----------------------\n");
    if((*ptTopo) != NULL){
        printf("RMV_TOPO_DA_PILHA. CHAVE = %d\n", (*ptTopo)->chave);
        NO *lixo = (*ptTopo);

        if((*ptTopo)->prox == NULL) (*ptTopo) = NULL;
        else (*ptTopo) = (*ptTopo)->prox;
        
        int miniBuff = lixo->chave;
        free(lixo);

        printf("Chave %d removida!\n", miniBuff);
        printf("-----------------------\n");
    } else{
        printf("RMV FALHOU!\n");
        printf("-----------------------\n");
    }
}

void imprimePilhaIterativa(NO *ptTopo){//O(n)
    if(ptTopo != NULL){
        NO *ptAux = ptTopo;
        do{
            printf("[%2d]\n",ptAux->chave);
            ptAux = ptAux->prox;
            if(ptAux == NULL) break;
        }while(1);
    } 
}