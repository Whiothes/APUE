#include "apue.h"

void setbuf_(FILE *restrict stream, char *restrict buf) {
    if (stream == NULL) {
        setvbuf(stream, buf, _IONBF, BUFSIZ);
    } else if (isatty(fileno(stream))) {
        setvbuf(stream, buf, _IOLBF, BUFSIZ);
    } else {
        setvbuf(stream, buf, _IOFBF, BUFSIZ);
    }
}

int is_unbuffered(FILE *fp) { return (fp->_flags & __SNBF); }

int is_linebuffered(FILE *fp) { return (fp->_flags & __SLBF); }

int buffer_size(FILE *fp) { return (fp->_bf._size); }

void pr_stdio(const char *name, FILE *fp) {
    printf("stream = %s, ", name);
    if (is_unbuffered(fp))
        printf("unbuffered");

    else if (is_linebuffered(fp))
        printf("line buffered");

    else /* if neither or above */
        printf("fully buffered");
    printf(", buffer size = %d\n", buffer_size(fp));
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char  buf[BUFSIZ];

    if (argc < 2) {
        err_quit("usage: ./a.out <path>");
    }

    fp = fopen(argv[1], "r+");
    pr_stdio(argv[1], fp);
    setbuf_(fp, buf);
    pr_stdio(argv[1], fp);
    fclose(fp);
}
