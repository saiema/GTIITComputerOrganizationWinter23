.global not
.global and
.global or
.global xor
.type not function
.type and function
.type or function
.type xor function

.text

.EQU TRUE, 1
.EQU FALSE, 0

# not function
# takes an unsigned number
# returns TRUE if the number is 0, FALSE otherwise
not:
    push %rbp
    mov %rsp, %rbp
    mov $FALSE, %rbx
    mov $TRUE, %rax
    cmp $0, %rdi
    cmovne %rbx, %rax
    pop %rbp
    ret

# and function
# takes two unsigned numbers
# returns TRUE iff both arguments are non-zero
and:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    cmp $0, %rdi
    setz %dil
    cmp $0, %rsi
    setz %sil
    or %sil, %dil
    setz %al
    pop %rbp
    ret
    
# or function
# takes two unsigned numbers
# returns TRUE iff at least one argument is non-zero
or:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    cmp $0, %rdi
    setnz %al
    cmp $0, %rsi
    setnz %r10b
    or %r10b, %al
    pop %rbp
    ret

# xor function
# takes two unsigned numbers
# return TRUE iff exactly only one argument is non-zero
xor:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    cmp $0, %rdi
    setnz %al
    cmp $0, %rsi
    setnz %r10b
    xor %r10b, %al
    pop %rbp
    ret
