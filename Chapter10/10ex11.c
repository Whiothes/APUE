#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>

#include "apue.h"

#define BUFFSIZ 10

int main(int argc, char *argv[]) {
    int  n;
    int  ret;
    char buf[BUFFSIZ];

    signal(SIGXFSZ, signal_intr);

    int in  = open(argv[1], O_RDONLY);
    int out = open(argv[2], O_CREAT | O_RDWR, 0644);

    struct rlimit r = {0};
    r.rlim_max      = 12;
    setrlimit(RLIMIT_FSIZE, &r);

    while ((n = read(in, buf, BUFFSIZ)) > 0) {
        if ((ret = write(out, buf, n)) != n) {
            // err_sys("write error: %d", ret);
            printf("%d write\n", ret);
        }
    }

    close(in);
    close(out);
    if (n < 0) {
        err_sys("read error");
    }
    return 0;
}
