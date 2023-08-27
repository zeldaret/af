#include "ac_post_office.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aPOFF_actor_ct(Actor* thisx, Game_Play* game_play);
void aPOFF_actor_dt(Actor* thisx, Game_Play* game_play);
void aPOFF_actor_init(Actor* thisx, Game_Play* game_play);
void aPOFF_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Post_Office_Profile = {
    /* */ ACTOR_POST_OFFICE,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5808,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Post_Office),
    /* */ aPOFF_actor_ct,
    /* */ aPOFF_actor_dt,
    /* */ aPOFF_actor_init,
    /* */ aPOFF_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/aPOFF_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/aPOFF_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A084B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A084E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08574_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08670_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08734_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A0878C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A0890C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A089D4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08A08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08A40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08B0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08B74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08C08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08C24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/aPOFF_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08CF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/func_80A08D80_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Post_Office/ac_post_office/aPOFF_actor_draw.s")
