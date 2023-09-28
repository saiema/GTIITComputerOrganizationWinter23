#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>  /* file operations and flags */
#include <string.h>
#include <ctype.h>

extern char * toUpperCase(const char * string);
extern unsigned int length(const char * string);
extern void treatStream(FILE * stream);
extern unsigned char isFile(const char * string);
extern void treatAsFile(const char * filename);
extern char * trim(const char * string);

void main(int argc, char ** argv) {
    if (argc > 1) {
        for (unsigned int i = 1; i < argc; i++) {
            char * currentArgument = argv[i];
            char * noTrailingSpacesArgument = trim(currentArgument);
            if (isFile(noTrailingSpacesArgument)) {
                treatAsFile(noTrailingSpacesArgument);
            } else {
                fputs(toUpperCase(currentArgument), stdout);
            }
        }
    } else {
        treatStream(stdin);
    }
    exit(0);
}

void treatAsFile(const char * filename) {
    FILE * stream = fopen(filename, "r");
    treatStream(stream);
    fclose(stream);
}

unsigned char isFile(const char * string) {
    int result;
    const char *filename = string;
    result = access(filename, R_OK);
    if ( result == 0 ) {
        return 1;
    }
    return 0;
}

void treatStream(FILE * stream) {
    char buffer[2];
    buffer[1] = 0;
    while ((buffer[0] = fgetc(stream)) != EOF) {
        fputs(toUpperCase(buffer), stdout);
    }
}

unsigned int length(const char * string) {
    int count = 0;
    while(string[count] != 0) {
        count++;
    }
    return count;
}

char * trim(const char * string) {
    unsigned int from = 0;
    unsigned int to = length(string) - 1;
    while(string[from] != 0 && isspace(string[from])) {
        from++;
    }
    while(string[to] != 0 && isspace(string[to])) {
        to--;
    }
    unsigned int resLength = (to - from) + 1;
    if (resLength < 0) {
        resLength = 0;
    }
    char * trimmed = (char *) malloc(resLength + 1);
    if (trimmed == 0) {
        return 0;
    }
    trimmed[resLength] = 0;
    for (int i = 0; i <= resLength; i++) {
        trimmed[i] = string[from + i];
    }
    return trimmed;
}

#define LOWER_CASE_MIN 97
#define LOWER_CASE_MAX 122

#define CASE_DIFF 32

char * toUpperCase(const char * string) {
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