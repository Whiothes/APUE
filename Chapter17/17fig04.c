/**
 *   @file     17fig04.c
 *   @date     2020-02-01
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Post a message to an XSI message queue
 */

#include <sys/msg.h>

#include "apue.h"

#define MAXMSZ 512

extern char *__progname;

struct mymesg {
    long mtype;
    char mtext[MAXMSZ];
};

int main(int argc, char *argv[]) {
    key_t        key;
    long         qid;
    size_t       nbytes;
    struct mymesg m;

    if (argc != 3) {
        fprintf(stderr, "usage: %s KEY message\n", __progname);
        exit(EXIT_FAILURE);
    }

    key = strtol(argv[1], NULL, 0);
    if ((qid = msgget(key, 0)) < 0) {
        err_sys("can't open queue key %s", argv[1]);
    }

    memset(&m, 0, sizeof(m));
    snprintf(m.mtext, sizeof(m.mtext), "%s", argv[2]);
    nbytes  = strlen(m.mtext);
    m.mtype = 1;

    if (msgsnd(qid, &m, nbytes, 0) < 0) {
        err_sys("can't send message");
    }

    exit(EXIT_FAILURE);
}
