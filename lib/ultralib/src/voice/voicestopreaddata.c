/**
 * File: voicestopreaddata.c
 *
 * Forcibly stops voice recognition processing by the Voice Recognition System
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"
#include "os_version.h"

s32 osVoiceStopReadData(OSVoiceHandle* hd) {
    s32 ret;
#if BUILD_VERSION >= VERSION_K 
    s32 i;
#endif
    u8 stat;
    u8 temp[4];

    ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
    if (ret != 0) {
        return ret;
    } else if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    if (hd->__mode == 0) {
        return CONT_ERR_INVALID;
    }

    *(u32*)temp = 0x700;
    ret = __osVoiceContWrite4(hd->__mq, hd->__channel, 0, temp);

    if (ret == 0) {
#if BUILD_VERSION >= VERSION_K 
        i = 0;
#endif
        do {
            ret = __osVoiceCheckResult(hd, &stat);
            if (ret & 0xFF00) {
                if (((ret & 7) == 0) || ((ret & 7) == 7)) {
                    ret = 0;
                    hd->__mode = 0;
                } else {
                    ret = CONT_ERR_INVALID;
                }
            } else {
                hd->__mode = 0;
            }
#if BUILD_VERSION >= VERSION_K 
            i++;
        } while ((ret == CONT_ERR_VOICE_NO_RESPONSE) && (i < 20));
#else
        } while ((ret == CONT_ERR_VOICE_NO_RESPONSE));
#endif
    }
#if BUILD_VERSION >= VERSION_K 
    if (i >= 20) {
        ret == CONT_ERR_VOICE_NO_RESPONSE;
    }
#endif

    return ret;
}
