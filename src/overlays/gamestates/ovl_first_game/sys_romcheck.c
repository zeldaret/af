#include "first_game.h"
#include "carthandle.h"
#include "m_nmi_buf.h"

#ifdef NON_MATCHING
void sys_romcheck(void) {
    u32 sp24;
    u8 temp;
    s32 pad;

    osEPiReadIo(carthandle, 0x3C, &sp24);

    temp = sp24;
    if (temp == 0x23) {
        APPNMI_ZURUMODE2_SET();
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_first_game/sys_romcheck/sys_romcheck.s")
#endif
