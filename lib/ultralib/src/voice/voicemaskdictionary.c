/**
 * File: voicemaskdictionary.c
 *
 * Mask words registered in the voice recognition system
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceMaskDictionary(OSVoiceHandle* hd, u8* pattern, int size) {
    s32 ret = 0;
    s32 i;
    s32 j;
    u8 stat;
    u8 buf[20];

    ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
    if (ret != 0) {
        return ret;
    } else if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (size & 1) {
        j = size + 1;
    } else {
        j = size;
    }

    bzero(&buf, ARRLEN(buf));

    buf[18 - j] = 4;

    for (i = 0; i < j; i += 2) {
        buf[i + ARRLEN(buf) - j] = pattern[i];
        buf[i + ARRLEN(buf) - j + 1] = pattern[i + 1];
    }

    if (size & 1) {
        buf[ARRLEN(buf) - 1] = 0;
    }

    ret = __osVoiceContWrite20(hd->__mq, hd->__channel, 0, (u8*)&buf);
    if (ret == 0) {
        ret = __osVoiceCheckResult(hd, &stat);
        if (ret & 0xFF00) {
            ret = CONT_ERR_INVALID;
        }
    }

    return ret;
}
