#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "os_version.h"

s32 osGbpakReadId(OSPfs* pfs, OSGbpakId* id, u8* status) {
    s32 i;
    s32 ret;
    u8 isum;
    u8 buf[96];
#if BUILD_VERSION >= VERSION_K
    u8 temp[32];
#endif
    static u8 nintendo[] = { 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
                             0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
                             0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
                             0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E };
    static u8 mmc_type[] = { 0x00, 0x01, 0x01, 0x01, 0xFF, 0x02, 0x02, 0xFF, 0x00, 0x00,
                             0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03 };

    ret = osGbpakGetStatus(pfs, status);

    if (ret == PFS_ERR_NEW_GBCART) {
        ret = osGbpakGetStatus(pfs, status);
    }

    if (ret == PFS_ERR_NEW_GBCART) {
        return PFS_ERR_CONTRFAIL;
    } else if (ret == 0) {
        if (!(*status & OS_GBPAK_POWER)) {
            ERRCK(osGbpakPower(pfs, OS_GBPAK_POWER_ON));
        }

        ERRCK(osGbpakReadWrite(pfs, OS_READ, 0x100U, buf, ARRLEN(buf)));

        ret = osGbpakGetStatus(pfs, status);

        if (ret == PFS_ERR_NEW_GBCART) {
            ret = PFS_ERR_CONTRFAIL;
        }

        if (ret != 0) {
            return ret;
        }

        if (!(*status & OS_GBPAK_RSTB_STATUS)) {
            return PFS_ERR_CONTRFAIL;
        }

#if BUILD_VERSION >= VERSION_K
        if (bcmp(nintendo, buf + 4, ARRLEN(nintendo))) {
            for (i = 0; i < ARRLEN(temp); temp[i++] = 0) {
                ;
            }

            ERRCK(osGbpakReadWrite(pfs, OS_WRITE, 0x6000U, temp, ARRLEN(temp)));
            ret = osGbpakReadWrite(pfs, OS_READ, 0x100U, buf, ARRLEN(buf));
            ERRCK(osGbpakReadWrite(pfs, OS_READ, 0x100U, buf, ARRLEN(buf)));

            ret = osGbpakGetStatus(pfs, status);

            if (ret == PFS_ERR_NEW_GBCART) {
                ret = PFS_ERR_CONTRFAIL;
            }

            if (ret != 0) {
                return ret;
            }

            if (bcmp(nintendo, buf + 4, ARRLEN(nintendo))) {
                return 4;
            }
        }
#else
        if (bcmp(nintendo, buf + 4, ARRLEN(nintendo))) {
            return 4;
        }
#endif
        for (i = 0x34, isum = 0; i < 0x4E; i++) {
            isum += buf[i];
        }

        if ((isum + 0x19) & 0xFF) {
            return 4;
        }

        bcopy(buf, id, 0x50);

        if (id->cart_type < 0x14) {
            pfs->version = (int)mmc_type[id->cart_type];
        }

        pfs->dir_size = (int)id->ram_size;
    }

    return ret;
}
