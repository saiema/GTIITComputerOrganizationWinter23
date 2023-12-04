#include <stdio.h>

extern char char_nth(char * s, int pos);
extern int int_array_nth(int * array, int pos);
extern char char_nth_in_ith_string(char ** strings, int string_pos, int char_pos);

int main(int argc, char ** argv) {
    for (int i = 0; i < argc; i++) {
        printf("First character of %s is %c\n", argv[i], char_nth(argv[i], 0));
        printf("Second character of %s is %c\n", argv[i], char_nth(argv[i], 1));
        printf("Third character of %s is %c\n", argv[i], char_nth(argv[i], 2));
    }
    int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("The first element in the array is %d\n", int_array_nth(values, 0));
    printf("The second element in the array is %d\n", int_array_nth(values, 1));
    printf("The fifth element in the array is %d\n", int_array_nth(values, 4));
    char * strings[4];
    strings[0] = "Hello";
    strings[1] = "there";
    strings[2] = "General";
    strings[3] = "Kenobi";
    char strings_2_3 = char_nth_in_ith_string(strings, 2, 3);
    char strings_1_3 = char_nth_in_ith_string(strings, 1, 3);
    printf("strings_2_3: %c\n", strings_2_3);
    printf("strings_1_3: %c\n", strings_1_3);
    return 0;
}