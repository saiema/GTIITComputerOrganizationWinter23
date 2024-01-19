/*
* A simple library offering operations to write to a file in a similar way as a very simplified printf and fprintf;
* an a function to execute an executable with a set of arguments.
*/

#ifndef SSTD_H
#define SSTD_H

#define ERROR_FORMAT_NULL 1
#define ERROR_VALUES_NULL 2

#define ERROR_SYSTEM_NO_FILE 3
#define ERROR_SYSTEM_NO_ACCESS 4
#define ERROR_SYSTEM_NULL_FILE 5
#define ERROR_SYSTEM_EXECUTION_FAILED 6
#define ERROR_SYSTEM_CHILD_INVALID_EXIT 7
#define ERROR_SYSTEM_READ_FILE_NULL 8
#define ERROR_SYSTEM_READ_FILE_ACCESS 9
#define ERROR_SYSTEM_READ_FILE_OPEN 10

typedef char * string;
typedef unsigned char boolean;

#define TRUE 1
#define FALSE 0

/*
* prints to a specific file.
* This function takes a file descriptor identifying the file to write to
* a formatted string containing one or more `%d` strings;
* and an array of integer values that must be the same length as there are `%d` in the string.
* This function will return how many bytes it wrote.
*/
extern int s_printf_to_file(int fd, const string const format, const int * const values);

/*
* prints to standard output.
* This function takes a formatted string containing one or more `%d` strings;
* and an array of integer values that must be the same length as there are `%d` in the string.
* This function will return how many bytes it wrote.
*/
extern int s_printf(const string const format, const int * const values);

/*
* This function takes a path to an executable, and a NULL-terminated array of strings to be used
* as arguments for the executable.
* This function will wait until the called executable finishes and return their exit code 
*/
extern int s_execute(const string const path_to_executable, const string * const args);

/*
* This function takes a path to an executable, a NULL-terminated array of strings to be used
* as arguments for the executable, and a boolean value that determines whether the caller of this function
* will wait for the called executable or not. 
*/
extern int s_execute_optional_wait(const string const path_to_executable, const string * const args, const boolean wait);

/*
* Defines the file redirection when executing an executable
*/
typedef enum {
    /*
    * No redirection
    */
    NONE,
    /*
    * Standard output is redirected to a file
    */
    REDIRECT_OUT,
    /*
    * A file is redirected to standard input
    */
    REDIRECT_IN
} redirect;

/*
* Executes an executable with potential file redirection and may wait on the executable to finish.
*
* Arguments:
* path_to_executable : a path to an executable;
* args :  a NULL-terminated array of strings to be used as arguments for the executable;
* redirect_op : a redirect value that determines if-and-which redirection will be used (*); 
* redirect_file : a path to a file used alongside the redirection operator (**);
* _wait : a boolean that determines whether this function will wait until the executable finished or not.
* 
* (*) : See `redirect` documentation for more information.
* (**) : ignored if `redirect_op` is `NONE`
*
* Returns the exit code of the executable, or 0 if `wait` is `False`.
*/
extern int s_execute_with_redirection(const string const path_to_executable, const string * const args, const redirect redirect_op, const string redirect_file, const boolean _wait);

#endif