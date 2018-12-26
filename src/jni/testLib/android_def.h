/*
Copyright (c) bruce 3350207067@qq.com
Auther: bruce
Date: 2018/12/24
Description:

*/


#ifndef ANDROID_H
#define ANDROID_H

enum media_event_type {
    MEDIA_NOP               = 0,        // interface test message
    MEDIA_PREPARED          = 1,
    MEDIA_PLAYBACK_COMPLETE = 2,
    MEDIA_BUFFERING_UPDATE  = 3,        // arg1 = percentage, arg2 = cached duration
    MEDIA_SEEK_COMPLETE     = 4,
    MEDIA_SET_VIDEO_SIZE    = 5,        // arg1 = width, arg2 = height
    MEDIA_GET_IMG_STATE     = 6,        // arg1 = timestamp, arg2 = result code, obj = file name

    MEDIA_ERROR             = 100,      // arg1, arg2
    MEDIA_INFO              = 200,      // arg1, arg2

    MEDIA_SET_VIDEO_SAR     = 10001,    // arg1 = sar.num, arg2 = sar.den
};

enum media_error_type {
    // 0xx
    MEDIA_ERROR_UNKNOWN = 1,
    // 1xx
    MEDIA_ERROR_SERVER_DIED = 100,
    // 2xx
    MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200,
    // 3xx

    // -xx
    MEDIA_ERROR_IO          = -1004,
    MEDIA_ERROR_MALFORMED   = -1007,
    MEDIA_ERROR_UNSUPPORTED = -1010,
    MEDIA_ERROR_TIMED_OUT   = -110,

    MEDIA_ERROR_IJK_PLAYER  = -10000,
};


#endif
