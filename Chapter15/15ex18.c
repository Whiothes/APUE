/**
 *   @file     15ex18.c
 *   @date     2020-02-03
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Redo the 15fig33 using POSIX semaphore functions
 */

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>

#include "apue.h"
#include "slock.h"

#define NLOOPS 10
#define SIZE   sizeof(long)  // size of shared memory area

static int update(int *ptr) {
    int ret = (*ptr)++;
    printf("%d: area: %d, counter = %d\n", getpid(), *ptr, ret);
    return ret;  // return value before increment
}

struct slock *sp = NULL;

void exit_func(void) { s_free(sp); }

int main() {
    int   i, counter;
    pid_t pid;
    int   area;

    atexit(exit_func);

    sp = s_alloc();

    TELL_WAIT();

#if 1
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) {
        for (i = 0; i < NLOOPS; i += 2) {
            s_lock(sp);

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("parent: <%p> %d\n", &area, area - 2);

            s_unlock(sp);
            TELL_CHILD(pid);
            WAIT_CHILD();
        }

    } else {
        /* child */
        area = 1;
        for (i = 1; i < NLOOPS + 1; i += 2) {
            WAIT_PARENT();
            s_lock(sp);

            area += 2;
            if (area - 2 != i) {
                err_sys("parent excepted %d got %d", i, area - 2);
            }
            printf("child: <%p> %d\n", &area, area - 2);

            s_unlock(sp);
            TELL_PARENT(getppid());
        }
    }
#endif
}

struct slock *s_alloc() {
    struct slock *sp;
    static int    cnt;

    if ((sp = malloc(sizeof(struct slock))) == NULL) return (NULL);
    do {
        snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
        sp->semp = sem_open(sp->name, O_CREAT | O_EXCL, 0666, 1);
    } while ((sp->semp == SEM_FAILED) && (errno == EEXIST));
    if (sp->semp == SEM_FAILED) {
        free(sp);
        return (NULL);
    }
    sem_unlink(sp->name);
    return (sp);
}

void s_free(struct slock *sp) {
    sem_close(sp->semp);
    free(sp);
}

int s_lock(struct slock *sp) { return sem_wait(sp->semp); }

int s_trylock(struct slock *sp) { return sem_trywait(sp->semp); }

int s_unlock(struct slock *sp) { return sem_post(sp->semp); }
