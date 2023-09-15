#include <stdlib.h>
#include <stdio.h>

#define SIZE 42
#define MAX_VALUE 100

int max(int a, int b);
int maximum(const int size, int values[size]);
void printArray(const int size, int values[size]);

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Wrong amount of arguments (%d)\nUsage ./maximum <seed>\n", argc);
        return 1;
    }
    int values[SIZE];
    int seed = atoi(argv[1]);
    srand(seed);
    for (int i = 0; i < SIZE; i++) {
        values[i] = rand() % MAX_VALUE;
    }
    printArray(SIZE, values);
    int maximumValue = maximum(SIZE, values);
    printf("Maximum value is %d\n", maximumValue);
    return 0;
}

int max(int a, int b) {
    int maxValue;
    if (a > b) {
        maxValue = a;
    } else {
        maxValue = b;
    }
    return maxValue;
}

int maximum(const int size, int values[size]) {
    int maxValue = -1;
    for (int i = 0; i < size; i++) {
        maxValue = max(maxValue, values[i]);
    }
    return maxValue;
}

void printArray(const int size, int values[size]) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", i);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]\n");
}