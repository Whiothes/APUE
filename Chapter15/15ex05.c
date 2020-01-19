/**
 *   @file     15ex05.c
 *   @date     2020-01-08
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Program to drive the add2 filter
 *          use standard I/O library instead
 */

#include "apue.h"

static void sig_pipe(int);  // our signal handler

int main(void) {
    int   n, fd1[2], fd2[2];
    FILE *fpr, *fpw;
    pid_t pid;
    char  line[MAXLINE];

    if (signal(SIGPIPE, sig_pipe) == SIG_ERR) {
        err_sys("signal error");
    }
    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        err_sys("pipe error");
    }

    if ((fpr = fdopen(fd2[0], "r")) == NULL) {
        err_sys("fdopen error");
    }
    if (setvbuf(fpr, NULL, _IOLBF, 0) < 0) {
        err_sys("setvbuf error");
    }
    if ((fpw = fdopen(fd1[1], "w")) == NULL) {
        err_sys("fdopen error");
    }
    if (setvbuf(fpw, NULL, _IOLBF, 0) < 0) {
        err_sys("setvbuf error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        // parent process
        close(fd1[0]);
        close(fd2[1]);

        while (fgets(line, MAXLINE, stdin) != NULL) {
            n = strlen(line);
#if 0
            if (write(fd1[1], line, n) != n) {
                err_sys("write error");
            }
            if ((n = read(fd2[0], line, MAXLINE)) < 0) {
                err_sys("read error");
            }
            if (n == 0) {
                err_msg("child closed pipe");
                break;
            }
#endif
            if (fputs(line, fpw) == EOF) {
                err_sys("fputs error");
            }
            if (fgets(line, MAXLINE, fpr) == NULL) {
                err_msg("fgets error");
                break;
            }
            line[n] = 0;
            if (fputs(line, stdout) == EOF) {
                err_sys("fputs error");
            }
        }

        if (ferror(stdin)) {
            err_sys("fgets error on stdin");
        }

        exit(EXIT_SUCCESS);
    } else {
        // child process
        close(fd1[1]);
        close(fd2[0]);

        if (fd1[0] != STDIN_FILENO) {
            if (dup2(fd1[0], STDIN_FILENO) < 0) {
                err_sys("dup2 error to stdin");
            }
            close(fd1[0]);
        }

        if (fd2[1] != STDOUT_FILENO) {
            if (dup2(fd2[1], STDOUT_FILENO) < 0) {
                err_sys("dup2 error to stdout");
            }
            close(fd2[1]);
        }

        // if (execl("../bin/15fig17", "15fig17", (char*)0) < 0) {
        if (execl("../bin/15fig19", "15fig19", (char *)0) < 0) {
            err_sys("excel error");
        }
        exit(EXIT_SUCCESS);
    }
}

static void sig_pipe(int signo) {
    printf("SIGPIPE caught\n");
    exit(EXIT_FAILURE);
}
