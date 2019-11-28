#include <sys/wait.h>

#include "apue.h"

static void sig_cld(int);

int main() {
    pid_t pid;

#if defined(__linux__)
    if (signal(SIGCLD, sig_cld) == SIG_ERR) {
        perror("signal error");
    }

#endif

    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid == 0) {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);
}

static void sig_cld(int signo) {  // interrupts pause()

    pid_t pid;
    int   status;

    printf("SIGCLD received\n");

#if defined(__linux__)
    if (signal(SIGCLD, sig_cld) == SIG_ERR) {
        perror("signal erro");
    }
#endif

    if ((pid = wait(&status)) < 0) {
        perror("wait error");
    }

    printf("pid = %d\n", pid);
}
