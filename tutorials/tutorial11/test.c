#include <stdio.h>

#define True 1
#define False 0

extern char equals(const char * const string1, const char * const string2);

int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("Wrong amount of arguments, usage: ./test <string> <string>\n");
        return 1;
    }
    char * s1 = argv[1];
    char * s2 = argv[2];
    printf("%s and %s are %s\n", s1, s2, equals(s1, s2)?"EQUAL":"DIFFERENT");
    return 0;
}

char equals_c(const char * const string1, const char * const string2) {
    if (string1 == NULL) {
        return string2 == NULL;
    } else if (string2 == NULL) {
        return False;
    } else {
        int i = 0;
        int stop = False; // 0
        while (!stop) {
            if (string1[i] != string2[i]) {
                return False;
            } else if (string1[i] == 0) {
                stop = True; // 1
            }
            i++;
        }
        return True;
    }
}

char equals_c_desugar(const char * const string1, const char * const string2) {
    if (string1 == NULL) {
        return string2 == NULL;
    } else {
        if (string2 == NULL) {
            return False;
        } else {
            int i = 0;
            int stop = False; // 0
            while (!stop) {
                if (string1[i] != string2[i]) {
                    return False;
                } else {
                    if (string1[i] == 0) {
                        stop = True; // 1
                    }
                }
                i++;
            }
            return True;
        }
    }
}