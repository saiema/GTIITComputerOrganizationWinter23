/* hello.c */
#define hi "Hello world\n"
#define hiLength 12

char *hello(void) {
    return hi;
}

int messageLength(void) {
    return hiLength;
}