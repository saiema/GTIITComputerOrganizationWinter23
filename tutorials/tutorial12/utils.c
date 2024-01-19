#include <utils.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int count_digits(int value) {
    int digits = 0;
    do {
        digits++;
        value = value / 10;
    } while (value != 0);
    return digits;
}

int string_to_integer(char * string) {
    assert(string != NULL);
    assert(*string != 0);
    int is_negative = 0;
    if (string[0] == '-') {
        is_negative = 1;
        string = string + 1;
        assert (*string != 0);
    }
    int digit;
    int value = 0;
    int multiplier = 10;
    while (*string != 0) {
        digit = (*string) - 48;
        value = (value * multiplier) + digit;
        string = string + 1;
    }
    if (is_negative) {
        return -1 * value;
    }
    return value;
}

char * int_to_string(int value) {
    int digits = count_digits(value);
    int is_negative = value < 0;
    int string_rep_size = digits + (is_negative * 1) + 1;
    char string_rep[string_rep_size];
    string_rep[string_rep_size - 1] = 0;
    if (is_negative) {
        string_rep[0] = '-';
    }
    int i = string_rep_size - 2;
    do {
        int digit = value % 10;
        if (is_negative) {
            digit = digit * -1;
        }
        string_rep[i] = digit + 48;
        i--;
        value = value / 10;
    } while (value != 0);
    char * rep_result = (char *) malloc(string_rep_size);
    for (int i = 0; i <= string_rep_size; i++) {
        rep_result[i] = string_rep[i];
    }
    return rep_result;
}