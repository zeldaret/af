#include "lbrtc.h"
#include "lib/ultralib/src/io/siint.h"
#include "lib/ultralib/src/io/controller.h"
#include "prevent_bss_reordering2.h"

OSTimer B_80152480_jp;
OSMesgQueue B_801524A0_jp;
OSMesg B_801524B8_jp;

s32 func_800FE8D0_jp(OSMesgQueue* mq, u8 v, u8* buf) {
    s32 ret;
    u8* ptr;
    __lbrtc_struct_unk1 sp28;

    __osSiGetAccess();
    func_800FEABC_jp(v, buf);  
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    __osContLastCmd = 8;

    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    ptr = (u8*)(&__osEepPifRam.ramarray[1]);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    sp28 = *((__lbrtc_struct_unk1*)ptr);
    ret = ((sp28.unk1) & 0xC0) >> 4;

    __osSiRelAccess();

    osSetTimer(&B_80152480_jp, OS_USEC_TO_CYCLES(300), 0, &B_801524A0_jp, &B_801524B8_jp);
    osRecvMesg(&B_801524A0_jp, NULL, OS_MESG_BLOCK);
    if (ret == 0) {
        bcopy(&sp28.unk4, buf, sizeof(__lbrtc_struct_unk));
        if (sp28.unkC & 1) {
            ret = 0x11;
        } else if (sp28.unkC & 1) {
            ret = 0x12;
        } else if (sp28.unkC & 0x80) {
            ret = 0x10;
        }
    } else if (ret & 0x80) {
        ret = 1;
    } else {
        ret = 4;
    }
    __osSiRelAccess();

    return ret;
}

s32 func_800FEABC_jp(u8 v, u8* buf) {
    s32 i;
    u8* ptr = (u8*)&__osEepPifRam;
    __lbrtc_struct_unk1 sp0;

    for (i = 0; i < ARRLEN(__osEepPifRam.ramarray); i++) {
        __osEepPifRam.ramarray[i] = 0xFF;
    }

    __osEepPifRam.pifstatus = 1;

    sp0.unk0 = 0xA;
    sp0.unk1 = 1;
    sp0.unk2 = 8;
    sp0.unk3 = v;

    for (i = 0; i < 8; i++) {
        (&sp0.unk0)[i + 4] = *buf++;
    }

    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__lbrtc_struct_unk1*)ptr = sp0;

    ptr += 0xD;
    ptr[0] = 0xFE;
}
