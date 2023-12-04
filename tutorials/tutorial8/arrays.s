.global int_array_nth
.global char_nth_in_ith_string
.type int_array_nth function
.type char_nth_in_ith_string function

.text

int_array_nth:
    push %rbp
    mov %rsp, %rbp
    # We have the address of the array in rdi
    # the position we want in rsi
    xor %rax, %rax
    mov (%rdi, %rsi, 4), %eax
    leave
    ret

char_nth_in_ith_string:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov (%rdi, %rsi, 8), %r8
    mov (%r8, %rdx), %al
    leave
    ret
