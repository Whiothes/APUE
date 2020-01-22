/**
 *   @file     14ex01.c
 *   @date     2019-12-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    test write lock
 */

#include <errno.h>
#include <fcntl.h>

#include <sys/select.h>

fd_set set;

#include "apue.h"

void sigint(int signo) {}

int  main(void) {
    pid_t pid1, pid2, pid3;
    int   fd;

    setbuf(stdout, NULL);
    signal_intr(SIGINT, sigint);

    if ((fd = open("lockfile", O_RDWR | O_CREAT, FILE_MODE)) < 0) {
        err_sys("can't create lockfile");
    }

    switch ((pid1 = fork())) {
        case -1:
            err_sys("fork failed");
            break;
        case 0: {
            if (read_lock(fd, 0, SEEK_SET, 0) < 0) {
                err_sys("child 1: can't set RD-LOCK on file");
            }
            printf("child 1: read lock on file.\n");
            pause();
            printf("child 1: exit.\n");
            exit(EXIT_SUCCESS);
        }

        default:
            sleep(2);
            break;
    }

    switch ((pid2 = fork())) {
        case -1:
            err_sys("fork failed");
            break;
        case 0: {
            if (read_lock(fd, 0, SEEK_SET, 0) < 0) {
                err_sys("child 2: can't set RD-LOCK on file");
            }
            printf("child 2: read lock on file.\n");
            pause();
            printf("child 2: exit.\n");
            exit(EXIT_SUCCESS);
        }

        default:
            sleep(2);
            break;
    }

    switch ((pid3 = fork())) {
        case -1:
            err_sys("fork failed");
            break;
        case 0: {
            if (write_lock(fd, 0, SEEK_SET, 0) < 0) {
                printf("child 3: can't set WR-LOCK on file.\n");
            }
            printf("child 3: wait to set WR_LOCK.\n");
            if (writew_lock(fd, 0, SEEK_SET, 0) < 0) {
                err_sys("child 3: can't WR-LOCK on file");
            }
            printf("child 3: obtained write lock on file.\n");
            pause();
            printf("child 3: exit.\n");
            exit(EXIT_SUCCESS);
        }

        default:
            sleep(2);
            break;
    }

    if (read_lock(fd, 0, SEEK_SET, 0) < 0) {
        printf("parent: can't set RD-LOCK on file: %s\n", strerror(errno));
    } else {
        printf(
            "parent: set RD-LOCK on file success while WR-LOCK is pending.\n");
    }

    printf("killing child 1...\n");
    kill(pid1, SIGINT);
    printf("killing child 2...\n");
    kill(pid2, SIGINT);
    printf("killing child 3...\n");
    kill(pid3, SIGINT);

    return (0);
}
