/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


#include "j4a_base.h"
#include "ijksdl_log.h"
#include "utils.h"

#define REQ_START  1
#define JNI_CLASS_TEST "bruce_base/simpleandroidjnicdemo/test"

typedef struct simple_test {
    jclass clazz;
} simple_test;

static simple_test g_clazz;
MessageQueue msg_queue = {0};

static JavaVM* g_jvm;
//static JNIEnv* g_env;


#define IJK_FIND_JAVA_CLASS(env__, var__, classsign__) \
    do { \
        jclass clazz = (*env__)->FindClass(env__, classsign__); \
        if (J4A_ExceptionCheck__catchAll(env) || !(clazz)) { \
            ALOGE("FindClass failed: %s", classsign__); \
            return -1; \
        } \
        var__ = (*env__)->NewGlobalRef(env__, clazz); \
        if (J4A_ExceptionCheck__catchAll(env) || !(var__)) { \
            ALOGE("FindClass::NewGlobalRef failed: %s", classsign__); \
            (*env__)->DeleteLocalRef(env__, clazz); \
            return -1; \
        } \
        (*env__)->DeleteLocalRef(env__, clazz); \
    } while(0);

#define JNI_CHECK_RET(condition__, env__, exception__, msg__, ret__) \
    do { \
        if (!(condition__)) { \
            if (exception__) { \
                SDL_JNI_ThrowException(env__, exception__, msg__); \
            } \
            return ret__; \
        } \
    }while(0)

#ifndef NELEM
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

static void SimpleTest_native_begin(JNIEnv *env, jobject thiz)
{
    notify_msg1(&msg_queue, REQ_START);
    ALOGI("bruce >>> hello world!");
}

static JNINativeMethod g_methods[] = {
    { "_native_begin", "()V", (void *) SimpleTest_native_begin },
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    //int retval;
    JNIEnv* env = NULL;

    g_jvm = vm;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }

    IJK_FIND_JAVA_CLASS(env, g_clazz.clazz, JNI_CLASS_TEST);
    (*env)->RegisterNatives(env, g_clazz.clazz, g_methods, NELEM(g_methods) );

    //retval = J4A_LoadAll__catchAll(env);
    //JNI_CHECK_RET(retval == 0, env, NULL, NULL, -1);

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved)
{
}
