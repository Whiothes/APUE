#include "apue.h"

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        exit(0);
    }

    sleep(4);

    system("ps -o pid,ppid,state,tty,command");
}
