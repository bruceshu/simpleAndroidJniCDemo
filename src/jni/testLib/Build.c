/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/11
Description:

*/


typedef struct J4AC_android_os_Build__VERSION {
    jclass id;
    jfieldID field_SDK_INT;
} J4AC_android_os_Build__VERSION;

typedef struct J4AC_android_os_Build {
    jclass id;
} J4AC_android_os_Build;

static J4AC_android_os_Build__VERSION class_J4AC_android_os_Build__VERSION;
static J4AC_android_os_Build class_J4AC_android_os_Build;



int J4A_loadClass__J4AC_android_os_Build__VERSION(JNIEnv *env)
{
    int         ret                   = -1;
    const char *name      = NULL;
    const char *sign      = NULL;
    jclass      class_id  = NULL;

    if (class_J4AC_android_os_Build__VERSION.id != NULL)
        return 0;

    sign = "android/os/Build$VERSION";
    class_J4AC_android_os_Build__VERSION.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_android_os_Build__VERSION.id == NULL)
        goto fail;

    class_id = class_J4AC_android_os_Build__VERSION.id;
    name     = "SDK_INT";
    sign     = "I";
    class_J4AC_android_os_Build__VERSION.field_SDK_INT = J4A_GetStaticFieldID__catchAll(env, class_id, name, sign);
    if (class_J4AC_android_os_Build__VERSION.field_SDK_INT == NULL)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "android.os.Build$VERSION");
    ret = 0;
    
fail:
    return ret;
}


int J4A_loadClass__J4AC_android_os_Build(JNIEnv *env)
{
    int ret             = -1;
    const char *sign    = NULL;

    if (class_J4AC_android_os_Build.id != NULL)
        return 0;

    sign = "android/os/Build";
    class_J4AC_android_os_Build.id = J4A_FindClass__asGlobalRef__catchAll(env, sign);
    if (class_J4AC_android_os_Build.id == NULL)
        goto fail;

    ret = J4A_loadClass__J4AC_android_os_Build__VERSION(env);
    if (ret)
        goto fail;

    J4A_ALOGD("J4ALoader: OK: '%s' loaded\n", "android.os.Build");
    ret = 0;
    
fail:
    return ret;
}

