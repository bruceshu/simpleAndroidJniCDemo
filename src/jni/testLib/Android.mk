# Copyright (c) 2018 Bruce <3350207067@qq.com>

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog -landroid

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH))
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/../j4a)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH)/../sdl)


LOCAL_SRC_FILES += test_internal.c
LOCAL_SRC_FILES += message.c
LOCAL_SRC_FILES += test_lib.c

LOCAL_SHARED_LIBRARIES := sdl

LOCAL_MODULE := test

include $(BUILD_SHARED_LIBRARY)


