#include <stdio.h>

extern unsigned int multiply(unsigned int a, unsigned int b);

int main(int argc, char ** argv) {
    if (argc < 3) {
        printf("Wrong amount of arguments (%d)\n", argc - 1);
        printf("Usage: ./multiply <integer> <integer>\n");
        return 1;
    }
    unsigned int a = atoi(argv[1]);
    unsigned int b = atoi(argv[2]);
    printf("%d * %d == %d\n", a, b, multiply(a, b));
    return 0;
}