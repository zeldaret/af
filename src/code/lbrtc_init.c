#include "lbrtc.h"
#include "attributes.h"

s32 D_801160C0_jp = 0;

s32 lbrtc_init(OSMesgQueue* mq) {
    s32 ret;
    u8 sp23;
    UNUSED s32 pad;
    __lbrtcStructUnk3 rtc[1];

    ret = func_800FE480_jp(mq, &sp23);
    if (ret == 0) {
        if (D_801160C0_jp == 0) {
            osCreateMesgQueue(&B_801524A0_jp, &B_801524B8_jp, OS_MESG_BLOCK);
            D_801160C0_jp = 1;
        }
        if (sp23 & 0x80) {
            ret = func_800FEE10_jp(mq, 0, (u8*)&rtc);
            if ((ret == 0) || (ret == 0x10)) {
                rtc[0].unk1 &= ~6;
                ret = func_800FE8D0_jp(mq, 0, (u8*)&rtc);
            }
        }
        if (sp23 & 1) {
            ret = (sp23 & 2) ? 0x13 : 0x11;

        } else if (sp23 & 2) {
            ret = 0x12;
        }
    }
    return ret;
}
