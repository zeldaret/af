/**
 * File: voicesetword.c
 *
 * Registers words to the Voice Recognition System dictionary
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceSetWord(OSVoiceHandle* hd, u8* word) {
    s32 j;
    s32 k;
    s32 ret;
    u8 stat;
    u8 buf[40];

    ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
    if (ret != 0) {
        return ret;
    } else if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    for (k = 0; word[k] != 0; k += 2) {
        ;
    }

#ifndef NDEBUG
    if (k >= 34) {
        return CONT_ERR_VOICE_WORD;
    }
#endif

    bzero(buf, ARRLEN(buf));

    for (j = 0; j < k; j += 2) {
        buf[ARRLEN(buf) - 1 - k + j] = word[j];
        buf[ARRLEN(buf) - 1 - k + j - 1] = word[j + 1];
    }

    buf[ARRLEN(buf) - 1 - j - 5] = 3;

    if (k >= 15) {
        ERRCK(__osVoiceContWrite20(hd->__mq, hd->__channel, 0, buf));
    }
    ERRCK(__osVoiceContWrite20(hd->__mq, hd->__channel, 0, buf + 20));
    ret = __osVoiceCheckResult(hd, &stat);
    if (ret != 0) {
        if (ret & 0x100) {
            ret = CONT_ERR_VOICE_MEMORY;
        } else if (ret & 0x200) {
            ret = CONT_ERR_VOICE_WORD;
        } else if (ret & 0xFF00) {
            ret = CONT_ERR_INVALID;
        }
    }
    return ret;
}
