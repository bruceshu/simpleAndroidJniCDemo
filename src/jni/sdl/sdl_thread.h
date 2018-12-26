/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/


#ifndef SDL_THREAD_H
#define SDL_THREAD_H

#include <pthread.h>

typedef struct SDL_mutex {
    pthread_mutex_t id;
} SDL_mutex;

typedef struct SDL_cond {
    pthread_cond_t id;
} SDL_cond;


typedef struct SDL_Thread
{
    pthread_t id;
    int (*func)(void *);
    void *data;
    char name[32];
    int retval;
} SDL_Thread;



SDL_Thread *SDL_CreateThreadEx(SDL_Thread *thread, int (*fn)(void *), void *data, const char *name);
void SDL_WaitThread(SDL_Thread *thread, int *status);
int SDL_LockMutex(SDL_mutex *mutex);
int SDL_UnlockMutex(SDL_mutex *mutex);
int SDL_CondSignal(SDL_cond *cond);
int SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex);



#endif
