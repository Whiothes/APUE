#include "apue.h"

void sig_alrm(int signo) {
    char signame[8] = {0};
    psignal(signo, signame);
    printf("%s was caught\n", signame);
    return;
}

int main() {
    char *buf = malloc(1024 * 1024 * 1024);

    memset(buf, '1', 1024 * 1024 * 1024);

    signal(SIGALRM, sig_alrm);
    alarm(1);

    FILE *fp = fopen("a.txt", "w");
    fwrite(buf, 1024 * 1024 * 1024, 1, fp);
    fclose(fp);
}
