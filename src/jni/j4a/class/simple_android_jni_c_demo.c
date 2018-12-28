/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


#include "simple_android_jni_c_demo.h"

typedef struct J4AC_BRUCE_SIMPLE_ANDROID_JNI_C_DEMO {
    jclass id;
    jfieldID field_mNativeTestDemo;
    jmethodID method_postEventFromNative;
} J4AC_BRUCE_SIMPLE_ANDROID_JNI_C_DEMO;

static J4AC_BRUCE_SIMPLE_ANDROID_JNI_C_DEMO class_J4AC_bruce_simple_android_jni_c_demo;


void J4AC_bruce_simple_android_jni_c_demo__postEventFromNative(JNIEnv *env, jobject weakThiz, jint what, jint arg1, jint arg2, jobject obj)
{
    (*env)->CallStaticVoidMethod(env, class_J4AC_bruce_simple_android_jni_c_demo.id, class_J4AC_bruce_simple_android_jni_c_demo.method_postEventFromNative, weakThiz, what, arg1, arg2, obj);
}

void J4AC_bruce_simple_android_jni_c_demo__postEventFromNative__catchAll(JNIEnv *env, jobject weakThiz, jint what, jint arg1, jint arg2, jobject obj)
{
    J4AC_bruce_simple_android_jni_c_demo__postEventFromNative(env, weakThiz, what, arg1, arg2, obj);
    J4A_ExceptionCheck__catchAll(env);
}

jlong J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get(JNIEnv *env, jobject thiz)
{
    return (*env)->GetLongField(env, thiz, class_J4AC_bruce_simple_android_jni_c_demo.field_mNativeTestDemo);
}

jlong J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get__catchAll(JNIEnv *env, jobject thiz)
{
    jlong ret_value = J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}

void J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__set(JNIEnv *env, jobject thiz, jlong value)
{
    (*env)->SetLongField(env, thiz, class_J4AC_bruce_simple_android_jni_c_demo.field_mNativeTestDemo, value);
}

void J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__set__catchAll(JNIEnv *env, jobject thiz, jlong value)
{
    J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__set(env, thiz, value);
    J4A_ExceptionCheck__catchAll(env);
}


int J4A_loadClass__J4AC_bruce_simple_android_jni_c_demo(JNIEnv *env)
{
    int ret  = -1;
    const char *name = NULL;
    const char *sign = NULL;
    jclass class_id = NULL;

    if (class_J4AC_bruce_simple_android_jni_c_demo.id != NULL)
        return 0;

    sign = "bruce/simple_android_jni_c_demo";
    class_J4AC_bruce_simple_android_jni_c_demo.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_bruce_simple_android_jni_c_demo.id == NULL)
        goto fail;

    class_id = class_J4AC_bruce_simple_android_jni_c_demo.id;
    name     = "mNativeTestDemo";
    sign     = "J";
    class_J4AC_bruce_simple_android_jni_c_demo.field_mNativeTestDemo = J4A_GetFieldID__catchAll(env, class_id, name, sign);
    if (class_J4AC_bruce_simple_android_jni_c_demo.field_mNativeTestDemo == NULL)
        goto fail;

    class_id = class_J4AC_bruce_simple_android_jni_c_demo.id;
    name = "postEventFromNative";
    sign = "(Ljava/lang/Object;IIILjava/lang/Object;)V";
    class_J4AC_bruce_simple_android_jni_c_demo.method_postEventFromNative = J4A_GetStaticMethodID__catchAll(env, class_id, name, sign);
    if (class_J4AC_bruce_simple_android_jni_c_demo.method_postEventFromNative == NULL)
        goto fail;
    
    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "bruce_base.simpleandroidjnicdemo");
    ret = 0;
    
fail:
    return ret;

}
