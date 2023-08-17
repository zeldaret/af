#include "m_collision_obj.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "macros.h"

typedef struct struct_mco_work {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_PTR unk_04[10];  // TODO: this may be an array of pointers to PlayState2138_unk_08
} struct_mco_work; // size = 0x2C

extern struct_mco_work mco_work;

typedef void (*OcCollisionFunc)(PlayState*, PlayState2138*, PlayState2138_unk_08*, PlayState2138_unk_08*);

extern OcCollisionFunc oc_collision_function[][3];

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076B40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076BA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076BE8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C3C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076CC0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076D68_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076D90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076DDC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076E00_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076E2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076ED0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076F9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007703C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077078_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007708C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800770CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077118_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077158_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800771BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800771FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077248_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007725C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007734C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077374_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800773C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800773E4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077410_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800774B4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077580_jp.s")


void func_80077620_jp(PlayState* play, PlayState2138* arg1) {
    arg1->unk_00 = 0;
    CollisionCheck_clear(play, arg1);
}

void CollisionCheck_dt(UNUSED PlayState* play, UNUSED PlayState2138* arg1) {

}

void CollisionCheck_clear(UNUSED PlayState* play, PlayState2138* arg1) {
    PlayState2138_unk_08** var_v0;
    UNK_PTR* var_v0_2;

    if (arg1->unk_00 & 1) {
        return;
    }

    arg1->unk_04 = 0;
    for (var_v0 = arg1->unk_08; var_v0 < &arg1->unk_08[ARRAY_COUNT(arg1->unk_08)]; var_v0++) {
        *var_v0 = 0;
    }

    mco_work.unk_00 = 0;
    for (var_v0_2 = mco_work.unk_04; (void*)var_v0_2 < (void*)&mco_work.unk_04[10]; var_v0_2++) {
        *var_v0_2 = 0;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_setOC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800777D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077B6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077D6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077EF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077F20_jp.s")

s32 CollisionCheck_Check1ClObjNoOC(PlayState2138_unk_08* arg0) {
    if (!(arg0->unk_08 & 1)) {
        return 1;
    }
    return 0;
}

s32 CollisionCheck_Check2ClObjNoOC(PlayState2138_unk_08* arg0, PlayState2138_unk_08* arg1) {
    if (!(arg0->unk_08 & arg1->unk_09 & 0x38) || !(arg0->unk_09 & arg1->unk_08 & 0x38)) {
        return 1;
    }
    if (arg0->unk_00 == arg1->unk_00) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OC(PlayState* play, PlayState2138* arg1) {
    PlayState2138_unk_08** var_s2;

    for (var_s2 = arg1->unk_08; var_s2 < &arg1->unk_08[arg1->unk_04]; var_s2++) {
        PlayState2138_unk_08** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = var_s2 + 1; var_s0 < &arg1->unk_08[arg1->unk_04]; var_s0++) {
            OcCollisionFunc temp_v0;

            if ((*var_s0 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s0) == 1) || (CollisionCheck_Check2ClObjNoOC(*var_s2, *var_s0) == 1)) {
                continue;
            }

            temp_v0 = oc_collision_function[(*var_s2)->unk_0A][(*var_s0)->unk_0A];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(play, arg1, *var_s2, *var_s0);
        }
    }

    CollisionCheck_OCC(play, arg1);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078258_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007841C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078568_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_OCC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007870C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007872C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800787E8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Status_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Status_Clear.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Status_set3.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Uty_ActorWorldPosSetPipeC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800789BC_jp.s")
