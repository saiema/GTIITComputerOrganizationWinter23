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
int s_printf_to_file(int fd, const string const format, const int * const values);

/*
* prints to standard output.
* This function takes a formatted string containing one or more `%d` strings;
* and an array of integer values that must be the same length as there are `%d` in the string.
* This function will return how many bytes it wrote.
*/
int s_printf(const string const format, const int * const values);

/*
* This function takes a path to an executable, and a NULL-terminated array of strings to be used
* as arguments for the executable.
* This function will wait until the called executable finishes and return their exit code 
*/
int s_execute(const string const path_to_executable, const string * const args);

#endif