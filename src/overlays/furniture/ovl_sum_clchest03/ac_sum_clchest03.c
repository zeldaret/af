#include "m_lib.h"
#include "c_keyframe.h"
#include "src/overlays/actors/ovl_My_Room/ac_my_room.h"
#include "segment_symbols.h"
#include "objects/furniture/int_sum_clchest03/int_sum_clchest03.h"

void aSumClChest03_ct(FurnitureActor* this, u8* data UNUSED);
void aSumClChest03_mv(FurnitureActor* this, Actor* myroomactor, Game_Play* game_play, u8* data UNUSED);
void aSumClChest03_dw(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED);
void aSumClChest03_dt(FurnitureActor* this UNUSED, u8* data UNUSED);

FurnitureActorFunctions aSumClChest03_func = {
    /* */ aSumClChest03_ct,
    /* */ aSumClChest03_mv,
    /* */ aSumClChest03_dw,
    /* */ aSumClChest03_dt,
    /* */ NULL,
};

FurnitureActorProfile iam_sum_clchest03 = {
    /* */ SEGMENT_ROM_START(int_sum_clchest03),
    /* */ SEGMENT_ROM_END(int_sum_clchest03),
    /* */ SEGMENT_VRAM_START(int_sum_clchest03),
    /* */ SEGMENT_VRAM_END(int_sum_clchest03),
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ NULL,
    /* */ 18.0f,
    /* */ 0.01f,
    /* */ 4,
    /* */ 0,
    /* */ 0,
    /* */ 0,
    /* */ 0,
    /* */ 4,
    /* */ &aSumClChest03_func,
};

void aSumClChest03_ct(FurnitureActor* this, u8* data UNUSED) {
    UNUSED s32 pad[2];
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    cKF_SkeletonInfo_R_ct(skeletonInfo, Lib_SegmentedToVirtual(&cKF_bs_r_int_sum_clchest03),
                          Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_clchest03), this->jointTable, this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(skeletonInfo, Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_clchest03), NULL);
    skeletonInfo->frameControl.speed = 0.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
}

void aSumClChest03_mv(FurnitureActor* this, Actor* myroomactor, Game_Play* game_play, u8* data UNUSED) {
    if (common_data.clip.myRoomClip != NULL) {
        common_data.clip.myRoomClip->unk_34(this, myroomactor, game_play, 1.0f, 16.0f);
    }
}

void aSumClChest03_dw(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED) {
    UNUSED s32 pad;
    s32 temp = game_play->state.frameCounter & 1;
    Mtx* mtx = &this->matrix[temp][0];

    OPEN_DISPS(game_play->state.gfxCtx);
    if (1) {}
    if (1) {}
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, &int_sum_clchest03_hiki_txt);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 7,
               G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD);
    gDPLoadSync(POLY_OPA_DISP++);
    gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 0);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 7,
               G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD);
    gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x00FC, 0x00FC);
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, &int_sum_clchest03_pal01_pal);
    gDPTileSync(POLY_OPA_DISP++);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x01F0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(POLY_OPA_DISP++);
    gDPLoadTLUTCmd(POLY_OPA_DISP++, G_TX_LOADTILE, 15);
    gDPPipeSync(POLY_OPA_DISP++);
    CLOSE_DISPS(game_play->state.gfxCtx);

    cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtx, NULL, NULL, NULL);
}

void aSumClChest03_dt(FurnitureActor* this UNUSED, u8* data UNUSED) {
}
