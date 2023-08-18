#include "m_collision_obj.h"
#include "m_actor.h"
#include "m_lib.h"
#include "sys_math3d.h"
#include "libc/math.h"
#include "attributes.h"
// #include "overlays/gamestates/ovl_play/m_play.h"
#include "macros.h"

typedef struct struct_mco_work {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ ClObj* unk_04[10];
} struct_mco_work; // size = 0x2C

extern struct_mco_work mco_work;

typedef void (*CollisionVsFunc)(struct Game_Play*, Game_Play2138*, ClObj*, ClObj*);

extern CollisionVsFunc oc_collision_function[][3];

extern CollisionCheck_Status D_80104770_jp;

extern CollisionVsFunc occ_collision_function[][3];

typedef s32 (*ClearFunc)(struct Game_Play*, ClObj*);

extern ClearFunc OCClearFunctionTable[];

extern ClearFunc OCCClearFunctionTable[];

extern ClObjTrisElemAttr D_801046D0_jp;

extern Math3D_pipeCrossTriangle_cp_arg0 D_801046C4_jp;

extern ClObj D_801046A0_jp;

void CollisionCheck_workTrisElemCenter(Tris_unk_10* arg0, Vec3f* arg1) {
    arg1->x = (arg0->unk_04.unk_00.unk_00[0].x + arg0->unk_04.unk_00.unk_00[1].x + arg0->unk_04.unk_00.unk_00[2].x) * (1.0f / 3.0f);
    arg1->y = (arg0->unk_04.unk_00.unk_00[0].y + arg0->unk_04.unk_00.unk_00[1].y + arg0->unk_04.unk_00.unk_00[2].y) * (1.0f / 3.0f);
    arg1->z = (arg0->unk_04.unk_00.unk_00[0].z + arg0->unk_04.unk_00.unk_00[1].z + arg0->unk_04.unk_00.unk_00[2].z) * (1.0f / 3.0f);
}

s32 ClObj_ct(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    *arg1 = D_801046A0_jp;

    return 1;
}

s32 ClObj_dt(UNUSED struct Game_Play* game_play, UNUSED ClObj* arg1) {
    return 1;
}

s32 ClObj_set4(UNUSED struct Game_Play* game_play, ClObj* arg1, struct Actor* actor, ClObj_set4_arg3* arg3) {
    arg1->actor = actor;
    arg1->unk_08 = arg3->unk_0;
    arg1->unk_09 = arg3->unk_1;
    arg1->unk_0A = arg3->unk_2;
    return 1;
}

void ClObj_OCClear(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    arg1->unk_04 = NULL;
    arg1->unk_08 &= ~0x2;
    arg1->unk_09 &= ~0x1;
}

s32 ClObjElem_ct(ClObjElem* arg0) {
    arg0->unk_0 = 0;
    return 1;
}

s32 ClObjElem_set(ClObjElem* arg0, ClObjElem* arg1) {
    arg0->unk_0 = arg1->unk_0;

    return 1;
}

void ClObjElem_OCClear(UNUSED struct Game_Play* arg0, ClObjElem* arg1) {
    arg1->unk_0 &= ~0x2;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076C78_jp.s")

s32 func_80076CC0_jp(UNUSED struct Game_Play* game_play, UNUSED UNK_PTR arg1) {
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076CD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076D2C_jp.s")


s32 func_80076D68_jp(struct Game_Play* game_play, JntSph_unk_10* arg1) {
    func_80076CC0_jp(game_play, &arg1->unk_04);
    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076D90_jp.s")

s32 ClObjJntSphElem_OCClear(struct Game_Play* game_play, JntSph_unk_10* arg1) {
    ClObjElem_OCClear(game_play, &arg1->unk_00);

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076E00_jp.s")

s32 func_80076E2C_jp(struct Game_Play* game_play, JntSph* jntSph) {
    JntSph_unk_10* var_s0;

    ClObj_dt(game_play, &jntSph->unk_00);

    for (var_s0 = jntSph->unk_10; var_s0 < &jntSph->unk_10[jntSph->unk_0C]; var_s0++) {
        func_80076D68_jp(game_play, var_s0);
    }

    jntSph->unk_0C = 0;
    jntSph->unk_10 = NULL;

    return 1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_collision_obj/func_80076ED0_jp.s")

s32 ClObjJntSph_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    JntSph* jntSph = (JntSph*)arg1;
    JntSph_unk_10* var_s0;

    ClObj_OCClear(game_play, &jntSph->unk_00);

    for (var_s0 = jntSph->unk_10; var_s0 < &jntSph->unk_10[jntSph->unk_0C]; var_s0++) {
        ClObjJntSphElem_OCClear(game_play, var_s0);
    }

    return 1;
}

s32 ClObjPipeAttr_ct(UNUSED struct Game_Play* game_play, Math3D_pipeCrossTriangle_cp_arg0* arg1) {
    *arg1 = D_801046C4_jp;

    return 1;
}

s32 ClObjPipeAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjPipeAttr_set_arg2* arg1) {
    return 1;
}

s32 ClObjPipeAttr_set(UNUSED struct Game_Play* game_play, ClObjPipeAttr_set_arg2* arg1, ClObjPipeAttr_set_arg2* arg2) {
    *arg1 = *arg2;
    return 1;
}

s32 ClObjPipe_ct(struct Game_Play* game_play, Pipe* pipe) {
    ClObj_ct(game_play, &pipe->unk_00);
    ClObjElem_ct(&pipe->unk_0C);
    ClObjPipeAttr_ct(game_play, &pipe->unk_0E);

    return 1;
}

s32 ClObjPipe_dt(struct Game_Play* game_play, Pipe* pipe) {
    ClObj_dt(game_play, &pipe->unk_00);
    ClObjPipeAttr_dt(game_play, &pipe->unk_0E);

    return 1;
}

s32 ClObjPipe_set5(struct Game_Play* game_play, Pipe* pipe, struct Actor* actor, ClObjPipe_set5_arg3* arg3) {
    ClObj_set4(game_play, &pipe->unk_00, actor, &arg3->unk_0);
    ClObjElem_set(&pipe->unk_0C, &arg3->unk_3);
    ClObjPipeAttr_set(game_play, &pipe->unk_0E, &arg3->unk_4);
    return 1;
}

s32 ClObjPipe_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    Pipe* pipe = (Pipe*) arg1;

    ClObj_OCClear(game_play, arg1);
    ClObjElem_OCClear(game_play, &pipe->unk_0C);

    return 1;
}

s32 ClObjTrisElemAttr_ct(UNUSED struct Game_Play* arg0, ClObjTrisElemAttr* arg1) {
    *arg1 = D_801046D0_jp;

    return 1;
}

s32 ClObjTrisElemAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjTrisElemAttr* arg1) {
    return 1;
}

s32 ClObjTrisElemAttr_set(UNUSED struct Game_Play* game_play, ClObjTrisElemAttr* arg1, ClObjTris_set5_nzm_arg3_unk_8_unk_04* arg2) {
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

s32 ClObjTrisElem_dt(struct Game_Play* game_play, Tris_unk_10* arg1) {
    ClObjTrisElemAttr_dt(game_play, &arg1->unk_04);

    return 1;
}

s32 ClObjTrisElem_set(struct Game_Play* game_play, Tris_unk_10* arg1, ClObjTris_set5_nzm_arg3_unk_8* arg2) {
    ClObjElem_set(&arg1->unk_00, &arg2->unk_00);
    ClObjTrisElemAttr_set(game_play, &arg1->unk_04, &arg2->unk_04);

    return 1;
}

s32 ClObjTrisElem_OCClear(struct Game_Play* game_play, Tris_unk_10* arg1) {
    ClObjElem_OCClear(game_play, &arg1->unk_00);

    return 1;
}

s32 ClObjTris_ct(struct Game_Play* game_play, Tris* tris) {
    ClObj_ct(game_play, &tris->unk_00);
    tris->unk_0C = 0;
    tris->unk_10 = NULL;
    return 1;
}

s32 ClObjTris_dt_nzf(struct Game_Play* game_play, Tris* tris) {
    Tris_unk_10* var_s0;

    ClObj_dt(game_play, &tris->unk_00);

    for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
        ClObjTrisElem_dt(game_play, var_s0);
    }

    tris->unk_0C = 0;
    tris->unk_10 = NULL;
    return 1;
}

s32 ClObjTris_set5_nzm(struct Game_Play* game_play, Tris* tris, Actor* actor, ClObjTris_set5_nzm_arg3* arg3, Tris_unk_10* arg4) {
    ClObjTris_set5_nzm_arg3_unk_8* var_s1;
    Tris_unk_10* var_s0;

    ClObj_set4(game_play, &tris->unk_00, actor, &arg3->unk_0);

    tris->unk_0C = arg3->unk_4;
    tris->unk_10 = arg4;

    for (var_s0 = arg4, var_s1 = arg3->unk_8; var_s0 <  &tris->unk_10[tris->unk_0C]; var_s0++, var_s1++) {
        ClObjTrisElem_ct(game_play, var_s0);
        ClObjTrisElem_set(game_play, var_s0, var_s1);
    }

    return 1;
}

s32 ClObjTris_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    Tris* tris = (Tris*)arg1;
    Tris_unk_10* var_s0;

    ClObj_OCClear(game_play, &tris->unk_00);

    for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
        ClObjTrisElem_OCClear(game_play, var_s0);
    }

    return 1;
}

void func_80077620_jp(struct Game_Play* game_play, Game_Play2138* arg1) {
    arg1->unk_00 = 0;
    CollisionCheck_clear(game_play, arg1);
}

void CollisionCheck_dt(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1) {

}

void CollisionCheck_clear(UNUSED struct Game_Play* game_play, Game_Play2138* arg1) {
    ClObj** var_v0;

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

s32 CollisionCheck_setOC(struct Game_Play* game_play, Game_Play2138* arg1, ClObj* arg2) {
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

s32 get_type(u8 arg0) {
    if (arg0 == 0xFF) {
        return 0;
    }

    if (arg0 == 0xFE) {
        return 1;
    }

    return 2;
}

void CollisionCheck_setOC_HitInfo(ClObj* arg0, ClObjElem* arg1, Vec3f* arg2, ClObj* arg3, ClObjElem* arg4, Vec3f* arg5, f32 arg6) {
    f32 temp_fa1; // sp4C
    f32 temp_fv0_2;
    f32 temp_ft5;
    f32 sp40;
    f32 var_fa0;
    f32 var_fa1;
    f32 sp34;
    f32 var_ft4;
    f32 var_fv1;
    s32 temp_v0;
    Actor* temp_t0; // sp24
    Actor* temp_t1; // sp20
    UNUSED s32 pad[1];
    s32 sp18;

    temp_t0 = arg0->actor;
    temp_t1 = arg3->actor;

    arg0->unk_04 = temp_t1;
    arg0->unk_08 |= 2;
    arg1->unk_0 |= 2;

    if (arg3->unk_09 & 8) {
        arg0->unk_09 |= 1;
    }

    arg3->unk_04 = temp_t0;
    arg3->unk_08 |= 2;
    arg4->unk_0 |= 2;
    if (arg0->unk_09 & 8) {
        arg3->unk_09 |= 1;
    }

    if ((temp_t0 == NULL) || (temp_t1 == NULL) || (arg0->unk_08 & 4) || (arg3->unk_08 & 4)) {
        return;
    }

    sp18 = get_type(temp_t0->colStatus.unk_12);
    temp_v0 = get_type(temp_t1->colStatus.unk_12);

    var_fa1 = temp_t0->colStatus.unk_12;
    var_ft4 = temp_t1->colStatus.unk_12;

    sp34 = var_fa1 + var_ft4;
    if (fabsf(sp34) < 0.008f) {
        var_fa1 = var_ft4 = 1.0f;
        sp34 = 2.0f;
    }

    temp_ft5 = arg5->x - arg2->x;
    temp_fa1 = arg5->z - arg2->z;
    sp40 = sqrtf(SQ(temp_ft5) + SQ(temp_fa1));

    if (sp18 == 0) {
        if (temp_v0 == 0) {
            return;
        }
        var_fv1 = 0.0f;
        var_fa0 = 1.0f;
    } else if (sp18 == 1) {
        if (temp_v0 == 0) {
            var_fv1 = 1.0f;
            var_fa0 = 0.0f;
        } else if (temp_v0 == 1) {
            var_fv1 = 0.5f;
            var_fa0 = 0.5f;
        } else {
            var_fv1 = 0.0f;
            var_fa0 = 1.0f;
        }
    } else {
        if (temp_v0 == 2) {
            temp_fv0_2 = 1.0f / sp34;
            var_fv1 = var_ft4 * temp_fv0_2;
            var_fa0 = var_fa1 * temp_fv0_2;
        } else {
            var_fv1 = 1.0f;
            var_fa0 = 0.0f;
        }
    }

    if (arg0->unk_08 & 0x40) {
        var_fv1 = 0.0f;
        var_fa0 = 1.0f;
        temp_t1->speed = 0.0f;
    } else if (arg3->unk_08 & 0x40) {
        var_fv1 = 1.0f;
        var_fa0 = 0.0f;
        temp_t0->speed = 0.0f;
    }

    if (!(fabsf(sp40) < 0.008f)) {
        temp_ft5 *= arg6 / sp40;
        temp_fa1 *= arg6 / sp40;
        temp_t0->colStatus.displacement.x += -temp_ft5 * var_fv1;
        temp_t0->colStatus.displacement.z += -temp_fa1 * var_fv1;
        temp_t1->colStatus.displacement.x += temp_ft5 * var_fa0;
        temp_t1->colStatus.displacement.z += temp_fa1 * var_fa0;
    } else if (arg6 != 0.0f) {
        temp_t0->colStatus.displacement.x += -arg6 * var_fv1;
        temp_t1->colStatus.displacement.x += (arg6 * var_fa0);
    } else {
        temp_t0->colStatus.displacement.x -= var_fv1;
        temp_t1->colStatus.displacement.x += var_fa0;
    }
}

void CollisionCheck_OC_JntSph_Vs_JntSph(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
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
        if (!(var_s4->unk_00.unk_0 & 1)) {
            continue;
        }

        for (var_s0 = jntSphB->unk_10; var_s0 < &jntSphB->unk_10[jntSphB->unk_0C]; var_s0++) {
            if (!(var_s0->unk_00.unk_0 & 1)) {
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

void CollisionCheck_OC_JntSph_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
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

        if (!(var_s0->unk_00.unk_0 & 1)) {
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

void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
    CollisionCheck_OC_JntSph_Vs_Pipe(game_play, arg1, arg3, arg2);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
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

s32 CollisionCheck_Check1ClObjNoOC(ClObj* arg0) {
    if (!(arg0->unk_08 & 1)) {
        return 1;
    }
    return 0;
}

s32 CollisionCheck_Check2ClObjNoOC(ClObj* arg0, ClObj* arg1) {
    if (!(arg0->unk_08 & arg1->unk_09 & 0x38) || !(arg0->unk_09 & arg1->unk_08 & 0x38)) {
        return 1;
    }
    if (arg0->actor == arg1->actor) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OC(struct Game_Play* game_play, Game_Play2138* arg1) {
    ClObj** var_s2;

    for (var_s2 = arg1->unk_08; var_s2 < &arg1->unk_08[arg1->unk_04]; var_s2++) {
        ClObj** var_s0;

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

void CollisionCheck_setOCC_HitInfo(UNUSED struct Game_Play* game_play, ClObj* arg1, Tris_unk_10* arg2, UNUSED Vec3f* arg3, ClObj* arg4, UNUSED ClObjElem* arg5, UNUSED Vec3f* arg6, Vec3f* arg7) {
    arg1->unk_04 = arg4->actor;
    arg1->unk_09 |= 4;
    arg2->unk_04.unk_34.x =  arg7->x;
    arg2->unk_04.unk_34.y =  arg7->y;
    arg2->unk_04.unk_34.z =  arg7->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, UNUSED Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
    JntSph_unk_10* var_s6;
    Tris* tris = (Tris*)arg2;
    JntSph* jntSph = (JntSph*)arg3;

    if ((tris->unk_0C <= 0) || (tris->unk_10 == NULL) || (jntSph->unk_0C <= 0) || (jntSph->unk_10 == NULL)) {
        return;
    }

    for (var_s6 = jntSph->unk_10; var_s6 < &jntSph->unk_10[jntSph->unk_0C]; var_s6++) {
        Tris_unk_10* var_s0;
        Vec3f sp74;

        if (!(var_s6->unk_00.unk_0 & 1)) {
            continue;
        }

        for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
            if (Math3D_sphereCrossTriangle3_cp(&var_s6->unk_0C, var_s0->unk_04.unk_00.unk_00, &sp74) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                xyz_t_move_s_xyz(&sp68, &var_s6->unk_0C);
                CollisionCheck_workTrisElemCenter(var_s0, &sp5C);
                CollisionCheck_setOCC_HitInfo(game_play, &tris->unk_00, var_s0, &sp5C, &jntSph->unk_00, &var_s6->unk_00, &sp68, &sp74);
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, UNUSED Game_Play2138* arg1, ClObj* arg2, ClObj* arg3) {
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

        if (Math3D_pipeCrossTriangle_cp(&pipe->unk_0E, var_s0->unk_04.unk_00.unk_00, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            CollisionCheck_workTrisElemCenter(var_s0, &sp50);
            xyz_t_move_s_xyz(&sp5C, &pipe->unk_0E.unk_6);
            CollisionCheck_setOCC_HitInfo(game_play, &tris->unk_00, var_s0, &sp50, &pipe->unk_00, &pipe->unk_0C, &sp5C, &sp68);
            break;
        }
    }
}

s32 CollisionCheck_Check1ClObjNoOCC(ClObj* arg0) {
    if (!(arg0->unk_09 & 2)) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OCC(struct Game_Play* game_play, Game_Play2138* arg1) {
    ClObj** var_s2;

    if (mco_work.unk_00 == 0) {
        return;
    }

    for (var_s2 = mco_work.unk_04; var_s2 < &mco_work.unk_04[mco_work.unk_00]; var_s2++) {
        ClObj** var_s0;

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

s32 ClObjTrisElem_OCCClear(UNUSED struct Game_Play* game_play, Tris_unk_10* arg1) {
    arg1->unk_04.unk_34.x = 0.0f;
    arg1->unk_04.unk_34.y = 0.0f;
    arg1->unk_04.unk_34.z = 0.0f;
    return 1;
}

void ClObj_OCCClear(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    arg1->unk_04 = NULL;
    arg1->unk_09 &= ~0x4;
}

s32 ClObjTris_OCCClear(struct Game_Play* game_play, ClObj* arg1) {
    Tris* tris = (Tris*)arg1;
    Tris_unk_10* var_s0;

    ClObj_OCCClear(game_play, &tris->unk_00);

    for (var_s0 = tris->unk_10; var_s0 < &tris->unk_10[tris->unk_0C]; var_s0++) {
        ClObjTrisElem_OCCClear(game_play, var_s0);
    }

    return 1;
}

s32 CollisionCheck_setOCC(struct Game_Play* game_play, Game_Play2138* arg1, ClObj* arg2) {
    s32 temp_v0;

    if (_Game_play_isPause(game_play) == 1) {
        return -1;
    }

    if ((arg2->unk_0A == 0) || (arg2->unk_0A == 1)) {
        return -1;
    }

    OCCClearFunctionTable[arg2->unk_0A](game_play, arg2);

    if ((arg2->actor != NULL) && (arg2->actor->update == NULL)) {
        return -1;
    }

    if (mco_work.unk_00 >= ARRAY_COUNT(mco_work.unk_04)) {
        return -1;
    }

    if (arg1->unk_00 & 1) {
        return -1;
    }

    temp_v0 = mco_work.unk_00;
    mco_work.unk_04[mco_work.unk_00] = arg2;
    mco_work.unk_00 += 1;

    return temp_v0;
}

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

void CollisionCheck_Status_set3(CollisionCheck_Status* status, CollisionCheck_Status_set3_arg1* arg1) {
    status->unk_13 = arg1->unk_0;
    status->unk_0C = arg1->unk_2;
    status->unk_0E = arg1->unk_4;
    status->unk_10 = arg1->unk_6;
    status->unk_12 = arg1->unk_8;
}

void CollisionCheck_Uty_ActorWorldPosSetPipeC(Actor* actor, Pipe* pipe) {
    pipe->unk_0E.unk_6.x = (s16) (s32) actor->world.pos.x;
    pipe->unk_0E.unk_6.y = (s16) (s32) actor->world.pos.y;
    pipe->unk_0E.unk_6.z = (s16) (s32) actor->world.pos.z;
}

s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* game_play, Tris* tris, s32 arg2, ClObjTris_set5_nzm_arg3_unk_8_unk_04* arg3) {
    Tris_unk_10* temp = &tris->unk_10[arg2];

    return ClObjTrisElemAttr_set(game_play, &temp->unk_04, arg3);
}
