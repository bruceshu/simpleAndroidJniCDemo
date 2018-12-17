/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/17
Description:

*/

if [ -z "$ANDROID_NDK" ]; then
    echo "You must define ANDROID_NDK before starting."
    echo "They must point to your NDK directories.\n"
    exit 1
fi

FF_MAKEFLAGS=-j`nproc`

$ANDROID_NDK/ndk-build $FF_MAKEFLAGS