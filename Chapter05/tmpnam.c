#include "apue.h"

int main(void) {
    char  name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL)); /* first temp name */

    tmpnam(name); /* second temp name */
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) /* create temp file */
        err_sys("tmpfile: %s\n", strerror(errno));

    fputs("one line of output\n", fp); /* write to temp file */
    rewind(fp);

    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets: %s\n", strerror(errno));
    fputs(line, stdout);

    return 0;
}
