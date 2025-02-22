/**
 * File: voiceinit.c
 *
 * Initializes Voice Recognition System control structure and hardware
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceInit(OSMesgQueue* mq, OSVoiceHandle* handle, int channel) {
    s32 ret;
    s32 i;
    u8 stat = 0;
    u8 buf[4];
    static u8 cmd[] = { 0x1E, 0x6E, 0x08, 0x56, 0x03 };

    handle->__channel = channel;
    handle->__mq = mq;
    handle->__mode = 0;

    ERRCK(__osVoiceGetStatus(mq, channel, &stat));

    ret = __osContChannelReset(mq, channel);
    if (ret != 0) {
        return CONT_ERR_CONTRFAIL;
    }

    for (i = 0; i < ARRLEN(cmd); i++) {
        ERRCK(__osVoiceSetADConverter(mq, channel, cmd[i]));
    }

    ERRCK(__osVoiceGetStatus(mq, channel, &stat));
    if (stat & 2) {
        return CONT_ERR_VOICE_NO_RESPONSE;
    }

    *(u32*)buf = 0x100;
    ERRCK(__osVoiceContWrite4(mq, channel, 0, buf));

    ret = __osVoiceCheckResult(handle, &stat);
    if (ret & 0xFF00) {
        ret = CONT_ERR_INVALID;
    }

    return ret;
}
