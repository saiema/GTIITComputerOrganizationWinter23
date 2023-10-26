#include <stdio.h>
#include <sstd.h>

int main(void) {
    static char * args[3] = {"/usr/bin/sleep", "5", 0};
    int exit_code = s_execute("/usr/bin/sleep", args);

    s_printf("Last program terminated with exit code: %d\n", &exit_code);

    s_printf("Let's test this without any placeholder\n", NULL);
    int values[4] = {-42, 42, -1278, 0};
    s_printf("Now let's see if we can get a negative number like %d, then %d, and now followed by %d, and ending with a %d\n", values);

}