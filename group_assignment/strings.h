#ifndef STRINGS_H
#define STRINGS_H

/*
    An alias to `unsigned char` to better represent a `boolean`
*/
typedef unsigned char boolean;

/*
    A `boolean` constant representing a `True` value
*/
#define TRUE 1

/*
    A `boolean` constant representing a `False` value
*/
#define FALSE 0

/*
    Returns the length of a `NULL-Terminated` string
    Takes a pointer to the first character of a string, the string must be `NULL-Terminated`
*/
extern unsigned int length(const char * string);

/*
    Returns whether two `NULL-Terminated` strings are equal or not
    Takes two strings (pointers to char) `string1` and `string2`
    Returns `True` iff both strings are of the same length and
    for every `i in [0..length(string1)] | string1[i] == string2[i]`
*/
extern boolean equals(const char * string1, const char * string2);

/*
    Returns the first index where a character appears in a string.
    Takes a `NULL-Terminated` string (`string`) and a character to look for (`e`)
    Returns `i` such that `string[i] == e` and there is no `j < i` where `string[j] == e`,
    returns `-1` if the character does not appear in the string
*/
extern int index_of(const char * string, const char e);

/*
    Returns the last index where a character appears in a string.
    Takes a `NULL-Terminated` string (`string`) and a character to look for (`e`)
    Returns `i` such that `string[i] == e` and there is no `j > i` where `string[j] == e`,
    returns `-1` if the character does not appear in the string
*/
extern int last_index_of(const char * string, const char e);

/*
    Returns a modified version of a string where every uppercase letter has been transformed into lowercase.
    Takes a `NULL-Terminated` string (`string`)
    Returns a new `NULL-terminated` string (`string2`) equal to `string` except for every uppercase letter
    in `string` will be in lowercase in `string2`
*/
extern char * to_lower_case(const char * string);

/*
    Returns a modified version of a string where every lowercase letter has been transformed into uppercase.
    Takes a `NULL-Terminated` string (`string`)
    Returns a new `NULL-terminated` string (`string2`) equal to `string` except for every lowercase letter
    in `string` will be in uppercase in `string2`
*/
extern char * to_upper_case(const char * string);

/*
    Returns a `NULL-Terminated` substring string of another `NULL-Terminated` string.
    Takes a `NULL-Terminated` string (`string`), and two unsigned ints (`from`, and `to`)
    Returns a slice of `string` going from index `from` (inclusive) to index `to` (exclusive),
*/
extern char * substring(const char * string, unsigned int from, unsigned int to);

#endif