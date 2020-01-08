/**
 *   @file     11fig16.c
 *   @date     2019-11-10
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    show how a barrier can be used to synchronize threads cooperating
 * on a single task
 */
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

#include "apue.h"

#define NTHR   8
#define NUMNUM 800000L
#define TNUM   (NUMNUM / NTHR)

long nums[NUMNUM];
long snums[NUMNUM];

#if defined(SOLARIS)
#define heapsort gsort
#elif defined(__linux__)
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t,
                    int (*)(const void *, const void *));
#endif

#if defined(__APPLE__)
typedef struct {
    int             counter;
    pthread_cond_t  cond;
    pthread_mutex_t mutex;
} pthread_barrier_t;

int pthread_barrier_init(pthread_barrier_t *b, void *attr, int count) {
    int ret;

    ret = pthread_mutex_init(&b->mutex, NULL);
    if (ret != 0) {
        goto err;
    }
    ret = pthread_cond_init(&b->cond, NULL);
    if (ret != 0) {
        pthread_mutex_destroy(&b->mutex);
        goto err;
    }
    b->counter = count;

    return ret;
err:
    return ret;
}

int pthread_destroy(pthread_barrier_t *b) {
    int ret = 0;

    ret = pthread_mutex_lock(&b->mutex);
    if (ret != 0) {
        goto err;
    }

    ret = pthread_mutex_destroy(&b->mutex);
    ret = pthread_cond_destroy(&b->cond);

    return ret;
err:
    return ret;
}

int pthread_barrier_wait(pthread_barrier_t *b) {
    int cancel = 0;

    int ret = pthread_mutex_lock(&b->mutex);
    if (ret != 0) {
        goto err;
    }

    if (--b->counter == 0) {
        pthread_cond_broadcast(&b->cond);
    } else {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cancel);

        pthread_cond_wait(&b->cond, &b->mutex);
        pthread_setcancelstate(cancel, NULL);
    }

    pthread_mutex_unlock(&b->mutex);
    return ret;

err:
    return ret;
}
#endif

pthread_barrier_t b;

int complong(const void *arg1, const void *arg2) {
    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;

    return l1 == l2 ? 0 : l1 > l2 ? 1 : -1;
}

void *thr_fn(void *arg) {
    long idx = (long)arg;

    heapsort(&nums[idx], TNUM, sizeof(long), complong);
    pthread_barrier_wait(&b);

    return ((void *)0);
}

void merge() {
    long idx[NTHR];
    long i, minidx, sidx, num;

    for (i = 0; i < NTHR; i++) idx[i] = i * TNUM;

    for (sidx = 0; sidx < NUMNUM; sidx++) {
        num = LONG_MAX;
        for (i = 0; i < NTHR; ++i) {
            if ((idx[i] < (i + 1) * TNUM) && (nums[idx[i]] < num)) {
                num    = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;
    }
}
int main() {
    unsigned long  i;
    struct timeval start, end;
    long long      startusec, endusec;
    double         elapsed;
    int            err;
    pthread_t      tid;

    srandom(1);
    for (i = 0; i < NUMNUM; ++i) {
        nums[i] = random();
    }

    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for (i = 0; i < NTHR; ++i) {
        void *func = thr_fn;
        err        = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0) {
            err_exit(err, "can't create thread");
        }
    }
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec   = end.tv_sec * 100000 + end.tv_usec;
    printf("sort took %.4f seconds", elapsed);

    for (i = 0; i < NUMNUM; ++i) {
        printf("%ld\n", snums[i]);
    }
    exit(0);
}
