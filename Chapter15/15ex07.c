/**
 *   @file     15ex07.c
 *   @date     2020-01-15
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    select/poll a pipe
 */

#include <sys/poll.h>
#include <sys/select.h>

#include "apue.h"

void test_select_closew() {
    int            fd[2];
    fd_set         rfds;
    struct timeval tv;
    int            ret;
    pid_t          pid;

    puts("test select: close write end");

    if (pipe(fd) < 0) {
        err_sys("pipe error");
    }

    FD_ZERO(&rfds);
    FD_SET(fd[0], &rfds);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        sleep(5);
        close(fd[1]);
        printf("child: write end closed");
        exit(EXIT_SUCCESS);
    } else {
        for (;;) {
            tv.tv_sec  = 1;
            tv.tv_usec = 0;

            write(fd[1], "hello, world\n", 13);
            ret = select(fd[0] + 1, &rfds, NULL, NULL, &tv);
            if (ret == -1) {
                err_sys("select error");
            } else if (ret > 0) {
                printf("data ready\n");
            } else {
                printf("time expired\n");
            }
        }
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    }
}

void test_select_closer() {
    int            fd[2];
    fd_set         rfds;
    struct timeval tv;
    int            ret;
    pid_t          pid;

    puts("test select: close read end");

    if (pipe(fd) < 0) {
        err_sys("pipe error");
    }

    FD_ZERO(&rfds);
    FD_SET(fd[0], &rfds);

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        write(fd[1], "hello, world\n", 13);
        sleep(5);
        close(fd[0]);
        printf("child: read end closed");
        exit(EXIT_SUCCESS);
    } else {
        for (;;) {
            tv.tv_sec  = 1;
            tv.tv_usec = 0;

            ret = select(fd[0] + 1, &rfds, NULL, NULL, &tv);
            if (ret == -1) {
                err_sys("select error");
            } else if (ret > 0) {
                printf("\rdata ready\n");
                if (FD_ISSET(fd[0], &rfds)) {
                    char buff[MAXLINE] = {0};
                    read(fd[0], buff, MAXLINE);
                    printf("data read: %s", buff);
                    write(fd[1], buff, strlen(buff));
                }
            } else {
                printf("time expired\n");
            }
        }
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    }
}

void test_poll() {}

int main() { test_select_closer(); }
