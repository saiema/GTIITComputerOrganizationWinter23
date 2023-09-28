#if !defined(STANDARD_DEF)
#define STANDARD_DEF
#include <limits.h>

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

// Math

/*
    Returns the maximum of two values
    Takes two integer values, `a` and `b`
    Returns `a` if `a >= b`, otherwise it will return `b`
*/
extern int max(const int a, const int b);

/*
    Returns the maximum value in an array
    Takes an integer `size` and an `array` of that size
    Returns `e`, where `e` is in `array` and there is no other value `f` in `array` such that `f > e`;
    if `array` is empty, it will return `MIN_VALUE`.
*/
extern int maximum(const int size, int values[size]);

/*
    Returns whether a number is even or not
    Takes one integer `value`
    Returns `TRUE` iff `value` is even.
*/
extern boolean isEven(const int value);

/*
    Returns whether a number is odd or not
    Takes one integer `value`
    Returns `TRUE` iff `value` is odd.
*/
extern boolean isOdd(const int value);

/*
    Returns whether a number is prime or not
    Takes one integer `value`
    Returns `TRUE` iff `value` is prime (`value` is only divisible by `1` and `value`).
*/
extern boolean isPrime(const unsigned int value);

/*
    Returns the nth fibonacci number
    Takes one integer `nth`
    Returns the `nth` number in the fibonacci sequence.
*/
extern unsigned int fibonnaci(const unsigned int nth);

// String

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
extern int indexOf(const char * string, const char e);

/*
    Returns the last index where a character appears in a string.
    Takes a `NULL-Terminated` string (`string`) and a character to look for (`e`)
    Returns `i` such that `string[i] == e` and there is no `j > i` where `string[j] == e`,
    returns `-1` if the character does not appear in the string
*/
extern int lastIndexOf(const char * string, const char e);

/*
    Returns a modified version of a string where every uppercase letter has been transformed into lowercase.
    Takes a `NULL-Terminated` string (`string`)
    Returns a new `NULL-terminated` string (`string2`) equal to `string` except for every uppercase letter
    in `string` will be in lowercase in `string2`
*/
extern char * toLowerCase(const char * string);

/*
    Returns a modified version of a string where every lowercase letter has been transformed into uppercase.
    Takes a `NULL-Terminated` string (`string`)
    Returns a new `NULL-terminated` string (`string2`) equal to `string` except for every lowercase letter
    in `string` will be in uppercase in `string2`
*/
extern char * toUpperCase(const char * string);

/*
    Returns a `NULL-Terminated` substring string of another `NULL-Terminated` string.
    Takes a `NULL-Terminated` string (`string`), and two unsigned ints (`from`, and `to`)
    Returns a slice of `string` going from index `from` (inclusive) to index `to` (exclusive),
*/
extern char * substring(const char * string, unsigned int from, unsigned int to);

// Boolean

/*
    Returns the logical and between two boolean values
    Takes two `boolean` values `a` and `b`
    Returns `a && b`
*/
extern boolean and(const boolean a, const boolean b);

/*
    Returns the logical not of a boolean value
    Takes one `boolean` value `a`
    Returns `! a`
*/
extern boolean not(const boolean a);

/*
    Returns the logical or between two boolean values
    Takes two `boolean` values `a` and `b`
    Returns `a || b`
*/
extern boolean or(const boolean a, const boolean b);

/*
    Returns the logical xor between two boolean values
    Takes two `boolean` values `a` and `b`
    Returns `a ^ b`
*/
extern boolean xor(const boolean a, const boolean b);

/*
    Defines a boolean expression that can be evaluated into a single `boolean` value
*/
struct expression;

/*
    Creates an `expression` representing a single boolean value.
    Takes a `boolean` value (`value`)
    Returns a pointer to a new `expression` representing a boolean value from `value`
*/
extern struct expression* BOOLEAN_VALUE(boolean value);

/*
    Creates an `expression` representing a negation of another `expression`.
    Takes a pointer to an `expression` `e`
    Returns a pointer to a new `expression` representing a negation of `e`
*/
extern struct expression* NOT(struct expression* e);

/*
    Creates an `expression` representing a conjunction of two other `expression`s.
    Takes two pointers to `expression`s `left` and `right`
    Returns a pointer to a new `expression` representing a conjunction of `left` and `right`
*/
extern struct expression* AND(struct expression* left, struct expression* right);

/*
    Creates an `expression` representing a disjunction of two other `expression`s.
    Takes two pointers to `expression`s `left` and `right`
    Returns a pointer to a new `expression` representing a disjunction of `left` and `right`
*/
extern struct expression* OR(struct expression* left, struct expression* right);

//TODO: add XOR function

/*
    Evaluates an `expression` into a `boolean` value
    Takes a pointer to an `expression` `expr`
    Evaluates `expr` into a `boolean` value
*/
extern boolean eval(struct expression* expr);

/*
    Cleans (free) an `expression` value
    Takes a pointer to an `expression` `expr`
    Frees all the memory taken by `expr`
*/
extern void drop(struct expression* expr);

/*
    An `expression` constant representing a `True` expression
*/
#define V BOOLEAN_VALUE(TRUE)

/*
    An `expression` constant representing a `False` expression
*/
#define F BOOLEAN_VALUE(FALSE)

#endif // STANDARD_DEF