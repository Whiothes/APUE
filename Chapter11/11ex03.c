/**
 *   @file     11fig14.c
 *   @date     2019-11-09
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    illustrates the use of reader–writer locks
 *
 *   @todo     something need to be considered
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct job {
    struct job *j_next;
    struct job *j_prev;
    pthread_t   j_id;  // tells which thread handles this job
    void *(*j_func)(void *);
};

struct queue {
    pthread_t       q_id;
    struct job *    q_head;
    struct job *    q_tail;
    pthread_cond_t  q_cond;
    pthread_mutex_t q_mutex;
};

void *thr_fn(void *arg) {
    printf("thread %lu start\n", (unsigned long)pthread_self());
    pthread_exit((void *)0);
}

int queue_init(struct queue *q) {
    int err;

    q->q_id   = pthread_self();
    q->q_head = NULL;
    q->q_tail = NULL;
    err       = pthread_mutex_init(&q->q_mutex, NULL);
    if (err != 0) {
        return (err);
    }

    err = pthread_cond_init(&q->q_cond, NULL);
    if (err != 0) {
        pthread_mutex_destroy(&q->q_mutex);
    }

    // continue initialization
    return err;
}

void job_insert(struct queue *qp, struct job *jp) {
    pthread_mutex_lock(&qp->q_mutex);

    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    jp->j_func = thr_fn;

    if (qp->q_head != NULL)
        qp->q_head->j_prev = jp;
    else
        qp->q_tail = jp;

    qp->q_head = jp;

    pthread_cond_signal(&qp->q_cond);
    pthread_mutex_unlock(&qp->q_mutex);
}

void job_append(struct queue *qp, struct job *jp) {
    pthread_mutex_lock(&qp->q_mutex);

    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    jp->j_func = thr_fn;

    if (qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->q_head = jp;

    qp->q_tail = jp;

    pthread_mutex_unlock(&qp->q_mutex);
}

void job_remove(struct queue *qp, struct job *jp) {
    pthread_mutex_lock(&qp->q_mutex);

    if (jp == qp->q_head) {
        qp->q_head = jp->j_next;
        if (qp->q_tail == jp)
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    } else if (jp == qp->q_tail) {
        qp->q_tail         = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    } else {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }

    pthread_mutex_unlock(&qp->q_mutex);
}

struct job *job_find(struct queue *qp, pthread_t id) {
    struct job *jp = NULL;
    if (pthread_mutex_lock(&qp->q_mutex) != 0) return NULL;

    for (jp = qp->q_head; jp; jp = jp->j_next) {
        if (pthread_equal(id, jp->j_id)) break;
    }
    pthread_mutex_unlock(&qp->q_mutex);
    return (jp);
}
