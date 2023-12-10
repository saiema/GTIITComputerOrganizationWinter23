#include <stdio.h>
#include <unistd.h>

int count_words_from_stdin(void);

int main(void) {
    printf("%d\n", count_words_from_stdin());
}

int count_words_from_stdin(void) {
    #define SPACE 32
    int words = 0;
    char current_char;
    unsigned char found_word = 0;
    while ((current_char = getchar()) != EOF) {
        printf("%c (%d)\n", current_char, current_char);
        if (current_char == SPACE && found_word) {
            words++;
            found_word = 0;
        } else if (current_char == SPACE) {
            continue;
        } else {
            found_word = 1;
        }
    }
    return words;
}