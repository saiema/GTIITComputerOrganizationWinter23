
extern int write(const char * string, int length);
extern int strLength(const char * string);

void main(void) {
    const char * helloWorld = "Hello world\n";
    write(helloWorld, strLength(helloWorld));
}