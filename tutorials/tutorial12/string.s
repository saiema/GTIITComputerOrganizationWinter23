.global print_integer
.global print_string
.global equals
.global strlength
.global stringToNumber
.type print_integer function
.type print_string function
.type equals function
.type strlength function
.type stringToNumber function

.text

.equ SYS_WRITE, 1
.equ STDOUT, 1
.equ NEWLINE, 10

/*
  Given a null-terminated string that represents a positive integer number,
  this function will return the corresponding number
*/
stringToNumber:
    push %rbp
    mov %rsp, %rbp
    push %rdi   # the string to convert at -8(%rbp)
    push $1     # multiplier variable at -16(%rbp)
    sub $8, %rsp # reserved space for our string's length at -24(%rbp)
    sub $8, %rsp # reserved space for our index variable at -32(%rbp)
    push $0      # our resulting number at -40(%rbp)
    call strlength
    mov %rax, -24(%rbp)
    dec %rax
    mov %rax, -32(%rbp) # we are starting our index with size - 1
    jmp stringToNumber_loop_test

stringToNumber_loop_body:
    mov -8(%rbp), %r8
    mov -32(%rbp), %r9
    movzbq (%r8, %r9, 1), %rcx  # string[index]
    sub $48, %rcx               # we substract 48 from our digit to get the actual number
    mov -16(%rbp), %r10         # our multiplier
    mov -40(%rbp), %r11         # our current number
    imul %r10, %rcx             # current digit*multiplier
    add %rcx, %r11              # current number + (digit*multiplier)
    mov %r11, -40(%rbp)         # current number = current number + (digit*multiplier)
    imul $10, %r10              # multiplier * 10
    mov %r10, -16(%rbp)         # multiplier = multiplier * 10
    decq -32(%rbp)              # index--

stringToNumber_loop_test:
    cmpq $0, -32(%rbp)
    jge stringToNumber_loop_body    # we want to see all digits from index size - 1 to 0
                                    # so the condition is (index >= 0)

stringToNumber_done:
    mov -40(%rbp), %rax
    sub $40, %rsp
    leave
    ret

/*
  Function that takes an integer number and prints its string representation
*/
print_integer:
    push %rbp
    mov %rsp, %rbp
    push %rdi       # number -8(%rbp)
    push $0         # isNegative -16(%rbp)
    push $-1        # counter -24(%rbp)
    push $1         # segments -32(%rbp)
    sub $8, %rsp    # first 8 bits to save the string
    cmp $0, %rdi
    jge print_integer_convert
    negq -8(%rbp)
    movq $1, -16(%rbp)

print_integer_convert:
    mov -8(%rbp), %rax
    mov $0, %rdx
    mov $10, %rbx
    div %rbx
    add $48, %rdx
    mov %rax, -8(%rbp)

    leaq -32(%rbp), %r8
    mov -24(%rbp), %r9
    leaq (%r8, %r9, 1), %r10
    mov %dl, (%r10)

    cmp $0, %rax
    jz print_integer_print_negative
    decb -24(%rbp)
    mov -24(%rbp), %rax
    neg %rax
    mov $0, %rdx
    mov $8, %rbx
    div %rbx

    inc %rax
    mov -32(%rbp), %r8
    cmp %r8, %rax
    jle print_integer_convert
    sub $8, %rsp
    incq -32(%rbp)
    jmp print_integer_convert

print_integer_print_negative:
    cmpq $0, -16(%rbp)
    jz print_integer_print_number
    mov $SYS_WRITE, %rax
    mov $STDOUT, %rdi
    leaq negativeSymbol(%rip), %rsi
    mov $1, %rdx
    syscall

print_integer_print_number:
    leaq -32(%rbp), %r8
    mov -24(%rbp), %r9
    leaq (%r8, %r9, 1), %r10
    neg %r9
    mov $SYS_WRITE, %rax
    mov $STDOUT, %rdi
    mov %r10, %rsi
    mov %r9, %rdx
    syscall

print_integer_print_newLine:
    mov $SYS_WRITE, %rax
    mov $STDOUT, %rdi
    leaq newLineSymbol(%rip), %rsi
    mov $1, %rdx
    syscall

print_integer_print_exit:
    mov -32(%rbp), %r8
    leaq (%rsp, %r8, 8), %rsp
    add $32, %rsp
    mov $0, %rax
    leave
    ret
  

/*
Print a null-terminate string, this subroutine expects only one argument:
the address where the string begins
*/
print_string:
  push %rbp
  mov %rsp, %rbp
  push %rdi # string to print (%rbp - 8)
  mov %rdi, %rax
  mov $0, %rbx
printLoop:
  mov (%rax), %cl # We use cl, because string characters in ASCII are one byte long
	cmp $0, %cl
	je endPrintLoop
	inc %rbx
	inc %rax
	jmp printLoop
endPrintLoop:
	mov $SYS_WRITE, %rax
	mov $STDOUT, %rdi
	pop %rsi
	mov %rbx, %rdx
  syscall
	leave
	ret

/*Compare two NULL-terminated strings*/
equals:
  push %rbp
  mov %rsp, %rbp
  push %rdi     # first string (a) at -8(%rbp)
  push %rsi     # second string (b) at -16(%rbp)
  push $0       # index i at -24(%rbp)
  xor %rax, %rax  # set %rax at all zeros (just in case)
  mov $1, %al     # equals flag
  jmp equals_loop_condition

equals_loop_body:
  mov -8(%rbp), %r8   # starting address of string a
  mov -24(%rbp), %r10
  mov (%r8, %r10), %cl  # character at a[i]
  mov -16(%rbp), %r9    # starting address of string b
  mov (%r9, %r10), %dl  # character at b[i]
  cmp %cl, %dl
  sete %al              # equals = a[i] == b[i]
  cmp $0, %cl
  sete %r8b             # a[i] == 0
  and %al, %r8b         # equals && a[i] == 0
  jnz equals_done
  incq -24(%rbp)

equals_loop_condition:
  cmp $0, %rax        # equals flag (compare if it's not zero)
  jnz equals_loop_body

equals_done:
	addq $32, %rsp  # remove/clean local variables
  leave
  ret

/*Given a NULL-terminated string, this function will return the size of that string*/
strlength:
  push %rbp
  mov %rsp, %rbp
  push %rdi       # string at -8(%rbp)
  push $0         # -16(%rbp)
  jmp strlength_loop_test

strlength_loop_body:
  incq -16(%rbp)

strlength_loop_test:
  mov -8(%rbp), %r8
  mov -16(%rbp), %r9
  mov (%r8, %r9), %cl
  cmp $0, %cl
  jnz strlength_loop_body

strlength_return:
  mov -16(%rbp), %rax
  sub $16, %rsp
  leave
  ret

.data
negativeSymbol: .ascii "-"
newLineSymbol: .ascii "\n"

