#include "lbrtc.h"
#include "lib/ultralib/src/io/siint.h"
#include "lib/ultralib/src/io/controller.h"

s32 func_800FE420_jp(OSMesgQueue* mq, OSRTCTime* time) {
    u8 buf;
    s32 ret;

    ret = func_800FE480_jp(mq, &buf);

    if (ret == 0) {
        ret = func_800FEE10_jp(mq, 1, (u8*)time);
    }

    return ret;
}

s32 func_800FE480_jp(OSMesgQueue* mq, u8* buf) {
    s32 ret = 0;
    s32 i;
    u8* ptr;
    __lbrtc_struct_unk2 sp1C;

    __osSiGetAccess();

    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    ptr = (u8*)&__osEepPifRam.ramarray;

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }

    sp1C.unk0 = 1;
    sp1C.unk1 = 3;
    sp1C.unk2 = 6;

    *(__lbrtc_struct_unk2*)ptr = sp1C;

    ptr += 6;

    ptr[0] = CONT_CMD_END;

    ret = __osSiRawStartDma(1, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    __osContLastCmd = 6;

    ret = __osSiRawStartDma(0, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    ptr = (u8*)&__osEepPifRam.ramarray[1];

    sp1C = *(__lbrtc_struct_unk2*)ptr;

    ret = 0xFF & (sp1C.unk1 & 0xC0);

    if (ret == 0) {
        if (!(((sp1C.unk4 << 8) | sp1C.unk3) & 0xFFFF & 0x1000)) {
            ret = 0xB;
        } else {
            *buf = sp1C.unk5;
        }
    } else if (ret & 0x80) {
        ret = 1;
    } else {
        ret = 4;
    }

    __osSiRelAccess();
    return ret;
}
   