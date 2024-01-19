.global main
.type main function

.text


main:
    push %rbp
    mov %rsp, %rbp
    push %rdi # argumentsCount at -8(%rbp)
    push %rsi # arguments at -16(%rbp)
    cmpq $2, -8(%rbp)
    jne main_wrong_amount_of_arguments

main_open_file:
    mov -16(%rbp), %r8
    mov $1, %r9
    mov (%r8, %r9, 8), %rdi
    mov $0, %rsi
    call file_open
    push %rax # fd (file descriptor) at -24(%rbp)
    cmpq $0, -24(%rbp)
    jl main_error_opening_file
    mov -24(%rbp), %rdi
    call countLines
    push %rax # lines at -32(%rbp)
    leaq messages_result(%rip), %rdi
    call print_string
    mov -32(%rbp), %rdi
    mov $1, %rsi
    call print_integer
    mov $0, %rax
    jmp main_done

main_error_opening_file:
    leaq messages_error_file_open(%rip), %rdi
    call print_string
    mov -24(%rbp), %rdi
    call errno
    mov %rax, %rdi
    mov $1, %rsi
    call print_integer
    mov $1, %rax
    jmp main_done

main_wrong_amount_of_arguments:
    leaq messages_error_argssize(%rip), %rdi
    call print_string
    mov $1, %rax
    jmp main_done

main_done:
    add $32, %rsp
    leave
    ret


/*
Function that count lines in a file, it takes a file descriptor as argument.
The new line symbol '\n' will be used to detect new lines, only an empty file will
have no lines.
*/
countLines:
    push %rbp
    mov %rsp, %rbp
    push %rdi       # fileDescriptor at -8(%rbp)
    push $0         # lines at -16(%rbp)
    sub $8, %rsp    # reserve 8 bytes, but only one will be used to store the read character at -17(%rbp)
    sub $8, %rsp    # bytesRead at -32(%rbp)
    mov -8(%rbp), %rdi
    leaq -17(%rbp), %rsi
    mov $1, %rdx
    call file_read
    mov %rax, -32(%rbp)
    cmpq $0, -32(%rbp)
    jl countLines_error_reading
    cmpq $1, -32(%rbp)
    jne countLines_done
    incq -16(%rbp)  # we read one byte, even if it is a new line character, it means that there is one empty line
    
countLines_loop_body:
    mov newline(%rip), %cl
    cmp -17(%rbp), %cl
    jne countLines_loop_body_next_character # the byte (character) we read, was not a new line
    incq -16(%rbp)

countLines_loop_body_next_character:
    mov -8(%rbp), %rdi
    leaq -17(%rbp), %rsi
    mov $1, %rdx
    call file_read
    mov %rax, -32(%rbp)
    cmpq $0, -32(%rbp)
    jl countLines_error_reading

countLines_loop_test:
    cmpq $1, -32(%rbp)
    je countLines_loop_body
    jmp countLines_done

countLines_error_reading:
    leaq messages_error_file_read(%rip), %rdi
    call print_string
    mov -32(%rbp), %rdi
    call errno
    mov %rax, %rdi
    mov $1, %rsi
    call print_integer

countLines_done:
    mov -16(%rbp), %rax
    add $32, %rsp
    leave
    ret

.data
    messages_error_argssize: .asciz "Wrong amount of arguments\nUsage: ./flines <path to file>\n"
    messages_error_file_open: .asciz "Error opening file, errno: "
    messages_error_file_read: .asciz "Error reading file, errno: "
    messages_result: .asciz "Lines in file: "
    newline: .ascii "\n"
