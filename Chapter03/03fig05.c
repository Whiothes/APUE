#include <fcntl.h>
#include <sys/stat.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    int  n;
    char buf[BUFSIZ];

    int in  = open(argv[1], O_RDONLY);
    int out = open(argv[2], O_CREAT | O_RDWR, 0644);

    while ((n = read(in, buf, BUFSIZ)) > 0) {
        if (write(out, buf, n) != n) {
            err_sys("write error");
        }
    }

    close(in);
    close(out);
    if (n < 0) {
        err_sys("read error");
    }
    return 0;
}
