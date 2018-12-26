/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/

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

void msg_queue_abort(MessageQueue *q)
{
    SDL_LockMutex(q->mutex);

    q->abort_request = 1;

    SDL_CondSignal(q->cond);

    SDL_UnlockMutex(q->mutex);
}

void msg_free_res(AVMessage *msg)
{
    if (!msg || !msg->obj)
        return;
    
    assert(msg->free_l);
    
    msg->free_l(msg->obj);
    msg->obj = NULL;
}

void notify_msg(MessageQueue *msg_queue, int what) 
{
    msg_queue_put_simple3(msg_queue, what, 0, 0);
}

static int msg_queue_get(MessageQueue *q, AVMessage *msg, int block)
{
    AVMessage *msg1;
    int ret;

    SDL_LockMutex(q->mutex);

    for (;;) {
        if (q->abort_request) {
            ret = -1;
            break;
        }

        msg1 = q->first_msg;
        if (msg1) {
            q->first_msg = msg1->next;
            if (!q->first_msg)
                q->last_msg = NULL;
            q->nb_messages--;
            *msg = *msg1;
            msg1->obj = NULL;
            ret = 1;
            break;
        } else if (!block) {
            ret = 0;
            break;
        } else {
            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}

int ijkmp_get_msg(SimpleTest *simpleTest, AVMessage *msg, int block)
{
    assert(simpleTest);
    
    while (1) {
        int continue_wait_next_msg = 0;
        int retval = msg_queue_get(&simpleTest->msg_queue, msg, block);
        if (retval <= 0)
            return retval;

        switch (msg->what) {
            
        }
        
        if (continue_wait_next_msg) {
            msg_free_res(msg);
            continue;
        }

        return retval;
    }
}

