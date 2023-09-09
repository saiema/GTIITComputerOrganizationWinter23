#include <unistd.h> /* UNIX syscalls */
#include <stdio.h>  /* portable i/o functions */
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    if (fork() == 0) {
        printf("I'm the child. Pid: %d\n", getpid());
        sleep(5);
        exit(0);
    } else {
        int status;
        printf("I'm the parent. Pid: %d\n", getpid());
        wait(&status);
        printf("In parent: child finished\n");
    }
}