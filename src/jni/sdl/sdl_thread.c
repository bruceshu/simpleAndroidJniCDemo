/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/


#include <assert.h>
#include <unistd.h>

#include "sdl_thread.h"
#include "sdl_log.h"
#include "sdl_android_jni.h"
#include "sdl_mic.h"

static void *SDL_RunThread(void *data)
{
    SDL_Thread *thread = data;
    ALOGI("SDL_RunThread: [%d] %s\n", (int)gettid(), thread->name);
    pthread_setname_np(pthread_self(), thread->name);
    thread->retval = thread->func(thread->data);
    
#ifdef __ANDROID__
    SDL_JNI_DetachThreadEnv();
#endif
    return NULL;
}

SDL_Thread *SDL_CreateThreadEx(SDL_Thread *thread, int (*fn)(void *), void *data, const char *name)
{
    thread->func = fn;
    thread->data = data;
    strlcpy(thread->name, name, sizeof(thread->name) - 1);
    int retval = pthread_create(&thread->id, NULL, SDL_RunThread, thread);
    if (retval)
        return NULL;

    return thread;
}

void SDL_WaitThread(SDL_Thread *thread, int *status)
{
    assert(thread);
    if (!thread)
        return;

    pthread_join(thread->id, NULL);

    if (status)
        *status = thread->retval;
}

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

int SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex)
{
    assert(cond);
    assert(mutex);

    return pthread_cond_wait(&cond->id, &mutex->id);
}

SDL_mutex *SDL_CreateMutex(void)
{
    SDL_mutex *mutex;
    mutex = (SDL_mutex *) mallocz(sizeof(SDL_mutex));
    if (!mutex)
        return NULL;

    if (pthread_mutex_init(&mutex->id, NULL) != 0) {
        free(mutex);
        return NULL;
    }

    return mutex;
}

SDL_cond *SDL_CreateCond(void)
{
    SDL_cond *cond;
    cond = (SDL_cond *) mallocz(sizeof(SDL_cond));
    if (!cond)
        return NULL;

    if (pthread_cond_init(&cond->id, NULL) != 0) {
        free(cond);
        return NULL;
    }

    return cond;
}

void SDL_DestroyMutex(SDL_mutex *mutex)
{
    if (mutex) {
        pthread_mutex_destroy(&mutex->id);
        free(mutex);
    }
}

void SDL_DestroyCond(SDL_cond *cond)
{
    if (cond) {
        pthread_cond_destroy(&cond->id);
        free(cond);
    }
}
