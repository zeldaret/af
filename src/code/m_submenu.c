#include "m_submenu.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "attributes.h"

extern UNK_FUN_PTR D_8010DD24_jp[];

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_80117920_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/RO_STR_8011792C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4420_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C453C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C46AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_ovlptr_dllcnv.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C47B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C497C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C49D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_submenu_ovlptr_cleanup.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/load_player.s")

void mSM_submenu_ct(Game_Play1CBC* arg0) {
    bzero(arg0, sizeof(Game_Play1CBC));

    arg0->unk_0C = 0;
    arg0->unk_20 = 0;

    if (common_data.unk_104AD == 1) {
        arg0->unk_E2 = 1;
        common_data.unk_104AD = 0;
    }

    arg0->unk_30 = none_proc1;
    arg0->unk_34 = none_proc1;
}

void mSM_submenu_dt(UNUSED Game_Play1CBC* arg0) {

}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4D8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4DFC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C4E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_submenu_ctrl.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C50C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C50EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C510C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5228_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C524C_jp.s")

void mSM_submenu_move(Game_Play1CBC* arg0) {
    // TODO: check if this should pass arg0
    D_8010DD24_jp[arg0->unk_0C]();
}

#if 0
extern UNK_TYPE D_8010DCEC_jp;
extern UNK_TYPE* D_8010DCE8_jp;

void mSM_submenu_draw(Game_Play1CBC* arg0) {
    if ((arg0->unk_00 >= 3) && (arg0->unk_0C == 3) && (&D_8010DCEC_jp == D_8010DCE8_jp)) {
        arg0->unk_34();
    }
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/mSM_submenu_draw.s")
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C53B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C543C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C54F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C557C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C55E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5640_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C56AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5798_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C582C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C58B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C592C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_submenu/func_800C5984_jp.s")
