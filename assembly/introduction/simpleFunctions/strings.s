.global write
.global strLength
.global indexOf
.global lastIndexOf
.global toUppercase
.global toLowercase
.global digitToChar
.type write function
.type strLength function
.type indexOf function
.type lastIndexOf function
.type toUppercase function
.type toLowercase function
.type digitToChar function

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

# indexOf function
# takes a pointer to a string and a character (1 byte) as arguments
# returns the first i such that string[i] == character, -1 if no i exists
indexOf:
    push %rbp
    mov %rsp, %rbp
    push %rdi # the string in which to search at -8(%rbp)
    push $0   # a found local variable (starting at false) at -16(%rbp)
    mov $0, %rax # we will use rax as index
    jmp indexOf_loop_test

indexOf_loop:
    mov -8(%rbp), %r8
    mov (%r8, %rax), %cl
    cmp %sil, %cl
    sete -16(%rbp)
    je indexOf_return
    inc %rax

indexOf_loop_test:
    mov -8(%rbp), %r8
    mov (%r8, %rax), %cl
    cmp $0, %cl
    jne indexOf_loop

indexOf_return:
    mov $-1, %r9
    cmpq $0, -16(%rbp)
    cmovz %r9, %rax
    add $16, %rsp
    pop %rbp
    ret

# lastIndexOf function
# takes a pointer to a string and a character (1 byte) as arguments
# returns the last i such that string[i] == character, -1 if no i exists
lastIndexOf:
    push %rbp
    mov %rsp, %rbp
    push %rdi # the string in which to search at -8(%rbp)
    mov $-1, %r10 # the current index at which the search character exists
    mov $0, %rax  # we will use rax as index
    jmp lastIndexOf_loop_test

lastIndexOf_loop:
    mov -8(%rbp), %r8
    mov (%r8, %rax), %cl
    cmp %sil, %cl
    cmove %rax, %r10
    inc %rax

lastIndexOf_loop_test:
    mov -8(%rbp), %r8
    mov (%r8, %rax), %cl
    cmp $0, %cl
    jne indexOf_loop

lastIndexOf_return:
    mov %r10, %rax
    add $8, %rsp
    pop %rbp
    ret

.EQU LOWER_FST_VALUE, 97
.EQU LOWER_LST_VALUE, 122
.EQU UPPER_FST_VALUE, 65
.EQU UPPER_LST_VALUE, 90
.EQU LOWER_UPPER_DIFF, 32

# toUppercase function
# takes a string as argument
# returns a string with every letter in upper case
toUppercase:
    push %rbp
    mov %rsp, %rbp
    xor %rcx, %rcx  # init auxiliary registers
    xor %r12, %r12  # init auxiliary registers
    push %rdi # the original string at -8(%rbp)
    push $0   # the new string at -16(%rbp)
    call strLength
    mov %rax, %rdi
    push %rax # the length of the original string at -24(%rbp)
    push $0   # local index (0) at -32(%rbp)
    call malloc
    mov %rax, -16(%rbp)
    cmp $0, %rax
    jle toUppercase_return
    jmp toUppercase_loop_test

toUppercase_loop:
    mov -8(%rbp), %r8
    mov -32(%rbp), %r9
    mov (%r8, %r9), %cl
    mov %cl, %r12b
    sub $LOWER_UPPER_DIFF, %r12b
    cmp $LOWER_FST_VALUE, %cl
    setge %r10b
    cmp $LOWER_LST_VALUE, %cl
    setle %r11b
    and %r10b, %r11b
    cmovnz %r12, %rcx
    mov -16(%rbp), %r8
    mov %cl, (%r8, %r9)
    incq -32(%rbp)


toUppercase_loop_test:
    mov -32(%rbp), %r8
    cmpq -24(%rbp), %r8
    jl toUppercase_loop

toUppercase_return:
    mov -16(%rbp), %rax
    add $32, %rsp
    pop %rbp
    ret

# toLowerrcase function
# takes a string as argument
# returns a string with every letter in lower case
toLowercase:
    push %rbp
    mov %rsp, %rbp
    xor %rcx, %rcx  # init auxiliary registers
    xor %r12, %r12  # init auxiliary registers
    push %rdi # the original string at -8(%rbp)
    push $0   # the new string at -16(%rbp)
    call strLength
    mov %rax, %rdi
    push %rax # the length of the original string at -24(%rbp)
    push $0   # local index (0) at -32(%rbp)
    call malloc
    mov %rax, -16(%rbp)
    cmp $0, %rax
    jle toLowercase_return
    jmp toLowercase_loop_test

toLowercase_loop:
    mov -8(%rbp), %r8
    mov -32(%rbp), %r9
    mov (%r8, %r9), %cl
    mov %cl, %r12b
    add $LOWER_UPPER_DIFF, %r12b
    cmp $UPPER_FST_VALUE, %cl
    setge %r10b
    cmp $UPPER_LST_VALUE, %cl
    setle %r11b
    and %r10b, %r11b
    cmovnz %r12, %rcx
    mov -16(%rbp), %r8
    mov %cl, (%r8, %r9)
    incq -32(%rbp)

toLowercase_loop_test:
    mov -32(%rbp), %r8
    cmpq -24(%rbp), %r8
    jl toUppercase_loop

toLowercase_return:
    mov -16(%rbp), %rax
    add $32, %rsp
    pop %rbp
    ret

.EQU DIGIT_ZERO_ASCII, 48

# digitToChar function
# takes an unsigned int as argument (digit)
# returns an ASCII representation of digit (or 0 if digit is not a number)
digitToChar:
    push %rbp
    mov %rsp, %rbp
    mov %rdi, %rax
    add $DIGIT_ZERO_ASCII, %rax
    mov $0, %r12
    cmp $0, %rdi
    setge %r10b
    cmp $9, %rdi
    setle %r11b
    and %r10b, %r11b
    cmovz %r12, %rax
    pop %rbp
    ret
