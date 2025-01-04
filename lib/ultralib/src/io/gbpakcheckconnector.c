#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

s32 osGbpakCheckConnector(OSPfs* pfs, u8* status) {
    s32 ret;
    s32 bufn = 1;
    s32 oldbufn = 0;
    u16 address = 0;
    u16 oldaddr = 0;
    u16 daddr = 0;
    u16 num;
    u8 buf[3][4][BLOCKSIZE];
    u8 buf_status[3][4];

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

        bzero(buf_status, sizeof(buf_status));

        for (address = 0x80; address <= 0x4000; address <<= 1) {
            num = 0;
            daddr = 0;

            do {
                ERRCK(osGbpakReadWrite(pfs, OS_READ, address + daddr, buf[bufn][num], BLOCKSIZE));
                buf_status[bufn][num] = 1;

                if (buf_status[oldbufn][num] == 0) {
                    ret = osGbpakReadWrite(pfs, OS_READ, oldaddr + daddr, buf[oldbufn][num], BLOCKSIZE);

                    if (ret != 0) {
                        return ret;
                    } else {
                        buf_status[oldbufn][num] = 1;
                    }
                }

                if (bcmp(buf[bufn][num], buf[oldbufn][num], BLOCKSIZE) != 0) {
                    num = 0;
                    break;
                }

                daddr += BLOCKSIZE;
            } while (num++ < ARRLEN(buf[0]) - 1);

            if (num != 0) {
                return PFS_ERR_CONTRFAIL;
            }

            if (oldbufn != 0) {
                num = 0;
                daddr = 0;

                do {
                    if (buf_status[bufn][num] == 0) {
                        ERRCK(osGbpakReadWrite(pfs, OS_READ, address + daddr, buf[bufn][num], BLOCKSIZE));
                        buf_status[bufn][num] = 1;
                    }

                    if (buf_status[0][num] == 0) {
                        ret = osGbpakReadWrite(pfs, OS_READ, daddr, buf[0][num], BLOCKSIZE);
                        if (ret != 0) {
                            return ret;
                        } else {
                            buf_status[0][num] = 1;
                        }
                    }

                    if (bcmp(buf[bufn][num], buf[0][num], BLOCKSIZE)) {
                        num = 0;
                        break;
                    }

                    daddr += BLOCKSIZE;
                } while (num++ < ARRLEN(buf_status[0]) - 1);
            }

            if (num != 0) {
                return PFS_ERR_CONTRFAIL;
            }

            if (oldbufn != 0) {
                bzero(buf_status[oldbufn], ARRLEN(buf_status[oldbufn]));
            }

            oldaddr = address;
            oldbufn = bufn;
            bufn ^= 3;
        }

        if ((pfs->dir_size >= 2) || (pfs->version == 2)) {
            num = 0;
            daddr = 0;

            do {
                ERRCK(osGbpakReadWrite(pfs, OS_READ, daddr + 0xA000, buf[bufn][num], BLOCKSIZE));
                ERRCK(osGbpakReadWrite(pfs, OS_READ, daddr + 0x2000, buf[oldbufn][num], BLOCKSIZE));

                if (bcmp(buf[bufn][num], buf[oldbufn][num], BLOCKSIZE)) {
                    num = 0;
                    break;
                }

                daddr += BLOCKSIZE;
            } while (num++ < ARRLEN(buf[0]) - 1);

            if (num != 0) {
                return PFS_ERR_CONTRFAIL;
            }
        }

        ret = osGbpakGetStatus(pfs, status);

        if (ret == PFS_ERR_NEW_GBCART) {
            ret = PFS_ERR_CONTRFAIL;
        }
    }

    return ret;
}
