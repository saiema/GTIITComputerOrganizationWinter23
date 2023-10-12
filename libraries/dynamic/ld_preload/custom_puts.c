#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

char * to_upper_case(const char * string);
unsigned int length(const char * string);

int puts(const char *str) {
    void *handle;
    void (*_puts)(char *);
 
    // get a handle to the library that contains 'puts' function
    handle = dlopen ("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LAZY);
 
    // reference to the dynamically-resolved function 'puts'
    _puts = dlsym(handle, "puts");
 
    _puts(to_upper_case(str));
 
    dlclose(handle);
}

int fputs(const char *str, FILE *stream) {
    void *handle;
    void (*_fputs)(char *, FILE *);
 
    // get a handle to the library that contains 'puts' function
    handle = dlopen ("/lib/x86_64-linux-gnu/libc.so.6", RTLD_LAZY);
 
    // reference to the dynamically-resolved function 'puts'
    _fputs = dlsym(handle, "fputs");
 
    _fputs(to_upper_case(str), stream);
 
    dlclose(handle);
}

#define LOWER_CASE_MIN 97
#define LOWER_CASE_MAX 122

#define CASE_DIFF 32

char * to_upper_case(const char * string) {
    unsigned int strLength = length(string);
    char * uCaseString = (char *) malloc(strLength + 1);
    if (uCaseString == 0) {
        return 0;
    }
    uCaseString[strLength] = 0;
    for (int i = 0; i < strLength; i++) {
        char currChar = string[i];
        if ((currChar >= LOWER_CASE_MIN) && (currChar <= LOWER_CASE_MAX)) {
            currChar = currChar - CASE_DIFF;
        }
        uCaseString[i] = currChar;
    }
    return uCaseString;
}

unsigned int length(const char * string) {
    int count = 0;
    while(string[count] != 0) {
        count++;
    }
    return count;
}