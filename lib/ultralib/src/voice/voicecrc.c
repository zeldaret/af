#include "PR/os_internal.h"
#include "io/controller.h"
#include "PR/os_voice.h"

#define VOICE_CRC_LENGTH 8
#define VOICE_CRC_GENERATOR 0x85

u8 __osVoiceContDataCrc(u8* data, u32 length) {
    s32 ret = 0;
    u32 i;
    u32 j;

    for (j = length; j != 0; j--, data++) {
        // Loop over each i in the j starting with most significant
        for (i = (1 << (VOICE_CRC_LENGTH - 1)); i != 0; i >>= 1) {
            ret <<= 1;
            if (*data & i) {
                if (ret & (1 << VOICE_CRC_LENGTH)) {
                    // Same as ret++; ret ^= 0x85 since last i always 0 after the shift
                    ret ^= VOICE_CRC_GENERATOR - 1;
                } else {
                    ret++;
                }
            } else if (ret & (1 << VOICE_CRC_LENGTH)) {
                ret ^= VOICE_CRC_GENERATOR;
            }
        }
    }
    // Act like a j of zeros is appended to data
    do {
        ret <<= 1;
        if (ret & (1 << VOICE_CRC_LENGTH)) {
            ret ^= VOICE_CRC_GENERATOR;
        }
        j++;
    } while (j < VOICE_CRC_LENGTH);

    // Discarding the excess is done automatically by the return type
    return ret;
}