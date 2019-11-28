#include "apue.h"

#ifdef SOLARIS
#include <sys/mkdev.h>
#endif  // SOLARIS

int main(int argc, char *argv[]) {
    int         i;
    struct stat buf;
    for (i = 0; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (stat(argv[i], &buf) < 0) {
            err_ret("stat error");
            continue;
        }
        printf("dev = %d/%d", MAJOR(buf.st_dev), MINOR(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)) {
            printf(" (%s) rdev = %d/%d",
                   (S_ISCHR(buf.st_mode)) ? "character" : "block",
                   major(buf.st_mode), minor(buf.st_rdev));
        }
        printf("\n");
    }
    return 0;
}
