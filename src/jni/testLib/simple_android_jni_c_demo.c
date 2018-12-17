/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


#include "j4a_base.h"

typedef struct J4AC_BRUCE_BASE_SIMPLEANDROIDJNICDEMO {
    jclass id;
} J4AC_BRUCE_BASE_SIMPLEANDROIDJNICDEMO;

static J4AC_BRUCE_BASE_SIMPLEANDROIDJNICDEMO class_J4AC_bruce_base_simpleandroidjnicdemo;

int J4A_loadClass__J4AC_bruce_base_simpleandroidjnicdemo(JNIEnv *env)
{
    int ret  = -1;
    const char *sign    = NULL;

    if (class_J4AC_bruce_base_simpleandroidjnicdemo.id != NULL)
        return 0;

    sign = "bruce_base/simpleandroidjnicdemo";
    class_J4AC_bruce_base_simpleandroidjnicdemo.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_bruce_base_simpleandroidjnicdemo.id == NULL)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "bruce_base.simpleandroidjnicdemo");
    ret = 0;
    
fail:
    return ret;

}
