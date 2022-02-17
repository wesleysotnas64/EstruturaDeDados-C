#include <stdio.h>
#include <stdlib.h>

void inserir(int elemento, int heap[], int *tamanho);

void imprimeHeap(int heap[], int tamanho);

int main(){

    int heap[15];
    int tamanho = 0;

    imprimeHeap(heap, tamanho);

    return 0;
}

void imprimeHeap(int heap[], int tamanho){ //O(n)
    if(tamanho >= 1){
        for(int i = 0; i < tamanho; i++){
         printf("[%d]\n", heap[i]);
        }
    } else printf("Heap vazia!\n");
    
}