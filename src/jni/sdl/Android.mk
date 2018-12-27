# Copyright (c) 2018 Bruce <3350207067@qq.com>

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog -landroid

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH))
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/../j4a)

LOCAL_SRC_FILES += sdl_thread.c
LOCAL_SRC_FILES += sdl_extra_log.c
LOCAL_SRC_FILES += sdl_android_jni.c

LOCAL_STATIC_LIBRARIES := j4a

LOCAL_MODULE := sdl
include $(BUILD_SHARED_LIBRARY)


