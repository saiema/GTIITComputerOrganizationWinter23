.global main
.type main function

.text

main:
    push %rbp
    mov %rsp, %rbp
    push $0 # size/index is in -8(%rbp)
    jmp str_length_loop_test

str_length_loop_body:
    incq -8(%rbp)   # we need to specify that we are increment an 8 Bytes value, because the destination is a memory address
    
str_length_loop_test:
    mov $my_string, %rdi    # moves the address of our "Hello World!" string to rdi
    mov -8(%rbp), %rsi      # moves size/index to rsi 
    mov (%rdi, %rsi), %cl   # moves the byte (character) at rdi+rsi ("Hello World!"[rsi]) to cl
    cmp $0, %cl             # compares the character obtained with 0
    jnz str_length_loop_body    # goes back to the loop if the character is not 0
    
    mov -8(%rbp), %rdi      # moves size/index to rdi (the first argument for malloc)
    inc %rdi                # increases the size by 1, to accomodate for the ending 0
    call malloc             # we call malloc and we will assume malloc succeded
    push %rax               # the pointer/address to the upper string version is at -16(%rbp)
    mov -8(%rbp), %r8       # we move the pointer/address of upper to r8
    movb $0, (%rax, %r8)    # we put a 0 at upper[size] or upper+size
    push $0                 # we save the index i with 0 at -24(%rbp)
    # TODO: complete implementation of to_upper
    
       
.data
my_string: .asciz "Hello World!"
result_format: .asciz "%s in upper case is %s\n"
