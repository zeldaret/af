#include "m_lib.h"
#include "src/overlays/actors/ovl_My_Room/ac_my_room.h"
#include "segment_symbols.h"

void func_80A4BC00_jp(FurnitureActor* this, u8* data UNUSED);
void func_80A4BC94_jp(FurnitureActor* this, Actor* myroomactor, Game_Play* game_play, u8* data UNUSED);
void func_80A4BCDC_jp(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED);
void func_80A4BEF0_jp(FurnitureActor* this UNUSED, u8* data UNUSED);

FurnitureActorFunctions aSumBlueBureau01_func = {
    /* */ func_80A4BC00_jp,
    /* */ func_80A4BC94_jp,
    /* */ func_80A4BCDC_jp,
    /* */ func_80A4BEF0_jp,
    /* */ NULL,
};

FurnitureActorProfile iam_sum_blue_bureau01 = {
    /* */ SEGMENT_ROM_START(int_sum_blue_bureau01),
    /* */ SEGMENT_ROM_END(int_sum_blue_bureau01),
    /* */ SEGMENT_VRAM_START(int_sum_blue_bureau01),
    /* */ SEGMENT_VRAM_END(int_sum_blue_bureau01),
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ 40.0f,
    /* */ 0.01f,
    /* */ 4,
    /* */ 0,
    /* */ 0,
    /* */ 0,
    /* */ 0,
    /* */ 4,
    /* */ &aSumBlueBureau01_func,
};

extern BaseSkeletonR D_6000DA8;
extern BaseAnimationR D_6000D70;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BC00_jp.s")
void func_80A4BC00_jp(FurnitureActor* this, u8* data UNUSED) {
    UNUSED s32 pad[2];
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    cKF_SkeletonInfo_R_ct(skeletonInfo, Lib_SegmentedToVirtual(&D_6000DA8),
                          Lib_SegmentedToVirtual(&D_6000D70), this->jointTable, this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(skeletonInfo, Lib_SegmentedToVirtual(&D_6000D70), NULL);
    skeletonInfo->frameControl.speed = 0.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BC94_jp.s")
void func_80A4BC94_jp(FurnitureActor* this, Actor* myroomactor, Game_Play* game_play, u8* data UNUSED) {
    if (common_data.clip.myRoomClip != NULL) {
        common_data.clip.myRoomClip->unk_34(this, myroomactor, game_play, 1.0f, 16.0f);
    }
}

extern u16* D_6000008;
extern u8* D_6000028;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BCDC_jp.s")
void func_80A4BCDC_jp(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED) {
    UNUSED s32 pad;
    s32 temp = game_play->state.frameCounter & 1;
    Mtx* mtx = &this->matrix[temp][0];

    OPEN_DISPS(game_play->state.gfxCtx);
    if(1) {};
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPLoadTextureBlockS(POLY_OPA_DISP++, &D_6000028, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 7, 7, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadTLUT_pal16(POLY_OPA_DISP++, 15, &D_6000008);
    CLOSE_DISPS(game_play->state.gfxCtx);
    cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtx, NULL, NULL, NULL);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BEF0_jp.s")
void func_80A4BEF0_jp(FurnitureActor* this UNUSED, u8* data UNUSED) {
}

