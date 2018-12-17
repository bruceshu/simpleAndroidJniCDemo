/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#include "ijksdl_extra_log.h"
#include "ijksdl_android_jni.h"
#include <stdio.h>

#define LOG_BUF_SIZE	1024

#ifdef EXTRA_LOG_PRINT
void ffp_log_extra_print(int level, const char *tag, const char *fmt, ...)
{
    JNIEnv *env = NULL;

    va_list ap;
    char log_buffer[LOG_BUF_SIZE] = {0};

    va_start(ap, fmt);
    vsnprintf(log_buffer, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);
    switch (level) {
        case ANDROID_LOG_UNKNOWN:
        case ANDROID_LOG_DEFAULT:
        case ANDROID_LOG_VERBOSE:
            J4AC_BLog__v__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_DEBUG:
            J4AC_BLog__d__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_INFO:
            J4AC_BLog__i__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_WARN:
            J4AC_BLog__w__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_FATAL:
        case ANDROID_LOG_SILENT:
        case ANDROID_LOG_ERROR:
            J4AC_BLog__e__withCString__catchAll(env, tag, log_buffer);
            break;
        default:
            break;
    }
}

void ffp_log_extra_vprint(int level, const char *tag, const char *fmt, va_list ap)
{
    JNIEnv *env = NULL;

    char log_buffer[LOG_BUF_SIZE] = {0};

    vsnprintf(log_buffer, LOG_BUF_SIZE, fmt, ap);
    switch (level) {
        case ANDROID_LOG_UNKNOWN:
        case ANDROID_LOG_DEFAULT:
        case ANDROID_LOG_VERBOSE:
            J4AC_BLog__v__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_DEBUG:
            J4AC_BLog__d__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_INFO:
            J4AC_BLog__i__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_WARN:
            J4AC_BLog__w__withCString__catchAll(env, tag, log_buffer);
            break;
        case ANDROID_LOG_FATAL:
        case ANDROID_LOG_SILENT:
        case ANDROID_LOG_ERROR:
            J4AC_BLog__e__withCString__catchAll(env, tag, log_buffer);
            break;
        default:
            break;
    }
}
#endif  // EXTRA_LOG_PRINT