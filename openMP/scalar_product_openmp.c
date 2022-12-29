#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../utils/index.h"

#ifdef _OPENMP

#include <omp.h>

#endif

#define NUMBER_OF_ELEMENTS 4

void scalarProduct(int *, int *, int *);

int main(void) {
    srand((unsigned) time(NULL));

    int * x = (int *)malloc(sizeof(int[NUMBER_OF_ELEMENTS])); 
    int * y = (int *)malloc(sizeof(int[NUMBER_OF_ELEMENTS])); 
    int threadCount;

    #ifdef _OPENMP
        int numberOfThreads = omp_get_num_procs();

        if(NUMBER_OF_ELEMENTS < numberOfThreads)
            threadCount = NUMBER_OF_ELEMENTS;
        else
            threadCount = numberOfThreads;
    #else
        threadCount = 1;
    #endif

    int result = 0; 

    fillVector(x, NUMBER_OF_ELEMENTS, 1);
    fillVector(y, NUMBER_OF_ELEMENTS, 1);

    printf("Vector 1\n\n");
    printf("( ");
    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        printf("%d ", x[i]);
    }
    printf(") \n\n");
    printf("\n");
    printf("Vector 2\n\n");
    printf("( ");
    for (int j = 0; j < NUMBER_OF_ELEMENTS; j++)
    {
        printf("%d ", y[j]);
    }
    printf(") \n\n");

    #ifdef _OPENMP
        double start = omp_get_wtime();
    #else
        double start = clock();
    #endif

    #pragma omp parallel num_threads(threadCount) 
    {
        scalarProduct(x, y, &result);
    }

    #ifdef _OPENMP
        double end = omp_get_wtime();
        printf("\nTempo de execucao: %.06lf\n", (double) (end - start));
    #else
        double end = clock();
        printf("\nTempo de execucao: %.06lf\n", (double) (end - start) / CLOCKS_PER_SEC);
    #endif

    printf("Result of scalar product of vectors(openmp): %d", result);

    free(x);
    free(y);

    return 0;
}

void scalarProduct(int * x, int * y, int * result) {
    #ifdef _OPENMP
        int rank = omp_get_thread_num();
        int threadCount = omp_get_num_threads();

        int load = NUMBER_OF_ELEMENTS/threadCount;
        int start = rank * load;
        int end = (rank + 1) * load;   

    #else
        int rank = 0;
        int threadCount = 1;

        int load = NUMBER_OF_ELEMENTS;
        int start = 0;
        int end = NUMBER_OF_ELEMENTS;  
    #endif

    #ifdef _OPENMP

        int local_result = 0;
        for (int i = start; i < end; i++)
        {
            local_result += x[i] * y[i];
        }

        #pragma omp critical
        {
            *result += local_result;
        }

    #else

        int local_result = 0;
        for (int i = 0; i < NUMBER_OF_ELEMENTS; i++){
            local_result += x[i] * y[i];
        }

        *result = local_result;

    #endif
}
