/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/27
Description:

*/



#ifndef TEST_INTERNAL_H
#define TEST_INTERNAL_H

#include <pthread.h>

#include "sdl_thread.h"
#include "message.h"


void test_demo_inc_ref(SimpleTest *simpleTest);
void test_demo_release(SimpleTest *simpleTest);
void test_demo_dec_ref(SimpleTest *simpleTest);
void *test_demo_get_weak_thiz(SimpleTest *simpleTest);
void *test_demo_set_weak_thiz(SimpleTest *simpleTest, void *weak_thiz);
SimpleTest *test_demo_create();


#endif
