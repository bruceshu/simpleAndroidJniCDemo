/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/


#ifndef MESSAGE_H
#define MESSAGE_H

#include "sdl_thread.h"

#define MSG_SIMPLE_TEST_BEGIN                       0
#define MSG_SIMPLE_TEST_END                         0

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


void notify_msg1(MessageQueue *msg_queue, int what);
void msg_queue_abort(MessageQueue *q);
void msg_free_res(AVMessage *msg);
int ijkmp_get_msg(SimpleTest *simpleTest, AVMessage *msg, int block);


#endif
