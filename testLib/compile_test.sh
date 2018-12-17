#! /usr/bin/env bash

if [ -z "$ANDROID_NDK" ]; then
    echo "You must define ANDROID_NDK before starting."
    echo "They must point to your NDK directories.\n"
    exit 1
fi

FF_MAKEFLAGS=-j`nproc`

$ANDROID_NDK/ndk-build $FF_MAKEFLAGS