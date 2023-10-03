#include "ac_t_pistol.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aTPT_actor_ct(Actor* thisx, Game_Play* game_play);
void aTPT_actor_move(Actor* thisx, Game_Play* game_play);
void aTPT_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile T_Pistol_Profile = {
    /* */ ACTOR_T_PISTOL,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_16,
    /* */ sizeof(T_Pistol),
    /* */ aTPT_actor_ct,
    /* */ (void*)none_proc1,
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
