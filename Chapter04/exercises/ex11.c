#include <dirent.h>
#include <errno.h>
#include <limits.h>

#include "apue.h"

/* function type that is called for each filename */
typedef int Myfunc(const char *fpath, const struct stat *sb, int typeflag);

static Myfunc myfunc;
static int    myftw(const char *dirpath, Myfunc *func);
static int    dopath(const char *dirname, Myfunc *func);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
    int ret;

    if (argc != 2) {
        err_quit("usage: %s <starting-pathname>", argv[0]);
    }
    ret = myftw(argv[1], myfunc);

    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0) {
        ntot = 1;
    }

    printf("regular files  = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

    return 0;
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */
#define FTW_F   1 /* file other than directory */
#define FTW_D   2 /* directory */
#define FTW_DNR 3 /* dirctory that cant'be read */
#define FTW_NS  4 /* file that we can't stat */

static size_t pathlen;

static int myftw(const char *pathname, Myfunc *func) {
    char *fullpath = path_alloc(&pathlen); /* malloc PATH_MAX+1 bytes */

    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
            err_sys("realloc %s", strerror(errno));
        }
    }
    return (dopath(pathname, func));
}

/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
/* we return whatever func() returns  */
static int dopath(const char *pathname, Myfunc *func) {
    struct stat    statbuf;
    struct dirent *dirp;
    DIR *          dp;
    int            ret, n;

    size_t l   = 0;
    char * cwd = path_alloc(&l);

    chdir(pathname);
    getcwd(cwd, l);
#ifdef DEBUG
    printf("%s\n", cwd);
#endif

    if ((dp = opendir(".")) == NULL) {
        /* can't read directory */
        return (func(pathname, &statbuf, FTW_DNR));
    }
    while ((dirp = readdir(dp)) != NULL) {
        if ((strcmp(dirp->d_name, ".") == 0) ||
            (strcmp(dirp->d_name, "..") == 0)) {
            continue; /* ignore dot and dot-dot */
        }
        if (lstat(dirp->d_name, &statbuf) < 0) { /* stat error */
            func(dirp->d_name, &statbuf, FTW_NS);
        }
        if (S_ISDIR(statbuf.st_mode) == 0) { /* not a directory */
            func(dirp->d_name, &statbuf, FTW_F);
        } else {
            func(dirp->d_name, &statbuf, FTW_D);
            /* chdir(dirp->d_name); */
            if ((ret = dopath(dirp->d_name, func)) != 0) {
                break;
            }
            /* chdir(".."); */
            getcwd(cwd, l);
        }
    }

    if (closedir(dp) < 0) {
        err_ret("%s: %s", cwd, strerror(errno));
    }

    return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR:
                    err_dump("for S_IFDIR for %s", pathname);
                default:
                    break;
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_dump("%s: %s", pathname, strerror(errno));
            break;
        case FTW_NS:
            err_dump("stat error for %s", pathname);
            break;
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }
    return (0);
}
