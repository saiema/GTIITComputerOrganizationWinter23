/* main.c */
#include <unistd.h>

extern char* hello(void);
extern int messageLength(void);

int main(void) {
    write(STDOUT_FILENO, hello(), messageLength());
    return 0;
}