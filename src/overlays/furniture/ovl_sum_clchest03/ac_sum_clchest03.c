#include "m_lib.h"
#include "c_keyframe.h"
#include "src/overlays/actors/ovl_My_Room/ac_my_room.h"

// D_80A70F60_jp
//  FurnitureActorFunctions aSumClChest03_func = {
//      /* */ func_80A70C60_jp,
//      /* */ func_80A70CF4_jp,
//      /* */ func_8007244C_jp,
//      /* */ func_80076358_jp,
//      /* */ NULL,
//  };

// D_80A70F74_jp
//  FurnitureActorUnkStruct iam_sum_clchest03 = {
//      /* */ 0x015D0000,
//      /* */ 0x015D0F70,
//      /* */ 0x06000000,
//      /* */ D_6000F70,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x00000000,
//      /* */ 0x41900000,
//      /* */ 0x3C23D70A,
//      /* */ 0x04000000,
//      /* */ 0x00000004,
//      /* */ aSumClChest03_func,
//  };

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70C60_jp.s")
extern BaseSkeletonR D_6000898;
extern BaseAnimationR D_6000F5C;

void func_80A70C60_jp(FurnitureActor* this, u8* data UNUSED) {
    s32 pad[2];
    SkeletonInfoR* skeletonInfo = &this->skeletonInfo;

    cKF_SkeletonInfo_R_ct(skeletonInfo, Lib_SegmentedToVirtual(&D_6000F5C), Lib_SegmentedToVirtual(&D_6000898),
                          &this->jointTable, &this->morphTable);
    cKF_SkeletonInfo_R_init_standard_stop(skeletonInfo, Lib_SegmentedToVirtual(&D_6000898), NULL);
    skeletonInfo->frameControl.speed = 0.0f;
    cKF_SkeletonInfo_R_play(skeletonInfo);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70CF4_jp.s")
void func_80A70CF4_jp(FurnitureActor *this, Actor *myroomactor, Game_Play *game_play, u8* data UNUSED)
{
    if (common_data.clip.myRoomClip != NULL)
    {
        common_data.clip.myRoomClip->unk_34(this, myroomactor, game_play, 1.0f, 16.0f);
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70D3C_jp.s")
extern UNK_PTR D_6000020;
extern UNK_PTR D_6000000;

void func_80A70D3C_jp(FurnitureActor* this, Actor* myRoomActor UNUSED, Game_Play* game_play, u8* data UNUSED)
{
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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70F50_jp.s")
void func_80A70F50_jp(FurnitureActor* this UNUSED, u8* data UNUSED)
{

}
