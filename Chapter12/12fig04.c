/**
 *   @file     12fig04.c
 *   @date     2019-11-15
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    create a thread in the detached state
 */
#include <pthread.h>

#include "apue.h"

int makethread(void *(*fn)(void *), void *arg) {
    int            err;
    pthread_t      tid;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if (err != 0) {
        return (err);
    }
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0) {
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return err;
}
