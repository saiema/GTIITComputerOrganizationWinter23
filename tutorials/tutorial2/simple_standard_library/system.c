#include <sstd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

static boolean file_exists(const string const filename);
static boolean file_is_executable(const string const filename);
static boolean file_is_readable(const string const filename);
static boolean file_is_writeable(const string const filename);
static int string_array_size(const string * const array);

int s_execute(const string const path_to_executable, const string * const args) {
    return s_execute_with_redirection(path_to_executable, args, NONE, NULL, TRUE);
}

int s_execute_optional_wait(const string const path_to_executable, const string * const args, const boolean wait) {
    return s_execute_with_redirection(path_to_executable, args, NONE, NULL, wait);
}

int s_execute_with_redirection(const string const path_to_executable, const string * const args, const redirect redirect_op, const string redirect_file, const boolean _wait) {
    if (path_to_executable == NULL) {
        return -ERROR_SYSTEM_NULL_FILE;
    }
    if (!file_exists(path_to_executable)) {
        return -ERROR_SYSTEM_NO_FILE;
    }
    if (!file_is_executable(path_to_executable)) {
        return -ERROR_SYSTEM_NO_ACCESS;
    }
    if (redirect_op != NONE && redirect_file == NULL) {
        return -ERROR_SYSTEM_READ_FILE_NULL;
    }
    int args_size = string_array_size(args);
    string * execve_args = (string *) malloc(sizeof (string *) * (args_size + 2));
    execve_args[0] = path_to_executable;
    execve_args[args_size + 1] = NULL;
    for (int i = 0; i < args_size; i++) {
        execve_args[i + 1] = args[i];
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (redirect_op == REDIRECT_OUT) {
            if (file_exists(redirect_file) && !file_is_writeable(redirect_file)) {
                return -ERROR_SYSTEM_READ_FILE_ACCESS;
            }
            int fd = open(redirect_file, O_CREAT | O_WRONLY, 0666);
            if (fd < 0) return -ERROR_SYSTEM_READ_FILE_OPEN;
            close(STDOUT_FILENO);
            dup(fd);
        } else if (redirect_op == REDIRECT_IN) {
            if (file_exists(redirect_file) && !file_is_readable(redirect_file)) {
                return -ERROR_SYSTEM_READ_FILE_ACCESS;
            }
            int fd = open(redirect_file, O_RDONLY);
            if (fd < 0) return -ERROR_SYSTEM_READ_FILE_OPEN;
            close(STDIN_FILENO);
            dup(fd);
        }
        execv(path_to_executable, execve_args);
        return -ERROR_SYSTEM_EXECUTION_FAILED;
    } else {
        if (!wait) {
            return 0;   
        }
        int status;
        if (wait(&status) == -1) {
            return -errno;
        }
        if (WIFEXITED(status)) {
            int es = WEXITSTATUS(status);
            return es;
        } else {
            return -ERROR_SYSTEM_CHILD_INVALID_EXIT;
        }
    }
}

static boolean file_exists(const string const filename) {
    return access(filename, F_OK) == 0;
}

static boolean file_is_executable(const string const filename) {
    return access(filename, X_OK) == 0;
}

static boolean file_is_readable(const string const filename) {
    return access(filename, R_OK) == 0;
}

static boolean file_is_writeable(const string const filename) {
    return access(filename, W_OK) == 0;
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
