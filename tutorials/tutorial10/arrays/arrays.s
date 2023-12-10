# Implementation of the following functions:
# extern char string_char_at(char * string, int nth);
# extern int integers_array_at(int size, int values[size], int at);
# extern char strings_string_at_char_at(char ** strings, int nth_string, int nth_char);

.global string_char_at
.global integers_array_at
.global strings_string_at_char_at
.type string_char_at function
.type integers_array_at function
.type strings_string_at_char_at function

.text

# Takes a string (string) and an integer (nth), returns string[nth].
string_char_at:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov (%rdi, %rsi), %al   # we move *(string + nth) into al (a char is 1 byte)
    leave
    ret

# Takes an integer (size), an integer array (values), and an integer (at), returns values[at]
integers_array_at:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov (%rsi, %rdx, 4), %eax # we move *(string + at) into eax (an int is 4 bytes)
    leave
    ret

# Takes an array of strings (strings), an integer (nth_string), an integer (nth_char)
# returns strings[nth_string][nth_char]
strings_string_at_char_at:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov (%rdi, %rsi, 8), %r8    # we move *(strings + nth_string) into r8 (a pointer is 8 bytes)
    mov (%r8, %rdx), %al        # we move *(r8 + nth_char) into al (a char is 1 byte)
    leave
    ret
