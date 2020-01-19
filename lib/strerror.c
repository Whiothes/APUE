#include <stdio.h>

#if defined(_GNU_SOURCE)
extern const char *const sys_errlist[];
extern int               sys_nerr;
#elif !defined(LINUX)
extern const char *const sys_errlist[];
extern const int         sys_nerr;
#endif

char *strerror(int error) {
    static char mesg[30];

    if (error >= 0 && error <= sys_nerr) {
        return ((char *)sys_errlist[error]);
    }
    sprintf(mesg, "Unknown error (%d)", error);
    return (mesg);
}
