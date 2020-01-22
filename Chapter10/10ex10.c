/**
 *   @file     10ex10.c
 *   @date     2019-11-03
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief
 */

#include <spawn.h>
#include <time.h>

#include "apue.h"

extern int log_to_stderr;

void cron() {
    log_to_stderr = 0;
    log_open("10ex10", 0, 0);
    for (int i = 0;; ++i) {
        if (i % 5 == 0) {
            time_t    t  = time(NULL);
            struct tm st = {};

            localtime_r(&t, &st);
            log_msg("time_of day: %02d:%02d:%02d", st.tm_hour, st.tm_min,
                    st.tm_sec);
            log_msg("tm_sec: %d", st.tm_sec);
        }
        sleep(60);
    }
}

int main(int argc, char *argv[], char **env) {
    pid_t pid = 0;
    daemonize(argv[0]);
    cron();
    exit(EXIT_SUCCESS);
}
