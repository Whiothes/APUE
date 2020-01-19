/**
 *   @file     15ex15.c
 *   @date     2020-01-10
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    IPC between parent and child using memory mapped I/O of /dev/zero
 */
#include <fcntl.h>
#include <sys/shm.h>

#include "apue.h"

#define NLOOPS 1000
#define SIZE   sizeof(long)  // size of shared memory area

static int update(long *ptr) {
    return ((*ptr)++);  // return value before increment
}

int main(void) {
    int   fd, i, counter;
    pid_t pid;
    void *area;

    int   shmid;
    FILE *fp;
    key_t key;

    if ((shmid = shmget(key, SIZE, 0600)) == -1) {
        err_sys("shmget error");
    }

    fclose(fp);

    if ((area = shmat(shmid, 0, 0)) == NULL) {
        err_sys("shmat error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) { /* parent */

        for (i = 0; i < NLOOPS; i += 2) {
            shmctl(shmid, IPC_SET | SHM_LOCK, 0);
            if ((counter = update((long *)area)) != i)
                err_quit("parent: expected %d, got %d", i, counter);

            shmctl(shmid, IPC_SET | SHM_UNLOCK, 0);
        }
    } else { /* child */

        for (i = 1; i < NLOOPS + 1; i += 2) {
            if ((counter = update((long *)area)) != i)
                err_quit("child: expected %d, got %d", i, counter);
        }
    }

    shmctl(shmid, IPC_RMID, 0);
}
