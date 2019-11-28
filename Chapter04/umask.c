#include <fcntl.h>

#include "apue.h"

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char *argv[argc]) {
    umask(0);
    if (creat("foo", RWRWRW) < 0) {
        err_sys("creat \"foo\": %s", strerror(errno));
    }

    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        err_sys("creat \"bar\": %s", strerror(errno));
    }
    return 0;
}
