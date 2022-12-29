#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../utils/index.h" 
#define MAX 400000
#define WORKERS 4

// 100000 200000 400000

#ifdef _OPENMP
    #include<omp.h>
#endif

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

    #ifdef _OPENMP
        #pragma omp task
        {
            quickSortRec(vet, esq, pivo - 1);
        }
        #pragma omp task 
        {
            quickSortRec(vet, pivo + 1, dir);
        }
    #else
        quickSortRec(vet, esq, pivo - 1);
        quickSortRec(vet, pivo + 1, dir);
    #endif
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
    
    #ifdef _OPENMP
        double start = omp_get_wtime();
    #else
        clock_t start = clock();
    #endif
    
    #ifdef _OPENMP
        omp_set_num_threads(WORKERS);

        #pragma omp parallel
        {
            #pragma omp single nowait
            quickSort(vet, MAX);
        }
    #else
        quickSort(vet, MAX);
    #endif

    #ifdef _OPENMP
        double end = omp_get_wtime();
    #else
        clock_t end = clock();
    #endif

    #ifdef _OPENMP
        double totalTime = end - start;
    #else
        double totalTime = (double)(end - start) / CLOCKS_PER_SEC;
    #endif

    printf("\n\nAFTER QUICKSORT\n\n");

    showVector(vet, MAX);

    printf("\n\nEXECUTION TIME: %f seconds\n", totalTime);

    free(vet);

    return 0;
}