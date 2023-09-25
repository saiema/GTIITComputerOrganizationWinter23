#include "standard.h"
#include <stdlib.h>

unsigned int length(const char * string) {
    int count = 0;
    while(string[count] != 0) {
        count++;
    }
    return count;
}

boolean equals(const char * string1, const char * string2) {
    int i = 0;
    while (string1[i] != 0) {
        if (string2[i] == 0) {
            return FALSE;
        } else if (string1[i] != string2[i]) {
            return FALSE;
        }
        i++;
    }
    return string2[i] == 0;
}

int indexOf(const char * string, const char e) {
    int idx = 0;
    boolean found = FALSE;
    while (string[idx] != 0) {
        if (string[idx] == e) {
            return idx;
        }
        idx++;
    }
    return found?idx:-1;
}

int lastIndexOf(const char * string, const char e) {
    int idx = 0;
    int resIdx = -1;
    while(string[idx] != 0) {
        if (string[idx] == e) {
           resIdx = idx; 
        }
        idx++;
    }
    return resIdx;
}

#define LOWER_CASE_MIN 65
#define LOWER_CASE_MAX 90

#define UPPER_CASE_MIN 97
#define UPPER_CASE_MAX 122

#define CASE_DIFF 32

char * toLowerCase(const char * string) {
    int strLength = length(string);
    char * lCaseString = (char *) malloc(strLength + 1);
    if (lCaseString == 0) {
        return 0;
    }
    lCaseString[strLength] = 0;
    for (int i = 0; i < strLength; i++) {
        char currChar = string[i];
        if ((currChar >= UPPER_CASE_MIN) && (currChar <= UPPER_CASE_MAX)) {
            currChar = currChar - CASE_DIFF;
        }
        lCaseString[i] = currChar;
    }
    return lCaseString;
}

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
            currChar = currChar + CASE_DIFF;
        }
        uCaseString[i] = currChar;
    }
    return uCaseString;
}

char * substring(const char * string, unsigned int from, unsigned int to) {
    unsigned int strLength = length(string);
    if (from < 0 || from >= strLength || to > strLength || from > to) {
        return 0;
    }
    unsigned int sliceLength = to - from;
    char * slice = (char *) malloc(sliceLength + 1);
    if (slice == 0) {
        return 0;
    }
    slice[sliceLength] = 0;
    for (int i = 0; i < sliceLength; i++) {
        char origChar = string[from + i];
        slice[i] = origChar;
    }
    return slice;
}