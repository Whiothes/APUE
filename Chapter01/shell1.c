#include <sys/wait.h>

#include "apue.h"

int main(void) {
    char  buf[MAXLINE]; /* from apue.h */
    pid_t pid;
    int   status;

    printf("%% "); /* print prompt (printf require %% to print %) */

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0; /* replace newline with null */
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, 0);
            err_ret("coulnd't excute: %s", buf);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }

        printf("%% ");
    }

    return 0;
}
