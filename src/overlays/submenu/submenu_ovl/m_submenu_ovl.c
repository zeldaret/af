#include "m_submenu_ovl.h"
#include "m_submenu.h"
#include "m_lib.h"
#include "game.h"
#include "overlays/gamestates/ovl_play/m_play.h"

extern struct_8085E9B0 ovl_base;

void func_8085BAC0_jp(mSM* arg0, GraphicsContext* gfxCtx, s32 arg1);

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BAC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BCD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085BD08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C20C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085C7B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085CE18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D094_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D128_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D244_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D2EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D358_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D398_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D43C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D4D4_jp.s")

void func_8085D500_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D500_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D5D4_jp.s")

void func_8085D638_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D638_jp.s")

void func_8085D674_jp(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D718_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D860_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085D92C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/func_8085DA08_jp.s")

void func_8085DA28_jp(mSM* arg0) {
    struct_8085E9B0_unk_10670* sp24 = &arg0->unk_2C->unk_10670;

    func_8085D500_jp(arg0);
    if (arg0->unk_04 != arg0->unk_08) {
        func_8085D638_jp(arg0);
    }
    func_8085D674_jp(arg0);
    (*sp24)(arg0);
}

void func_8085DA9C_jp(mSM* arg0, Game_Play* game_play) {
    func_8085BAC0_jp(arg0, game_play->state.gfxCtx, 1);
    arg0->unk_2C->unk_10674(arg0, game_play);
}

#if 0
void mSM_menu_ovl_init(mSM* arg0) {
    void* var_v1;

    arg0->unk_2C = &ovl_base;
    bzero(&ovl_base, 0x10730);
    if (arg0->unk_00 != 4) {
        var_v1 = gamePT + 0x110;
    } else {
        var_v1 = gamePT + 0x2FC;
    }
    ovl_base.unk_10000 = (s32) var_v1->unk_1818;
    arg0->unk_8 = 0;
    ovl_base.unk_00000[0x10670] = none_proc1;
    ovl_base.unk_00000[0x10670] = none_proc1;
    ovl_base.unk_00000[0x10678] = none_proc1;
    ovl_base.unk_00000[0x10678] = none_proc1;
    ovl_base.unk_00000[0x10680] = none_proc1;
    ovl_base.unk_00000[0x10680] = none_proc1;
    ovl_base.unk_00000[0x10696] = 0x2000;
    arg0->unk_2C->unk_106A4 = func_8085D718_jp;
    arg0->unk_2C->unk_106A8 = func_8085D92C_jp;
    arg0->unk_2C->unk_106AC = func_8085DA08_jp;
    arg0->unk_2C->unk_106B0 = func_8085D4D4_jp;
    arg0->unk_2C->unk_106B4 = func_8085BCD8_jp;
    arg0->unk_2C->unk_106B8 = func_8085BD08_jp;
    arg0->unk_2C->unk_106BC = func_8085C20C_jp;
    arg0->unk_2C->unk_106C0 = func_8085C7B8_jp;
    arg0->unk_2C->unk_106C4 = func_8085CE18_jp;
    arg0->unk_2C->unk_106C8 = func_8085BAC0_jp;
    arg0->unk_2C->unk_106CC = func_8085D43C_jp;
    func_8085D638_jp(arg0);
    arg0->play = func_8085DA28_jp;
    arg0->draw = (void (*)(mSM*, struct Game_Play*)) func_8085DA9C_jp;
    func_8085DA28_jp(arg0);
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_menu_ovl_init.s")
#endif
