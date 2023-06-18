#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceStopReadData(OSVoiceHandle* hd) {
    s32 ret;
    s32 i;
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
        i = 0;
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
            i++;
        } while ((ret == CONT_ERR_VOICE_NO_RESPONSE) && (i < 20));
    }
    if (i >= 20) {
        ret == CONT_ERR_VOICE_NO_RESPONSE;
    }

    return ret;
}
