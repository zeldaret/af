#include "PR/os_internal.h"

u8 __osContAddressCrc(u16 addr) {
    u32 temp = 0;
    u32 i = 0x400;

    do {
        temp <<= 1;

        if ((u32)addr & i) {
            if (temp & 0x20) {
                temp ^= 0x14;
            } else {
                ++temp;
            }
        } else if (temp & 0x20) {
            temp ^= 0x15;
        }

        i >>= 1;
    } while (i != 0);

    i = 5;

    do {
        temp <<= 1;
        if (temp & 0x20) {
            temp ^= 0x15;
        }
    } while (--i != 0);

    return temp & 0x1F;
}

u8 __osContDataCrc(u8* data) {
    u32 temp = 0;
    u32 i;
    u32 j;

    for (i = 0x20; i; --i) {
        for (j = 0x80; j; j >>= 1) {
            temp <<= 1;

            if ((*data & j) != 0) {
                if ((temp & 0x100) != 0) {
                    temp ^= 0x84;
                } else {
                    ++temp;
                }
            } else if (temp & 0x100) {
                temp ^= 0x85;
            }
        }

        data++;
    }
    do {
        temp <<= 1;

        if (temp & 0x100) {
            temp ^= 0x85;
        }
    } while (++i < 8U);

    return temp;
}
