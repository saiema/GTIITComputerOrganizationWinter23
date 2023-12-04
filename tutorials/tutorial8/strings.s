.global char_nth
.type char_nth function

.text

# sudden change is sudden

char_nth:
    push %rbp
    mov %rsp, %rbp
    # in register rax we need to have the nth character
    # of the string
    xor %rax, %rax
    mov (%rdi, %rsi), %al
    leave
    ret
