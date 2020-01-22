/**
 *   @file     13ex03.c
 *   @date     2019-12-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    call daemonize then call getlogin
 */
#include "apue.h"

extern char *__progname;

int main() {
    FILE *fp   = NULL;
    char *name = NULL;
    char *tdir = NULL;
    char out[FILENAME_MAX] = {0};

    daemonize(__progname);
    name = getlogin();

    tdir = getenv("TMPDIR");
    if (tdir) {
        snprintf(out, sizeof(out), "%s/getlog.txt", tdir);
    } else {
        snprintf(out, sizeof(out), "/var/tmp/getlog.txt");
    }

    fp = fopen(out, "w+");
    if (fp != NULL) {
        if (name == NULL) {
            fprintf(fp, "null");
        } else {
            fprintf(fp, "login name: %s\n", name);
        }
    }

    fclose(fp);
    fp = NULL;
}
