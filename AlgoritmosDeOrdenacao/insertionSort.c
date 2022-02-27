#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10

void insertionSort(int vetor[], int tamanho);
void troca(int vetor[], int posi1, int posi2);
void imprimeVetor(int vetor[], int tamanho);

int main(){

    int vetor[TAMANHO];

    vetor[0] = 10;
    vetor[1] = 9;
    vetor[2] = 8;
    vetor[3] = 7;
    vetor[4] = 6;
    vetor[5] = 5;
    vetor[6] = 4;
    vetor[7] = 3;
    vetor[8] = 2;
    vetor[9] = 1;

    imprimeVetor(vetor, TAMANHO);

    insertionSort(vetor, TAMANHO);
    imprimeVetor(vetor, TAMANHO);

    return 0;
}


void insertionSort(int vetor[], int tamanho){//O(n^2)
    for(int i = 1; i < tamanho; i++){
        for(int j = i; j > 0; j--){
            if(vetor[j] < vetor[j-1]) troca(vetor, j, j-1);
        } 
    }
}

void troca(int vetor[], int posi1, int posi2){ //O(1)
    int aux = vetor[posi1];
    vetor[posi1] = vetor[posi2];
    vetor[posi2] = aux;
}

void imprimeVetor(int vetor[], int tamanho){ //O(n)
    for(int i = 0; i < tamanho; i++) printf("[%2d] ", vetor[i]);
    printf("\n");
}