.global isEven
.global isOdd
.global max
.type isEven function
.type isOdd function
.type max function

.text

# isEven function
# takes one integer number as argument
# returns true (1) iff the argument is even
isEven:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    and $1, %rdi
    setz %al
    pop %rbp
    ret

# isOdd function
# takes one integer number as argument
# returns true (1) iff the argument is odd
isOdd:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    and $1, %rdi
    setnz %al
    pop %rbp
    ret

# max function
# takes two integer numbers as arguments
# returns the maximum of the two
max:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov %rdi, %rax
    cmp %rsi, %rdi
    cmovl %rsi, %rax
    pop %rbp
    ret
