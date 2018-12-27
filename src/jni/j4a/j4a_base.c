/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#include "j4a_base.h"
#include "class/Build.h"

bool J4A_ExceptionCheck__catchAll(JNIEnv *env)
{
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionDescribe(env);
        (*env)->ExceptionClear(env);
        return true;
    }

    return false;
}

/********************
 * References
 ********************/
jclass J4A_NewGlobalRef__catchAll(JNIEnv *env, jobject obj)
{
    jclass obj_global = (*env)->NewGlobalRef(env, obj);
    if (J4A_ExceptionCheck__catchAll(env) || !(obj_global)) {
        J4A_FUNC_FAIL_TRACE();
        goto fail;
    }

fail:
    return obj_global;
}

void J4A_DeleteLocalRef(JNIEnv *env, jobject obj)
{
    if (!obj)
        return;
    (*env)->DeleteLocalRef(env, obj);
}

void J4A_DeleteLocalRef__p(JNIEnv *env, jobject *obj)
{
    if (!obj)
        return;
    J4A_DeleteLocalRef(env, *obj);
    *obj = NULL;
}


/********************
 * Class Load
 ********************/
jclass J4A_FindClass__catchAll(JNIEnv *env, const char *class_sign)
{
    jclass clazz = (*env)->FindClass(env, class_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !(clazz)) {
        J4A_FUNC_FAIL_TRACE();
        clazz = NULL;
        goto fail;
    }

fail:
    return clazz;
}

jclass J4A_FindClass__asGlobalRef__catchAll(JNIEnv *env, const char *class_sign)
{
    jclass clazz_global = NULL;
    jclass clazz = J4A_FindClass__catchAll(env, class_sign);
    if (!clazz) {
        J4A_FUNC_FAIL_TRACE1(class_sign);
        goto fail;
    }

    clazz_global = J4A_NewGlobalRef__catchAll(env, clazz);
    if (!clazz_global) {
        J4A_FUNC_FAIL_TRACE1(class_sign);
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &clazz);
    return clazz_global;
}

jfieldID J4A_GetStaticFieldID__catchAll(JNIEnv *env, jclass clazz, const char *field_name, const char *field_sign)
{
    jfieldID field_id = (*env)->GetStaticFieldID(env, clazz, field_name, field_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !field_id) {
        J4A_FUNC_FAIL_TRACE2(field_name, field_sign);
        field_id = NULL;
        goto fail;
    }

fail:
    return field_id;
}

jfieldID J4A_GetFieldID__catchAll(JNIEnv *env, jclass clazz, const char *field_name, const char *field_sign)
{
    jfieldID field_id = (*env)->GetFieldID(env, clazz, field_name, field_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !field_id) {
        J4A_FUNC_FAIL_TRACE2(field_name, field_sign);
        field_id = NULL;
        goto fail;
    }

fail:
    return field_id;
}

jmethodID J4A_GetStaticMethodID__catchAll(JNIEnv *env, jclass clazz, const char *method_name, const char *method_sign)
{
    jmethodID method_id = (*env)->GetStaticMethodID(env, clazz, method_name, method_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !method_id) {
        J4A_FUNC_FAIL_TRACE2(method_name, method_sign);
        method_id = NULL;
        goto fail;
    }

fail:
    return method_id;
}

