/**
 *   @file     15ex16.c
 *   @date     2020-02-03
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Redo the 15fig33 using XSI semaphore functions
 */

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

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

static void sem_doit(int semid, short op) {
    struct sembuf sbuf[1];
    int           ret;

    sbuf[0].sem_num = 0;
    sbuf[0].sem_op  = op;
    sbuf[0].sem_flg = SEM_UNDO;

    if (semop(semid, sbuf, 1) < 0) {
        perror("semop: ");
        exit(EXIT_FAILURE);
    }
}

static void _P(int semid) { sem_doit(semid, -1); }
static void _V(int semid) { sem_doit(semid, 1); }

static int sem_set(int *semid) {
    key_t       key;
    union semun un;

    if ((key = ftok("/dev/zero", 1)) < 0) {
        err_sys("ftok error");
    }
    if ((*semid = semget(key, 1, IPC_EXCL | IPC_CREAT | 0600)) < 0) {
        err_sys("semget error");
    }

    un.val = 1;
    if (semctl(*semid, 0, SETVAL, un) == -1) {
        err_sys("semctl error");
    }

    return *semid;
}

static int sem_rm(int semid) { return semctl(semid, IPC_RMID, 0); }

int semid;

void exit_func(void) { sem_rm(semid); }

int main() {
    int   i, counter;
    pid_t pid;
    int   area;

    sem_set(&semid);
    atexit(exit_func);

    TELL_WAIT();

#if 1
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        for (i = 0; i < NLOOPS; i += 2) {
            _P(semid);

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("parent: <%p> %d\n", &area, area - 2);

            _V(semid); /* +1 */
            TELL_CHILD(pid);
            WAIT_CHILD();
        }

    } else {
        /* child */
        area = 1;
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();
            _P(semid); /* -1 */

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("child: <%p> %d\n", &area, area - 2);

            _V(semid); /* +1 */
            TELL_PARENT(getppid());
        }
    }
#endif
}
