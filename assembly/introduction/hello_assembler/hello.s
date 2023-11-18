.global main
.type main function

.text

main:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax
    mov $hello_msg, %rdi
    call printf
    mov $0, %rax
    leave
    ret
    

.data

hello_msg: .asciz "Hello World!\n"
