/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#include <assert.h>

#include "j4a_base.h"
#include "sdl_log.h"
#include "sdl_android.h"
#include "sdl_android_jni.h"
#include "sdl_mic.h"

#include "test_internal.h"
#include "android_def.h"
#include "message.h"

#include "class/simple_android_jni_c_demo.h"


#define JNI_CLASS_TEST "bruce/simple_android_jni_c_demo/TestDemo"

typedef struct simple_test {
    pthread_mutex_t mutex;

    jclass clazz;
} simple_test;

SimpleTest *g_SimpleTest = NULL;

static simple_test g_clazz;
static JavaVM* g_jvm;

static void post_event(JNIEnv *env, jobject weak_this, int what, int arg1, int arg2)
{
    J4AC_bruce_simple_android_jni_c_demo__postEventFromNative__catchAll(env, weak_this, what, arg1, arg2, NULL);
}

static void post_event2(JNIEnv *env, jobject weak_this, int what, int arg1, int arg2, jobject obj)
{
    J4AC_bruce_simple_android_jni_c_demo__postEventFromNative__catchAll(env, weak_this, what, arg1, arg2, obj);
}

static void message_loop_n(JNIEnv *env, SimpleTest *simpleTest)
{
    jobject weak_thiz = (jobject) test_demo_get_weak_thiz(simpleTest);
    JNI_CHECK_GOTO(weak_thiz, env, NULL, NULL, LABEL_RETURN);
    
    while (1) {
        AVMessage msg;

        int retval = ijkmp_get_msg(simpleTest, &msg, 1);
        if (retval < 0)
            break;

        // block-get should never return 0
        assert(retval > 0);

        switch (msg.what) {
        case MSG_SIMPLE_TEST_BEGIN:
            ALOGV("MSG_SIMPLE_TEST_BEGIN\n");
            post_event(env, weak_thiz, MEDIA_NOP, 0, 0);
            break;
        case MSG_SIMPLE_TEST_END:
            ALOGV("MSG_SIMPLE_TEST_END\n");
            if (msg.obj) {
                jstring text = (*env)->NewStringUTF(env, (char *)msg.obj);
                post_event2(env, weak_thiz, MEDIA_NOP, 0, 0, text);
                J4A_DeleteLocalRef__p(env, &text);
            } else {
                post_event2(env, weak_thiz, MEDIA_NOP, 0, 0, NULL);
            }
            break;
        default:
            ALOGE("unknown MSG_xxx(%d)\n", msg.what);
            break;
        }
        msg_free_res(&msg);
    }

LABEL_RETURN:
    ;
}

static int message_loop(void *arg)
{
    ALOGV("%s\n", __func__);

    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("%s: SetupThreadEnv failed\n", __func__);
        return -1;
    }

    SimpleTest *simpleTest = (SimpleTest*) arg;
    JNI_CHECK_GOTO(simpleTest, env, NULL, "jni: native_message_loop: null simpleTest", LABEL_RETURN);

    message_loop_n(env, simpleTest);

LABEL_RETURN:
    test_demo_dec_ref(simpleTest);

    ALOGV("message_loop exit");
    return 0;
}

static SimpleTest *jni_set_test_demo(JNIEnv* env, jobject thiz, SimpleTest *simpleTest)
{
    pthread_mutex_lock(&g_clazz.mutex);
    SimpleTest *old = (SimpleTest*) (intptr_t) J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get__catchAll(env, thiz);
    if (simpleTest) {
        test_demo_inc_ref(simpleTest);
    }
    
    J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__set__catchAll(env, thiz, (intptr_t) simpleTest);
    pthread_mutex_unlock(&g_clazz.mutex);

    if (old != NULL ) {
        test_demo_dec_ref(old);
    }

    return old;
}

static SimpleTest *jni_get_test_demo(JNIEnv* env, jobject thiz)
{
    pthread_mutex_lock(&g_clazz.mutex);

    SimpleTest *simpleTest = (SimpleTest *) (intptr_t) J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get__catchAll(env, thiz);
    if (simpleTest) {
        test_demo_inc_ref(simpleTest);
    }

    pthread_mutex_unlock(&g_clazz.mutex);
    return simpleTest;
}

static void SimpleTest_native_setup(JNIEnv *env, jobject thiz, jobject weak_this)
{
    ALOGV("%s\n", __func__);
    SimpleTest *simpleTest = test_demo_create();
    JNI_CHECK_GOTO(simpleTest, env, "java/lang/OutOfMemoryError", "jni: native_setup: test_demo_create() failed", LABEL_RETURN);

    jni_set_test_demo(env, thiz, simpleTest);
    test_demo_set_weak_thiz(simpleTest, (*env)->NewGlobalRef(env, weak_this));

    ALOGV("bruce >>> hello world!");

LABEL_RETURN:
    test_demo_dec_ref(simpleTest);
}

static void SimpleTest_native_begin(JNIEnv *env, jobject thiz)
{
    ALOGV("%s\n", __func__);
    SimpleTest *simpleTest = jni_get_test_demo(env, thiz);
    JNI_CHECK_GOTO(simpleTest, env, "java/lang/IllegalStateException", "jni: native_begin: null simpleTest", LABEL_RETURN);
    
    simpleTest->msg_thread = SDL_CreateThreadEx(&simpleTest->_msg_thread, message_loop, simpleTest, "msg_loop");
    if (!simpleTest->msg_thread) {
        ALOGE("create msg loop failed!\n"); 
        goto LABEL_RETURN;
    }
    
    notify_msg(&g_SimpleTest->msg_queue, MSG_SIMPLE_TEST_BEGIN);
    
LABEL_RETURN:
    test_demo_dec_ref(simpleTest);
}

static void SimpleTest_native_end(JNIEnv *env, jobject thiz)
{
    ALOGV("%s\n", __func__);
    SimpleTest *simpleTest = jni_get_test_demo(env, thiz);
    JNI_CHECK_GOTO(simpleTest, env, "java/lang/IllegalStateException", "jni: native_begin: null simpleTest", LABEL_RETURN);
     
    notify_msg(&simpleTest->msg_queue, MSG_SIMPLE_TEST_END);

LABEL_RETURN:
    test_demo_dec_ref(simpleTest);
}

static void SimpleTest_native_release(JNIEnv *env, jobject thiz)
{
    ALOGV("%s\n", __func__);
    SimpleTest *simpleTest = jni_get_test_demo(env, thiz);
    if (!simpleTest)
        return;

    jobject weak_thiz = (jobject) test_demo_set_weak_thiz(simpleTest, NULL );
    (*env)->DeleteGlobalRef(env, weak_thiz);
    jni_set_test_demo(env, thiz, NULL);
    
    test_demo_dec_ref(simpleTest);
}

static JNINativeMethod g_methods[] = {
    { "_native_setup",     "(Ljava/lang/Object;)V", (void *) SimpleTest_native_setup },
    { "_native_begin",     "()V", (void *) SimpleTest_native_begin },
    { "_native_end",       "()V", (void *) SimpleTest_native_end },
    { "_native_release",   "()V", (void *) SimpleTest_native_release },
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

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved)
{
    pthread_mutex_destroy(&g_clazz.mutex);
}
