/**
 *   @file     15ex17.c
 *   @date     2020-02-03
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Redo the 15fig33 using advisory record lock
 */

#include <fcntl.h>

#include "apue.h"

#define NLOOPS 10
#define SIZE   sizeof(long)  // size of shared memory area

#if defined(__linux__)
union semun {
    int              val;   /* Value for SETVAL */
    struct semid_ds *buf;   /* Buffer for IPC_STAT, IPC_SET */
    unsigned short * array; /* Array for GETALL, SETALL */
    struct seminfo * __buf; /* Buffer for IPC_INFO
                               (Linux-specific) */
};
#endif

static int update(int *ptr) {
    int ret = (*ptr)++;
    printf("%d: area: %d, counter = %d\n", getpid(), *ptr, ret);
    return ret;  // return value before increment
}

int main() {
    int   i, counter;
    pid_t pid;
    int   area;
    int   fd;

    fd = open("/dev/zero", O_RDONLY);

    TELL_WAIT();

#if 1
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        for (i = 0; i < NLOOPS; i += 2) {
            flock(fd, LOCK_SH);

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("parent: <%p> %d\n", &area, area - 2);

            flock(fd, LOCK_UN);

            TELL_CHILD(pid);
            WAIT_CHILD();
        }

    } else {
        /* child */
        area = 1;
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();

            flock(fd, LOCK_SH);

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("child: <%p> %d\n", &area, area - 2);

            flock(fd, LOCK_UN);

            TELL_PARENT(getppid());
        }
    }
#endif
}
