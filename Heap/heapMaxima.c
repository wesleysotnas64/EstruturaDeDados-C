/*
    Nesta heap máxima, encare o NULL como o número '0'.
*/

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 15

void inserir(int elemento, int heap[], int tamanho, int *quantidade);
int remover(int heap[], int *quantidade);
void inicializaHeap(int heap[], int tamanho);
void imprimeHeap(int heap[], int tamanho);

int main(){

    int heap[TAMANHO];
    int quantidade = 0;

    inicializaHeap(heap, TAMANHO);

    imprimeHeap(heap, TAMANHO);

    inserir(10, heap, TAMANHO, &quantidade);

    imprimeHeap(heap, TAMANHO);

    int item = remover(heap, &quantidade);
    imprimeHeap(heap, TAMANHO);
    printf("%d\n", quantidade);
    printf("%d\n", item);

    return 0;
}

void inserir(int elemento, int heap[], int tamanho, int *quantidade){
    printf("-------------------\n");
    printf("INSERINDO ELEMENTO %d DA HEAP!\n", elemento);
    if((*quantidade) < tamanho){
        heap[(*quantidade)] = elemento;
        //subir()
        (*quantidade)++;
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

void imprimeHeap(int heap[], int tamanho){ //O(n)
    printf("-------------------\n");
    printf("IMPRIMINDO HEAP!\n");
    if(tamanho >= 1){
        for(int i = 0; i < tamanho; i++) printf("%2d -> [%2d]\n", i, heap[i]);
    } else printf("Heap vazia!\n");
    printf("-------------------\n");
}