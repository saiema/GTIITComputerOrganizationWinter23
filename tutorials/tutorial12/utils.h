#ifndef STRINGS_H
#define STRINGS_H

/*
    counts how many digits are in a number
*/
int count_digits(int value);

/*
    Given a NULL-Terminated string representing an integer number (can be negative),
    returns an the int representation.
*/
int string_to_integer(char * string);

/*
    Given an integer number (can be negative), it returns a new string with the representation.
    This function will call malloc, the user should free the returned string when it will no longer
    be used.
*/
char * int_to_string(int value);


#endif