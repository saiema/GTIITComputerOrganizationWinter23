/*
* Given a list of integers, this program will return the maximum.
* Compile: gcc maximum.c -o maximum
* Run: ./maximum <list of integers>
*/

#include <stdio.h>

int max(const int a, const int b);
int maximum(const int size, const int values[size]);
void printArray(const int size, const int values[size]);

int main(int argc, char ** argv) {
    if (argc < 2) {
        printf("Usage: ./maximum <list of integers>\n");
        return 1;
    }
    int size = argc - 1;
    int values[size];
    for (int i = 0; i < size; i++) {
        values[i] = atoi(argv[i + 1]);
    }
    printArray(size, values);
    int maximumValue = maximum(size, values);
    printf("Maximum value is %d\n", maximumValue);
    return 0;
}

int max(const int a, const int b) {
    int maxValue;
    if (a > b) {
        maxValue = a;
    } else {
        maxValue = b;
    }
    return maxValue;
}

int maximum(const int size, const int values[size]) {
    int maxValue = -1;
    for (int i = 0; i < size; i++) {
        maxValue = max(maxValue, values[i]);
    }
    return maxValue;
}

void printArray(const int size, const int values[size]) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d",values[i]);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]\n");
}