/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/

#include "j4a_base.h"

int J4A_LoadAll__catchAll(JNIEnv *env)
{
    int ret = 0;

    // load android.os.Build at very beginning
    J4A_LOAD_CLASS(android_os_Build);
    J4A_LOAD_CLASS(bruce_base_simpleandroidjnicdemo);

fail:
    return ret;
}

