/* main.c */
#include <stdio.h>

extern char* hello(void);
extern int messageLength(void);

int main(void) {
    printf("%s (length: %d)\n", hello(), messageLength());
    return 0;
}