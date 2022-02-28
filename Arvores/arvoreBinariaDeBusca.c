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
void remover(int chave, NO **pt, NO *raiz);
void menor(NO *pt, NO **substituto);
void maior(NO *pt, NO **substituto);
void imprimeIn(NO *pt);
void imprimePre(NO *pt);
void imprimePos(NO *pt);

int main(){

    NO *raiz = NULL;

    adicionar(40, &raiz);
    adicionar(20, &raiz);
    adicionar(60, &raiz);
    //adicionar(10, &raiz);
    //adicionar(30, &raiz);
    //adicionar(50, &raiz);
    //adicionar(70, &raiz);
    //adicionar(15, &raiz);
    //adicionar(25, &raiz);
    //adicionar(55, &raiz);
    //adicionar(65, &raiz);
    imprimePos(raiz);

    remover(40, &raiz, raiz);


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
        printf("NO atual: %d\n", pt->chave);
        if(chave < pt->chave){
            printf("%d menor que %d\n", chave, pt->chave);
            if(pt->esq != NULL){
                printf("Existe %d a ESQ de %d\n", pt->esq->chave, pt->chave);
                (*pai) = pt;
                printf("Status antes da recursiva\n");
                printf("Atual: %d\n", (*pai)->chave);
                printf("proximo: ");
                if((*pai)->esq != NULL) printf("%d\n", (*pai)->esq->chave);
                else printf("NULL\n");
                buscar(chave, pt->esq, &(*pai), encontra);
            } else{
                (*pai) = pt;
                printf("Chave %d não existe a ESQ de %d\n", chave, (*pai)->chave);
                (*encontra) = 2;
            }
        } else if( chave > pt->chave){
            printf("%d maior que %d\n", chave, pt->chave);
            if(pt->dir != NULL){
                printf("Existe %d a DIR de %d\n", pt->dir->chave, pt->chave);
                (*pai) = pt;
                printf("Status antes da recursiva\n");
                printf("Atual: %d\n", (*pai)->chave);
                printf("proximo: ");
                if((*pai)->dir != NULL) printf("%d\n", (*pai)->dir->chave);
                else printf("NULL\n");
                buscar(chave, pt->dir, &(*pai), encontra);
            } else{
                (*pai) = pt;
                printf("Chave %d não existe a DIR de %d\n", chave, (*pai)->chave);
                (*encontra) = 3;
            }
        } else{
            printf("Chave %d encontrada!\n", chave);
            printf("O pai dela é: %d\n", (*pai)->chave);
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

void remover(int chave, NO **pt, NO *raiz){
    printf("\n-------------------------\n");
    printf("INICIO - REMOVER %d\n", chave);

    NO *pai = (*pt);
    int encontra = 0;

    buscar(chave, (*pt), &pai, &encontra);

    if(encontra == 1){
        NO *lixo;
        if(chave == raiz->chave){//Caso especial. Separar para ficar mais fácil.
            lixo = (*pt);
            if(lixo->esq == NULL && lixo->dir == NULL){ //0 filhos
                (*pt) = NULL;
            } else if(lixo->esq != NULL || lixo->dir != NULL){//1 filho pelo menos
                if(lixo->esq != NULL) (*pt) = lixo->esq;
                else (*pt) = lixo->dir;
            } else{//2 filhos
                //Opta por substituir pelo 'maior a esquerda' OU o 'menor a direita'
                //MENOR A DIREITA
                NO *substituto      = lixo->dir;
                NO *paiDoSubstituto = lixo;

                printf("\nooooooooooooooooooooooooo\n");
                printf("BUSCANDO O MENOR A DIREITA DE %d!\n", lixo->chave);

                menor(lixo->dir, &substituto);

                printf("Substituto: %d", substituto->chave);
                printf("\nooooooooooooooooooooooooo\n\n");

                buscar(substituto->chave, lixo, &paiDoSubstituto, &encontra);

                if(substituto->dir == NULL){ //Se o substituto for folha
                    if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = NULL;
                    else paiDoSubstituto->dir = NULL;
                        
                    substituto->esq = lixo->esq;
                    substituto->dir = lixo->dir;

                    (*pt) = substituto;
                        
                } else{ //Se o substituto tem filho na direita
                    if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = substituto->dir;
                    else paiDoSubstituto->dir = substituto->dir;
                        
                    substituto->esq = lixo->esq;
                    substituto->dir = lixo->dir;

                    (*pt) = substituto;  
                }
            }
            
        } else{
            if(chave < pai->chave){//Se a chave estiver a esquerda do pai
                lixo = pai->esq;
                //Agora os 3 Casos do NO a ser removido: Se tem 0, 1 ou 2 filhos
                if(lixo->esq == NULL && lixo->dir == NULL){// É um NO folha. 0 filhos.
                    pai->esq = NULL;
                    free(lixo);
                } else if(lixo->esq == NULL || lixo->dir == NULL){ //Não é folha. Pelo menos um filho.
                    if(lixo->esq != NULL && lixo->dir == NULL){//Um filho na esquerda
                        pai->esq = lixo->esq;
                        free(lixo);
                    } else if(lixo->esq == NULL && lixo->dir != NULL){//Um filho na direita
                        pai->esq = lixo->dir;
                        free(lixo);
                    }
                } else{//Tem 2 filhos.
                    //Opta por substituir pelo maior a esquerda ou o menor a direita
                    //MENOR A DIREITA
                    NO *substituto      = lixo->dir;
                    NO *paiDoSubstituto = lixo;

                    printf("\nooooooooooooooooooooooooo\n");
                    printf("BUSCANDO O MENOR A DIREITA DE %d!\n", lixo->chave);

                    menor(lixo->dir, &substituto);

                    printf("Substituto: %d", substituto->chave);
                    printf("\nooooooooooooooooooooooooo\n\n");

                    buscar(substituto->chave, lixo, &paiDoSubstituto, &encontra);

                    if(substituto->dir == NULL){ //Se o substituto for folha
                        if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = NULL;
                        else paiDoSubstituto->dir = NULL;
                        
                        substituto->esq = lixo->esq;
                        substituto->dir = lixo->dir;

                        pai->esq = substituto;
                        
                    } else{ //Se o substituto tem filho na direita
                        if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = substituto->dir;
                        else paiDoSubstituto->dir = substituto->dir;
                        
                        substituto->esq = lixo->esq;
                        substituto->dir = lixo->dir;

                        pai->esq = substituto;
                        
                    }
                }
            } else if(chave > pai->chave){ //Se a chave estiver a direita do pai
                lixo = pai->dir;
                //Agora os 3 Casos do NO a ser removido: Se tem 0, 1 ou 2 filhos
                if(lixo->esq == NULL && lixo->dir == NULL){// É um NO folha. 0 filhos.
                    pai->dir = NULL;
                    free(lixo);
                } else if(lixo->esq == NULL || lixo->dir == NULL){ //Não é folha. Pelo menos um filho.
                    if(lixo->esq != NULL && lixo->dir == NULL){//Um filho na esquerda
                        pai->dir = lixo->esq;
                        free(lixo);
                    } else if(lixo->esq == NULL && lixo->dir != NULL){//Um filho na direita
                        pai->dir = lixo->dir;
                        free(lixo);
                    }
                } else{//Tem 2 filhos.
                    //Opta por substituir pelo maior a esquerda ou o menor a direita
                    //MAIOR A ESQUERDA
                    NO *substituto      = lixo->esq;
                    NO *paiDoSubstituto = lixo;

                    printf("\nooooooooooooooooooooooooo\n");
                    printf("BUSCANDO O MAIOR A ESQUERDA DE %d!\n", lixo->chave);

                    maior(lixo->esq, &substituto);

                    printf("Substituto: %d", substituto->chave);
                    printf("\nooooooooooooooooooooooooo\n\n");

                    buscar(substituto->chave, lixo, &paiDoSubstituto, &encontra);

                    if(substituto->esq == NULL){ //Se o substituto for folha
                        if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = NULL;
                        else paiDoSubstituto->dir = NULL;
                        
                        substituto->esq = lixo->esq;
                        substituto->dir = lixo->dir;

                        pai->dir = substituto;
                        
                    } else{ //Se o substituto tem filho na esquerda
                        if(substituto->chave < paiDoSubstituto->chave) paiDoSubstituto->esq = substituto->esq;
                        else paiDoSubstituto->dir = substituto->esq;
                        
                        substituto->esq = lixo->esq;
                        substituto->dir = lixo->dir;

                        pai->dir = substituto;
                        
                    }
                }
            }
        }
        
        free(lixo);
    } else printf("Chave %d inexistente!\n", chave);

    printf("FIM - REMOVER\n");
    printf("-------------------------\n\n");
}

void menor(NO *pt, NO **substituto){//retorna a menor chave
    if(pt->esq != NULL){
        (*substituto) = pt->esq;
        menor(pt->esq, &(*substituto));
    }
}

void maior(NO *pt, NO **substituto){//retorna a maior chave
    if(pt->dir != NULL){
        (*substituto) = pt->dir;
        maior(pt->dir, &(*substituto));
    }
}

void imprimeIn(NO *pt){//O(n)
    if(pt != NULL){
        if(pt->esq != NULL) imprimeIn(pt->esq);

        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir -> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);

        if(pt->dir != NULL) imprimeIn(pt->dir);
    }
}

void imprimePre(NO *pt){//O(n)
    if(pt != NULL){
        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir -> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);

        if(pt->esq != NULL) imprimePre(pt->esq);
        if(pt->dir != NULL) imprimePre(pt->dir);
    }
}

void imprimePos(NO *pt){//O(n)
    if(pt != NULL){
        if(pt->esq != NULL) imprimePos(pt->esq);
        if(pt->dir != NULL) imprimePos(pt->dir);
        
        printf("[%2d] | esq -> ", pt->chave);
        if(pt->esq == NULL) printf("NULL | dir -> ");
        else printf("[%2d] | dir -> ", pt->esq->chave);
        if(pt->dir == NULL) printf("NULL\n");
        else printf("[%2d]\n", pt->dir->chave);
    }
}