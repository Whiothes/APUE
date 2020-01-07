/**
 *   @file     15fig05.c
 *   @date     2020-01-04
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Figure 15.5 send data from parent to child over a pipe
 */

#include "apue.h"

int main(void) {
    int   n;
    int   fd[2];
    pid_t pid;
    char  line[MAXLINE];

    if ((pipe(fd)) < 0) {
        err_sys("pipe error");
    }
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else {
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }

    return (0);
}
