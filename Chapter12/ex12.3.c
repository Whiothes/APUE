/**
 *   @file     12fig13.c
 *   @date     2019-11-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    a signal-blocked version of getenv
 */
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRINGSZ 4096

static pthread_key_t  key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t       env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init(void) { pthread_key_create(&key, free); }

char *getenv(const char *name) {
    int       i, len;
    char     *envbuf;
    sigset_t  mask, omask;

    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &omask);

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(key);
    if (envbuf == NULL) {
        envbuf = malloc(MAXSTRINGSZ);
        if (envbuf == NULL) {
            goto nil;
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len]) == '=') {
            snprintf(envbuf, MAXSTRINGSZ - 1, "%s", &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);

            sigprocmask(SIG_SETMASK, &omask, NULL);
            return (envbuf);
        }
    }

nil:
    sigprocmask(SIG_SETMASK, &omask, NULL);
    pthread_mutex_unlock(&env_mutex);
    return (NULL);
}
