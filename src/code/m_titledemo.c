#include "global.h"
#include "6EC9E0.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C8D40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C8D98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/mTD_demono_get.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/mTD_player_keydata_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C8ECC_jp.s")

void func_800C8F5C_jp(void) {
    extern u16 func_800C8ECC_jp(void);
    extern void func_800B5980_jp(u16 keydata);

    func_800B5980_jp(func_800C8ECC_jp());
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C8F84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/title_demo_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_titledemo/func_800C9010_jp.s")

void func_800C9088_jp(void) {
    extern u16 D_8010EDD0_jp;

    D_8010EDD0_jp = 1;
}

s32 mTD_get_titledemo_no(void) {
    extern s32 D_8010EDA4_jp;
    s32 titledemo_no = D_8010EDA4_jp;

    if (titledemo_no <= 0) {
        titledemo_no = 1;
    }

    return titledemo_no - 1;
}

s32 func_800C90BC_jp(void) {
    extern s32 D_8010EDA0_jp;
    s32 result = 1;

    if (D_8010EDA0_jp >= 1765) {
        result = 0;
    }

    return result;
}
