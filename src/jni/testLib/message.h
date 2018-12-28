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
#define MSG_SIMPLE_TEST_END                         1

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

typedef struct SimpleTest {
    volatile int ref_count; //从内存中读取数据，经过计数后，将结果直接放入内存中。
                            //volatile作用是避免编译器意外修改寄存器中的数据。
    pthread_mutex_t mutex;
    
    MessageQueue msg_queue;
    SDL_Thread *msg_thread;
    SDL_Thread _msg_thread;

    void *weak_thiz;
} SimpleTest;

void notify_msg(MessageQueue *msg_queue, int what);
void msg_queue_abort(MessageQueue *q);
void msg_free_res(AVMessage *msg);
int ijkmp_get_msg(SimpleTest *simpleTest, AVMessage *msg, int block);


#endif
