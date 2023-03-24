#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"

s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* stat) {
    s32 ret;
    u8 buf[2];

    if (ret = __osVoiceGetStatus(hd->__mq, hd->__channel, stat), ret == 0) {
        if (*stat & 1) {
            ret = CONT_ERR_VOICE_NO_RESPONSE;
        } else if (ret = __osVoiceContRead2(hd->__mq, hd->__channel, 0, buf), ret == 0) {
            hd->cmd_status = buf[0] & 7;

            if (buf[0] & 0x40) {
                ret = CONT_ERR_VOICE_NO_RESPONSE;
            } else {
                ret = buf[1] << 8;
            }
        }
    }
    return ret;
}