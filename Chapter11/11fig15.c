/**
 *   @file     11fig15.c
 *   @date     2019-11-10
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    an example of how to use a condition variable and a mutex
 * together to synchronize threads.
 */

#include <pthread.h>

struct msg {
    struct msg *m_next;
    // more stuff here
};

struct msg *workd;

pthread_cond_t  qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock  = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void) {
    struct msg *mp;
    for (;;) {
        pthread_mutex_lock(&qlock);
        while (workd == NULL) {
            pthread_cond_wait(&qready, &qlock);
        }
        mp    = workd;
        workd = mp->m_next;
        pthread_mutex_unlock(&qlock);
        // now process the messg mp
    }
}

void enqueue_msg(struct msg *mp) {
    pthread_mutex_lock(&qlock);
    mp->m_next = workd;
    workd      = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}
