/**
 *   @file     12ex02.c
 *   @date     2019-11-28
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    a thread-safe reentrant version of putenv
 */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void) {
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int putenv_r(const char *name, const char *val) {
    int   i, len;
    char *buf = NULL;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);

    setenv(name, val, 1);

    pthread_mutex_unlock(&env_mutex);
    pthread_mutex_destroy(&env_mutex);
    return 0;
}
