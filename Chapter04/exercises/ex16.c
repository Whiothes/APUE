#include <fcntl.h>

#include "apue.h"

int main(int argc, char *argv[argc]) {
    const char *dirname = "testdir";
    size_t      pathmax = pathconf(".", _PC_PATH_MAX);
    printf("pathmax: %ld\n", pathmax);

    char   path[pathmax];
    size_t curlen;

    strcpy(path, dirname);

    for (;;) {
        curlen = strlen(getcwd(path, pathmax)) + strlen(dirname);
        if (curlen <= pathmax) {
            if (mkdir(dirname, 0777) < 0) {
                printf("mkdir: %s\n", strerror(errno));
                return -1;
            }
            sprintf(path, "/%s", dirname);
            chdir(dirname);
        } else {
            break;
        }
    }
    printf("curlen = %ld\n", curlen);

    return 0;
}
