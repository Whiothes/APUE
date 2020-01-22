/**
 *   @file     fig.8.c
 *   @date     2019-11-15
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Using a recursive mutex
 */
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#include "apue.h"

extern int makethread(void *(*)(void *), void *);

struct to_info {
    void (*to_fn)(void *);   // function
    void *         to_arg;   // argument
    struct timeval to_wait;  // time to wait
};

#define SECTOUSEC 1000000  // seconds to nanoseconds

#define clock_nanosleep(ID, FL, REQ, REM) nanosleep((REQ), (REM))

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC     1000  // microseconds to nanoseconds

void clock_gettime(int id, struct timespec *tsp) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    tsp->tv_sec  = tv.tv_sec;
    tsp->tv_nsec = tv.tv_usec * USECTONSEC
}
#endif

void *timeout_helper(void *arg) {
    struct to_info *tip;

    tip = (struct to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return 0;
}

void timeout(const struct timespec *when, void (*func)(void *), void *arg) {
    struct timespec now;
    struct to_info *tip;
    int             err;

    clock_gettime(CLOCK_REALTIME, &now);
    if ((when->tv_sec > now.tv_sec) ||
        (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
        tip = malloc(sizeof(struct to_info));
        if (tip != NULL) {
            tip->to_fn          = func;
            tip->to_arg         = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec) {
                tip->to_wait.tv_usec = when->tv_nsec / 1000 - now.tv_nsec;
            } else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_usec =
                    SECTOUSEC - now.tv_usec + when->tv_nsec / 1000;
            }

            select(0, NULL, NULL, NULL, &tip->to_wait);
        }
    }
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t     mutex;

void retry(void *arg) {
    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
}

int main(void) {
    int             err = 0, condition = 0, arg = 0;
    struct timespec when;

    if ((err = pthread_mutexattr_init(&attr)) != 0) {
        err_exit(err, "pthread_mutexattr_init failed");
    }
    if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) !=
        0) {
        err_exit(err, "can't set recursive type");
    }
    if ((err = pthread_mutex_init(&mutex, &attr)) != 0) {
        err_exit(err, "can't create recursive mutex");
    }

    if (condition == 0) {
        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 10;  // 10 seconds after now
        timeout(&when, retry, (void *)((unsigned long)arg));
    }
    pthread_mutex_unlock(&mutex);

    exit(0);
}
