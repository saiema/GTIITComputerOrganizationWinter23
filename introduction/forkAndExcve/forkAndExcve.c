#include <unistd.h> /* UNIX syscalls */
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>  /* portable i/o functions */

int main(void) {
    char *args[] = {"ls", "-l", 0};

    if (fork() == 0) {
        /* in child */
        execve("/bin/ls", args, 0);
        printf("Ooops, exec() failed!\n");
        exit(-1); /* finish with error exit code */
    } else {
        wait(0);
        printf("In parent: child finished\n");
    }
}