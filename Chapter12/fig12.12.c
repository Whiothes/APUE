/**
 *   @file     fig12.12.c
 *   @date     2019-11-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    a reentrant version of getenv
 */

#include <errno.h>
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

int getenv_r(const char *name, char *buf, int buflen) {
  int i, len, olen;

  pthread_once(&init_done, thread_init);
  len = strlen(name);
  pthread_mutex_lock(&env_mutex);
  for (i = 0; environ[i] != NULL; ++i) {
    if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
      olen = strlen(&environ[i][len + 1]);
      if (olen >= buflen) {
        pthread_mutex_unlock(&env_mutex);
        return (ENOSPC);
      }
      strcpy(buf, &environ[i][len + 1]);
      pthread_mutex_unlock(&env_mutex);
      return (0);
    }
  }

  pthread_mutex_unlock(&env_mutex);
  return (ENOENT);
}
