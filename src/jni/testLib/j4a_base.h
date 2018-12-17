/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#include <android/log.h>
#include <jni.h>
#include <stdbool.h>



#ifndef J4A_BASE_H
#define J4A_BASE_H

#define J4A_LOG_TAG "J4A"
#define J4A_ALOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,    J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,      J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGI(...)  __android_log_print(ANDROID_LOG_INFO,       J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGW(...)  __android_log_print(ANDROID_LOG_WARN,       J4A_LOG_TAG, __VA_ARGS__)
#define J4A_ALOGE(...)  __android_log_print(ANDROID_LOG_ERROR,      J4A_LOG_TAG, __VA_ARGS__)


#define J4A_FUNC_FAIL_TRACE()               do {J4A_ALOGE("%s: failed\n", __func__);} while (0)
#define J4A_FUNC_FAIL_TRACE1(x__)           do {J4A_ALOGE("%s: failed: %s\n", __func__, x__);} while (0)
#define J4A_FUNC_FAIL_TRACE2(x1__, x2__)    do {J4A_ALOGE("%s: failed: %s %s\n", __func__, x1__, x2__);} while (0)

#define J4A_LOAD_CLASS(class__) \
    do { \
        ret = J4A_loadClass__J4AC_##class__(env); \
        if (ret) \
            goto fail; \
    } while (0)

bool J4A_ExceptionCheck__catchAll(JNIEnv *env);
jclass J4A_NewGlobalRef__catchAll(JNIEnv *env, jobject obj);
jclass J4A_FindClass__catchAll(JNIEnv *env, const char *class_sign);
void J4A_DeleteLocalRef(JNIEnv *env, jobject obj);
void J4A_DeleteLocalRef__p(JNIEnv *env, jobject *obj);
jclass J4A_FindClass__asGlobalRef__catchAll(JNIEnv *env, const char *class_sign);
jfieldID J4A_GetStaticFieldID__catchAll(JNIEnv *env, jclass clazz, const char *field_name, const char *field_sign);


#endif
