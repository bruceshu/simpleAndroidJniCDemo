# Copyright (c) 2018 Bruce <3350207067@qq.com>

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -std=c99

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH))

LOCAL_SRC_FILES += j4a_allclasses.c
LOCAL_SRC_FILES += j4a_base.c

LOCAL_SRC_FILES += class/Build.c
LOCAL_SRC_FILES += class/simple_android_jni_c_demo.c

LOCAL_MODULE := j4a
include $(BUILD_STATIC_LIBRARY)

