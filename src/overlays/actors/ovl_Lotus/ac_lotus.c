#include "ac_lotus.h"
#include "m_collision_obj.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aLOT_actor_ct(Actor* thisx, Game_Play* game_play);
void aLOT_actor_dt(Actor* thisx, Game_Play* game_play);
void aLOT_actor_init(Actor* thisx, Game_Play* game_play);
void aLOT_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Lotus_Profile = {
    /* */ ACTOR_LOTUS,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5840,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Lotus),
    /* */ aLOT_actor_ct,
    /* */ aLOT_actor_dt,
    /* */ aLOT_actor_init,
    /* */ aLOT_actor_draw,
    /* */ NULL,
};
#endif

extern CollisionCheck_Status_Init lotus_StatusData;
extern ClObjPipe_Init lotus_CoInfoData;
#if 0
CollisionCheck_Status_Init lotus_StatusData = { 0, 0, 0, 0, 10, };
ClObjPipe_Init lotus_CoInfoData = { { OC1_1 | OC1_4 | OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20, OC2_TYPE_10, COLSHAPE_PIPE }, { ELEM_FLAG_1 }, { { 0x46, 6, 0, { 0, 0, 0 } } }, };
#endif

extern ClObjPipe pipeinfo;
#if 0
ClObjPipe pipeinfo;
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EE40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EE60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EF04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9EF6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9F004_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/func_80A9F0F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lotus/ac_lotus/aLOT_actor_draw.s")
