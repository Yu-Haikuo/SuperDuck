
#ifndef algorithm_h
#define algorithm_h

void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;
}

int abs(int number) {
    if (number >= 0) {
        return number;
    } else {
        return 0 - number;
    }
}

// Randomly shuffle the given array elements. 
void shuffle(int* array, int size) {
    int i, j;
    srand(time(NULL));

    for (i = size - 1; i > 0; i--) {
        j = rand() % (i+1); // Pick up one item from index 0 to i. 
        swap(&array[i], &array[j]);
    }
}

#endif /* algorith_h */