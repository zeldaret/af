#include "ac_t_pistol.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTPT_actor_ct(Actor* thisx, PlayState* play);
void aTPT_actor_move(Actor* thisx, PlayState* play);
void aTPT_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile T_Pistol_Profile = {
    /* */ 138,
    /* */ ACTOR_PART_4,
    /* */ 48,
    /* */ 0,
    /* */ 16,
    /* */ sizeof(T_Pistol),
    /* */ aTPT_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ aTPT_actor_move,
    /* */ aTPT_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/aTPT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/func_80A20494_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/func_80A204FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/func_80A2051C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/func_80A2053C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/func_80A2055C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/aTPT_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_T_Pistol/ac_t_pistol/aTPT_actor_draw.s")
