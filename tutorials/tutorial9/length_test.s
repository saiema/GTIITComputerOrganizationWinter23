.global main
.type main function

.text

main:
    push %rbp               # Function prologue
    mov %rsp, %rbp          # Function prologue
    # assume the string is not null
    mov $0, %rsi            # we will use rsi as an index and a counter
    jmp str_length_loop_test

str_length_loop_body:
    inc %rsi                # Increases the index / counter by 1
    
str_length_loop_test:
    mov $my_string, %rdi    # moves the address of my_string, not the value pointed at by that address to rdi
    mov (%rdi, %rsi), %cl   # moves 1 Byte (given by the use of %cl as destination) at address rdi + rsi
    cmp $0, %cl             # does cl - 0 without modifying any operand
    jnz str_length_loop_body    # if the previous operation resulted in 0, the Zero Flag will be 1, this will jump if ZF is 0
    
    xor %rax, %rax              # ensures rax is all zeros, to avoid missbehavior of printf
    mov $result_format, %rdi    # sets the address of the first byte of the format string as first argument (the "pointer" to a string)
    mov %rsi, %rdx              # sets the index / counter value to the third argument of printf
    mov $my_string, %rsi        # sets the address of the first byte of the "Hello World!" string as the second argument of printf
    call printf                 # calls printf
    leave                       # Function epilogue
    mov $0, %rax                # moves 0 to rax, so the main function can return 0
    ret                         # returns to the previous function (this would be function _start from the C standard library)
    
       
.data
my_string: .asciz "Hello World!"
result_format: .asciz "%s has a length of %d\n"
