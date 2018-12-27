/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/27
Description:

*/



#ifndef TEST_INTERNAL_H
#define TEST_INTERNAL_H

#include <pthread.h>

#include "sdl/sdl_thread.h"

#include "message.h"

typedef struct SimpleTest {
    volatile int ref_count; //从内存中读取数据，经过计数后，将结果直接放入内存中。
                            //volatile作用是避免编译器意外修改寄存器中的数据。
    pthread_mutex_t mutex;
    
    MessageQueue msg_queue;
    SDL_Thread *msg_thread;
    SDL_Thread _msg_thread;

    void *weak_thiz;
} SimpleTest;


void test_demo_inc_ref(SimpleTest *simpleTest);
void test_demo_release(SimpleTest *simpleTest);
void test_demo_dec_ref(SimpleTest *simpleTest);
void *test_demo_get_weak_thiz(SimpleTest *simpleTest);
void *test_demo_set_weak_thiz(SimpleTest *simpleTest, void *weak_thiz);
SimpleTest *test_demo_create();


#endif
