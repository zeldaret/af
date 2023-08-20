#include "m_collision_obj.h"
#include "m_actor.h"
#include "m_lib.h"
#include "sys_math3d.h"
#include "libc/math.h"
#include "attributes.h"
#include "macros.h"

typedef struct struct_mco_work {
    /* 0x00 */ s32 count;
    /* 0x04 */ ClObj* coliders[10];
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
    arg1->x = (arg0->attr.unk_00.unk_00.vertices[0].x + arg0->attr.unk_00.unk_00.vertices[1].x + arg0->attr.unk_00.unk_00.vertices[2].x) * (1.0f / 3.0f);
    arg1->y = (arg0->attr.unk_00.unk_00.vertices[0].y + arg0->attr.unk_00.unk_00.vertices[1].y + arg0->attr.unk_00.unk_00.vertices[2].y) * (1.0f / 3.0f);
    arg1->z = (arg0->attr.unk_00.unk_00.vertices[0].z + arg0->attr.unk_00.unk_00.vertices[1].z + arg0->attr.unk_00.unk_00.vertices[2].z) * (1.0f / 3.0f);
}

s32 ClObj_ct(UNUSED struct Game_Play* game_play, ClObj* cl) {
    *cl = clobj_default;

    return 1;
}

s32 ClObj_dt(UNUSED struct Game_Play* game_play, UNUSED ClObj* cl) {
    return 1;
}

s32 ClObj_set4(UNUSED struct Game_Play* game_play, ClObj* cl, struct Actor* actor, ClObj_Properties* prop) {
    cl->actor = actor;
    cl->prop.ocFlags1 = prop->ocFlags1;
    cl->prop.ocFlags2 = prop->ocFlags2;
    cl->prop.shape = prop->shape;

    return 1;
}

void ClObj_OCClear(UNUSED struct Game_Play* game_play, ClObj* cl) {
    cl->oc = NULL;
    cl->prop.ocFlags1 &= ~OC1_2;
    cl->prop.ocFlags2 &= ~OC2_1;
}

s32 ClObjElem_ct(ClObjElem* elem) {
    elem->flags = ELEM_FLAG_NONE;

    return 1;
}

s32 ClObjElem_set(ClObjElem* dst, ClObjElem* src) {
    dst->flags = src->flags;

    return 1;
}

void ClObjElem_OCClear(UNUSED struct Game_Play* game_play, ClObjElem* elem) {
    elem->flags &= ~ELEM_FLAG_2;
}

s32 ClObjJntSphElemAttr_ct(UNUSED struct Game_Play* game_play, ClObjJntSphElemAttr* attr) {
    *attr = default_jntsphelem_attr;

    return 1;
}

s32 ClObjJntSphElemAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjJntSphElemAttr* attr) {
    return 1;
}

s32 ClObjJntSphElemAttr_set(UNUSED struct Game_Play* game_play, ClObjJntSphElemAttr* attr, ClObjJntSphElemAttr_Init* init) {
    attr->unk_14 = init->unk_0;
    attr->unk_00 = init->unk_2;
    attr->unk_10 = init->unk_A * 0.01f;

    return 1;
}

s32 ClObjJntSphElem_ct(struct Game_Play* game_play, ClObjJntSphElem* elem) {
    ClObjElem_ct(&elem->elem);
    ClObjJntSphElemAttr_ct(game_play, &elem->attr);

    return 1;
}

s32 ClObjJntSphElem_dt(struct Game_Play* game_play, ClObjJntSphElem* elem) {
    ClObjJntSphElemAttr_dt(game_play, &elem->attr);

    return 1;
}

s32 ClObjJntSphElem_set(struct Game_Play* game_play, ClObjJntSphElem* elem, ClObjJntSphElem_Init* init) {
    ClObjElem_set(&elem->elem, &init->elem);
    ClObjJntSphElemAttr_set(game_play, &elem->attr, &init->attr);

    return 1;
}

s32 ClObjJntSphElem_OCClear(struct Game_Play* game_play, ClObjJntSphElem* elem) {
    ClObjElem_OCClear(game_play, &elem->elem);

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

s32 ClObjJntSph_set5_nzm(struct Game_Play* game_play, ClObjJntSph* colJntSph, Actor* actor, ClObjJntSph_Init* init, ClObjJntSphElem elements[]) {
    ClObjJntSphElem_Init* elemInit;
    ClObjJntSphElem* elem;

    ClObj_set4(game_play, &colJntSph->base, actor, &init->prop);

    colJntSph->count = init->count;
    colJntSph->elements = elements;

    for (elem = colJntSph->elements, elemInit = init->elements; elem < &colJntSph->elements[colJntSph->count]; elem++, elemInit++) {
        ClObjJntSphElem_ct(game_play, elem);
        ClObjJntSphElem_set(game_play, elem, elemInit);
    }

    return 1;
}

s32 ClObjJntSph_OCClear(struct Game_Play* game_play, ClObj* cl) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl;
    ClObjJntSphElem* elem;

    ClObj_OCClear(game_play, &colJntSph->base);

    for (elem = colJntSph->elements; elem < &colJntSph->elements[colJntSph->count]; elem++) {
        ClObjJntSphElem_OCClear(game_play, elem);
    }

    return 1;
}

s32 ClObjPipeAttr_ct(UNUSED struct Game_Play* game_play, ClObjPipeAttr* attr) {
    *attr = default_pipe_attr;

    return 1;
}

s32 ClObjPipeAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjPipeAttr* attr) {
    return 1;
}

s32 ClObjPipeAttr_set(UNUSED struct Game_Play* game_play, ClObjPipeAttr* dst, ClObjPipeAttr* src) {
    *dst = *src;

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

s32 ClObjPipe_set5(struct Game_Play* game_play, ClObjPipe* colPipe, struct Actor* actor, ClObjPipe_Init* init) {
    ClObj_set4(game_play, &colPipe->base, actor, &init->prop);
    ClObjElem_set(&colPipe->element, &init->elem);
    ClObjPipeAttr_set(game_play, &colPipe->attribute, &init->attr);
    return 1;
}

s32 ClObjPipe_OCClear(struct Game_Play* game_play, ClObj* cl) {
    ClObjPipe* colPipe = (ClObjPipe*) cl;

    ClObj_OCClear(game_play, &colPipe->base);
    ClObjElem_OCClear(game_play, &colPipe->element);

    return 1;
}

s32 ClObjTrisElemAttr_ct(UNUSED struct Game_Play* game_play, ClObjTrisElemAttr* attr) {
    *attr = default_clobjtriselem_attr;

    return 1;
}

s32 ClObjTrisElemAttr_dt(UNUSED struct Game_Play* game_play, UNUSED ClObjTrisElemAttr* arg1) {
    return 1;
}

s32 ClObjTrisElemAttr_set(UNUSED struct Game_Play* game_play, ClObjTrisElemAttr* attr, ClObjTrisElemAttr_Init* init) {
    Vec3f* var_v0;
    Vec3f* var_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    for (var_v0 = attr->unk_00.unk_00.vertices, var_v1 = init->unk_00.vertices; var_v0 < &attr->unk_00.unk_00.vertices[ARRAY_COUNT(attr->unk_00.unk_00.vertices)]; var_v0++, var_v1++) {
        *var_v0 = *var_v1;
    }

    Math3DPlane(&init->unk_00.vertices[0], &init->unk_00.vertices[1], &init->unk_00.vertices[2], &sp44, &sp40, &sp3C, &sp38);
    attr->unk_00.unk_24.x = sp44;
    attr->unk_00.unk_24.y = sp40;
    attr->unk_00.unk_24.z = sp3C;
    attr->unk_00.unk_30 = sp38;

    return 1;
}

s32 ClObjTrisElem_ct(struct Game_Play* game_play, ClObjTrisElem* elem) {
    ClObjElem_ct(&elem->elem);
    ClObjTrisElemAttr_ct(game_play, &elem->attr);

    return 1;
}

s32 ClObjTrisElem_dt(struct Game_Play* game_play, ClObjTrisElem* elem) {
    ClObjTrisElemAttr_dt(game_play, &elem->attr);

    return 1;
}

s32 ClObjTrisElem_set(struct Game_Play* game_play, ClObjTrisElem* elem, ClObjTrisElem_Init* init) {
    ClObjElem_set(&elem->elem, &init->elem);
    ClObjTrisElemAttr_set(game_play, &elem->attr, &init->attr);

    return 1;
}

s32 ClObjTrisElem_OCClear(struct Game_Play* game_play, ClObjTrisElem* elem) {
    ClObjElem_OCClear(game_play, &elem->elem);

    return 1;
}

s32 ClObjTris_ct(struct Game_Play* game_play, ClObjTris* colTris) {
    ClObj_ct(game_play, &colTris->base);
    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_dt_nzf(struct Game_Play* game_play, ClObjTris* colTris) {
    ClObjTrisElem* element;

    ClObj_dt(game_play, &colTris->base);

    for (element = colTris->elements; element < &colTris->elements[colTris->count]; element++) {
        ClObjTrisElem_dt(game_play, element);
    }

    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_set5_nzm(struct Game_Play* game_play, ClObjTris* colTris, Actor* actor, ClObjTris_Init* init, ClObjTrisElem* elements) {
    ClObjTrisElem_Init* elemInit;
    ClObjTrisElem* element;

    ClObj_set4(game_play, &colTris->base, actor, &init->prop);

    colTris->count = init->count;
    colTris->elements = elements;

    for (element = elements, elemInit = init->elem; element <  &colTris->elements[colTris->count]; element++, elemInit++) {
        ClObjTrisElem_ct(game_play, element);
        ClObjTrisElem_set(game_play, element, elemInit);
    }

    return 1;
}

s32 ClObjTris_OCClear(struct Game_Play* game_play, ClObj* cl) {
    ClObjTris* colTris = (ClObjTris*)cl;
    ClObjTrisElem* var_s0;

    ClObj_OCClear(game_play, &colTris->base);

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        ClObjTrisElem_OCClear(game_play, var_s0);
    }

    return 1;
}

void CollisionCheck_ct(struct Game_Play* game_play, CollisionCheck* colCheck) {
    colCheck->flags = COLCHECK_FLAG_NONE;
    CollisionCheck_clear(game_play, colCheck);
}

void CollisionCheck_dt(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1) {
}

void CollisionCheck_clear(UNUSED struct Game_Play* game_play, CollisionCheck* arg1) {
    ClObj** var_v0;

    if (arg1->flags & COLCHECK_FLAG_1) {
        return;
    }

    arg1->ocColCount = 0;
    for (var_v0 = arg1->ocColliders; var_v0 < &arg1->ocColliders[ARRAY_COUNT(arg1->ocColliders)]; var_v0++) {
        *var_v0 = NULL;
    }

    mco_work.count = 0;
    for (var_v0 = mco_work.coliders; var_v0 < &mco_work.coliders[ARRAY_COUNT(mco_work.coliders)]; var_v0++) {
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

    if (arg1->flags & COLCHECK_FLAG_1) {
        return -1;
    }

    temp_v1 = arg1->ocColCount;

    arg1->ocColliders[arg1->ocColCount] = arg2;
    arg1->ocColCount++;

    return temp_v1;
}

ColMassType get_type(u8 arg0) {
    if (arg0 == MASS_IMMOVABLE) {
        return MASSTYPE_IMMOVABLE;
    }

    if (arg0 == MASS_HEAVY) {
        return MASSTYPE_HEAVY;
    }

    return MASSTYPE_NORMAL;
}

void CollisionCheck_setOC_HitInfo(ClObj* cl1, ClObjElem* clElem1, Vec3f* pos1, ClObj* cl2, ClObjElem* clElem2, Vec3f* pos2, f32 overlap) {
    f32 zDelta;
    f32 massInverse;
    f32 xDelta;
    f32 xzDist;
    f32 displacementRatio2;
    f32 mass1;
    f32 totalMass;
    f32 mass2;
    f32 displacementRatio1;
    UNUSED s32 pad;
    Actor* actor1 = cl1->actor;
    Actor* actor2 = cl2->actor;
    ColMassType massType2;
    ColMassType massType1;

    cl1->oc = actor2;
    cl1->prop.ocFlags1 |= OC1_2;
    clElem1->flags |= ELEM_FLAG_2;

    if (cl2->prop.ocFlags2 & OC2_TYPE_8) {
        cl1->prop.ocFlags2 |= OC2_1;
    }

    cl2->oc = actor1;
    cl2->prop.ocFlags1 |= OC1_2;
    clElem2->flags |= ELEM_FLAG_2;
    if (cl1->prop.ocFlags2 & OC2_TYPE_8) {
        cl2->prop.ocFlags2 |= OC2_1;
    }

    if ((actor1 == NULL) || (actor2 == NULL) || (cl1->prop.ocFlags1 & OC1_4) || (cl2->prop.ocFlags1 & OC1_4)) {
        return;
    }

    massType1 = get_type(actor1->colStatus.mass);
    massType2 = get_type(actor2->colStatus.mass);

    mass1 = actor1->colStatus.mass;
    mass2 = actor2->colStatus.mass;

    totalMass = mass1 + mass2;
    if (IS_ZERO(totalMass)) {
        mass1 = mass2 = 1.0f;
        totalMass = 2.0f;
    }

    xDelta = pos2->x - pos1->x;
    zDelta = pos2->z - pos1->z;
    xzDist = sqrtf(SQ(xDelta) + SQ(zDelta));

    if (massType1 == MASSTYPE_IMMOVABLE) {
        if (massType2 == MASSTYPE_IMMOVABLE) {
            return;
        }
        displacementRatio1 = 0.0f;
        displacementRatio2 = 1.0f;
    } else if (massType1 == MASSTYPE_HEAVY) {
        if (massType2 == MASSTYPE_IMMOVABLE) {
            displacementRatio1 = 1.0f;
            displacementRatio2 = 0.0f;
        } else if (massType2 == MASSTYPE_HEAVY) {
            displacementRatio1 = 0.5f;
            displacementRatio2 = 0.5f;
        } else {
            displacementRatio1 = 0.0f;
            displacementRatio2 = 1.0f;
        }
    } else {
        if (massType2 == MASSTYPE_NORMAL) {
            massInverse = 1.0f / totalMass;
            displacementRatio1 = mass2 * massInverse;
            displacementRatio2 = mass1 * massInverse;
        } else {
            displacementRatio1 = 1.0f;
            displacementRatio2 = 0.0f;
        }
    }

    if (cl1->prop.ocFlags1 & OC1_40) {
        displacementRatio1 = 0.0f;
        displacementRatio2 = 1.0f;
        actor2->speed = 0.0f;
    } else if (cl2->prop.ocFlags1 & OC1_40) {
        displacementRatio1 = 1.0f;
        displacementRatio2 = 0.0f;
        actor1->speed = 0.0f;
    }

    if (!IS_ZERO(xzDist)) {
        xDelta *= overlap / xzDist;
        zDelta *= overlap / xzDist;

        actor1->colStatus.displacement.x += -xDelta * displacementRatio1;
        actor1->colStatus.displacement.z += -zDelta * displacementRatio1;
        actor2->colStatus.displacement.x += xDelta * displacementRatio2;
        actor2->colStatus.displacement.z += zDelta * displacementRatio2;
    } else if (overlap != 0.0f) {
        actor1->colStatus.displacement.x += -overlap * displacementRatio1;
        actor2->colStatus.displacement.x += overlap * displacementRatio2;
    } else {
        actor1->colStatus.displacement.x -= displacementRatio1;
        actor2->colStatus.displacement.x += displacementRatio2;
    }
}

void CollisionCheck_OC_JntSph_Vs_JntSph(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* colCheck, ClObj* cl1, ClObj* cl2) {
    ClObjJntSph* jntSphA = (ClObjJntSph*)cl1;
    ClObjJntSph* jntSphB = (ClObjJntSph*)cl2;
    ClObjJntSphElem* var_s0;
    ClObjJntSphElem* var_s4;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;

    if ((jntSphA->count <= 0) || (jntSphA->elements == NULL) || (jntSphB->count <= 0) || (jntSphB->elements == NULL)) {
        return;
    }

    for (var_s4 = jntSphA->elements; var_s4 < &jntSphA->elements[jntSphA->count]; var_s4++) {
        if (!(var_s4->elem.flags & ELEM_FLAG_1)) {
            continue;
        }

        for (var_s0 = jntSphB->elements; var_s0 < &jntSphB->elements[jntSphB->count]; var_s0++) {
            if (!(var_s0->elem.flags & ELEM_FLAG_1)) {
                continue;
            }

            if (Math3D_sphereCrossSphere_cl(&var_s4->attr.unk_08, &var_s0->attr.unk_08, &sp74) == 1) {
                xyz_t_move_s_xyz(&sp68, &var_s4->attr.unk_08.center);
                xyz_t_move_s_xyz(&sp5C, &var_s0->attr.unk_08.center);
                CollisionCheck_setOC_HitInfo(&jntSphA->base, &var_s4->elem, &sp68, &jntSphB->base, &var_s0->elem, &sp5C, sp74);
            }
        }
    }
}

void CollisionCheck_OC_JntSph_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* colCheck, ClObj* cl1, ClObj* cl2) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl1;
    ClObjPipe* colPipe = (ClObjPipe*)cl2;
    ClObjJntSphElem* var_s0;

    if ((colJntSph->count <= 0) || (colJntSph->elements == NULL)) {
        return;
    }

    if (!(colJntSph->base.prop.ocFlags1 & OC1_1) || !(colPipe->base.prop.ocFlags1 & OC1_1) || !(colPipe->element.flags & ELEM_FLAG_1)) {
        return;
    }

    for (var_s0 = colJntSph->elements; var_s0 < &colJntSph->elements[colJntSph->count]; var_s0++) {
        f32 sp78;

        if (!(var_s0->elem.flags & ELEM_FLAG_1)) {
            continue;
        }

        if (Math3D_sphereVsPipe_cl(&var_s0->attr.unk_08, &colPipe->attribute.dim, &sp78) == 1) {
            Vec3f sp6C;
            Vec3f sp60;

            xyz_t_move_s_xyz(&sp6C, &var_s0->attr.unk_08.center);
            xyz_t_move_s_xyz(&sp60, &colPipe->attribute.dim.pos);
            CollisionCheck_setOC_HitInfo(&colJntSph->base, &var_s0->elem, &sp6C, &colPipe->base, &colPipe->element, &sp60, sp78);
        }
    }
}

void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, CollisionCheck* colCheck, ClObj* cl1, ClObj* cl2) {
    CollisionCheck_OC_JntSph_Vs_Pipe(game_play, colCheck, cl2, cl1);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(UNUSED struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* cl1, ClObj* cl2) {
    ClObjPipe* pipeA = (ClObjPipe*)cl1;
    ClObjPipe* pipeB = (ClObjPipe*)cl2;
    f32 sp4C;
    Vec3f sp40;
    Vec3f sp34;

    if ((!(pipeA->base.prop.ocFlags1 & OC1_1) || !(pipeB->base.prop.ocFlags1 & OC1_1) || !(pipeA->element.flags & ELEM_FLAG_1) || !(pipeB->element.flags & ELEM_FLAG_1))) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipeA->attribute.dim, &pipeB->attribute.dim, &sp4C) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&sp40, &pipeA->attribute.dim.pos);
    xyz_t_move_s_xyz(&sp34, &pipeB->attribute.dim.pos);
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

void CollisionCheck_OC(struct Game_Play* game_play, CollisionCheck* colCheck) {
    ClObj** cl1P;

    for (cl1P = colCheck->ocColliders; cl1P < &colCheck->ocColliders[colCheck->ocColCount]; cl1P++) {
        ClObj** cl2P;

        if ((*cl1P == NULL) || (CollisionCheck_Check1ClObjNoOC(*cl1P) == 1)) {
            continue;
        }

        for (cl2P = cl1P + 1; cl2P < &colCheck->ocColliders[colCheck->ocColCount]; cl2P++) {
            CollisionVsFunc temp_v0;

            if ((*cl2P == NULL) || (CollisionCheck_Check1ClObjNoOC(*cl2P) == 1) || (CollisionCheck_Check2ClObjNoOC(*cl1P, *cl2P) == 1)) {
                continue;
            }

            temp_v0 = oc_collision_function[(*cl1P)->prop.shape][(*cl2P)->prop.shape];
            if (temp_v0 == NULL) {
                continue;
            }

            temp_v0(game_play, colCheck, *cl1P, *cl2P);
        }
    }

    CollisionCheck_OCC(game_play, colCheck);
}

void CollisionCheck_setOCC_HitInfo(UNUSED struct Game_Play* game_play, ClObj* arg1, ClObjTrisElem* arg2, UNUSED Vec3f* arg3, ClObj* arg4, UNUSED ClObjElem* arg5, UNUSED Vec3f* arg6, Vec3f* arg7) {
    arg1->oc = arg4->actor;
    arg1->prop.ocFlags2 |= OC2_4;
    arg2->attr.unk_34.x =  arg7->x;
    arg2->attr.unk_34.y =  arg7->y;
    arg2->attr.unk_34.z =  arg7->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, UNUSED CollisionCheck* arg1, ClObj* cl1, ClObj* cl2) {
    ClObjJntSphElem* sphElem;
    ClObjTris* colTris = (ClObjTris*)cl1;
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl2;

    if ((colTris->count <= 0) || (colTris->elements == NULL) || (colJntSph->count <= 0) || (colJntSph->elements == NULL)) {
        return;
    }

    for (sphElem = colJntSph->elements; sphElem < &colJntSph->elements[colJntSph->count]; sphElem++) {
        ClObjTrisElem* trisElem;
        Vec3f sp74;

        if (!(sphElem->elem.flags & ELEM_FLAG_1)) {
            continue;
        }

        for (trisElem = colTris->elements; trisElem < &colTris->elements[colTris->count]; trisElem++) {
            if (Math3D_sphereCrossTriangle3_cp(&sphElem->attr.unk_08, &trisElem->attr.unk_00, &sp74) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                xyz_t_move_s_xyz(&sp68, &sphElem->attr.unk_08.center);
                CollisionCheck_workTrisElemCenter(trisElem, &sp5C);
                CollisionCheck_setOCC_HitInfo(game_play, &colTris->base, trisElem, &sp5C, &colJntSph->base, &sphElem->elem, &sp68, &sp74);
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, UNUSED CollisionCheck* colCheck, ClObj* cl1, ClObj* cl2) {
    ClObjTris* colTris = (ClObjTris*)cl1;
    ClObjPipe* colPipe = (ClObjPipe*)cl2;
    ClObjTrisElem* elem;

    if ((colPipe->attribute.dim.radius <= 0) || (colPipe->attribute.dim.unk_2 <= 0) || !(colPipe->element.flags & ELEM_FLAG_1)) {
        return;
    }

    if ((colTris->count <= 0) || (colTris->elements == NULL)) {
        return;
    }

    for (elem = colTris->elements; elem < &colTris->elements[colTris->count]; elem++) {
        Vec3f sp68;

        if (Math3D_pipeCrossTriangle_cp(&colPipe->attribute.dim, &elem->attr.unk_00.unk_00, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            CollisionCheck_workTrisElemCenter(elem, &sp50);
            xyz_t_move_s_xyz(&sp5C, &colPipe->attribute.dim.pos);
            CollisionCheck_setOCC_HitInfo(game_play, &colTris->base, elem, &sp50, &colPipe->base, &colPipe->element, &sp5C, &sp68);
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

void CollisionCheck_OCC(struct Game_Play* game_play, CollisionCheck* colCheck) {
    ClObj** cl1P;

    if (mco_work.count == 0) {
        return;
    }

    for (cl1P = mco_work.coliders; cl1P < &mco_work.coliders[mco_work.count]; cl1P++) {
        ClObj** cl2P;

        if ((*cl1P == NULL) || (CollisionCheck_Check1ClObjNoOCC(*cl1P) == 1)) {
            continue;
        }

        for (cl2P = colCheck->ocColliders; cl2P < &colCheck->ocColliders[colCheck->ocColCount]; cl2P++) {
            CollisionVsFunc func;

            if ((*cl2P) == NULL) {
                continue;
            }

            if ((*cl1P)->actor == (*cl2P)->actor) {
                continue;
            }

            func = occ_collision_function[(*cl1P)->prop.shape][(*cl2P)->prop.shape];
            if (func == NULL) {
                continue;
            }

            func(game_play, colCheck, *cl1P, *cl2P);
        }
    }
}

s32 ClObjTrisElem_OCCClear(UNUSED struct Game_Play* game_play, ClObjTrisElem* arg1) {
    arg1->attr.unk_34.x = 0.0f;
    arg1->attr.unk_34.y = 0.0f;
    arg1->attr.unk_34.z = 0.0f;
    return 1;
}

void ClObj_OCCClear(UNUSED struct Game_Play* game_play, ClObj* arg1) {
    arg1->oc = NULL;
    arg1->prop.ocFlags2 &= ~OC2_4;
}

s32 ClObjTris_OCCClear(struct Game_Play* game_play, ClObj* cl) {
    ClObjTris* colTris = (ClObjTris*)cl;
    ClObjTrisElem* elem;

    ClObj_OCCClear(game_play, &colTris->base);

    for (elem = colTris->elements; elem < &colTris->elements[colTris->count]; elem++) {
        ClObjTrisElem_OCCClear(game_play, elem);
    }

    return 1;
}

s32 CollisionCheck_setOCC(struct Game_Play* game_play, CollisionCheck* colCheck, ClObj* cl) {
    s32 ret;

    if (_Game_play_isPause(game_play) == 1) {
        return -1;
    }

    if ((cl->prop.shape == COLSHAPE_JNTSPH) || (cl->prop.shape == COLSHAPE_PIPE)) {
        return -1;
    }

    OCCClearFunctionTable[cl->prop.shape](game_play, cl);

    if ((cl->actor != NULL) && (cl->actor->update == NULL)) {
        return -1;
    }

    if (mco_work.count >= ARRAY_COUNT(mco_work.coliders)) {
        return -1;
    }

    if (colCheck->flags & COLCHECK_FLAG_1) {
        return -1;
    }

    ret = mco_work.count;
    mco_work.coliders[mco_work.count] = cl;
    mco_work.count++;

    return ret;
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

void CollisionCheck_Status_set3(CollisionCheck_Status* status, CollisionCheck_Status_Init* init) {
    status->unk_13 = init->unk_0;
    status->unk_0C = init->unk_2;
    status->unk_0E = init->unk_4;
    status->unk_10 = init->unk_6;
    status->mass = init->unk_8;
}

void CollisionCheck_Uty_ActorWorldPosSetPipeC(Actor* actor, ClObjPipe* colPipe) {
    colPipe->attribute.dim.pos.x = (s16) (s32) actor->world.pos.x;
    colPipe->attribute.dim.pos.y = (s16) (s32) actor->world.pos.y;
    colPipe->attribute.dim.pos.z = (s16) (s32) actor->world.pos.z;
}

s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* game_play, ClObjTris* colTris, s32 index, ClObjTrisElemAttr_Init* init) {
    ClObjTrisElem* temp = &colTris->elements[index];

    return ClObjTrisElemAttr_set(game_play, &temp->attr, init);
}
