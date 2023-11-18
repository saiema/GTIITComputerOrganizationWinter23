.global and
.type and function

.text

.EQU A, 10
.EQU B, 11

# AND A B === FALSE if (NOT A) OR (NOT B)
# argument registers: rdi, rsi, rdx, rcx, r8, r9

and:
    # Since we will use several "sub-registers"
    # we want to set them all to zero to avoid 
    # garbage data
    xor %rdi, %rdi
    xor %rsi, %rsi
    xor %rdx, %rdx
    xor %rcx, %rcx
    # "Function" AND starts
    mov $A, %dil    # (%dil <- A)
    mov $B, %sil    # (%sil <- B)
    cmp $0, %dil    # (%dil (A) - 0, without saving the result)
    setz %dil       # (%dil <- A == 0)
    cmp $0, %sil    # (%sil (B) - 0, without saving the result)
    setz %sil       # (%sil <- B == 0)
    or %dil, %sil   # (%sil <- (NOT A) OR (NOT B))
    setz %cl        # (%cl <- (NOT A) OR (NOT B) == 0, setting A AND B as fourth argument of printf)
    # "Function" AND ends 
    # Calling printf starts
    mov $A, %rsi    # (%rsi <- A, setting A as second argument of printf)
    mov $B, %rdx    # (%rdx <- A, setting B as third argument of printf)
    mov $printf_format, %rdi    # (%rdi <- address of format string, setting format string as first argument of printf)
    call printf     # printf(printf_format, A, B, A AND B)
    # Calling printf ends
    # Calling exit(0) starts
    mov $0, %rdi
    call exit
    # Calling exit (0) ends



.data
printf_format: .asciz "A (%d) AND B (%d): %d\n"
