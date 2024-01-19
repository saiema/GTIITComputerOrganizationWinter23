#include <utils.h>
#include <stdio.h>

int main() {
    char * string = "-138";
    printf("%s\n", int_to_string(-537));
    printf("%d\n", string_to_integer(string));
    printf("%s\n", int_to_string(string_to_integer(string)));
    return 0;
}