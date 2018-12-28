/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/27
Description:

*/

#ifndef SDL_ANDROID_JNI_H
#define SDL_ANDROID_JNI_H

#include <jni.h>

void SDL_JNI_DetachThreadEnv();
jint SDL_JNI_SetupThreadEnv(JNIEnv **p_env);

int SDL_JNI_ThrowException(JNIEnv* env, const char* className, const char* msg);

#endif
