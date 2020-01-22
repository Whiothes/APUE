/**
 *   @file     09ex02.c
 *   @date     2019-12-14
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Exercises 9.2
 *
 *  Write a small program that calls fork and has the child create a new
 * session. Verify that the child becomes a process group leader and that the
 * child no longer has a controlling terminal.
 *
 */

#include <errno.h>
#include <fcntl.h>

#include "apue.h"

int main(void) {
    int   fd  = 0;
    pid_t pid = 0;

    TELL_WAIT();

    pid = fork();
    switch (pid) {
        case -1:
            err_quit("fork error");

        case 0:
            WAIT_PARENT();

            printf("getsid in child before setsid: %lu\n",
                   (unsigned long)getsid(pid));
            setsid();
            printf("getsid in child after setsid : %lu\n",
                   (unsigned long)getsid(pid));

            fd = open("/dev/tty", O_RDONLY);
            if (fd < 0) {
                printf("child get tty failed: %s\n", strerror(errno));
            } else {
                printf("child get tty success\n");
                close(fd);
            }

            TELL_PARENT(getppid());
            exit(EXIT_SUCCESS);

        default:
            printf("getsid in parent before child setsid: %lu\n",
                   (unsigned long)getsid(pid));
            TELL_CHILD(pid);
            WAIT_CHILD();

            fd = open("/dev/tty", O_RDONLY);
            if (fd < 0) {
                printf("parent get tty failed: %s\n", strerror(errno));
            } else {
                printf("parent get tty success\n");
                close(fd);
            }

            printf("getsid in parent after child setsid: %lu\n",
                   (unsigned long)getsid(pid));

            exit(EXIT_SUCCESS);
    }
}
