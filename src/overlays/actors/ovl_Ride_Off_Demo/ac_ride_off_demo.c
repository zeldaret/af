#include "ac_ride_off_demo.h"
#include "m_lib.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aROD_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aROD_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aROD_actor_move(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Ride_Off_Demo_Profile = {
    /* */ ACTOR_RIDE_OFF_DEMO,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20000000,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Ride_Off_Demo),
    /* */ aROD_actor_ct,
    /* */ aROD_actor_dt,
    /* */ aROD_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/aROD_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/aROD_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_8095388C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_809538CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953910_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_809539CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953A44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953AE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953B30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953B98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953C24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953C60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/func_80953C90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Ride_Off_Demo/ac_ride_off_demo/aROD_actor_move.s")
