/*
    Nesta heap máxima, encare o NULL como o número '0'.
*/

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 15

void inserir(int elemento, int heap[], int tamanho, int *quantidade);
int remover(int heap[], int *quantidade);
void inicializaHeap(int heap[], int tamanho);
void subir(int heap[], int posicao, int quantidade);
void imprimeHeap(int heap[], int tamanho);

//auxiliar
int par(int posicao);
void troca(int heap[], int posi1, int posi2);

int main(){

    int heap[TAMANHO];
    int quantidade = 0;

    inicializaHeap(heap, TAMANHO);

    imprimeHeap(heap, TAMANHO);

    inserir(10, heap, TAMANHO, &quantidade);
    inserir(20, heap, TAMANHO, &quantidade);
    inserir(12, heap, TAMANHO, &quantidade);
    inserir(37, heap, TAMANHO, &quantidade);
    inserir(11, heap, TAMANHO, &quantidade);
    inserir(99, heap, TAMANHO, &quantidade);
    inserir(13, heap, TAMANHO, &quantidade);

    imprimeHeap(heap, TAMANHO);

    //int item = remover(heap, &quantidade);
    //imprimeHeap(heap, TAMANHO);
    //printf("%d\n", quantidade);
    //printf("%d\n", item);

    return 0;
}

void inserir(int elemento, int heap[], int tamanho, int *quantidade){
    printf("-------------------\n");
    printf("INSERINDO ELEMENTO %d DA HEAP!\n", elemento);
    if((*quantidade) < tamanho){
        heap[(*quantidade)] = elemento;
        (*quantidade)++;
        if((*quantidade) > 1) subir(heap, (*quantidade)-1, (*quantidade));
    } else printf("Heap cheia!\n");
    printf("-------------------\n");
}

int remover(int heap[], int *quantidade){
    printf("-------------------\n");
    printf("REMOVENDO ELEMENTO %d DA HEAP!\n", heap[0]);
    int elemento = heap[0];
    if((*quantidade) == 0) printf("Heap vazia!\n");
    else{
        if((*quantidade) == 1) heap[0] = 0;
        else{
            heap[0] = heap[(*quantidade)-1];
            heap[(*quantidade)-1] = 0;
            //descer()
        }
        (*quantidade)--;
    }
    printf("-------------------\n");
    return elemento;
}

void inicializaHeap(int heap[], int tamanho){
    for(int i = 0; i < tamanho; i++) heap[i] = 0;
}

void subir(int heap[], int posicao, int quantidade){ //O(log n)
    printf("-------------------\n");
    printf("SUBIR!\n");
    if(quantidade > 1){
        if(posicao > 0){
            int pai;
            int irmao;

            //'cast' acontece automático
            if(par(posicao)) pai = (posicao/2)-1;
            else pai = posicao/2;

            if(heap[posicao] > heap[pai]){
                //troca. verificando se o irmão é maior. Se sim, então sobe o irmão
                if(par(posicao)){ //Filho da direita
                    irmao = posicao-1;
                    if(heap[irmao] > heap[posicao]) subir(heap, irmao, quantidade);
                    else troca(heap, posicao, pai);
                } else{//Filho da esquerda
                    irmao = posicao+1;
                    if(heap[posicao] < heap[irmao]) subir(heap, irmao, quantidade);
                    else troca(heap, posicao, pai);
                }
            }

            subir(heap, pai, quantidade);
        } else printf("Na raiz! Subir parou.\n");
    } else printf("Heap vazia!\n");
    printf("-------------------\n");
}

void imprimeHeap(int heap[], int tamanho){ //O(n)
    printf("-------------------\n");
    printf("IMPRIMINDO HEAP!\n");
    if(tamanho >= 1){
        for(int i = 0; i < tamanho; i++) printf("%2d -> [%2d]\n", i, heap[i]);
    } else printf("Heap vazia!\n");
    printf("-------------------\n");
}

//Auxiliar

//Retorna '1' se é par e '0' se for impar
int par(int posicao){
    if(posicao%2 == 0) return 1;
    else return 0;
}

void troca(int heap[], int posi1, int posi2){
    printf("[%d] : %d -> %d\n", heap[posi1], posi1, posi2);
    int aux = heap[posi1];
    heap[posi1] = heap[posi2];
    heap[posi2] = aux;
}