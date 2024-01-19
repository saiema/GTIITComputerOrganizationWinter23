.global _exit
.type _exit function
.global file_open
.type file_open function
.global file_read
.type file_read function
.global file_seek
.type file_seek function
.global errno
.type errno function

.text

.equ SYS_EXIT, 60
.equ FILE_OPEN, 2
.equ FILE_READ, 0
.equ FILE_LSEEK, 8
	
/*
Call the exit system function with a provided exit code
*/
_exit:
    mov $SYS_EXIT, %rax
    syscall

/*
Opens a file and returns it's descriptor.
it takes two arguments, the path of the file to open and the flags to use
*/
file_open:
    push %rbp
    mov %rsp, %rbp
    mov $FILE_OPEN, %rax
    syscall
    leave
    ret

/*
Reads n bytes from a file, the first argument is the file descriptor, the
second one is the buffer where to store the read data, the third one is
how many bytes to read, the fourth one are flags, to read a file use 0.
Result: how many bytes were read, or a negative value -errno
*/
file_read:
    push %rbp
    mov %rsp, %rbp
    mov $FILE_READ, %rax
    syscall
    leave
    ret

/*
Positions a file's offset into a provided one. The first argument is the file's
descriptor, and the second one must be a positive number indicating the offset.
*/
file_seek:
    push %rbp
    mov %rsp, %rbp
    mov $FILE_LSEEK, %rax
    syscall
    leave
    ret

/*
    given an error value (errno), translate it from a negative value into 1 byte value.
*/
errno:
    push %rbp
    mov %rsp, %rbp
    neg %rdi
    xor %rax, %rax
    mov %dil, %al
    leave
    ret
    