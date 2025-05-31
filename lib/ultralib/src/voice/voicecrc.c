/**
 * File: voicecrc.c
 * Description: CRC check used by the voice files
 *
 * For general information about CRC, see the crc.c file
 */
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PR/os_voice.h"

#define VOICE_CRC_LENGTH 8
#define VOICE_CRC_GENERATOR 0x85

/**
 * This function is essentially the same as __osContDataCrc, but allows for a variable message length, specified by
 * `numBytes`.
 */
u8 __osVoiceContDataCrc(u8* data, u32 length) {
    s32 temp = 0;
    u32 i;
    u32 j;

    for (i = length; i != 0; i--) {
        // Loop over each j in the i starting with most significant
        for (j = (1 << (VOICE_CRC_LENGTH - 1)); j != 0; j >>= 1) {
            temp <<= 1;
            if (*data & j) {
                if (temp & (1 << VOICE_CRC_LENGTH)) {
                    // Same as temp++; temp ^= 0x85 since last j always 0 after the shift
                    temp ^= VOICE_CRC_GENERATOR - 1;
                } else {
                    temp++;
                }
            } else if (temp & (1 << VOICE_CRC_LENGTH)) {
                temp ^= VOICE_CRC_GENERATOR;
            }
        }
        data++;
    }
    // Act like a i of zeros is appended to data
    do {
        temp <<= 1;
        if (temp & (1 << VOICE_CRC_LENGTH)) {
            temp ^= VOICE_CRC_GENERATOR;
        }
    } while (++i < VOICE_CRC_LENGTH);

    // Discarding the excess is done automatically by the return type
    return temp;
}
