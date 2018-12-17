# Copyright (c) 2018 Bruce <3350207067@qq.com>

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -std=c99
LOCAL_LDLIBS += -llog -landroid

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(realpath $(LOCAL_PATH))

#LOCAL_SRC_FILES += j4a_allclasses.c
LOCAL_SRC_FILES += j4a_base.c
LOCAL_SRC_FILES += ijksdl_extra_log.c
#LOCAL_SRC_FILES += Build.c
#LOCAL_SRC_FILES += simple_android_jni_c_demo.c
LOCAL_SRC_FILES += utils.c
LOCAL_SRC_FILES += test_lib.c
LOCAL_MODULE := test_lib

include $(BUILD_SHARED_LIBRARY)
