#include "ac_mikuji.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805b414c(Actor* thisx, Game_Play* game_play);
void func_80A82638_jp(Actor* thisx, Game_Play* game_play);
void func_805b437c(Actor* thisx, Game_Play* game_play);
void func_805b43f4(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Mikuji_Profile = {
    /* */ ACTOR_MIKUJI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5830,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Mikuji),
    /* */ func_805b414c,
    /* */ func_80A82638_jp,
    /* */ func_805b437c,
    /* */ func_805b43f4,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_805b414c.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_80A82638_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_80A826C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_80A82848_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_80A82858_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_80A82878_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_805b437c.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikuji/ac_mikuji/func_805b43f4.s")
