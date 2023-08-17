#include "ac_arrange_room.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Arrange_Room_Actor_ct(Actor* thisx, Game_Play* play);
void Arrange_Room_Actor_dt(Actor* thisx, Game_Play* play);
void Arrange_Room_Actor_move(Actor* thisx, Game_Play* play);
void Arrange_Room_Actor_draw(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Arrange_Room_Profile = {
    /* */ ACTOR_ARRANGE_ROOM,
    /* */ ACTOR_PART_5,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x8006,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Arrange_Room),
    /* */ Arrange_Room_Actor_ct,
    /* */ Arrange_Room_Actor_dt,
    /* */ Arrange_Room_Actor_move,
    /* */ Arrange_Room_Actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80950E50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80950EC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80950F1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80950F70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/Arrange_Room_Actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/Arrange_Room_Actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80951124_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_809512C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/Arrange_Room_Actor_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/Arrange_Room_Actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Arrange_Room/ac_arrange_room/func_80951480_jp.s")
