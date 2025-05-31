#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "os_version.h"

s32 __osGbpakSetBank(OSPfs* pfs, u8 bank);

s32 osGbpakReadWrite(OSPfs* pfs, u16 flag, u16 address, u8* buffer, u16 size) {
    s32 i;
    s32 ret;
    u8 bank;

    bank = (u8)(address >> 0xE);

    if (bank != pfs->banks) {
        ret = __osGbpakSetBank(pfs, bank);

        if (ret != 0) {
            return ret;
        }
    }

#if BUILD_VERSION >= VERSION_K
    if (size == 0) {
        return 0;
    }
#endif

    size = (u16)(size >> 5);
    address = (u16)((address | 0xC000) >> 5);

    if (flag == 1) {
        for (i = 0; i < (s32)size; i++, buffer += BLOCKSIZE) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, address, buffer, 0);

            if (ret != 0) {
                break;
            }

            if ((++address >= 0x800) && (i < (s32)(size - 1))) {
                ret = __osGbpakSetBank(pfs, ++bank);

                if (ret != 0) {
                    break;
                }

                address = 0x600U;
            }
        }
    } else {
        for (i = 0; i < (s32)size; i++, buffer += BLOCKSIZE) {
            ret = __osContRamRead(pfs->queue, pfs->channel, address, buffer);

            if (ret != 0) {
                break;
            }

            if (++address >= 0x800 && (i < (s32)(size - 1))) {
                ret = __osGbpakSetBank(pfs, ++bank);

                if (ret != 0) {
                    break;
                }

                address = 0x600U;
            }
        }
    }

    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }

    return ret;
}
