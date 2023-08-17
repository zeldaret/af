#include "m_collision_obj.h"
#include "m_lib.h"
#include "sys_math3d.h"
// #include "overlays/gamestates/ovl_play/m_play.h"
#include "attributes.h"
#include "macros.h"

typedef struct struct_mco_work {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Game_Play2138_unk_08* unk_04[10];
} struct_mco_work; // size = 0x2C

extern struct_mco_work mco_work;

typedef void (*CollisionVsFunc)(struct Game_Play*, Game_Play2138*, Game_Play2138_unk_08*, Game_Play2138_unk_08*);

extern CollisionVsFunc oc_collision_function[][3];

extern CollisionCheck_Status D_80104770_jp;

extern CollisionVsFunc occ_collision_function[][3];

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


void func_80077620_jp(struct Game_Play* game_play, Game_Play2138* arg1) {
    arg1->unk_00 = 0;
    CollisionCheck_clear(game_play, arg1);
}

void CollisionCheck_dt(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1) {

}

void CollisionCheck_clear(UNUSED struct Game_Play* game_play, Game_Play2138* arg1) {
    Game_Play2138_unk_08** var_v0;

    if (arg1->unk_00 & 1) {
        return;
    }

    arg1->unk_04 = 0;
    for (var_v0 = arg1->unk_08; var_v0 < &arg1->unk_08[ARRAY_COUNT(arg1->unk_08)]; var_v0++) {
        *var_v0 = NULL;
    }

    mco_work.unk_00 = 0;
    for (var_v0 = mco_work.unk_04; var_v0 < &mco_work.unk_04[ARRAY_COUNT(mco_work.unk_04)]; var_v0++) {
        *var_v0 = NULL;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_setOC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077794_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_setOC_HitInfo.s")

void CollisionCheck_OC_JntSph_Vs_JntSph(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    JntSph* jntSphA = (JntSph*)arg2;
    JntSph* jntSphB = (JntSph*)arg3;
    JntSph_unk_10* var_s0;
    JntSph_unk_10* var_s4;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;

    if ((jntSphA->unk_0C <= 0) || (jntSphA->unk_10 == NULL) || (jntSphB->unk_0C <= 0) || (jntSphB->unk_10 == NULL)) {
        return;
    }

    for (var_s4 = jntSphA->unk_10; var_s4 < &jntSphA->unk_10[jntSphA->unk_0C]; var_s4++) {
        if (!(var_s4->unk_00 & 1)) {
            continue;
        }

        for (var_s0 = jntSphB->unk_10; var_s0 < &jntSphB->unk_10[jntSphB->unk_0C]; var_s0++) {
            if (!(var_s0->unk_00 & 1)) {
                continue;
            }

            if (Math3D_sphereCrossSphere_cl(&var_s4->unk_0C, &var_s0->unk_0C, &sp74) == 1) {
                xyz_t_move_s_xyz(&sp68, &var_s4->unk_0C);
                xyz_t_move_s_xyz(&sp5C, &var_s0->unk_0C);
                CollisionCheck_setOC_HitInfo(&jntSphA->unk_00, &var_s4->unk_00, &sp68, &jntSphB->unk_00, &var_s0->unk_00, &sp5C, sp74);
            }
        }
    }
}

void CollisionCheck_OC_JntSph_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    JntSph* jntSph = (JntSph*)arg2;
    Pipe* pipe = (Pipe*)arg3;
    JntSph_unk_10* var_s0;

    if ((jntSph->unk_0C <= 0) || (jntSph->unk_10 == NULL)) {
        return;
    }

    if (!(jntSph->unk_00.unk_08 & 1) || !(pipe->unk_00.unk_08 & 1) || !(pipe->unk_0C & 1)) {
        return;
    }

    for (var_s0 = jntSph->unk_10; var_s0 < &jntSph->unk_10[jntSph->unk_0C]; var_s0++) {
        f32 sp78;

        if (!(var_s0->unk_00 & 1)) {
            continue;
        }

        if (Math3D_sphereVsPipe_cl(&var_s0->unk_0C, &pipe->unk_0E, &sp78) == 1) {
            Vec3f sp6C;
            Vec3f sp60;

            xyz_t_move_s_xyz(&sp6C, &var_s0->unk_0C);
            xyz_t_move_s_xyz(&sp60, &pipe->unk_14);
            CollisionCheck_setOC_HitInfo(&jntSph->unk_00, &var_s0->unk_00, &sp6C, &pipe->unk_00, &pipe->unk_0C, &sp60, sp78);
        }
    }
}

void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    CollisionCheck_OC_JntSph_Vs_Pipe(game_play, arg1, arg3, arg2);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    Pipe* pipeA = (Pipe*)arg2;
    Pipe* pipeB = (Pipe*)arg3;
    f32 sp4C;
    Vec3f sp40;
    Vec3f sp34;

    if ((!(pipeA->unk_00.unk_08 & 1) || !(pipeB->unk_00.unk_08 & 1) || !(pipeA->unk_0C & 1) || !(pipeB->unk_0C & 1))) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipeA->unk_0E, &pipeB->unk_0E, &sp4C) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&sp40, &pipeA->unk_14);
    xyz_t_move_s_xyz(&sp34, &pipeB->unk_14);
    CollisionCheck_setOC_HitInfo(&pipeA->unk_00, &pipeA->unk_0C, &sp40, &pipeB->unk_00, &pipeB->unk_0C, &sp34, sp4C);
}

s32 CollisionCheck_Check1ClObjNoOC(Game_Play2138_unk_08* arg0) {
    if (!(arg0->unk_08 & 1)) {
        return 1;
    }
    return 0;
}

s32 CollisionCheck_Check2ClObjNoOC(Game_Play2138_unk_08* arg0, Game_Play2138_unk_08* arg1) {
    if (!(arg0->unk_08 & arg1->unk_09 & 0x38) || !(arg0->unk_09 & arg1->unk_08 & 0x38)) {
        return 1;
    }
    if (arg0->unk_00 == arg1->unk_00) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OC(struct Game_Play* game_play, Game_Play2138* arg1) {
    Game_Play2138_unk_08** var_s2;

    for (var_s2 = arg1->unk_08; var_s2 < &arg1->unk_08[arg1->unk_04]; var_s2++) {
        Game_Play2138_unk_08** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = var_s2 + 1; var_s0 < &arg1->unk_08[arg1->unk_04]; var_s0++) {
            CollisionVsFunc temp_v0;

            if ((*var_s0 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s0) == 1) || (CollisionCheck_Check2ClObjNoOC(*var_s2, *var_s0) == 1)) {
                continue;
            }

            temp_v0 = oc_collision_function[(*var_s2)->unk_0A][(*var_s0)->unk_0A];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(game_play, arg1, *var_s2, *var_s0);
        }
    }

    CollisionCheck_OCC(game_play, arg1);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_OCC_Tris_Vs_JntSph.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_OCC_Tris_Vs_Pipe.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Check1ClObjNoOCC.s")

void CollisionCheck_OCC(struct Game_Play* game_play, Game_Play2138* arg1) {
    Game_Play2138_unk_08** var_s2;

    if (mco_work.unk_00 == 0) {
        return;
    }

    for (var_s2 = mco_work.unk_04; (u32) var_s2 < (u32) &mco_work.unk_04[mco_work.unk_00]; var_s2++) {
        Game_Play2138_unk_08** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOCC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = arg1->unk_08; (u32) var_s0 < (u32) &arg1->unk_08[arg1->unk_04]; var_s0++) {
            CollisionVsFunc temp_v0;

            if ((*var_s0) == NULL) {
                continue;
            }

            if ((*var_s2)->unk_00 == (*var_s0)->unk_00) {
                continue;
            }

            temp_v0 = occ_collision_function[(*var_s2)->unk_0A][(*var_s0)->unk_0A];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(game_play, arg1, (*var_s2), (*var_s0));
        }
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007870C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007872C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80078748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800787E8_jp.s")

void CollisionCheck_Status_ct(CollisionCheck_Status* status) {
    *status = D_80104770_jp;
}

void CollisionCheck_Status_Clear(CollisionCheck_Status* status) {
    status->unk_14 = 0;
    status->unk_15 = 0;
    status->unk_16 = 0;
    status->unk_17 = 0;
    status->displacement.z = 0.0f;
    status->displacement.y = 0.0f;
    status->displacement.x = 0.0f;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Status_set3.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/CollisionCheck_Uty_ActorWorldPosSetPipeC.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800789BC_jp.s")
