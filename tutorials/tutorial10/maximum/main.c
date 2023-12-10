/*
* Given a list of integers, this program will return the maximum.
* Compile: gcc -no-pie main.c maximum.s -o maximum
* Run: ./maximum <list of integers>
*/

#include <stdio.h>
#include <stdlib.h>

extern int maximum(const int size, int values[size]);

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
    printf("The maximum number is %d\n", maximum(size, values));
    return 0;
}