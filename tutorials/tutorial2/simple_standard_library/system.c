#include <sstd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

static boolean file_exists(const string const filename);
static boolean file_is_executable(const string const filename);

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
    pid_t pid = fork();
    if (pid == 0) {
        execve(path_to_executable, args, environ);
        return -ERROR_SYSTEM_EXECUTION_FAILED;
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
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

boolean file_exists(const string const filename) {
    return access(filename, F_OK) == 0;
}

boolean file_is_executable(const string const filename) {
    return access(filename, X_OK) == 0;
}
