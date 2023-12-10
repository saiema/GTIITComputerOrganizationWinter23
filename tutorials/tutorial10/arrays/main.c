/*
* Example on using mov with a memory specified as (register, register, scale)
* Compile: gcc -no-pie main.c arrays.s -o arrays
* Run: ./arrays
*/

#include <stdio.h>

extern char string_char_at(char * string, int nth);

extern int integers_array_at(int size, int values[size], int at);

extern char strings_string_at_char_at(char ** strings, int nth_string, int nth_char);

int main() {
    int int_values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char * string = "Hello good sir!";
    char * strings[10] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    printf("The character at position %d, for string %s, is %c\n", 6, string, string_char_at(string, 6));
    printf("The integer at position %d is %d\n", 3, integers_array_at(10, int_values, 3));
    printf("The character at position %d for the string at position %d, is %c\n", 4, 3, strings_string_at_char_at(strings, 4, 3));
    return 0;
}