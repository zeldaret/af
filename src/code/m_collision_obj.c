#include "m_collision_obj.h"
#include "m_actor.h"
#include "m_lib.h"
#include "sys_math3d.h"
#include "libc/math.h"
#include "attributes.h"
#include "macros.h"

typedef struct struct_mco_work {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ ClObj* unk_04[10];
} struct_mco_work; // size = 0x2C

extern struct_mco_work mco_work;


typedef void (*CollisionVsFunc)(struct Game_Play*, CollisionCheck*, ClObj*, ClObj*);

typedef s32 (*ClearFunc)(struct Game_Play*, ClObj*);


extern ClObj clobj_default;

extern ClObjJntSphElemAttr default_jntsphelem_attr;

extern ClObjPipeAttr default_pipe_attr;

extern ClObjTrisElemAttr default_clobjtriselem_attr;

extern ClearFunc OCClearFunctionTable[COLSHAPE_MAX];

extern CollisionVsFunc oc_collision_function[COLSHAPE_MAX][COLSHAPE_MAX];

extern CollisionVsFunc occ_collision_function[COLSHAPE_MAX][COLSHAPE_MAX];

extern ClearFunc OCCClearFunctionTable[COLSHAPE_MAX];

extern CollisionCheck_Status status_org;


void CollisionCheck_workTrisElemCenter(ClObjTrisElem* arg0, Vec3f* arg1) {
    arg1->x = (arg0->unk_04.unk_00.unk_00.vertices[0].x + arg0->unk_04.unk_00.unk_00.vertices[1].x + arg0->unk_04.unk_00.unk_00.vertices[2].x) * (1.0f / 3.0f);
    arg1->y = (arg0->unk_04.unk_00.unk_00.vertices[0].y + arg0->unk_04.unk_00.unk_00.vertices[1].y + arg0->unk_04.unk_00.unk_00.vertices[2].y) * (1.0f / 3.0f);
    arg1->z = (arg0->unk_04.unk_00.unk_00.vertices[0].z + arg0->unk_04.unk_00.unk_00.vertices[1].z + arg0->unk_04.unk_00.unk_00.vertices[2].z) * (1.0f / 3.0f);
}

s32 ClObj_ct(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    *arg1 = clobj_default;

    return 1;
}

s32 ClObj_dt(UNUSED struct Game_Play* game_play, UNUSED ClObj* arg1) {
    return 1;
}

s32 ClObj_set4(UNUSED struct Game_Play* game_play, ClObj* arg1, struct Actor* actor, ClObj_Properties* arg3) {
    arg1->actor = actor;
    arg1->prop.ocFlags1 = arg3->ocFlags1;
    arg1->prop.ocFlags2 = arg3->ocFlags2;
    arg1->prop.shape = arg3->shape;

    return 1;
}

void ClObj_OCClear(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    arg1->unk_4 = NULL;
    arg1->prop.ocFlags1 &= ~OC1_2;
    arg1->prop.ocFlags2 &= ~OC2_1;
}

s32 ClObjElem_ct(ClObjElem* arg0) {
    arg0->unk_0 = 0;
    return 1;
}

s32 ClObjElem_set(ClObjElem* arg0, ClObjElem* arg1) {
    arg0->unk_0 = arg1->unk_0;

    return 1;
}

void ClObjElem_OCClear(UNUSED struct Game_Play* game_play, ClObjElem* arg1) {
    arg1->unk_0 &= ~0x2;
}

s32 ClObjJntSphElemAttr_ct(UNUSED struct Game_Play* game_play, ClObjJntSphElemAttr* arg1) {
    *arg1 = default_jntsphelem_attr;

    return 1;
}

s32 ClObjJntSphElemAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjJntSphElemAttr* arg1) {
    return 1;
}

s32 ClObjJntSphElemAttr_set(UNUSED struct Game_Play* game_play, ClObjJntSphElemAttr* arg1, ClObjJntSphElemAttr_Init* arg2) {
    arg1->unk_14 = arg2->unk_0;
    arg1->unk_00 = arg2->unk_2;
    arg1->unk_10 = arg2->unk_A * 0.01f;

    return 1;
}

s32 ClObjJntSphElem_ct(struct Game_Play* game_play, ClObjJntSphElem* arg1) {
    ClObjElem_ct(&arg1->unk_00);
    ClObjJntSphElemAttr_ct(game_play, &arg1->unk_04);

    return 1;
}

s32 ClObjJntSphElem_dt(struct Game_Play* game_play, ClObjJntSphElem* arg1) {
    ClObjJntSphElemAttr_dt(game_play, &arg1->unk_04);

    return 1;
}

s32 ClObjJntSphElem_set(struct Game_Play* game_play, ClObjJntSphElem* arg1, ClObjJntSphElem_Init* arg2) {
    ClObjElem_set(&arg1->unk_00, &arg2->unk_0);
    ClObjJntSphElemAttr_set(game_play, &arg1->unk_04, &arg2->unk_2);

    return 1;
}

s32 ClObjJntSphElem_OCClear(struct Game_Play* game_play, ClObjJntSphElem* arg1) {
    ClObjElem_OCClear(game_play, &arg1->unk_00);

    return 1;
}

s32 ClObjJntSph_ct(struct Game_Play* game_play, ClObjJntSph* colJntSph) {
    ClObj_ct(game_play, &colJntSph->base);
    colJntSph->count = 0;
    colJntSph->elements = NULL;

    return 1;
}

s32 ClObjJntSph_dt_nzf(struct Game_Play* game_play, ClObjJntSph* colJntSph) {
    ClObjJntSphElem* element;

    ClObj_dt(game_play, &colJntSph->base);

    for (element = colJntSph->elements; element < &colJntSph->elements[colJntSph->count]; element++) {
        ClObjJntSphElem_dt(game_play, element);
    }

    colJntSph->count = 0;
    colJntSph->elements = NULL;

    return 1;
}

s32 ClObjJntSph_set5_nzm(struct Game_Play* game_play, ClObjJntSph* colJntSph, Actor* actor, ClObjJntSph_Init* arg3, ClObjJntSphElem* arg4) {
    ClObjJntSphElem_Init* var_s1;
    ClObjJntSphElem* var_s0;

    ClObj_set4(game_play, &colJntSph->base, actor, &arg3->unk_0);

    colJntSph->count = arg3->unk_4;
    colJntSph->elements = arg4;

    for (var_s0 = colJntSph->elements, var_s1 = arg3->unk_8; var_s0 < &colJntSph->elements[colJntSph->count]; var_s0++, var_s1++) {
        ClObjJntSphElem_ct(game_play, var_s0);
        ClObjJntSphElem_set(game_play, var_s0, var_s1);
    }

    return 1;
}

s32 ClObjJntSph_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)arg1;
    ClObjJntSphElem* var_s0;

    ClObj_OCClear(game_play, &colJntSph->base);

    for (var_s0 = colJntSph->elements; var_s0 < &colJntSph->elements[colJntSph->count]; var_s0++) {
        ClObjJntSphElem_OCClear(game_play, var_s0);
    }

    return 1;
}

s32 ClObjPipeAttr_ct(UNUSED struct Game_Play* game_play, ClObjPipeAttr* arg1) {
    *arg1 = default_pipe_attr;

    return 1;
}

s32 ClObjPipeAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjPipeAttr* arg1) {
    return 1;
}

s32 ClObjPipeAttr_set(UNUSED struct Game_Play* game_play, ClObjPipeAttr* arg1, ClObjPipeAttr* arg2) {
    *arg1 = *arg2;

    return 1;
}

s32 ClObjPipe_ct(struct Game_Play* game_play, ClObjPipe* colPipe) {
    ClObj_ct(game_play, &colPipe->base);
    ClObjElem_ct(&colPipe->element);
    ClObjPipeAttr_ct(game_play, &colPipe->attribute);

    return 1;
}

s32 ClObjPipe_dt(struct Game_Play* game_play, ClObjPipe* colPipe) {
    ClObj_dt(game_play, &colPipe->base);
    ClObjPipeAttr_dt(game_play, &colPipe->attribute);

    return 1;
}

s32 ClObjPipe_set5(struct Game_Play* game_play, ClObjPipe* colPipe, struct Actor* actor, ClObjPipe_Init* arg3) {
    ClObj_set4(game_play, &colPipe->base, actor, &arg3->unk_0);
    ClObjElem_set(&colPipe->element, &arg3->unk_3);
    ClObjPipeAttr_set(game_play, &colPipe->attribute, &arg3->unk_4);
    return 1;
}

s32 ClObjPipe_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    ClObjPipe* colPipe = (ClObjPipe*) arg1;

    ClObj_OCClear(game_play, arg1);
    ClObjElem_OCClear(game_play, &colPipe->element);

    return 1;
}

s32 ClObjTrisElemAttr_ct(UNUSED struct Game_Play* game_play, ClObjTrisElemAttr* arg1) {
    *arg1 = default_clobjtriselem_attr;

    return 1;
}

s32 ClObjTrisElemAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjTrisElemAttr* arg1) {
    return 1;
}

s32 ClObjTrisElemAttr_set(UNUSED struct Game_Play* game_play, ClObjTrisElemAttr* arg1, ClObjTrisElemAttr_Init* arg2) {
    Vec3f* var_v0;
    Vec3f* var_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    for (var_v0 = arg1->unk_00.unk_00.vertices, var_v1 = arg2->unk_00.vertices; var_v0 < &arg1->unk_00.unk_00.vertices[ARRAY_COUNT(arg1->unk_00.unk_00.vertices)]; var_v0++, var_v1++) {
        *var_v0 = *var_v1;
    }

    Math3DPlane(&arg2->unk_00.vertices[0], &arg2->unk_00.vertices[1], &arg2->unk_00.vertices[2], &sp44, &sp40, &sp3C, &sp38);
    arg1->unk_00.unk_24.x = sp44;
    arg1->unk_00.unk_24.y = sp40;
    arg1->unk_00.unk_24.z = sp3C;
    arg1->unk_00.unk_30 = sp38;

    return 1;
}

s32 ClObjTrisElem_ct(struct Game_Play* game_play, ClObjTrisElem* arg1) {
    ClObjElem_ct(&arg1->unk_00);
    ClObjTrisElemAttr_ct(game_play, &arg1->unk_04);

    return 1;
}

s32 ClObjTrisElem_dt(struct Game_Play* game_play, ClObjTrisElem* arg1) {
    ClObjTrisElemAttr_dt(game_play, &arg1->unk_04);

    return 1;
}

s32 ClObjTrisElem_set(struct Game_Play* game_play, ClObjTrisElem* arg1, ClObjTris_set5_nzm_arg3_unk_8* arg2) {
    ClObjElem_set(&arg1->unk_00, &arg2->unk_00);
    ClObjTrisElemAttr_set(game_play, &arg1->unk_04, &arg2->unk_04);

    return 1;
}

s32 ClObjTrisElem_OCClear(struct Game_Play* game_play, ClObjTrisElem* arg1) {
    ClObjElem_OCClear(game_play, &arg1->unk_00);

    return 1;
}

s32 ClObjTris_ct(struct Game_Play* game_play, ClObjTris* colTris) {
    ClObj_ct(game_play, &colTris->base);
    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_dt_nzf(struct Game_Play* game_play, ClObjTris* colTris) {
    ClObjTrisElem* var_s0;

    ClObj_dt(game_play, &colTris->base);

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        ClObjTrisElem_dt(game_play, var_s0);
    }

    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_set5_nzm(struct Game_Play* game_play, ClObjTris* colTris, Actor* actor, ClObjTris_set5_nzm_arg3* arg3, ClObjTrisElem* arg4) {
    ClObjTris_set5_nzm_arg3_unk_8* var_s1;
    ClObjTrisElem* var_s0;

    ClObj_set4(game_play, &colTris->base, actor, &arg3->unk_0);

    colTris->count = arg3->unk_4;
    colTris->elements = arg4;

    for (var_s0 = arg4, var_s1 = arg3->unk_8; var_s0 <  &colTris->elements[colTris->count]; var_s0++, var_s1++) {
        ClObjTrisElem_ct(game_play, var_s0);
        ClObjTrisElem_set(game_play, var_s0, var_s1);
    }

    return 1;
}

s32 ClObjTris_OCClear(struct Game_Play* game_play, ClObj* arg1) {
    ClObjTris* colTris = (ClObjTris*)arg1;
    ClObjTrisElem* var_s0;

    ClObj_OCClear(game_play, &colTris->base);

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        ClObjTrisElem_OCClear(game_play, var_s0);
    }

    return 1;
}

void CollisionCheck_ct(struct Game_Play* game_play, CollisionCheck* arg1) {
    arg1->unk_00 = 0;
    CollisionCheck_clear(game_play, arg1);
}

void CollisionCheck_dt(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1) {

}

void CollisionCheck_clear(UNUSED struct Game_Play* game_play, CollisionCheck* arg1) {
    ClObj** var_v0;

    if (arg1->unk_00 & 1) {
        return;
    }

    arg1->ocColCount = 0;
    for (var_v0 = arg1->ocColliders; var_v0 < &arg1->ocColliders[ARRAY_COUNT(arg1->ocColliders)]; var_v0++) {
        *var_v0 = NULL;
    }

    mco_work.unk_00 = 0;
    for (var_v0 = mco_work.unk_04; var_v0 < &mco_work.unk_04[ARRAY_COUNT(mco_work.unk_04)]; var_v0++) {
        *var_v0 = NULL;
    }
}

s32 CollisionCheck_setOC(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2) {
    s32 temp_v1;

    if (_Game_play_isPause(game_play) == 1) {
        return -1;
    }

    OCClearFunctionTable[arg2->prop.shape](game_play, arg2);

    if ((arg2->actor != NULL) && (arg2->actor->update == NULL)) {
        return -1;
    }

    if (arg1->ocColCount >= ARRAY_COUNT(arg1->ocColliders)) {
        return -1;
    }

    if (arg1->unk_00 & 1) {
        return -1;
    }

    temp_v1 = arg1->ocColCount;

    arg1->ocColliders[arg1->ocColCount] = arg2;
    arg1->ocColCount++;

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

    arg0->unk_4 = temp_t1;
    arg0->prop.ocFlags1 |= OC1_2;
    arg1->unk_0 |= 2;

    if (arg3->prop.ocFlags2 & OC2_TYPE_8) {
        arg0->prop.ocFlags2 |= OC2_1;
    }

    arg3->unk_4 = temp_t0;
    arg3->prop.ocFlags1 |= OC1_2;
    arg4->unk_0 |= 2;
    if (arg0->prop.ocFlags2 & OC2_TYPE_8) {
        arg3->prop.ocFlags2 |= OC2_1;
    }

    if ((temp_t0 == NULL) || (temp_t1 == NULL) || (arg0->prop.ocFlags1 & OC1_4) || (arg3->prop.ocFlags1 & OC1_4)) {
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

    if (arg0->prop.ocFlags1 & OC1_40) {
        var_fv1 = 0.0f;
        var_fa0 = 1.0f;
        temp_t1->speed = 0.0f;
    } else if (arg3->prop.ocFlags1 & OC1_40) {
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

void CollisionCheck_OC_JntSph_Vs_JntSph(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    ClObjJntSph* jntSphA = (ClObjJntSph*)arg2;
    ClObjJntSph* jntSphB = (ClObjJntSph*)arg3;
    ClObjJntSphElem* var_s0;
    ClObjJntSphElem* var_s4;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;

    if ((jntSphA->count <= 0) || (jntSphA->elements == NULL) || (jntSphB->count <= 0) || (jntSphB->elements == NULL)) {
        return;
    }

    for (var_s4 = jntSphA->elements; var_s4 < &jntSphA->elements[jntSphA->count]; var_s4++) {
        if (!(var_s4->unk_00.unk_0 & 1)) {
            continue;
        }

        for (var_s0 = jntSphB->elements; var_s0 < &jntSphB->elements[jntSphB->count]; var_s0++) {
            if (!(var_s0->unk_00.unk_0 & 1)) {
                continue;
            }

            if (Math3D_sphereCrossSphere_cl(&var_s4->unk_04.unk_08, &var_s0->unk_04.unk_08, &sp74) == 1) {
                xyz_t_move_s_xyz(&sp68, &var_s4->unk_04.unk_08.center);
                xyz_t_move_s_xyz(&sp5C, &var_s0->unk_04.unk_08.center);
                CollisionCheck_setOC_HitInfo(&jntSphA->base, &var_s4->unk_00, &sp68, &jntSphB->base, &var_s0->unk_00, &sp5C, sp74);
            }
        }
    }
}

void CollisionCheck_OC_JntSph_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)arg2;
    ClObjPipe* colPipe = (ClObjPipe*)arg3;
    ClObjJntSphElem* var_s0;

    if ((colJntSph->count <= 0) || (colJntSph->elements == NULL)) {
        return;
    }

    if (!(colJntSph->base.prop.ocFlags1 & OC1_1) || !(colPipe->base.prop.ocFlags1 & OC1_1) || !(colPipe->element.unk_0 & 1)) {
        return;
    }

    for (var_s0 = colJntSph->elements; var_s0 < &colJntSph->elements[colJntSph->count]; var_s0++) {
        f32 sp78;

        if (!(var_s0->unk_00.unk_0 & 1)) {
            continue;
        }

        if (Math3D_sphereVsPipe_cl(&var_s0->unk_04.unk_08, &colPipe->attribute.unk_0, &sp78) == 1) {
            Vec3f sp6C;
            Vec3f sp60;

            xyz_t_move_s_xyz(&sp6C, &var_s0->unk_04.unk_08.center);
            xyz_t_move_s_xyz(&sp60, &colPipe->attribute.unk_0.pos);
            CollisionCheck_setOC_HitInfo(&colJntSph->base, &var_s0->unk_00, &sp6C, &colPipe->base, &colPipe->element, &sp60, sp78);
        }
    }
}

void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    CollisionCheck_OC_JntSph_Vs_Pipe(game_play, arg1, arg3, arg2);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    ClObjPipe* pipeA = (ClObjPipe*)arg2;
    ClObjPipe* pipeB = (ClObjPipe*)arg3;
    f32 sp4C;
    Vec3f sp40;
    Vec3f sp34;

    if ((!(pipeA->base.prop.ocFlags1 & OC1_1) || !(pipeB->base.prop.ocFlags1 & OC1_1) || !(pipeA->element.unk_0 & 1) || !(pipeB->element.unk_0 & 1))) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipeA->attribute.unk_0, &pipeB->attribute.unk_0, &sp4C) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&sp40, &pipeA->attribute.unk_0.pos);
    xyz_t_move_s_xyz(&sp34, &pipeB->attribute.unk_0.pos);
    CollisionCheck_setOC_HitInfo(&pipeA->base, &pipeA->element, &sp40, &pipeB->base, &pipeB->element, &sp34, sp4C);
}

s32 CollisionCheck_Check1ClObjNoOC(ClObj* arg0) {
    if (!(arg0->prop.ocFlags1 & OC1_1)) {
        return 1;
    }
    return 0;
}

s32 CollisionCheck_Check2ClObjNoOC(ClObj* arg0, ClObj* arg1) {
    if (!(arg0->prop.ocFlags1 & arg1->prop.ocFlags2 & OC1_TYPE_ALL) || !(arg0->prop.ocFlags2 & arg1->prop.ocFlags1 & OC1_TYPE_ALL)) {
        return 1;
    }
    if (arg0->actor == arg1->actor) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OC(struct Game_Play* game_play, CollisionCheck* arg1) {
    ClObj** var_s2;

    for (var_s2 = arg1->ocColliders; var_s2 < &arg1->ocColliders[arg1->ocColCount]; var_s2++) {
        ClObj** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = var_s2 + 1; var_s0 < &arg1->ocColliders[arg1->ocColCount]; var_s0++) {
            CollisionVsFunc temp_v0;

            if ((*var_s0 == NULL) || (CollisionCheck_Check1ClObjNoOC(*var_s0) == 1) || (CollisionCheck_Check2ClObjNoOC(*var_s2, *var_s0) == 1)) {
                continue;
            }

            temp_v0 = oc_collision_function[(*var_s2)->prop.shape][(*var_s0)->prop.shape];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(game_play, arg1, *var_s2, *var_s0);
        }
    }

    CollisionCheck_OCC(game_play, arg1);
}

void CollisionCheck_setOCC_HitInfo(UNUSED struct Game_Play* game_play, ClObj* arg1, ClObjTrisElem* arg2, UNUSED Vec3f* arg3, ClObj* arg4, UNUSED ClObjElem* arg5, UNUSED Vec3f* arg6, Vec3f* arg7) {
    arg1->unk_4 = arg4->actor;
    arg1->prop.ocFlags2 |= OC2_4;
    arg2->unk_04.unk_34.x =  arg7->x;
    arg2->unk_04.unk_34.y =  arg7->y;
    arg2->unk_04.unk_34.z =  arg7->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    ClObjJntSphElem* var_s6;
    ClObjTris* colTris = (ClObjTris*)arg2;
    ClObjJntSph* colJntSph = (ClObjJntSph*)arg3;

    if ((colTris->count <= 0) || (colTris->elements == NULL) || (colJntSph->count <= 0) || (colJntSph->elements == NULL)) {
        return;
    }

    for (var_s6 = colJntSph->elements; var_s6 < &colJntSph->elements[colJntSph->count]; var_s6++) {
        ClObjTrisElem* var_s0;
        Vec3f sp74;

        if (!(var_s6->unk_00.unk_0 & 1)) {
            continue;
        }

        for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
            if (Math3D_sphereCrossTriangle3_cp(&var_s6->unk_04.unk_08, &var_s0->unk_04.unk_00, &sp74) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                xyz_t_move_s_xyz(&sp68, &var_s6->unk_04.unk_08.center);
                CollisionCheck_workTrisElemCenter(var_s0, &sp5C);
                CollisionCheck_setOCC_HitInfo(game_play, &colTris->base, var_s0, &sp5C, &colJntSph->base, &var_s6->unk_00, &sp68, &sp74);
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* arg2, ClObj* arg3) {
    ClObjTris* colTris = (ClObjTris*)arg2;
    ClObjPipe* colPipe = (ClObjPipe*)arg3;
    ClObjTrisElem* var_s0;

    if ((colPipe->attribute.unk_0.radius <= 0) || (colPipe->attribute.unk_0.unk_2 <= 0) || !(colPipe->element.unk_0 & 1)) {
        return;
    }

    if ((colTris->count <= 0) || (colTris->elements == NULL)) {
        return;
    }

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        Vec3f sp68;

        if (Math3D_pipeCrossTriangle_cp(&colPipe->attribute.unk_0, &var_s0->unk_04.unk_00.unk_00, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            CollisionCheck_workTrisElemCenter(var_s0, &sp50);
            xyz_t_move_s_xyz(&sp5C, &colPipe->attribute.unk_0.pos);
            CollisionCheck_setOCC_HitInfo(game_play, &colTris->base, var_s0, &sp50, &colPipe->base, &colPipe->element, &sp5C, &sp68);
            break;
        }
    }
}

s32 CollisionCheck_Check1ClObjNoOCC(ClObj* arg0) {
    if (!(arg0->prop.ocFlags2 & OC2_2)) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OCC(struct Game_Play* game_play, CollisionCheck* arg1) {
    ClObj** var_s2;

    if (mco_work.unk_00 == 0) {
        return;
    }

    for (var_s2 = mco_work.unk_04; var_s2 < &mco_work.unk_04[mco_work.unk_00]; var_s2++) {
        ClObj** var_s0;

        if ((*var_s2 == NULL) || (CollisionCheck_Check1ClObjNoOCC(*var_s2) == 1)) {
            continue;
        }

        for (var_s0 = arg1->ocColliders; var_s0 < &arg1->ocColliders[arg1->ocColCount]; var_s0++) {
            CollisionVsFunc temp_v0;

            if ((*var_s0) == NULL) {
                continue;
            }

            if ((*var_s2)->actor == (*var_s0)->actor) {
                continue;
            }

            temp_v0 = occ_collision_function[(*var_s2)->prop.shape][(*var_s0)->prop.shape];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(game_play, arg1, (*var_s2), (*var_s0));
        }
    }
}

s32 ClObjTrisElem_OCCClear(UNUSED struct Game_Play* game_play, ClObjTrisElem* arg1) {
    arg1->unk_04.unk_34.x = 0.0f;
    arg1->unk_04.unk_34.y = 0.0f;
    arg1->unk_04.unk_34.z = 0.0f;
    return 1;
}

void ClObj_OCCClear(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    arg1->unk_4 = NULL;
    arg1->prop.ocFlags2 &= ~OC2_4;
}

s32 ClObjTris_OCCClear(struct Game_Play* game_play, ClObj* arg1) {
    ClObjTris* colTris = (ClObjTris*)arg1;
    ClObjTrisElem* var_s0;

    ClObj_OCCClear(game_play, &colTris->base);

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        ClObjTrisElem_OCCClear(game_play, var_s0);
    }

    return 1;
}

s32 CollisionCheck_setOCC(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2) {
    s32 temp_v0;

    if (_Game_play_isPause(game_play) == 1) {
        return -1;
    }

    if ((arg2->prop.shape == COLSHAPE_JNTSPH) || (arg2->prop.shape == COLSHAPE_PIPE)) {
        return -1;
    }

    OCCClearFunctionTable[arg2->prop.shape](game_play, arg2);

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
    *status = status_org;
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

void CollisionCheck_Uty_ActorWorldPosSetPipeC(Actor* actor, ClObjPipe* colPipe) {
    colPipe->attribute.unk_0.pos.x = (s16) (s32) actor->world.pos.x;
    colPipe->attribute.unk_0.pos.y = (s16) (s32) actor->world.pos.y;
    colPipe->attribute.unk_0.pos.z = (s16) (s32) actor->world.pos.z;
}

s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* game_play, ClObjTris* colTris, s32 arg2, ClObjTrisElemAttr_Init* arg3) {
    ClObjTrisElem* temp = &colTris->elements[arg2];

    return ClObjTrisElemAttr_set(game_play, &temp->unk_04, arg3);
}
