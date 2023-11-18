.global hello
.type hello function

.text

hello:
    xor %rax, %rax
    mov $hello_msg, %rdi
    call printf
    mov $0, %rdi
    call exit

.data

hello_msg: .asciz "Hello World!\n"
