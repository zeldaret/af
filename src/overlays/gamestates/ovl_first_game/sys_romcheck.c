#include "first_game.h"

#if 0
typedef struct NmiBuffer {
    /* 0x00 */ UNK_TYPE1 unk_00[0x3C];
    /* 0x3C */ s32 unk_3C;
} NmiBuffer; // size = 0x40

void sys_romcheck(void) {
    u32 sp24;
    s32 pad;
    u8 temp;

    osEPiReadIo(gCartHandle, 0x3CU, &sp24);

    temp = sp24;
    if (temp == 0x23) {

        //osAppNMIBuffer->unk_3C = (s32) (osAppNMIBuffer->unk_3C | 8);
        osAppNMIBuffer[0xF] |= 0x8;
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/gamestates/ovl_first_game/sys_romcheck/sys_romcheck.s")
#endif
