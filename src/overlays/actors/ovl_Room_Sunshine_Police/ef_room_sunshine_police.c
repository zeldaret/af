#include "ef_room_sunshine_police.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ef_Room_Sunshine_Police_actor_ct(Actor* thisx, Game_Play* game_play);
void Ef_Room_Sunshine_PoliceR_actor_move(Actor* thisx, Game_Play* game_play);
void Ef_Room_Sunshine_PoliceR_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Room_Sunshine_Police_Profile = {
    /* */ ACTOR_ROOM_SUNSHINE_POLICE,
    /* */ ACTOR_PART_6,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ OBJECT_44,
    /* */ sizeof(Room_Sunshine_Police),
    /* */ Ef_Room_Sunshine_Police_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ Ef_Room_Sunshine_PoliceR_actor_move,
    /* */ Ef_Room_Sunshine_PoliceR_actor_draw,
    /* */ NULL,
};
#endif

// clang-format off
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/Ef_Room_Sunshine_Police_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_80966ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_80966F90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_809670A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/Ef_Room_Sunshine_PoliceR_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_809671D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_8096722C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/func_8096739C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Police/ef_room_sunshine_police/Ef_Room_Sunshine_PoliceR_actor_draw.s")
// clang-format on
