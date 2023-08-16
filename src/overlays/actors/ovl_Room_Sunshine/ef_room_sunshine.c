#include "ef_room_sunshine.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ef_Room_Sunshine_actor_ct(Actor* thisx, PlayState* play);
void Ef_Room_SunshineR_actor_move(Actor* thisx, PlayState* play);
void Ef_Room_SunshineR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Room_Sunshine_Profile = {
    /* */ ACTOR_ROOM_SUNSHINE,
    /* */ ACTOR_PART_6,
    /* */ 48,
    /* */ 0x0000,
    /* */ OBJECT_5,
    /* */ sizeof(Room_Sunshine),
    /* */ Ef_Room_Sunshine_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ Ef_Room_SunshineR_actor_move,
    /* */ Ef_Room_SunshineR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/Ef_Room_Sunshine_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/func_80965E38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/func_80965EE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/func_80965FF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/Ef_Room_SunshineR_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/func_80966120_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/func_8096628C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine/ef_room_sunshine/Ef_Room_SunshineR_actor_draw.s")
