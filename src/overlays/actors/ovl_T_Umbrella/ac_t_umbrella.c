#include "ac_t_umbrella.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTUMB_actor_ct(Actor* thisx, Game_Play* game_play);
void aTUMB_actor_move(Actor* thisx, Game_Play* game_play);
void aTUMB_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Umbrella_Profile = {
    /* */ ACTOR_T_UMBRELLA,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_28,
    /* */ sizeof(T_Umbrella),
    /* */ aTUMB_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTUMB_actor_move,
    /* */ aTUMB_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/aTUMB_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1ECD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1ED04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1ED4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1EE48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1EE84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1EF00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/func_80A1EF20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/aTUMB_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Umbrella/ac_t_umbrella/aTUMB_actor_draw.s")
