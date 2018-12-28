/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#ifndef SIMPLE_ANDROID_JNI_C_DEMO_H
#define SIMPLE_ANDROID_JNI_C_DEMO_H

#include "j4a_base.h"

void J4AC_bruce_simple_android_jni_c_demo__postEventFromNative__catchAll(JNIEnv *env, jobject weakThiz, jint what, jint arg1, jint arg2, jobject obj);
jlong J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__get__catchAll(JNIEnv *env, jobject thiz);
void J4AC_bruce_simple_android_jni_c_demo__mNativeTestDemo__set__catchAll(JNIEnv *env, jobject thiz, jlong value);
int J4A_loadClass__J4AC_bruce_simple_android_jni_c_demo(JNIEnv *env);

#endif
