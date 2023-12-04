.global main
.type main function

.text

main:
    push %rbp
    mov %rsp, %rbp
    
    # assume the string is not null
    mov $0, %rsi
    jmp str_length_loop_test

str_length_loop_body:
    inc %rsi
    
str_length_loop_test:
    mov $my_string, %rdi
    mov (%rdi, %rsi), %cl
    cmp $0, %cl
    jnz str_length_loop_body
    
    xor %rax, %rax
    mov $result_format, %rdi
    mov %rsi, %rdx
    mov $my_string, %rsi
    call printf
    leave
    mov $0, %rax
    ret
    
       
.data
my_string: .asciz "Hello World!"
result_format: .asciz "%s has a length of %d\n"
