/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


#ifndef IJKSDL__IJKSDL_EXTRA_LOG_H
#define IJKSDL__IJKSDL_EXTRA_LOG_H

#ifdef __ANDROID__
#include <android/log.h>

void ffp_log_extra_print(int level, const char *tag, const char *fmt, ...);
void ffp_log_extra_vprint(int level, const char *tag, const char *fmt, va_list ap);
#endif

#endif  // IJKSDL__IJKSDL_EXTRA_LOG_H
