#include <pwd.h>

#include "apue.h"

static void my_alarm(int signo) {
    struct passwd *rootptr;

    printf("in signal hander\n");

    if ((rootptr = getpwnam("hello")) == NULL) {
        err_sys("getpwnam(root) error");
    }
    alarm(1);
}

int main() {
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);

    // usleep(500);                  // it seems alarm cannot interrupt sleep
    // function

    for (;;) {
        if ((ptr = getpwnam("zhoush")) == NULL) {
            err_sys("getpwnam error");
        }

        if (strcmp(ptr->pw_name, "zhoush") != 0) {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
}
