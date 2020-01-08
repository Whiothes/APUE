/**
 *   @file     12fig11.c
 *   @date     2019-11-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    a possible implementation of getenv
 */
#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ 4096

static char envbuf[MAXSTRINGSZ];

extern char **environ;

char *getenv(const char *name) {
    int i, len;

    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i) {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '=')) {
            strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
            return (envbuf);
        }
    }

    return (NULL);
}
