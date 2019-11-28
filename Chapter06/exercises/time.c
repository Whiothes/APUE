#include <time.h>

#include "apue.h"

int main(void) {
    char   tbuf[64];
    time_t t;

    time(&t);

    strftime(tbuf, sizeof(tbuf), "%a %b %d %T %Z %Y", localtime(&t));
    printf("%s\n", tbuf);

    setenv("TZ", "dkladjlkjklasdj", 1);
    strftime(tbuf, sizeof(tbuf), "%a %b %d %T %Z %Y", localtime(&t));
    printf("%s\n", tbuf);

    return 0;
}
