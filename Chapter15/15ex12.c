/**
 *   @file     15ex12.c
 *   @date     2020-01-17
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    practice a message queue
 */

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include "apue.h"

#define MSG_KEY 5
#define MSG_LEN 32

typedef struct {
    long mtype;
    char mtext[MSG_LEN];
} msgbuf;

int main() {
    int    msqid;
    msgbuf msg = {0};

    for (int i = 0; i < 5; ++i) {
        if ((msqid = msgget(MSG_KEY, IPC_CREAT)) == -1) {
            err_msg("msgget error");
        } else {
            printf("id: %d\n", msqid);
            msgctl(msqid, IPC_RMID, NULL);
        }
    }

    getchar();

    for (int i = 0; i < 5; ++i) {
        if ((msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600)) == -1) {
            err_msg("msgget error");
        }

        msg.mtype = 1;
        snprintf(msg.mtext, MSG_LEN, "hello world");

        int msgsz = strlen(msg.mtext);
        if ((msgsnd(msqid, &msg, msgsz, 0)) == -1) {
            perror("msgsnd error: ");
        }

        memset(msg.mtext, 0, MSG_LEN);
        if (msgrcv(msqid, &msg, MSG_LEN, 0, 0) == -1) {
            perror("msgrcv error: ");
        }

        printf("mtext: %s\n", msg.mtext);
    }

    return 0;
}
