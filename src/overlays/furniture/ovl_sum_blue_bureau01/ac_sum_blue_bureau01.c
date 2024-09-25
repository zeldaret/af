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


#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BC00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BC94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BCDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_blue_bureau01/ac_sum_blue_bureau01/func_80A4BEF0_jp.s")
