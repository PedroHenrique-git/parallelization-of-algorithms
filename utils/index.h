int generateNumber(int limit) {
    return rand() % limit;
}

void clearVector(int vector[], int size) {
    for(int i = 0; i < size; i++) {
        vector[i] = 0;
    }
}

void showVector(int vector[], int size) {
    for(int i = 0; i < size; i++) {
        printf("[%d]: %d\n", i, vector[i]);
    }
}

void fillVector(int vector[], int size, int order) {
    if(order == 0) {
        for(int i = size, j = 0; i > 0; i--, j++) {
            vector[j] = i;
        }

        return;
    }

    if(order == 1) {
        for(int i = 0; i < size; i++) {
            vector[i] = generateNumber(size);
        }

        return;
    }

    for(int i = 0; i < size; i++) {
        vector[i] = i + 1;
    }
}