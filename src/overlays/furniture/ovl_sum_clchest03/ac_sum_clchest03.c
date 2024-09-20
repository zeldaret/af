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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70CF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70D3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/furniture/ovl_sum_clchest03/ac_sum_clchest03/func_80A70F50_jp.s")
