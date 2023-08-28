#include "ac_mikanbox.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void func_805b3010(Actor* thisx, Game_Play* game_play);
void aMIK_actor_dt(Actor* thisx, Game_Play* game_play);
void func_805b3e58(Actor* thisx, Game_Play* game_play);
void func_805b4054(Actor* thisx, Game_Play* game_play);
void aMIK_actor_save(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Mikanbox_Profile = {
    /* */ ACTOR_MIKANBOX,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5841,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Mikanbox),
    /* */ func_805b3010,
    /* */ aMIK_actor_dt,
    /* */ func_805b3e58,
    /* */ func_805b4054,
    /* */ aMIK_actor_save,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_805b3010.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/aMIK_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA3D08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA3D94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA406C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA40D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA411C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA41C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA424C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4278_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA429C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA434C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4388_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA43B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4408_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4478_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4634_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA47E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA482C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA48A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4998_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA49EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA49FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4A0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4A2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_805b3e58.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_80AA4AB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/func_805b4054.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Mikanbox/ac_mikanbox/aMIK_actor_save.s")
