#include <stdio.h>
#include <stdlib.h>
#include "standard.h"

#define SIZE 42
#define MAX_VALUE 15

void print_array(const int size, const int values[size]);

void main(int argc, char ** argv) {
    printf("max(1,2): %d\n", max(1,2));
    printf("max(2,1): %d\n", max(2,1));
    printf("max(-1, 1): %d\n", max(-1, 1));
    printf("max(1, -1): %d\n", max(1, -1));

    int values[SIZE];
    int seed = argc>1?atoi(argv[1]):33;
    srand(seed);
    for (int i = 0; i < SIZE; i++) {
        values[i] = rand() % MAX_VALUE;
    }
    print_array(SIZE, values);
    printf("maximum is: %d\n", maximum(SIZE, values));

    for (int i = 0; i < SIZE; i++) {
        printf("isEven(%1$d): %2$d\t|\tisOdd(%1$d): %3$d\t|\tisPrime(%1$d): %4$d\n",
            values[i],
            is_even(values[i]),
            is_odd(values[i]),
            is_prime(values[i])
        );
    }
    
    printf("Fibonnaci sequence:\n");
    for (int ith = 1; ith < 20; ith++) {
        printf("%dth fibonacci: %d\n", ith, fibonnaci(ith));
    }
    const char * helloThere = "Hello there! - General Kenobi!";
    const char * hello = "Hello!";
    const char * hello_ = "Hello! ";
    const char * h3llo = "H3llo!";
    printf("length(%s): %d\n", helloThere, length(helloThere));
    printf("toLowerCase(%s): %s\n", helloThere, to_lower_case(helloThere));
    printf("toUpperCase(%s): %s\n", helloThere, to_upper_case(helloThere));
    printf("indexOf(%s, %c): %d\n", helloThere, 'e', index_of(helloThere, 'e'));
    printf("lastIndexOf(%s, %c): %d\n", helloThere, 'e', last_index_of(helloThere, 'e'));
    printf("equals(%s, %s): %d\n", hello, hello, equals(hello, hello));
    printf("equals(%s, %s): %d\n", hello_, hello, equals(hello_, hello));
    printf("equals(%s, %s): %d\n", hello, hello_, equals(hello, hello_));
    printf("equals(%s, %s): %d\n", h3llo, hello, equals(h3llo, hello));
    printf("equals(%s, %s): %d\n", hello, h3llo, equals(hello, h3llo));
    printf("equals(%s, %s): %d\n", h3llo, hello_, equals(h3llo, hello_));
    printf("equals(%s, %s): %d\n", hello_, h3llo, equals(hello_, h3llo));
    printf("substring(%s, %d, %d): %s\n",
        helloThere, 0, length(helloThere),
        substring(helloThere, 0, length(helloThere))
    );
    printf("substring(%s, %d, %d): %s\n",
        helloThere, 15, 30,
        substring(helloThere, 15, 30)
    );
    printf("substring(%s, %d, %d): %s\n",
        helloThere, 15, 22,
        substring(helloThere, 15, 22)
    );
    const boolean booleans[2] = {TRUE, FALSE};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            struct expression * e = NOT( 
                AND(
                    BOOLEAN_VALUE(booleans[i]),
                    OR(
                        BOOLEAN_VALUE(booleans[i]),
                        BOOLEAN_VALUE(booleans[j])
                    )
                )
            );
            printf("NOT(AND(%d, OR(%d, %d))): %d\n",
                booleans[i],
                booleans[i],
                booleans[j],
                eval(e)
            );
            drop(e);
        }
    }
}

void print_array(const int size, const int values[size]) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", values[i]);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf("]\n");
}