#include <unistd.h> /* UNIX syscalls */
#include <stdio.h>  /* portable i/o functions */

int main(void) {
    if (fork() == 0) {
        printf("I'm the child. Pid: %d\n", getpid());
    } else {
        printf("I'm the parent. Pid: %d\n", getpid());
    }
}