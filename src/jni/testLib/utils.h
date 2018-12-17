/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#ifndef UTILS_H
#define UTILS_H

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

void notify_msg1(MessageQueue *msg_queue, int what);


#endif
