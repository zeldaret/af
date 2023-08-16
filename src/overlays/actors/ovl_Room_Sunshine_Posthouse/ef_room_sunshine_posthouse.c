#include "ef_room_sunshine_posthouse.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ef_Room_Sunshine_Posthouse_actor_ct(Actor* thisx, PlayState* play);
void Ef_Room_Sunshine_PosthouseR_actor_move(Actor* thisx, PlayState* play);
void Ef_Room_Sunshine_PosthouseR_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Room_Sunshine_Posthouse_Profile = {
    /* */ 117,
    /* */ ACTOR_PART_6,
    /* */ 48,
    /* */ 0,
    /* */ 43,
    /* */ sizeof(Room_Sunshine_Posthouse),
    /* */ Ef_Room_Sunshine_Posthouse_actor_ct,
    /* */ (ActorFunc)none_proc1,
    /* */ Ef_Room_Sunshine_PosthouseR_actor_move,
    /* */ Ef_Room_Sunshine_PosthouseR_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/Ef_Room_Sunshine_Posthouse_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/func_809666C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/func_80966788_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/func_80966898_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/Ef_Room_Sunshine_PosthouseR_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/func_809669D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/func_80966B40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Room_Sunshine_Posthouse/ef_room_sunshine_posthouse/Ef_Room_Sunshine_PosthouseR_actor_draw.s")