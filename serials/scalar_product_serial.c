#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "../utils/index.h"
#define NUMBER_OF_ELEMENTS 800000

long long int scalarProduct(int *, int *);

int main(void) {
    srand((unsigned) time(NULL));

    int * x = (int *)malloc(sizeof(int[NUMBER_OF_ELEMENTS])); 
    int * y = (int *)malloc(sizeof(int[NUMBER_OF_ELEMENTS])); 

    fillVector(x, NUMBER_OF_ELEMENTS, 1);
    fillVector(y, NUMBER_OF_ELEMENTS, 1);

    printf("\nNumber of elements: %d\n", NUMBER_OF_ELEMENTS);

    printf("Vector 1\n\n");
    printf("( ");
    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        printf("%d ", x[i]);
    }
    printf(") \n");
    printf("\n");
    printf("Vector 2\n\n");
    printf("( ");
    for (int j = 0; j < NUMBER_OF_ELEMENTS; j++)
    {
        printf("%d ", y[j]);
    }
    printf(") \n\n");

    clock_t start = clock();
    long long int scalarProductResult = scalarProduct(x,y);
    clock_t end = clock();


    printf("Result of scalar product of vectors(serial): %lld\n", scalarProductResult);


    double totalTime = (double) (end - start) / CLOCKS_PER_SEC;

    printf("\nTotal time: %f\n\n", totalTime);

    free(x);
    free(y);

    return 0;
}

long long int scalarProduct(int * x, int * y) {
    long long int result = 0;

    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        result += x[i] * y[i];
    }
    
    return result;
}

