#include "ef_lamp_light.h"
#include "m_lib.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void Ef_Lamp_Light_actor_ct(Actor* thisx, Game_Play* play);
void Ef_Lamp_Light_actor_dt(Actor* thisx, Game_Play* play);
void Ef_Lamp_Light_actor_move(Actor* thisx, Game_Play* play);

#if 0
ActorProfile Lamp_Light_Profile = {
    /* */ ACTOR_LAMP_LIGHT,
    /* */ ACTOR_PART_6,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Lamp_Light),
    /* */ Ef_Lamp_Light_actor_ct,
    /* */ Ef_Lamp_Light_actor_dt,
    /* */ Ef_Lamp_Light_actor_move,
    /* */ (ActorFunc)none_proc1,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/Ef_Lamp_Light_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/Ef_Lamp_Light_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/func_80967644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/func_80967678_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/func_809676BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/func_809676E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Lamp_Light/ef_lamp_light/Ef_Lamp_Light_actor_move.s")
