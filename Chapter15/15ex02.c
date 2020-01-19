/**
 *   @file     15ex02.c
 *   @date     2020-01-04
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    copy file to pager program
 */

#include <sys/wait.h>

#include "apue.h"

extern char *__progname;

#define DEF_PAGER "/bin/more"  // default pager program

int main(int argc, char *argv[]) {
    int   n;
    int   fd[2];
    pid_t pid;
    char *pager, *argv0;
    char  line[MAXLINE];
    FILE *fp;

    if (argc != 2) {
        err_quit("usage: %s <pathname>", __progname);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        err_sys("can't open %s", argv[1]);
    }
    if (pipe(fd) < 0) {
        err_sys("pipe error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");

    } else if (pid == 0) {
        // child
        close(fd[1]);
        // close write end

        if (fd[0] != STDIN_FILENO) {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                err_sys("dup2 error");
            }
            close(fd[0]);
        }

        if ((pager = getenv("PAGER")) == NULL) {
            pager = DEF_PAGER;
        }

        if ((argv0 = strchr(pager, '/')) != NULL) {
            argv0++;
        } else {
            argv0 = pager;
        }

        if (execl(pager, argv0, (char *)0) < 0) {
            err_sys("execl error for %s", pager);
        }

    } else {
        // parent
        close(fd[0]);  // close read end

        while (fgets(line, sizeof(line), fp) != NULL) {
            n = strlen(line);
            if (write(fd[1], line, n) != n) {
                err_sys("write to pipe error");
            }
        }
        if (ferror(fp)) {
            err_sys("fgets error");
        }

        close(fd[1]);
        // if (waitpid(pid, NULL, 0) < 0) {
        //     err_sys("waitpid error");
        // }
        exit(0);
    }
}
