/**
 *   @file     10ex05.c
 *   @date     2019-10-29
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    Implementing Software Timers
 * www.kohala.com/start/libes.timers.txt
 */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define MAX_TIMERS 3
typedef long TIME;
#define VERY_LONG_TIME 10240000

struct timer {
    int   inuse;      /* TRUE if in use */
    TIME  time;       /* relative time to wait */
    char* event;      /* set to TRUE at timeout */
} timers[MAX_TIMERS]; /* set of timers */

void timers_init() {
    struct timer* t;

    for (t = timers; t < &timers[MAX_TIMERS]; t++) t->inuse = FALSE;
}

volatile TIME time_now;
struct timer* timer_next = NULL;
TIME          time_timer_set;

void timers_update();

void timer_undeclare(struct timer* t) {
    disable_interrupts();
    if (!t->inuse) {
        enable_interrupts();
        return;
    }

    t->inuse = FALSE;

    if (t == timer_next) {
        timers_update(time_now - time_timer_set);
        if (timer_next) {
            start_physical_timer(timer_next->time);
            time_timer_set = time_now;
        }
    }
    enable_interrupts();
}
