/**
 *   @file     15ex15.c
 *   @date     2020-02-03
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Redo the 15fig33 using XSI shared memory functions
 */

#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "apue.h"

#define NLOOPS 10
#define SIZE   sizeof(long)  // size of shared memory area

static int update(long *ptr) {
    return ((*ptr)++);  // return value before increment
}

int main(void) {
    int   i, counter, shmid;
    pid_t pid;
    long *area;
    key_t key;

    if ((key = ftok("/dev/zero", 1)) < 0) {
        err_sys("ftok error");
    }

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        if ((shmid = shmget(key, sizeof(long), IPC_EXCL | IPC_CREAT | 0600)) <
            0) {
            err_sys("shmget error");
        }

        area = shmat(shmid, NULL, IPC_NOWAIT);
        if (area == NULL) {
            err_sys("shmat error");
        }
        for (i = 0; i < NLOOPS; i += 2) {
            if ((counter = update((long *)area)) != i) {
                err_quit("parent: expected %d, got %d", i, counter);
            }
            printf("parent: %d\n", counter);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }
    } else {
        if ((shmid = shmget(key, sizeof(long), IPC_CREAT | 0600)) < 0) {
            err_sys("shmget error");
        }

        area = shmat(shmid, NULL, IPC_NOWAIT);
        if (area == NULL) {
            err_sys("shmat error");
        }

        /* child */
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();

            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);

            printf("child: %d\n", counter);
            TELL_PARENT(getppid());
        }
    }

    shmctl(shmid, IPC_RMID, 0);

    TELL_WAIT();
}
