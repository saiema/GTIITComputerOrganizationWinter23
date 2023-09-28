#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

extern unsigned char isFile(const char * string, int type);
extern unsigned int length(const char * string);
extern char * trim(const char * string);
extern void startResponding(FILE * in, FILE * out);
extern FILE * toFile(const char * filename, int type, const char * mode);

void main(int argc, char ** argv) {
    FILE * in = NULL;
    FILE * out = NULL;
    unsigned char closeIn = 0;
    unsigned char closeOut = 0;
    if (argc >= 2 && argc <= 3) {
        char * inputFilename = trim(argv[1]);
        in = toFile(inputFilename, R_OK, "r");
        closeIn = 1;
        if (argc == 3) {
            char * outputFilename = trim(argv[2]);
            out = toFile(outputFilename, W_OK, "w");
            closeOut = 1;
        }
    } else if (argc > 3) {
        fprintf(stderr, 
        "Wrong amount of arguments: %d\
        \nUsage: ./lameChatGPT [input filename] [output filename]\n", argc);
        exit(1);
    }
    if (in == NULL) in = stdin;
    if (out == NULL) out = stdout;
    startResponding(in, out);
    if (closeIn) fclose(in);
    if (closeOut) fclose(out);
}

FILE * toFile(const char * filename, int type, const char * mode) {
    FILE * file;
    if (isFile(filename, type)) {
        file = fopen(filename, mode);
    }
    return file;
}

void startResponding(FILE * in, FILE * out) {
    #define SIZE 1024
    char input[SIZE];
    unsigned char stop = 0;
    while (!stop) {
        if (read(fileno(in), input, SIZE) == 0) {
            continue;
        }
        if (strstr(input, "I'm ") != NULL) {
            char name[30];
            sscanf(input, "I'm %s", name);
            fprintf(out, "Hello %s, nice to meet you!\n", name);
        } else if (strstr(input, "Time") != NULL) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            fprintf(out, "now: %d-%02d-%02d %02d:%02d:%02d\n",
                tm.tm_year + 1900,
                tm.tm_mon + 1,
                tm.tm_mday,
                tm.tm_hour,
                tm.tm_min,
                tm.tm_sec
            );
        } else if (strstr(input, "Goodbye") != NULL) {
            fputs("Goodbye, shutting down...\n", out);
            stop = 1;
        }
    }
}

unsigned char isFile(const char * string, int type) {
    int result;
    const char *filename = string;
    result = access(filename, type);
    if ( result == 0 ) {
        return 1;
    }
    return 0;
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