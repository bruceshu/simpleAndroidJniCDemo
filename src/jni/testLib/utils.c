/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct SDL_mutex {
    pthread_mutex_t id;
} SDL_mutex;

typedef struct SDL_cond {
    pthread_cond_t id;
} SDL_cond;

typedef struct AVMessage {
    int what;
    int arg1;
    int arg2;
    void *obj;
    void (*free_l)(void *obj);
    struct AVMessage *next;
} AVMessage;

typedef struct MessageQueue {
    AVMessage *first_msg, *last_msg;
    int nb_messages;
    int abort_request;
    SDL_mutex *mutex;
    SDL_cond *cond;
} MessageQueue;

int SDL_LockMutex(SDL_mutex *mutex)
{
    assert(mutex);
    if (!mutex)
        return -1;

    return pthread_mutex_lock(&mutex->id);
}

int SDL_UnlockMutex(SDL_mutex *mutex)
{
    assert(mutex);
    if (!mutex)
        return -1;

    return pthread_mutex_unlock(&mutex->id);
}

int SDL_CondSignal(SDL_cond *cond)
{
    assert(cond);
    if (!cond)
        return -1;

    return pthread_cond_signal(&cond->id);
}

static void msg_init_msg(AVMessage *msg)
{
    memset(msg, 0, sizeof(AVMessage));
}

static int msg_queue_put_private(MessageQueue *q, AVMessage *msg)
{
    AVMessage *msg1;

    if (q->abort_request)
        return -1;

    msg1 = malloc(sizeof(AVMessage));
    if (!msg1)
        return -1;

    *msg1 = *msg;
    msg1->next = NULL;

    if (!q->last_msg)
        q->first_msg = msg1;
    else
        q->last_msg->next = msg1;
    
    q->last_msg = msg1;
    q->nb_messages++;
    SDL_CondSignal(q->cond);
    return 0;
}

static int msg_queue_put(MessageQueue *q, AVMessage *msg)
{
    int ret;

    SDL_LockMutex(q->mutex);
    ret = msg_queue_put_private(q, msg);
    SDL_UnlockMutex(q->mutex);

    return ret;
}

static void msg_queue_put_simple3(MessageQueue *q, int what, int arg1, int arg2)
{
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg_queue_put(q, &msg);
}

void notify_msg1(MessageQueue *msg_queue, int what) {
    msg_queue_put_simple3(msg_queue, what, 0, 0);
}
