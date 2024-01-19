#include <sstd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>

static boolean file_exists(const string const filename);
static boolean file_is_executable(const string const filename);
static int string_array_size(const string * const array);
static void sigterm(int signal);
static void sigint(int signal);
static pid_t pid;

int s_execute(const string const path_to_executable, const string * const args) {
    extern char ** environ;
    if (path_to_executable == NULL) {
        return -ERROR_SYSTEM_NULL_FILE;
    }
    if (!file_exists(path_to_executable)) {
        return -ERROR_SYSTEM_NO_FILE;
    }
    if (!file_is_executable(path_to_executable)) {
        return -ERROR_SYSTEM_NO_ACCESS;
    }
    int args_size = string_array_size(args);
    string * execve_args = (string *) malloc(sizeof (string *) * (args_size + 2));
    execve_args[0] = path_to_executable;
    execve_args[args_size + 1] = NULL;
    for (int i = 0; i < args_size; i++) {
        execve_args[i + 1] = args[i];
    }
    pid = fork();
    if (pid == 0) {
        execve(path_to_executable, execve_args, environ);
        return -ERROR_SYSTEM_EXECUTION_FAILED;
    } else {
        signal(SIGTERM, sigterm);
        signal(SIGINT, sigint);
        int status;
        if (wait(&status) == -1) {
            return -errno;
        }
        if (WIFEXITED(status)) {
            int es = WEXITSTATUS(status);
            return es;
        } else if (WIFSIGNALED(status)) {
            int es = WTERMSIG(status);
            return -es;
        } else {
            return -ERROR_SYSTEM_CHILD_INVALID_EXIT;
        }
    }
}

static void sigterm(int signal) {
    if (signal == SIGTERM) {
        kill(pid, SIGTERM);
    }
}

static void sigint(int signal) {
    if (signal == SIGINT) {
        kill(pid, SIGINT);
    }
}

boolean file_exists(const string const filename) {
    return access(filename, F_OK) == 0;
}

boolean file_is_executable(const string const filename) {
    return access(filename, X_OK) == 0;
}

static int string_array_size(const string * const array) {
    if (array == NULL) {
        return 0;
    }
    int i = 0;
    while (array[i] != NULL) {
        i++;
    }
    return i;
}
