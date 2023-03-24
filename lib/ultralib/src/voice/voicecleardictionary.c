#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"

s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 words) {
    s32 ret;
    u8 stat;
    u8 buf[4];

    ERRCK(__osVoiceGetStatus(hd->__mq, hd->__channel, &stat));

    if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    *(u32*)buf = 0x02000000;
    buf[2] = words;

    ERRCK(__osVoiceContWrite4(hd->__mq, hd->__channel, 0, buf));

    ret = __osVoiceCheckResult(hd, &stat);
    if (ret & 0xFF00) {
        ret = CONT_ERR_INVALID;
    }

    return ret;
}

