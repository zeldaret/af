#include "m_lib.h"
#include "c_keyframe.h"
#include "src/overlays/actors/ovl_My_Room/ac_my_room.h"

void aSumHalChest02_ct(FurnitureActor* this, u8* data);
void aSumHalChest02_mv(FurnitureActor* this, Actor* myRoomActor, Game_Play* game_play, u8* data);
void aSumHalChest03_dw(FurnitureActor* this, Actor* myRoomActor, Game_Play* game_play, u8* data);
void aSumHalChest03_dt(FurnitureActor* this, u8* data);

FurnitureActorFunctions aSumHalChest02_func = {
    /* */ aSumHalChest02_ct,
    /* */ aSumHalChest02_mv,
    /* */ aSumHalChest03_dw,
    /* */ aSumHalChest03_dt,
    /* */ NULL,
};

FurnitureActorUnkStruct iam_sum_hal_chest02 = {
    /* */ 0x015C8000,
    /* */ 0x015C9020,
    /* */ 0x06000000,
    /* */ 0x06001020,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x00000000,
    /* */ 0x42200000,
    /* */ 0x3C23D70A,
    /* */ 0x04000000,
    /* */ 0x00000004,
    /* */ &aSumHalChest02_func,
};

extern BaseSkeletonR cKF_bs_r_int_sum_hal_chest02;
extern BaseAnimationR cKF_ba_r_int_sum_hal_chest02;

void aSumHalChest02_ct(FurnitureActor* this, u8* data UNUSED) {
    UNUSED s32 pad[2];
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    cKF_SkeletonInfo_R_ct(skeletonInfo, Lib_SegmentedToVirtual(&cKF_bs_r_int_sum_hal_chest02),
                          Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_hal_chest02), this->jointTable, this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(skeletonInfo, Lib_SegmentedToVirtual(&cKF_ba_r_int_sum_hal_chest02), NULL);
    skeletonInfo->frameControl.speed = 0.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
}

void aSumHalChest02_mv(FurnitureActor* this, Actor* myRoomActor, Game_Play* game_play, u8* data UNUSED) {
    if (common_data.clip.myRoomClip != NULL) {
        common_data.clip.myRoomClip->unk_34(this, myRoomActor, game_play, 1.0f, 16.0f);
    }
}

extern UNK_PTR D_6000020;
extern UNK_PTR D_6000000;

void aSumHalChest03_dw(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED) {
    UNUSED s32 pad;
    s32 temp = game_play->state.frameCounter & 1;
    Mtx* mtx = &this->matrix[temp][0];

    OPEN_DISPS(game_play->state.gfxCtx);
    if (1) {}
    if (1) {}
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(game_play->state.gfxCtx),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, &D_6000020);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 7,
               G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD);
    gDPLoadSync(POLY_OPA_DISP++);
    gDPLoadBlock(POLY_OPA_DISP++, G_TX_LOADTILE, 0, 0, 2047, 0);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_8b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 7,
               G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 7, G_TX_NOLOD);
    gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, 0, 0, 0x00FC, 0x00FC);
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, &D_6000000);
    gDPTileSync(POLY_OPA_DISP++);
    gDPSetTile(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x01F0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(POLY_OPA_DISP++);
    gDPLoadTLUTCmd(POLY_OPA_DISP++, G_TX_LOADTILE, 15);
    gDPPipeSync(POLY_OPA_DISP++);
    CLOSE_DISPS(game_play->state.gfxCtx);

    cKF_Si3_draw_R_SV(game_play, &this->skeletonInfo, mtx, NULL, NULL, NULL);
}

void aSumHalChest03_dt(FurnitureActor* this UNUSED, u8* data UNUSED) {
}
