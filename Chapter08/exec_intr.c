#include <sys/wait.h>

#include "apue.h"

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (execlp("systype.sh", NULL, NULL) < 0) err_sys("execl error");
    }

    if (waitpid(pid, NULL, 0) < 0) err_sys("waitpid error");

    return 0;
}
