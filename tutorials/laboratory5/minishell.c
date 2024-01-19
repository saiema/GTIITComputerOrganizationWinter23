/* minishell: Simple shell showing redirection, and sequential and concurrent
 * proceses execution
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define WAIT    1
#define NOWAIT  0

#define NO_REDIRECT 0
#define REDIRECT_OUTPUT 1
#define REDIRECT_INPUT 2

/*
* Prints a message to Standard Error, and returns -1;
*/
static int error(const char *msg);

/* split in (space separated) words. Output is the result: array of pointers to
 * start character of each word */
void split_cmd(char *str, char **left, char **op, char **right) {
    int words = 0, i;

    *left = str;
    for (i=0; str[i]; i++) {
        if (str[i] == ' ') {
            str[i] = 0;
            words++;
            if (words == 1) {
                *op = str + (i+1);
            } else if (words == 2) {
                *right = str + (i+1);
            } else
                return;
        }
    }
}

/* redirect standard input/output */ 
int redirect(char cmd, char *path) {
    int fd;
    
    switch(cmd) {
        case '>':
            fd = open(path, O_CREAT | O_WRONLY, 0666);
            if (fd < 0) return 0;
            close(1);
            dup(fd);
            break;
        //TODO: complete for <
        //hint: O_RDONLY for readonly
    }
    return 1;
}

int launch(char *cmd, int wait_for_child, char redirect_cmd, char *path) {
    int pid = fork();

    if (pid == 0) {
        /* in child process */
        char *args[] = {cmd, 0};

        if (redirect_cmd != ' ') {
            if (!redirect(redirect_cmd, path)) {
                error("Redirection failed!");
                return 1;
            }
        }

        execv(cmd, args);
        printf("%s failed!\n", cmd);
        return 1;
    } else if (pid > 0) {
        /* in parent */
        if (wait_for_child) {
            int exit_code;
            wait(&exit_code);
            return exit_code;
        }
        return 0;
    } else
        return 1;
}

int main(int argc, char *argv[]) {
    int exit_status = 0, i;
    char *left = 0, *op = 0, *right = 0;

    if (argc != 2) {
        return error("Usage: %s \"cmd op file/cmd\"");
    }

    split_cmd(argv[1], &left, &op, &right);

    /*
    printf("cmd: %s %s %s\n", left, op? op : 0, right ? right: 0);
    */
   
    if (!op) {
        return launch(left, WAIT, ' ', 0);
    }

    if (op[0] == '&' && !right) {
        return launch(left, NOWAIT, ' ', 0);
    }

    if (op && right) {
        switch (op[0]) {
            case ';': launch(left, WAIT, ' ', 0); 
                      exit_status = launch(right, WAIT, ' ', 0);
                      break;
            case '&': launch(left, NOWAIT, ' ', 0);
                      exit_status = launch(right, WAIT, ' ', 0);
                      break;
            case '>': exit_status = launch(left, WAIT, '>', right);
                      break;
            case '<': exit_status = launch(left, WAIT, '<', right);
                      break;
            //TODO: complete '&&', and '||'
            default:  error("Operator not supported\n");
        }
    }
        
    return exit_status;
}

static int error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    return -1;
}