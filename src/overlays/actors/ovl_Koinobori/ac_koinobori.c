#include "global.h"
#include "ac_koinobori.h"
#include "m_actor_dlftbls.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "c_keyframe.h"

#define THIS ((Koinobori*)thisx)

void aKOI_actor_ct(Actor* thisx, Game_Play* game_play);
void aKOI_actor_dt(Actor* thisx, Game_Play* game_play);
void aKOI_actor_init(Actor* thisx, Game_Play* game_play);
void aKOI_actor_draw(Actor* thisx, Game_Play* game_play);

#if 0
ActorProfile Koinobori_Profile = {
    /* */ ACTOR_KOINOBORI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5839,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Koinobori),
    /* */ aKOI_actor_ct,
    /* */ aKOI_actor_dt,
    /* */ aKOI_actor_init,
    /* */ aKOI_actor_draw,
    /* */ NULL,
};
#endif

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_ct.s")
void func_80A9369C_jp(Koinobori* this, s32);                     /* extern */
void func_80A936BC_jp(Koinobori* this, s32);                     /* extern */
extern BaseSkeletonR D_601F22C;

void aKOI_actor_ct(Actor *thisx, Game_Play *game_play)
{
    Koinobori* this = THIS;
    // void *sp28;
    // void *temp_a0;

    // temp_a0 = thisx + 0x178;
    gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098->unk_AC(0x27));
    // sp28 = temp_a0;
    cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &D_601F22C, 0, this->jointTable, this->morphTable);
    func_80A9369C_jp(this, 1);
    func_80A936BC_jp(this, 0);
    cKF_SkeletonInfo_R_play(&this->skeletonInfo);
}


#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9369C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A936BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/func_80A9373C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Koinobori/ac_koinobori/aKOI_actor_draw.s")
