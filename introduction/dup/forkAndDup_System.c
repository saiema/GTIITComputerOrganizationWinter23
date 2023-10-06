#include <unistd.h> /* UNIX syscalls */
#include <fcntl.h>  /* file operations and flags */
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    if (fork() == 0) {
        /* in child: open/create file with permissions (user: rw, group:r) */
        int fd = open("out.txt", O_WRONLY | O_CREAT, 0640);

        close(1);                       /* close stdout */
        dup(fd);                        /* duplicate fd (copy in ofiles[1]) */
        system("echo \"Hello world\"");
        exit(0);
    }
    write(1, "This is the father!\n", 20);
    wait(0);
    write(1, "Bye bye!\n", 9);
}