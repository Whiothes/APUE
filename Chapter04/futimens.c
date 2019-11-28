#include <fcntl.h>
#include <sys/stat.h>

#include "apue.h"

int main(int argc, char *argv[argc]) {
    int             i, fd;
    struct stat     statbuf;
    struct timespec times[2];

    for (i = 0; i < argc; ++i) {
        if (stat(argv[i], &statbuf) < 0) { /* fetch current times */
            err_ret("%s: %s", argv[i], strerror(errno));
            continue;
        }

        if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { /* truncate */
            err_ret("%s: %s", argv[i], strerror(errno));
            continue;
        }

        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;

        if (futimens(fd, times) < 0) { /* reset times */
            err_ret("%s: %s", argv[i], strerror(errno));
        }

        close(fd);
    }

    return 0;
}
