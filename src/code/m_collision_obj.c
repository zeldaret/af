#include "m_collision_obj.h"
#include "m_actor.h"
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

typedef s32 (*OcClearFunc)(struct Game_Play*, Game_Play2138*);

extern OcClearFunc OCClearFunctionTable[];

extern ClObjTrisElemAttr D_801046D0_jp;

void CollisionCheck_workTrisElemCenter(Tris_unk_10* arg0, Vec3f* arg1) {
    arg1->x = (arg0->unk_04.unk_00.unk_00[0].x + arg0->unk_04.unk_00.unk_00[1].x + arg0->unk_04.unk_00.unk_00[2].x) * (1.0f / 3.0f);
    arg1->y = (arg0->unk_04.unk_00.unk_00[0].y + arg0->unk_04.unk_00.unk_00[1].y + arg0->unk_04.unk_00.unk_00[2].y) * (1.0f / 3.0f);
    arg1->z = (arg0->unk_04.unk_00.unk_00[0].z + arg0->unk_04.unk_00.unk_00[1].z + arg0->unk_04.unk_00.unk_00[2].z) * (1.0f / 3.0f);
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObj_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076BD4_jp.s")

s32 ClObj_set4(UNUSED struct Game_Play* game_play, Game_Play2138_unk_08* arg1, struct Actor* actor, ClObj_set4_arg3* arg3) {
    arg1->actor = actor;
    arg1->unk_08 = arg3->unk_0;
    arg1->unk_09 = arg3->unk_1;
    arg1->unk_0A = arg3->unk_2;
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C14_jp.s")

s32 ClObjElem_ct(ClObjElem* arg0) {
    arg0->unk_0 = 0;
    return 1;
}

s32 ClObjElem_set(ClObjElem* arg0, ClObjElem* arg1) {
    arg0->unk_0 = arg1->unk_0;

    return 1;
}

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObjJntSph_OCClear.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObjPipeAttr_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077078_jp.s")

s32 ClObjPipeAttr_set(UNUSED struct Game_Play* game_play, UNUSED ClObjPipeAttr_set_arg2* arg1, UNUSED ClObjPipeAttr_set_arg2* arg2) {
    *arg1 = *arg2;
    return 1;
}

s32 ClObjPipe_ct(struct Game_Play* game_play, Pipe* pipe) {
    ClObj_ct(game_play, &pipe->unk_00);
    ClObjElem_ct(&pipe->unk_0C);
    ClObjPipeAttr_ct(game_play, &pipe->unk_0E);
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObjPipe_dt.s")

s32 ClObjPipe_set5(struct Game_Play* game_play, Pipe* pipe, struct Actor* actor, ClObjPipe_set5_arg3* arg3) {
    ClObj_set4(game_play, &pipe->unk_00, actor, &arg3->unk_0);
    ClObjElem_set(&pipe->unk_0C, &arg3->unk_3);
    ClObjPipeAttr_set(game_play, &pipe->unk_0E, &arg3->unk_4);
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObjPipe_OCClear.s")

s32 ClObjTrisElemAttr_ct(struct Game_Play* arg0, ClObjTrisElemAttr* arg1) {
    *arg1 = D_801046D0_jp;

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077248_jp.s")

s32 ClObjTrisElemAttr_set(struct Game_Play* game_play, ClObjTrisElemAttr* arg1, ClObjTris_set5_nzm_arg3_unk_8_unk_04* arg2) {
    Vec3f* var_v0;
    Vec3f* var_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    for (var_v0 = arg1->unk_00.unk_00, var_v1 = arg2->unk_00; var_v0 < &arg1->unk_00.unk_00[ARRAY_COUNT(arg1->unk_00.unk_00)]; var_v0++, var_v1++) {
        *var_v0 = *var_v1;
    }

    Math3DPlane(&arg2->unk_00[0], &arg2->unk_00[1], &arg2->unk_00[2], &sp44, &sp40, &sp3C, &sp38);
    arg1->unk_24 = sp44;
    arg1->unk_28 = sp40;
    arg1->unk_2C = sp3C;
    arg1->unk_30 = sp38;

    return 1;
}

s32 ClObjTrisElem_ct(struct Game_Play* game_play, Tris_unk_10* arg1) {
    ClObjElem_ct(&arg1->unk_00);
    ClObjTrisElemAttr_ct(game_play, &arg1->unk_04);

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_8007734C_jp.s")

s32 ClObjTrisElem_set(struct Game_Play* game_play, Tris_unk_10* arg1, ClObjTris_set5_nzm_arg3_unk_8* arg2) {
    ClObjElem_set(&arg1->unk_00, &arg2->unk_00);
    ClObjTrisElemAttr_set(game_play, &arg1->unk_04, &arg2->unk_04);

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_800773C0_jp.s")

s32 ClObjTris_ct(struct Game_Play* game_play, Tris* tris) {
    ClObj_ct(game_play, &tris->unk_00);
    tris->unk_0C = 0;
    tris->unk_10 = NULL;
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80077410_jp.s")

s32 ClObjTris_set5_nzm(struct Game_Play* game_play, Tris* tris, Actor* actor, ClObjTris_set5_nzm_arg3* arg3, Tris_unk_10* arg4) {
    ClObjTris_set5_nzm_arg3_unk_8* var_s1;
    Tris_unk_10* var_s0;

    ClObj_set4(game_play, &tris->unk_00, actor, arg3);

    tris->unk_0C = arg3->unk_4;
    tris->unk_10 = arg4;

    for (var_s0 = arg4, var_s1 = arg3->unk_8; var_s0 <  &tris->unk_10[tris->unk_0C]; var_s0++, var_s1++) {
        ClObjTrisElem_ct(game_play, var_s0);
        ClObjTrisElem_set(game_play, var_s0, var_s1);
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/ClObjTris_OCClear.s")

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

s32 CollisionCheck_setOC(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2) {
    s32 temp_v1;

    if (_Game_play_isPause(game_play) == 1) {
        return -1;
    }

    OCClearFunctionTable[arg2->unk_0A](game_play, arg2);

    if ((arg2->actor != NULL) && (arg2->actor->update == NULL)) {
        return -1;
    }

    if (arg1->unk_04 >= ARRAY_COUNT(arg1->unk_08)) {
        return -1;
    }

    if (arg1->unk_00 & 1) {
        return -1;
    }

    temp_v1 = arg1->unk_04;

    arg1->unk_08[arg1->unk_04] = arg2;
    arg1->unk_04++;

    return temp_v1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/get_type.s")

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

    if (!(jntSph->unk_00.unk_08 & 1) || !(pipe->unk_00.unk_08 & 1) || !(pipe->unk_0C.unk_0 & 1)) {
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
            xyz_t_move_s_xyz(&sp60, &pipe->unk_0E.unk_6);
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

    if ((!(pipeA->unk_00.unk_08 & 1) || !(pipeB->unk_00.unk_08 & 1) || !(pipeA->unk_0C.unk_0 & 1) || !(pipeB->unk_0C.unk_0 & 1))) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipeA->unk_0E, &pipeB->unk_0E, &sp4C) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&sp40, &pipeA->unk_0E.unk_6);
    xyz_t_move_s_xyz(&sp34, &pipeB->unk_0E.unk_6);
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
    if (arg0->actor == arg1->actor) {
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

void CollisionCheck_setOCC_HitInfo(UNUSED struct Game_Play* game_play, Game_Play2138_unk_08* arg1, Tris_unk_10* arg2, UNUSED Vec3f* arg3, Game_Play2138_unk_08* arg4, UNUSED u8* arg5, UNUSED Vec3f* arg6, Vec3f* arg7) {
    arg1->unk_04 = arg4->actor;
    arg1->unk_09 |= 4;
    arg2->unk_04.unk_34.x =  arg7->x;
    arg2->unk_04.unk_34.y =  arg7->y;
    arg2->unk_04.unk_34.z =  arg7->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, UNUSED Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    JntSph_unk_10* var_s6;
    Tris* tris = (Tris*)arg2;
    JntSph* jntSph = (JntSph*)arg3;

    if ((tris->unk_0C <= 0) || (tris->unk_10 == NULL) || (jntSph->unk_0C <= 0) || (jntSph->unk_10 == NULL)) {
        return;
    }

    for (var_s6 = jntSph->unk_10; var_s6 < &jntSph->unk_10[jntSph->unk_0C]; var_s6++) {
        Tris_unk_10* var_s0;
        Vec3f sp74;

        if (!(var_s6->unk_00 & 1)) {
            continue;
        }

        for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
            if (func_800DE13C_jp(&var_s6->unk_0C, &var_s0->unk_04, &sp74) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                xyz_t_move_s_xyz(&sp68, &var_s6->unk_0C);
                CollisionCheck_workTrisElemCenter(var_s0, &sp5C);
                CollisionCheck_setOCC_HitInfo(game_play, &tris->unk_00, var_s0, &sp5C, &jntSph->unk_00, &var_s6->unk_00, &sp68, &sp74);
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, UNUSED Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3) {
    Tris* tris = (Tris*)arg2;
    Pipe* pipe = (Pipe*)arg3;
    Tris_unk_10* var_s0;

    if ((pipe->unk_0E.unk_0 <= 0) || (pipe->unk_0E.unk_2 <= 0) || !(pipe->unk_0C.unk_0 & 1)) {
        return;
    }

    if ((tris->unk_0C <= 0) || (tris->unk_10 == NULL)) {
        return;
    }

    for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
        Vec3f sp68;

        if (Math3D_pipeCrossTriangle_cp(&pipe->unk_0E, &var_s0->unk_04, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            CollisionCheck_workTrisElemCenter(var_s0, &sp50);
            xyz_t_move_s_xyz(&sp5C, &pipe->unk_0E.unk_6);
            CollisionCheck_setOCC_HitInfo(game_play, &tris->unk_00, var_s0, &sp50, &pipe->unk_00, &pipe->unk_0C, &sp5C, &sp68);
            break;
        }
    }
}

s32 CollisionCheck_Check1ClObjNoOCC(Game_Play2138_unk_08* arg0) {
    if (!(arg0->unk_09 & 2)) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OCC(struct Game_Play* game_play, Game_Play2138* arg1) {
    Game_Play2138_unk_08** var_s2;

    if (mco_work.unk_00 == 0) {
        return;
    }

    for (var_s2 = mco_work.unk_04; var_s2 < &mco_work.unk_04[mco_work.unk_00]; var_s2++) {
        Game_Play2138_unk_08** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOCC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = arg1->unk_08; var_s0 < &arg1->unk_08[arg1->unk_04]; var_s0++) {
            CollisionVsFunc temp_v0;

            if ((*var_s0) == NULL) {
                continue;
            }

            if ((*var_s2)->actor == (*var_s0)->actor) {
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
