/**
 * File: voicecontrolgain.c
 *
 * Adjusts the input gain of the Voice Recognition System
 */

#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceControlGain(OSVoiceHandle* hd, s32 analog, s32 digital) {
    s32 ret;
    u8 cmd;

    static u8 digital_table[] = { 0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0 };

    if (analog == 0) {
        cmd = 0x18;
    } else {
        cmd = 0x98;
    }

    ERRCK(__osVoiceSetADConverter(hd->__mq, hd->__channel, cmd));

    if ((digital < ARRLEN(digital_table)) && (digital >= 0)) {
        cmd = digital_table[digital] + 2;
    } else {
        return CONT_ERR_INVALID;
    }

    ERRCK(__osVoiceSetADConverter(hd->__mq, hd->__channel, cmd));
    return ret;
}
