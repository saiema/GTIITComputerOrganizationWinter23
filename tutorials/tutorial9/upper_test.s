.global main
.type main function

.text

main:
    push %rbp
    mov %rsp, %rbp
    push $0 # size in -8(%rbp)
    jmp str_length_loop_test

str_length_loop_body:
    incq -8(%rbp)
    
str_length_loop_test:
    mov $my_string, %rdi
    mov -8(%rbp), %rsi
    mov (%rdi, %rsi), %cl
    cmp $0, %cl
    jnz str_length_loop_body
    
    mov -8(%rbp), %rdi
    inc %rdi
    call malloc # we will assume malloc succeded
    push %rax # upper is at -16(%rbp)
    mov -8(%rbp), %r8
    movb $0, (%rax, %r8)
    push $0 # i is at -24(%rbp)
    
       
.data
my_string: .asciz "Hello World!"
result_format: .asciz "%s in upper case is %s\n"
