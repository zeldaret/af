/**
 * File: voicecleardictionary.c
 *
 * Initializes Voice Recognition System word registration dictionary.
 *
 * The dictionary is initialized so that the specified "numWords" can be
 * registered in the dictionary. 1-255 words can be registered in the dictionary.
 *
 * Words cannot be registered with the osVoiceSetWord before the dictionary
 * is initialized with the osVoiceClearDictionary function
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceClearDictionary(OSVoiceHandle* hd, u8 words) {
    s32 ret;
    u8 stat;
    u8 buf[4];

    ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
    if (ret != 0) {
        return ret;
    } else if (stat & 2) {
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
