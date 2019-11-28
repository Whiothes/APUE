#include <sys/resource.h>

#include "apue.h"

#define doit(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(int argc, char *argv[argc]) {
#ifdef RLIMIT_AS
    doit(RLIMIT_AS);
#endif

    doit(RLIMIT_CORE);
    doit(RLIMIT_CPU);
    doit(RLIMIT_DATA);
    doit(RLIMIT_FSIZE);

#ifdef RLIMIT_MEMLOCK
    doit(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMITS_MSGQUEUE
    doit(RLIMITS_MSGQUEUE);
#endif

    doit(RLIMIT_NOFILE);

    struct rlimit r;
    memset(&r, 0, sizeof(r));
    getrlimit(RLIMIT_NOFILE, &r);
    r.rlim_cur = 4096;
    setrlimit(RLIMIT_NOFILE, &r);

    doit(RLIMIT_NOFILE);
#ifdef RLIMIT_NPTS
    doit(RLIMIT_NPTS);
#endif

#ifdef RLIMIT_RSS
    doit(RLIMIT_RSS);
#endif

#ifdef RLIMIT_SBSIZE
    doit(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    doit(RLIMIT_SIGPENDING);
#endif

    doit(RLIMIT_STACK);

#ifdef RLIMIT_SWAP
    doit(RLIMIT_SWAP);
#endif

#ifdef RLIMIT_VMEM
    doit(RLIMIT_VMEM);
#endif

    return 0;
}

static void pr_limits(char *name, int resource) {
    struct rlimit      limit;
    unsigned long long lim;

    if (getrlimit(resource, &limit) < 0)
        err_sys("getrlimit error for %s", name);
    printf("%-14s ", name);

    if (limit.rlim_cur == RLIM_INFINITY)
        printf("(infinite) ");
    else {
        lim = limit.rlim_cur;
        printf("%10lld ", lim);
    }
    if (limit.rlim_max == RLIM_INFINITY) {
        printf("(infinite)");
    } else {
        lim = limit.rlim_max;
        printf("%10lld", lim);
    }
    putchar('\n');
}
