#include "ac_kamakura_indoor.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Kamakura_Indoor_Actor_ct(Actor* thisx, PlayState* play);
void Kamakura_Indoor_Actor_dt(Actor* thisx, PlayState* play);
void Kamakura_Indoor_Actor_move(Actor* thisx, PlayState* play);
void Kamakura_Indoor_Actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Kamakura_Indoor_Profile = {
    /* */ ACTOR_KAMAKURA_INDOOR,
    /* */ ACTOR_PART_5,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_22,
    /* */ sizeof(Kamakura_Indoor),
    /* */ Kamakura_Indoor_Actor_ct,
    /* */ Kamakura_Indoor_Actor_dt,
    /* */ Kamakura_Indoor_Actor_move,
    /* */ Kamakura_Indoor_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/Kamakura_Indoor_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/Kamakura_Indoor_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A801C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A80370_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A80440_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A806B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/Kamakura_Indoor_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A80804_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/func_80A80A9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Kamakura_Indoor/ac_kamakura_indoor/Kamakura_Indoor_Actor_move.s")
