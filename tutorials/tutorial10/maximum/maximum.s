# Implements functions int maximum(const int size, int values[size])
# This implementation does not make any checks on the arguments

.global maximum
.type maximum function

# maximum takes an integer size (greater than 0), and an array of integers
# of size elements.
# It returns the maximum element in the array
maximum:
    push %rbp           # Function prologue, saves the current rbp (stack base pointer)
    mov %rsp, %rbp      # and updates the rbp (stack base pointer) for the current activation record.

    # We will save the arguments into the stack, so we can use registers rdi and rsi without any issues
    push %rdi   # size is at -8(%rbp)
    push %rsi   # values is at -16(%rbp)
    
    sub $8, %rsp        # current_max at -20(%rbp), i at -24(%rbp), we decide where to store this local variables
                        # and how much space we will use (we could have used 8 bytes for each one, instead of 4).
    # to make the assignment current_max = values[0] we need to make current_max = *values
    # but both current_max, and values are in memory, and the mov operator cannot take two memory arguments (or operands)
    movl (%rsi), %r8d   # current_max = values[0]
    mov %r8d, -20(%rbp) # current_max = values[0] (we don't need to specify movl, because r8d is 4 bytes)

    movl $1, -24(%rbp)  # we initialize i with 1
    jmp maximum_loop_test # we will implement the while loop using the jump-to-middle template

maximum_loop_body:
    movl -20(%rbp), %edi # we move current_max into edi, because we want to call max(current_max, values[i])
    
    # The next three operations move values[i] (or values + i) into the second argument of max
    mov -16(%rbp), %r8
    movl -24(%rbp), %r9d
    movl (%r8, %r9, 4), %esi

    # we call max with current_max and values[i]
    call max
    mov %eax, -20(%rbp) # we move the result into current_max
    addl $1, -24(%rbp)  # we increase i by 1

maximum_loop_test:
    # we need to check if i < size
    mov -8(%rbp), %r8d      # we move size into r8d (is not needed to specify movl, r8d is 4 bytes)
    mov -24(%rbp), %r9d     # we move i into r9d (is not needed to specify movl, r9d is 4 bytes)
    cmp %r8d, %r9d          # we are comparing size and i
    jl maximum_loop_body    # if i is less than size, we make the jump back to the loop's body

maximum_done:
    mov -20(%rbp), %eax     # we move current_max to eax, to be able to execute return current_max
    add $24, %rsp           # we restore the stack pointer to point at the saved rbp
    leave                   # we restore the stack base pointer (rbp) to the saved value, and the stack pointer is now pointing to the return address
    ret                     # we return from the function (the program counter is updated with the return address, the stack pointer is increased by 8)


# Will take two integers (a, and b), and return the maximum of the two
max:
    push %rbp           # Function prologue, saves the current rbp (stack base pointer)
    mov %rsp, %rbp      # and updates the rbp (stack base pointer) for the current activation record.
    
    # we start by setting a (the first argument) as our result value
    xor %rax, %rax      # we zero out rax, to avoid garbage data messing with our result
    mov %edi, %eax
    
    cmp %edi, %esi      # we compare a and b      
    cmovg %esi, %eax    # if b is greater than a, we move b to eax (our result)
    leave               # we restore the stack base pointer (rbp) to the saved value, and the stack pointer is now pointing to the return address
    ret                 # we return from the function (the program counter is updated with the return address, the stack pointer is increased by 8)
