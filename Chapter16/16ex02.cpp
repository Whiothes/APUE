
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

void print_stat_info(struct stat *s) {
    cout << "ID of device containing file: " << s->st_dev << endl;
    cout << "Mode of file (see below): " << s->st_mode << endl;
    cout << "Number of hard links: " << s->st_nlink << endl;
    cout << "File serial number: " << s->st_ino << endl;
    cout << "User ID of the file: " << s->st_uid << endl;
    cout << "Group ID of the file: " << s->st_gid << endl;
    cout << "Device ID: " << s->st_rdev << endl;

#if defined(__APPLE__)
    cout << "time of last access: " << s->st_atimespec.tv_sec << endl;
    cout << "time of last data modification: " << s->st_mtimespec.tv_sec
         << endl;
    cout << "time of last status change: " << s->st_ctimespec.tv_sec << endl;
    cout << "time of file creation(birth): " << s->st_birthtimespec.tv_sec
         << endl;
    cout << "user defined flags for file: " << s->st_flags << endl;
    cout << "file generation number: " << s->st_gen << endl;
#elif defined(__linux__)
    cout << "time of last access: " << s->st_atime << endl;
    cout << "time of last data modification: " << s->st_mtime << endl;
    cout << "time of last status change: " << s->st_ctime << endl;
#endif
    cout << "file size, in bytes: " << s->st_size << endl;
    cout << "blocks allocated for file: " << s->st_blocks << endl;
    cout << "optimal blocksize for I/O: " << s->st_blksize << endl;
}

int main() {
    struct stat      s;
    int              fd, err, n;
    struct addrinfo *ailist, *aip;
    struct addrinfo  hint;
    char *           host;

    if (sysconf(_SC_HOST_NAME_MAX) < 0) {
        n = HOST_NAME_MAX;
    }

    host = new char[n];

    if (gethostname(host, n) < 0) {
        cerr << "gethostname: " << strerror(errno) << endl;
    }

    memset(&hint, 0, sizeof(hint));
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_socktype  = SOCK_STREAM;
    hint.ai_addr      = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next      = NULL;

    if ((err = getaddrinfo("localhost", "ftp", &hint, &ailist)) < 0) {
        cerr << "getaddrinfo: " << gai_strerror(err) << endl;
    }

    for (aip = ailist; aip; aip = aip->ai_next) {
        if ((fd = socket(aip->ai_family, SOCK_STREAM, 0)) < 0) {
            cerr << "socket: " << strerror(errno) << endl;
        }

        bind(fd, aip->ai_addr, aip->ai_addrlen);

        listen(fd, 10);

        goto end;
    }

end:
    fstat(fd, &s);
    print_stat_info(&s);
    close(fd);

    delete (host);

    exit(EXIT_SUCCESS);

errout:
    close(fd);
    delete (host);
    exit(EXIT_FAILURE);
}
