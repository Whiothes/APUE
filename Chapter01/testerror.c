#include <errno.h>

#include "apue.h"

int main(int argc, char *argv[]) {
    fprintf(stderr, "EACCESS: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    return 0;
}
