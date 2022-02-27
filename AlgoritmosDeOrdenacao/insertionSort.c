#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

void insertionSort(int vetor[], int tamanho);
void imprimeVetor(int vetor[], int tamanho);

int main(){

    int vetor[TAMANHO];

    vetor[0] = 33;
    vetor[1] = 12;
    vetor[2] = 99;
    vetor[3] = 54;
    vetor[4] = 42;
    vetor[5] = 87;
    vetor[6] = 15;
    vetor[7] = 10;
    vetor[8] = 96;
    vetor[9] = 81;

    imprimeVetor(vetor, TAMANHO);

    insertionSort(vetor, TAMANHO);
    imprimeVetor(vetor, TAMANHO);

    return 0;
}


void insertionSort(int vetor[], int tamanho){//O(n^2)
    int aux;
    for(int i = 1; i < tamanho; i++){
        aux = vetor[i];
        for(int j = i; j > 0; j--){
            if(aux < vetor[j-1]){
                vetor[j] = vetor[j-1];
            } else{
                vetor[j] = aux;
                break;
            } 
        } 
    }
}

void imprimeVetor(int vetor[], int tamanho){ //O(n)
    for(int i = 0; i < tamanho; i++) printf("[%2d] ", vetor[i]);
    printf("\n");
}