.global write
.global strLength
.type write function
.type strLength function

.text

.EQU SYSCALL_WRITE, 1
.EQU STDOUT, 1

# write function
# takes a pointer to a string and an amount of characters (bytes) to write
# returns the amount of written bytes
write:
    push %rbp
    mov %rsp, %rbp
    mov $SYSCALL_WRITE, %rax
    mov %rsi, %rdx
    mov %rdi, %rsi
    mov $STDOUT, %rdi
    syscall
    pop %rbp
    ret

# strLength function
# takes a pointer to a null-terminated string and returns how many characters it has
# returns the length of the string
strLength:
    push %rbp
    mov %rsp, %rbp
    mov $0, %rax # we will use rax as both our counter and index
    jmp strLength_loop_test

strLength_loop:
    inc %rax

strLength_loop_test:
    mov (%rdi, %rax), %cl
    cmp $0, %cl
    jnz strLength_loop

strLength_return:
    pop %rbp
    ret
    