#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../utils/index.h" 
#define MAX 400000 

// 100000 200000 400000

void trocar(int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particao(int vet[], int esq, int dir) {
    int idPivo = esq;

    for(int i = idPivo + 1; i <= dir; i += 1) {
        if (vet[i] < vet[esq]) {
            idPivo += 1;
            trocar(vet, idPivo, i);
        }
    }

    trocar(vet, esq, idPivo);

    return idPivo; 
}

void quickSortRec(int vet[], int esq, int dir) {
    if(esq >= dir) return;
    int pivo = particao(vet, esq, dir);
    quickSortRec(vet, esq, pivo - 1);
    quickSortRec(vet, pivo + 1, dir);
}

void quickSort(int vet[], int n) {
    quickSortRec(vet, 0, n - 1);
}

int main (void) {
    srand((unsigned) time(NULL));

    int * vet = (int *)malloc(sizeof(int) * MAX);

    clearVector(vet, MAX);

    fillVector(vet, MAX, 1);

    printf("BEFORE QUICKSORT\n\n");

    showVector(vet, MAX);

    clock_t start = clock();

    quickSort(vet, MAX);

    clock_t end = clock();

    double totalTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n\nAFTER QUICKSORT\n\n");

    showVector(vet, MAX);

    printf("\n\nEXECUTION TIME: %f seconds\n", totalTime);

    free(vet);

    return 0;
}