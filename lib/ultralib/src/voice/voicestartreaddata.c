/**
 * File: voicestartreaddata.c
 *
 * Start voice recognition by the Voice Recognition System
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceStartReadData(OSVoiceHandle* hd) {
    s32 ret;
    u8 stat;
    u8 temp[4];

    ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
    if (ret != 0) {
        return ret;
    } else if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (hd->__mode != 0) {
        return CONT_ERR_INVALID;
    }

    *(u32*)temp = 0x5000000;
    ret = __osVoiceContWrite4(hd->__mq, hd->__channel, 0, temp);

    if (ret == 0) {
        ret = __osVoiceCheckResult(hd, &stat);

        if (ret & 0xFF00) {
            ret = CONT_ERR_INVALID;
        } else {
            hd->__mode = 1;
        }
    }

    return ret;
}
