#include <sys/types.h>
#include <sys/wait.h>

#include "apue.h"

#define INFO_FLAGS WEXITED | WSTOPPED | WCONTINUED

void pr_info(siginfo_t *info) {
    switch (info->si_code) {
        case CLD_EXITED:
        case CLD_KILLED:
        case CLD_STOPPED:
            printf("normal termination, exit status = %d\n", info->si_status);
            break;

        default:
            printf("abnormal termination, sginal number = %d%s\n",
                   info->si_status, strsignal(info->si_status));
    }
}

int main(void) {
    pid_t pid;
    int   status;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) /* child */
        exit(7);

    siginfo_t info;
    if (waitid(P_PID, pid, &info, INFO_FLAGS) < 0) {
        err_sys("waitid error");
    }
    pr_info(&info);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (waitid(P_PID, pid, &info, INFO_FLAGS) < 0) {
        err_sys("waitid error");
    }
    pr_info(&info);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        status /= 0;

    if (wait(&status) != pid) err_sys("wait error");
    pr_exit(status);

    return 0;
}
