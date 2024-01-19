/*
* A small files library emulating how files descriptor tables work along file related operations
*/
#ifndef FILES_H
#define FILES_H

#include <fcntl.h>

#define STD_OUT 0
#define STD_IN 1
#define STD_ERR 2

/*
* Represents read permission
*/
#define PERMS_READ 1

/*
* Represents write permission
*/
#define PERMS_WRITE 2

/*
* When using write permission, this flag determines if the data written
* will be appended (when this flag is used) to the end of the file; or
* the data written will overwrite (when this flag is not used) the existing data.
*/
#define PERMS_APPEND 4

/*
* When using write permission, this flag determines if the file will be created if it
* does not exists (when the flag is used).
*/
#define PERMS_CREATE 8

struct fd_table_s;
typedef struct fd_table_s * fd_table;

/*
* Creates and initialize a new file descriptor table
*/
fd_table fd_table_new();

/*
* Opens a new file and return a descriptor.
*
* Arguments:
* fdt : The File Descriptor Table to use
* filename : The name of the file to open
* flags : The flags to use, read the flags documentation, you can use a bitwise or to use more than one flag
*
* Return value:
* the file descriptor if the open operation was successful, or a negative number if not.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error. 
*/
extern int fdt_open(fd_table fdt, const char * filename, int flags);

/*
* Closes an already opened file given it's descriptor.
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file to close
*
* Return Value:
* The file descriptor if the operation was successful, or a negative number if not.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*/
extern int fdt_close(fd_table fdt, const int fd);

/*
* Reads from a file
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file to read from
* bytes : an amount of bytes to read (*)
* dest : a destination buffer where bytes read will be stored (**)
*
* Return value:
* How many values were read, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) The read operation will read data until either of the following conditions are met:
*       1. The requests bytes were read.
*       2. EOF is reached.
*
* (**) This buffer must contain at least enough memory space to store the requested amount of bytes.
*/
extern int fdt_read_from(fd_table fdt, const int fd, int bytes, char * dest);

/*
* Reads from standard input
* This function is equivalent to read(fdt, STD_IN, bytes, dest)
*
* Arguments:
* fdt : The File Descriptor Table to use
* bytes : an amount of bytes to read (*)
* buf : a destination buffer where bytes read will be stored (**)
*
* Return value:
* How many values were read, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) The read operation will read data until either of the following conditions are met:
*       1. The requests bytes were read.
*       2. EOF is reached.
*
* (**) This buffer must contain at least enough memory space to store the requested amount of bytes.
*/
extern int fdt_read(fd_table fdt, int bytes, char * dest);

/*
* Reads a string from a file
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file to read from
* bytes : an amount of bytes to read (*)
* buf : a destination buffer where bytes read will be stored (**)
*
* Return value:
* How many values were read, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) The read operation will read data until either of the following conditions are met:
*       1. The requests bytes were read.
*       2. A newline is reached.
*       3. EOF is reached.
*
* (**) This buffer must contain at least enough memory space to store bytes + 1; a 0 will be appended
* at the end of the data read.
*/
extern int fdt_fgets(fd_table fdt, int fd, int bytes, char * dest);S

/*
* Reads a string from standard input
* This function is equivalent to fdt_fgets(fdt, STD_IN, bytes, dest)
*
* Arguments:
* fdt : The File Descriptor Table to use
* bytes : an amount of bytes to read (*)
* buf : a destination buffer where bytes read will be stored (**)
*
* Return value:
* How many values were read, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) The read operation will read data until either of the following conditions are met:
*       1. The requests bytes were read.
*       2. A newline is reached.
*       3. EOF is reached.
*
* (**) This buffer must contain at least enough memory space to store bytes + 1; a 0 will be appended
* at the end of the data read.
*/
extern int fdt_gets(fd_table fdt, int bytes, char * dest);

/*
* Writes to a file
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file to write to
* bytes : an amount of bytes to write
* dest : a buffer containing the bytes to write (*)
*
* Return value:
* How many values were written, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) This buffer must have a size of at least the amount of bytes requested to write, no extra data will
* be written to the file.
*/
extern int fdt_write_to(fd_table fdt, const int fd, int bytes, const char * buf);

/*
* Writes to standard output
* This function is equivalent to write(fdt, STD_OUT, bytes, buf)
*
* Arguments:
* fdt : The File Descriptor Table to use
* bytes : an amount of bytes to write
* buf : a buffer containing the bytes to write (*)
*
* Return value:
* How many values were written, this number can be less than the bytes requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*
* (*) This buffer must have a size of at least the amount of bytes requested to write, no extra data will
* be written to the file.
*/
extern int fdt_write(fd_table fdt, int bytes, const char * buf);

/*
* Writes a string into a file
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file to write to
* string : A NULL-Terminated string
*
* Return value:
* How many values were written, this number can be less than the size of the string requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*/
extern int fdt_print_to(fd_table fdt, const int fd, char * string);

/*
* Writes a string into standard output
* This function is equivalent to print_to(fdt, STD_OUT, string)
*
* Arguments:
* fdt : The File Descriptor Table to use
* string : A NULL-Terminated string
*
* Return value:
* How many values were written, this number can be less than the size of the string requested; or a negative
* value if the operation was unsuccessful.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*/
extern int fdt_print(fd_table fdt, char * string);

/*
* Duplicates a file descriptor
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor to duplicate
*
* This function will use the lowest available (unused) file descriptor as the new file descriptor.
*
* Return value:
* On success, this function will return the new file descriptor; on failure this function will return
* a negative value.
* If the operation was unsuccessful, you can use the error_msg function with the returned value
* to get a description of the error.
*/
extern int fdt_dup(fd_table fdt, const int fd);

/*
* Searches a string in a file
*
* Arguments:
* fdt : The File Descriptor Table to use
* fd : The file descriptor of the file in which to search
* target : A NULL-terminated string to search for (*)
* status : A pointer to int where the status will be saved (**)
* 
* Return value:
* The index in which the string occurs in the file, or -1 if the string was not found.
*
* (*) The NULL at the end will not be considered as part of the search
* (**) If status points to 0, the operation was successful; if not it will point to a
* negative value.
* If the operation was unsuccessful, you can use the error_msg function with the status value
* to get a description of the error.
*/
extern int fdt_search_string_in(fd_table fdt, const int fd, char * target, unsigned int * status);

/*
* Searches for a file containing a particular string
* This function will NOT search into any of the standard files (IN, OUT, ERROR)
* 
* Arguments:
* fdt : The File Descriptor Table to use
* target : A NULL-terminated string to search for (*)
* status : A pointer to int where the status will be saved (**)
* 
* Return value:
* The lowest file descriptor of a file containing the string to search for; or -1 if no file
* contains the string.
* 
* (*) The NULL at the end will not be considered as part of the search
* (**) If status points to 0, the operation was successful; if not it will point to a
* negative value.
* If the operation was unsuccessful, you can use the error_msg function with the status value
* to get a description of the error.
*/
extern int fdt_search_string(fd_table fdt, char * target, unsigned int * status);

/*
* Given a negative value representing an error, returns a related string description.
* SEE DOCUMENTATION OF
* char *strerror(int errnum);
* (man strerror)
*/
extern char * fdt_error_msg(const int error_nr);

/*
* Destroys a File Descriptor Table
*
* Arguments:
* fdt : The File Descriptor Table to use
*
* All files except from Standard Input, Standard Error, and Standard Output
* must be closed.
*/
extern void fdt_destroy(fd_table fdt);

#endif