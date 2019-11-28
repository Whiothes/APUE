#include "apue.h"

static void charatatime(char *);

int main(void) {
    pid_t pid;

    TELL_WAIT();

#if 1
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        WAIT_PARENT(); /* parent goes first */
        charatatime("output from child\n");
        TELL_PARENT(getppid());
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
#else
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        charatatime("output from child\n");
        TELL_PARENT(getppid());
    } else {
        WAIT_CHILD();
        charatatime("output from parent\n");
    }
#endif

    exit(0);
}

static void charatatime(char *str) {
    char *ptr;
    int   c;

    setbuf(stdout, NULL); /* set unbuffered */
    for (ptr = str; (c = *ptr++) != 0;) {
        usleep(100);
        putc(c, stdout);
    }
}
