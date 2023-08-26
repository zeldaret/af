#include "ac_animal_logo.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"

void aAL_actor_ct(Actor* thisx, Game_Play* gamePlay);
void aAL_actor_dt(Actor* thisx, Game_Play* gamePlay);
void aAL_actor_move(Actor* thisx, Game_Play* gamePlay);
void aAL_actor_draw(Actor* thisx, Game_Play* gamePlay);

#if 0
ActorProfile Animal_Logo_Profile = {
    /* */ ACTOR_ANIMAL_LOGO,
    /* */ ACTOR_PART_4,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Animal_Logo),
    /* */ aAL_actor_ct,
    /* */ aAL_actor_dt,
    /* */ aAL_actor_move,
    /* */ aAL_actor_draw,
    /* */ NULL,
};
#endif

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FC70_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FCD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FD6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FE38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FF24_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FF60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80A9FFF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0070_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA01A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0234_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0264_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA02A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA02E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0320_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0360_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0398_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA03BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0478_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0668_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA07F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA08E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0A6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0C98_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA0FA8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA12A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA1458_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA19CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA1B78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/func_80AA1C50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/aAL_actor_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/aAL_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/aAL_actor_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Animal_Logo/ac_animal_logo/aAL_actor_draw.s")
