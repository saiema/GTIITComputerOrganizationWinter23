.global write
.global strLength
.global indexOf
.global lastIndexOf
.global toUppercase
.global toLowercase
.global digitToChar
.type write function
.type strLength function
.type indexOf function
.type lastIndexOf function
.type toUppercase function
.type toLowercase function
.type digitToChar function

.text

.EQU SYSCALL_WRITE, 1
.EQU STDOUT, 1

# write function
# takes a pointer to a string and an amount of characters (bytes) to write
# returns the amount of written bytes
write:
    //TODO: complete

# strLength function
# takes a pointer to a null-terminated string and returns how many characters it has
# returns the length of the string
strLength:
    //TODO: complete

# indexOf function
# takes a pointer to a string and a character (1 byte) as arguments
# returns the first i such that string[i] == character, -1 if no i exists
indexOf:
    //TODO: complete

# lastIndexOf function
# takes a pointer to a string and a character (1 byte) as arguments
# returns the last i such that string[i] == character, -1 if no i exists
lastIndexOf:
    //TODO: complete

.EQU LOWER_FST_VALUE, 97
.EQU LOWER_LST_VALUE, 122
.EQU UPPER_FST_VALUE, 65
.EQU UPPER_LST_VALUE, 90
.EQU LOWER_UPPER_DIFF, 32

# toUppercase function
# takes a string as argument
# returns a string with every letter in upper case
toUppercase:
    //TODO: complete

# toLowerrcase function
# takes a string as argument
# returns a string with every letter in lower case
toLowercase:
    //TODO: complete

.EQU DIGIT_ZERO_ASCII, 48

# digitToChar function
# takes an unsigned int as argument (digit)
# returns an ASCII representation of digit (or 0 if digit is not a number)
digitToChar:
    //TODO: complete
