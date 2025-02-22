/**
 * File: voicegetreaddata.c
 *
 * Gets voice recognition result from the Voice Recognition System
 */

#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"
#include "voiceinternal.h"

s32 osVoiceGetReadData(OSVoiceHandle* hd, OSVoiceData* micdata) {
    s32 ret = 0;
    s32 i;
    u8 stat;
    u8 temp[36];
    static u8 c;

    switch (hd->__mode) {
        case 1:
            ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
            if (ret != 0) {
                return ret;
            } else if (stat & 1) {
                return CONT_ERR_NOT_READY;
            }

            ERRCK(__osVoiceContRead2(hd->__mq, hd->__channel, 0, temp));

            c = temp[0] & 7;
            hd->cmd_status = c;
            if ((c != 0) && (c != 7)) {
                return CONT_ERR_NOT_READY;
            }
        case 2:
            hd->__mode = 2;

            ERRCK(__osVoiceGetStatus(hd->__mq, hd->__channel, &stat));

            if (stat & 2) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            *(u32*)temp = 0x600;
            ERRCK(__osVoiceContWrite4(hd->__mq, hd->__channel, 0, temp));

        case 3:
            hd->__mode = 3;

            ret = __osVoiceGetStatus(hd->__mq, hd->__channel, &stat);
            if (ret != 0) {
                return ret;
            } else if (stat & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            ERRCK(__osVoiceContRead36(hd->__mq, hd->__channel, 0, temp));

            micdata->warning = temp[4] + (temp[5] << 8);
            micdata->answer_num = temp[6];
            micdata->voice_level = temp[8] + (temp[9] << 8);
            micdata->voice_sn = temp[10] + (temp[11] << 8);
            micdata->voice_time = temp[12] + (temp[13] << 8);

            for (i = 0; i < 5; i++) {
                micdata->answer[i] = temp[14 + (i << 2)] + (temp[15 + (i << 2)] << 8);
                micdata->distance[i] = temp[16 + (i << 2)] + (temp[17 + (i << 2)] << 8);
            }

            if (micdata->answer[0] == 0x7FFF) {
                micdata->answer_num = 0;
            }

            hd->cmd_status = temp[34] & 7;
            if ((c == 0) || (hd->cmd_status == 0)) {
                break;
            }
        case 4:
            hd->__mode = 4;

            ERRCK(__osVoiceGetStatus(hd->__mq, hd->__channel, &stat));

            if (stat & 1) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            ERRCK(__osVoiceContRead2(hd->__mq, hd->__channel, 0, temp));

            hd->cmd_status = temp[0] & 7;
            if (temp[0] & 7) {
                return CONT_ERR_VOICE_NO_RESPONSE;
            }

            break;
        default:
            return CONT_ERR_INVALID;
    }
    hd->__mode = 0;
    return ret;
}
