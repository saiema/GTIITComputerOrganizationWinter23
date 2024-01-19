.global not
.global and
.global or
.global xor
.type not function
.type and function
.type or function
.type xor function

.text

.EQU TRUE, 1
.EQU FALSE, 0

# not function
# takes an unsigned number
# returns TRUE if the number is 0, FALSE otherwise
not:
    //TODO: complete

# and function
# takes two unsigned numbers
# returns TRUE iff both arguments are non-zero
and:
    //TODO: complete
    
# or function
# takes two unsigned numbers
# returns TRUE iff at least one argument is non-zero
or:
    //TODO: complete

# xor function
# takes two unsigned numbers
# return TRUE iff exactly only one argument is non-zero
xor:
    //TODO: complete
