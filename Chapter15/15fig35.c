/**
 *   @file     15fig35.c
 *   @date     2020-01-11
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Mutual exclusion using a POSIX semaphore
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "slock.h"

struct slock *s_alloc() {
    struct slock *sp;
    static int    cnt;

    if ((sp = malloc(sizeof(struct slock))) == NULL) {
        return NULL;
    }

    do {
        snprintf(sp->name, sizeof(sp->name), "/%ld.%d", (long)getpid(), cnt++);
        sp->semp = sem_open(sp->name, O_CREAT | O_EXCL, S_IRWXU, 1);
    } while ((sp->semp == SEM_FAILED) && (errno == EEXIST));
    if (sp->semp == SEM_FAILED) {
        free(sp);
        return NULL;
    }

    sem_unlink(sp->name);
    return sp;
}

void s_free(struct slock *sp) {
    sem_close(sp->semp);
    free(sp);
}

int s_lock(struct slock *sp) { return sem_wait(sp->semp); }

int s_trylock(struct slock *sp) { return sem_trywait(sp->semp); }

int s_unlock(struct slock *sp) { return sem_post(sp->semp); }
