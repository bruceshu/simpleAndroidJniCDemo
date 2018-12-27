/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/


#include <assert.h>
#include <unistd.h>

#include "sdl_log.h"
#include "sdl_mic.h"

#include "test_internal.h"
#include "message.h"

void test_demo_inc_ref(SimpleTest *simpleTest)
{
    assert(simpleTest);
    __sync_fetch_and_add(&simpleTest->ref_count, 1);
}

void test_demo_release(SimpleTest *simpleTest)
{
     msg_queue_abort(&simpleTest->msg_queue);
     
     if (simpleTest->msg_thread) {
        SDL_WaitThread(simpleTest->msg_thread, NULL);
        simpleTest->msg_thread = NULL;
    }
     
    pthread_mutex_destroy(&simpleTest->mutex);
    memset(simpleTest, 0, sizeof(SimpleTest));

    free(simpleTest);
}

void test_demo_dec_ref(SimpleTest *simpleTest)
{
    if (!simpleTest)
        return;

    int ref_count = __sync_sub_and_fetch(&simpleTest->ref_count, 1);
    if (ref_count == 0) {
        ALOGV("dec_ref(): ref=0\n");
        test_demo_release(simpleTest);
    }
}

void *test_demo_get_weak_thiz(SimpleTest *simpleTest)
{
    return simpleTest->weak_thiz;
}

void *test_demo_set_weak_thiz(SimpleTest *simpleTest, void *weak_thiz)
{
    void *prev_weak_thiz = simpleTest->weak_thiz;
    
    simpleTest->weak_thiz = weak_thiz;
    
    return prev_weak_thiz;
}

SimpleTest *test_demo_create()
{
    SimpleTest *simpleTest = mallocz(SimpleTest);
    if (!simpleTest) {
        ALOGE("malloc g_SimpleTest failed!\n");
    }
    
    pthread_mutex_init(&simpleTest->mutex, NULL);
    test_demo_inc_ref(simpleTest);

    return simpleTest;
}
