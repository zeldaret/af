#include "ac_toudai.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTOU_actor_ct(Actor* thisx, Game_Play* play);
void aTOU_actor_dt(Actor* thisx, Game_Play* play);
void aTOU_actor_init(Actor* thisx, Game_Play* play);
void aTOU_actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Toudai_Profile = {
    /* */ ACTOR_TOUDAI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5843,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Toudai),
    /* */ aTOU_actor_ct,
    /* */ aTOU_actor_dt,
    /* */ aTOU_actor_init,
    /* */ aTOU_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB60C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB840_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB894_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB8D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB9C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw.s")
