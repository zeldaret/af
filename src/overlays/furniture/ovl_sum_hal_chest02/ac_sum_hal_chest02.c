#include "global.h"
#include "m_lib.h"
#include "c_keyframe.h"
#include "src/overlays/actors/ovl_My_Room/ac_my_room.h"

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_hal_chest02/ac_sum_hal_chest02/func_80A6FBE0_jp.s")

extern BaseSkeletonR cKF_bs_r_int_sum_hal_chest02;
extern BaseAnimationR cKF_ba_r_int_sum_hal_chest02;

void func_80A6FBE0_jp(FurnitureActor* this, u8 data UNUSED) {
    s32 pad[2];
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    cKF_SkeletonInfo_R_ct(skeletonInfo, Lib_SegmentedToVirtual(&cKF_bs_r_int_sum_hal_chest02), Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_hal_chest02), this->jointTable,
                        this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(skeletonInfo, Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_hal_chest02), NULL);
    skeletonInfo->frameControl.speed = 0.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_hal_chest02/ac_sum_hal_chest02/func_80A6FC74_jp.s")
void func_80A6FC74_jp(FurnitureActor* this, Actor* myRoomActor, Game_Play* game_play, u8* data UNUSED)
{
    if (common_data.unk_1008C != NULL)
    {
        common_data.unk_1008C->unk_34(this, myRoomActor, game_play, 1.0f, 16.0f);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_hal_chest02/ac_sum_hal_chest02/func_80A6FCBC_jp.s")
void func_80A6FCBC_jp(FurnitureActor *this, Actor *myRoomActor, Game_Play *game_play, u8 *data)
{
    s32 sp30;
    GraphicsContext *sp28;
    void *sp20;
    GraphicsContext *temp_a1;
    s32 temp_t0;
    void *temp_v0;
    void *temp_v0_10;
    void *temp_v0_11;
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v0_9;

    temp_t0 = game_play->state.unk_A0 & 1;
    temp_a1 = game_play->state.gfxCtx;
    temp_v0 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0 + 8;
    // *temp_v0 = 0xDA380003;
    sp30 = temp_t0;
    sp28 = temp_a1;
    sp20 = temp_v0;
    // sp20->unk4 = _Matrix_to_Mtx_new(game_play->state.gfxCtx);
    gSPMatrix(__polyOpa++, _Matrix_to_Mtx_new(game_play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    temp_v0_2 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_2 + 8;
    temp_v0_2->unk0 = 0xFD900000;
    temp_v0_2->unk4 = 0x06000020;
    temp_v0_3 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_3 + 8;
    temp_v0_3->unk0 = 0xF5900000;
    temp_v0_3->unk4 = (? *)0x0705C170;
    temp_v0_4 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_4 + 8;
    temp_v0_4->unk4 = NULL;
    temp_v0_4->unk0 = 0xE6000000;
    temp_v0_5 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_5 + 8;
    temp_v0_5->unk4 = (? *)0x077FF000;
    temp_v0_5->unk0 = 0xF3000000;
    temp_v0_6 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_6 + 8;
    temp_v0_6->unk4 = NULL;
    temp_v0_6->unk0 = 0xE7000000;
    temp_v0_7 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_7 + 8;
    temp_v0_7->unk4 = (? *)0x5C170;
    temp_v0_7->unk0 = 0xF5881000;
    temp_v0_8 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_8 + 8;
    temp_v0_8->unk0 = 0xF2000000;
    temp_v0_8->unk4 = (? *)0xFC0FC;
    temp_v0_9 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_9 + 8;
    temp_v0_9->unk0 = 0xFD100000;
    temp_v0_9->unk4 = (? *)0x06000000;
    temp_v0_10 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_10 + 8;
    temp_v0_10->unk4 = NULL;
    temp_v0_10->unk0 = 0xE8000000;
    temp_v0_11 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_11 + 8;
    temp_v0_11->unk4 = (? *)0x07000000;
    temp_v0_11->unk0 = 0xF50001F0;
    temp_v0_12 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_12 + 8;
    temp_v0_12->unk4 = NULL;
    temp_v0_12->unk0 = 0xE6000000;
    temp_v0_13 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_13 + 8;
    temp_v0_13->unk4 = (? *)0x0703C000;
    temp_v0_13->unk0 = 0xF0000000;
    temp_v0_14 = temp_a1->polyOpa.tha.head;
    temp_a1->polyOpa.tha.head = temp_v0_14 + 8;
    temp_v0_14->unk4 = NULL;
    temp_v0_14->unk0 = 0xE7000000;
    cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, this + (temp_t0 * 0x280) + 0x210, NULL, NULL, NULL);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_hal_chest02/ac_sum_hal_chest02/func_80A6FED0_jp.s")
void func_80A6FED0_jp(FurnitureActor* this UNUSED, u8 data UNUSED)
{
}
