#include "global.h"

#include "6FD190.h"

uintptr_t func_800D94F0_jp(void) {
    B_80146070_jp = 0x80400000;
    B_80146070_jp &= ~0x3F;
    return B_80146070_jp;
}

void func_800D9514_jp(void) {
    B_80146070_jp = 0;
}

void func_800D9524_jp(void) {
    B_80146060_jp[0] = 0;
    B_80146060_jp[1] = 0;
    B_80146060_jp[2] = 0;
    B_8014606C_jp = 0;
    func_800D9770_jp();
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D955C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9618_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D96A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D96E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9700_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9750_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D9788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D97A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D97F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/6FD190/func_800D986C_jp.s")
