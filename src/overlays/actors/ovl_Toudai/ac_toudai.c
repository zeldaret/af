#include "global.h"
#include "ac_toudai.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "c_keyframe.h"
#include "m_field_info.h"

#define THIS ((Toudai*)thisx)

void aTOU_actor_ct(Actor* thisx, PlayState* play);
void aTOU_actor_dt(Actor* thisx, PlayState* play);
void aTOU_actor_init(Actor* thisx, PlayState* play);
void aTOU_actor_draw(Actor* thisx, PlayState* play);

#if 0
ActorProfile Toudai_Profile = {
    /* */ ACTOR_TOUDAI,
    /* */ ACTOR_PART_0,
    /* */ 0,
    /* */ 0x5843,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Toudai),
    /* */ aTOU_actor_ct,
    /* */ aTOU_actor_dt,
    /* */ aTOU_actor_init,
    /* */ aTOU_actor_draw,
    /* */ NULL,
};
#endif

// aTOU_fgunit_on
// aTOU_fgunit_off
// aTOU_actor_ct
// aTOU_actor_dt
// aTOU_rewrite_door
// aTOU_set_bgOffset
// aTOU_color_ctrl
// aTOU_init
// aTOU_wait
// aTOU_lighting
// aTOU_lightout
// aTOU_setup_action
// aTOU_actor_move
// aTOU_actor_init
// aTOU_actor_draw_before
// aTOU_actor_draw_after
// aTOU_actor_draw

void func_80AAB488_jp(Toudai* this, s32);                     /* extern */
void func_80AAB918_jp(Toudai* this, s32);                     /* extern */
extern BaseSkeletonR* D_80AAC0AC_jp;

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_ct.s")
// void aTOU_actor_ct(Actor *thisx, PlayState *play)
// {
//     Toudai* this = THIS;
//     s32 sp30;
//     // SkeletonInfoR *sp2C;
//     // SkeletonInfoR *temp_a0;

//     sp30 = (common_data.unk1010C == 3);
//     // temp_a0 = thisx + 0x178;
//     // gSegments[6] = common_data.unk_10098->unkAC(0x2D) + 0x80000000;
//     gSegments[6] = OS_K0_TO_PHYSICAL(common_data.unk_10098);
//     // sp2C = temp_a0;
//     cKF_SkeletonInfo_R_ct(&this->skeletonInfo, &D_80AAC0AC_jp[sp30], NULL, &this->jointTable, &this->morphTable);
//     func_80AAB488_jp(this, 1);
//     func_80AAB918_jp(this, 0);
//     cKF_SkeletonInfo_R_play(&this->skeletonInfo);
//     this->actor.world.pos.x -= 20.0f;
//     this->actor.world.pos.z -= 20.0f;
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_dt.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB488_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB60C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB81C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB840_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB894_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB8D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB918_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AAB9C8_jp.s")
// void func_80AAB9C8_jp(Toudai *this, PlayState *play)
// {
//     // gSegments[6] = common_data.unk_10098->unkAC(0x2D) + 0x80000000;
//     gSegments[6] = common_data.unk_10098;
//     this->unk174 = cKF_SkeletonInfo_R_play(&this->skeletonInfo);
//     this->unk1E8 = this->skeletonInfo.frameControl.currentFrame;
//     this->unk2A0(this, play);
//     func_80AAB60C_jp(this);
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_init.s")
void func_80AAB9C8_jp(Toudai *this, PlayState *play); /* extern */

void aTOU_actor_init(Actor *thisx, PlayState *play)
{
    mFI_SetFG_common(0xF10A, thisx->home.pos, 0);
    func_80AAB9C8_jp(thisx, play);
    thisx->update = func_80AAB9C8_jp;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAB8_jp.s")
//aTOU_actor_draw_before
s32 func_80AABAB8_jp(PlayState* play, SkeletonInfoR* skeletonInfo, s32 jointIndex, Gfx** dlist)
{
    if (jointIndex == 4)
    {
        *dlist = NULL;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/func_80AABAD8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Toudai/ac_toudai/aTOU_actor_draw.s")
