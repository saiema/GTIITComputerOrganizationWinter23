#include "standard.h"


int max(const int a, const int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int maximum(const int size, int values[size]) {
    int maxValue = INT_MIN;
    for (int i = 0; i < size; i++) {
        maxValue = max(maxValue, values[i]);
    }
    return maxValue;
}

boolean is_even(const int value) {
    if (value & 1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

boolean is_odd(const int value) {
    if (value & 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

boolean is_prime(const unsigned int value) {
    int divisors = 1;
    for (int divisor = 2; divisor <= value; divisor++) {
        if (value % divisor == 0) {
            divisors++;
        }
    }
    return divisors == 2;
}

unsigned int fibonnaci(const unsigned int nth) {
    int fib1 = 0;
    int fib2 = 1;
    for (int i = 1; i < nth; i++) {
        int aux = fib2;
        fib2 = fib1 + fib2;
        fib1 = aux;
    }
    return fib1;
}