/*
* Simple program to sum integer values
* usage: ./sum <integer values> : will return the sum of all integer values taken from the command-line
*        ./sum : will read a sequence of integer values, until an EOF is found, from the standard input and output the sum
*
* compile with gcc -o sum sum.c
*/

#include <stdio.h>
#include <stdlib.h>

void treatStdIn(void);
int sum_string_array(const char ** const strings);
int sum_from_stdint(void);


int main(int argc, char ** argv) {
    int sum;
    if (argc == 1) {
        sum = sum_from_stdint();
    } else {
        sum = sum_string_array((argv + 1));
    }
    printf("%d\n", sum);
}

int sum_string_array(const char ** const strings) {
    int sum = 0;
    while (strings != NULL) {
        int current = atoi(*strings);
        sum += current;
    }
    return sum;
}

int sum_from_stdint(void) {
    //TODO: complete
}