#include <stdio.h>
#include <stdlib.h>

typedef struct no NO;
struct no{
    int chave;
    NO *esq;
    NO *dir;
};

NO *criaNO(int chave);
void buscar(int chave, NO *pt, NO **pai, int *encontra);
void adicionar(int chave, NO **pt);
void imprimeIn(NO *pt);
void imprimePre(NO *pt);
void imprimePos(NO *pt);

int main(){

    NO *raiz = NULL;

    adicionar( 4, &raiz);
    imprimePos(raiz);
    adicionar( 2, &raiz);
    imprimePos(raiz);
    adicionar( 6, &raiz);
    imprimePos(raiz);
    adicionar( 1, &raiz);
    imprimePos(raiz);
    adicionar( 3, &raiz);
    imprimePos(raiz);
    adicionar( 5, &raiz);
    imprimePos(raiz);
    adicionar( 7, &raiz);
    imprimePos(raiz);

    return 0;
}

NO *criaNO(int chave){ //O(1)
    NO *novo = malloc(sizeof(NO));

    novo->chave = chave;
    novo->esq   = NULL;
    novo->dir   = NULL;

    return novo;
}

void buscar(int chave, NO *pt, NO **pai, int *encontra){
    printf(":::::::::::::::::::::::::\n");
    printf("INICIO - BUSCAR\n");
    if(pt != NULL){
        if(chave < pt->chave){
            printf("%d menor que %d\n", chave, pt->chave);
            if(pt->esq != NULL){
                (*pai) = pt;
                buscar(chave, pt->esq, &(*pai), encontra);
            } else{
                //(*pai) = pt;
                printf("Chave %d não existe a ESQ de %d\n", chave, (*pai)->chave);
                (*encontra) = 2;
            }
        } else if( chave > pt->chave){
            printf("%d maior que %d\n", chave, pt->chave);
            if(pt->dir != NULL){
                (*pai) = pt;
                buscar(chave, pt->dir, &(*pai), encontra);
            } else{
                //(*pai) = pt;
                printf("Chave %d não existe a DIR de %d\n", chave, (*pai)->chave);
                (*encontra) = 3;
            }
        } else{
            printf("Chave %d encontrada!\n", chave);
            (*encontra) = 1;
        } 
    } else{
        printf("Arvore vazia!\n");
        (*encontra) = 0;
    }

    printf("FIM - BUSCAR\n");
    printf(":::::::::::::::::::::::::\n"); 
}

void adicionar(int chave, NO **pt){
    printf("\n+++++++++++++++++++++++++\n");
    printf("INICIO - ADICIONAR %d\n", chave);

    NO *pai = (*pt);
    int encontra = 0;

    buscar(chave, (*pt), &pai, &encontra);

    if(encontra != 1){
        NO **no  = malloc(sizeof(NO*));
        (*no) = criaNO(chave);

        if(encontra == 0) (*pt) = (*no);
        if(encontra == 2) pai->esq = (*no);
        if(encontra == 3) pai->dir = (*no);
    } else printf("Chave [%d] existe!\n", chave);
    printf("FIM - ADICIONAR\n");
    printf("+++++++++++++++++++++++++\n\n");
}

void imprimeIn(NO *pt){//O(n)
    if(pt != NULL){
        if(pt->esq != NULL) imprimeIn(pt->esq);

        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir-> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);

        if(pt->dir != NULL) imprimeIn(pt->dir);
    }
}

void imprimePre(NO *pt){//O(n)
    if(pt != NULL){
        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir-> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);

        if(pt->esq != NULL) imprimeIn(pt->esq);
        if(pt->dir != NULL) imprimeIn(pt->dir);
    }
}

void imprimePos(NO *pt){//O(n)
    if(pt != NULL){
        if(pt->esq != NULL) imprimeIn(pt->esq);
        if(pt->dir != NULL) imprimeIn(pt->dir);
        
        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir-> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);
    }
}