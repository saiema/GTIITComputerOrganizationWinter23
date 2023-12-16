.global equals
.type equals function

.text

equals:
    push %rbp
    mov %rsp, %rbp
    xor %rax, %rax  # cleaning result register of any garbage data
    cmp $0, %rdi    # string1 == NULL (0)
    jnz equals_string1_not_null 

equals_string1_is_null:
    cmp $0, %rsi    # string2 == NULL (0)
    setz %al
    leave
    ret

equals_string1_not_null:
    cmp $0, %rsi    # string2 == NULL (0)
    jnz equals_both_not_null

equals_string1_null_string2_not_null:
    mov $0, %rax
    leave
    ret

equals_both_not_null:
    xor %r8, %r8        # clean %r8 of any garbage data
    sub $8, %rsp
    movl $0, -4(%rbp)   #   i at -4(%rbp)
    movl $0, -8(%rbp)   #   stop at -8(%rbp)
    jmp equals_loop_test

equals_loop_body:
    movl -4(%rbp), %r8d     #   we have i at r8 (we use r8d, with movl the most significant 32 bits of r8 will be set as zero)
    mov (%rdi, %r8), %cl    #   string1[i] in cl
    mov (%rsi, %r8), %dl    #   string2[i] in dl
    cmp %cl, %dl            #   string1[i] == string2[i]
    jz equals_string_equals

equals_string_not_equals:
    mov $0, %rax
    add $8, %rsp
    leave
    ret

equals_string_equals:
    movl -4(%rbp), %r8d     #   we have i at r8 (we use r8d, with movl the most significant 32 bits of r8 will be set as zero)
    mov (%rdi, %r8), %cl    #   string1[i] in cl
    cmp $0, %cl             #   string1[i] == 0
    jnz equals_string_equals_done

equals_stop:
    movl $1, -8(%rbp)   #   stop = 1

equals_string_equals_done:
    addl $1, -4(%rbp)   # i++

equals_loop_test:
    cmpl $0, -8(%rbp)   # stop == 0
    jz equals_loop_body

equals_loop_done:
    mov $1, %rax
    add $8, %rsp
    leave
    ret


