/**
 *   @file     11fig14.c
 *   @date     2019-11-09
 *   @author   whiothes <whiothes81@gmail.com>
 *   @version  1.0
 *   @brief    illustrates the use of reader–writer locks
 */
#include <pthread.h>
#include <stdlib.h>

struct job {
    struct job *j_next;
    struct job *j_prev;
    pthread_t   j_id;  // tells which thread handles this job
};

struct queue {
    struct job *     q_head;
    struct job *     q_tail;
    pthread_rwlock_t q_lock;
};

int queue_init(struct queue *q) {
    int err;

    q->q_head = NULL;
    q->q_tail = NULL;
    err       = pthread_rwlock_init(&q->q_lock, NULL);
    if (err != 0) {
        return (err);
    }

    // continue initialization
    return 0;
}

void job_insert(struct queue *qp, struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;

    if (qp->q_head != NULL)
        qp->q_head->j_prev = jp;
    else
        qp->q_tail = jp;

    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

void job_append(struct queue *qp, struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;

    if (qp->q_tail != NULL)
        qp->q_tail->j_next = jp;
    else
        qp->q_head = jp;

    qp->q_tail = jp;

    pthread_rwlock_unlock(&qp->q_lock);
}

void job_remove(struct queue *qp, struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
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
    pthread_rwlock_unlock(&qp->q_lock);
}

struct job *job_find(struct queue *qp, pthread_t id) {
    struct job *jp = NULL;
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0) {
        return NULL;
    }

    for (jp = qp->q_head; jp; jp = jp->j_next) {
        if (pthread_equal(id, jp->j_id)) break;
    }
    pthread_rwlock_unlock(&qp->q_lock);
    return (jp);
}
