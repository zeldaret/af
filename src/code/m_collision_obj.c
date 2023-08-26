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

struct_mco_work mco_work;

typedef void (*CollisionVsFunc)(struct Game_Play*, CollisionCheck*, ClObj*, ClObj*);

typedef s32 (*ClearFunc)(struct Game_Play*, ClObj*);

void CollisionCheck_workTrisElemCenter(ClObjTrisElem* arg0, Vec3f* arg1) {
    arg1->x = (arg0->attr.unk_00.unk_00.vertices[0].x + arg0->attr.unk_00.unk_00.vertices[1].x +
               arg0->attr.unk_00.unk_00.vertices[2].x) *
              (1.0f / 3.0f);
    arg1->y = (arg0->attr.unk_00.unk_00.vertices[0].y + arg0->attr.unk_00.unk_00.vertices[1].y +
               arg0->attr.unk_00.unk_00.vertices[2].y) *
              (1.0f / 3.0f);
    arg1->z = (arg0->attr.unk_00.unk_00.vertices[0].z + arg0->attr.unk_00.unk_00.vertices[1].z +
               arg0->attr.unk_00.unk_00.vertices[2].z) *
              (1.0f / 3.0f);
}

ClObj clobj_default = { NULL, NULL, { OC1_NONE, OC2_NONE, COLSHAPE_MAX } };

s32 ClObj_ct(UNUSED struct Game_Play* gamePlay, ClObj* cl) {
    *cl = clobj_default;

    return 1;
}

s32 ClObj_dt(UNUSED struct Game_Play* gamePlay, UNUSED ClObj* cl) {
    return 1;
}

s32 ClObj_set4(UNUSED struct Game_Play* gamePlay, ClObj* cl, struct Actor* actor, ClObj_Properties* prop) {
    cl->actor = actor;
    cl->prop.ocFlags1 = prop->ocFlags1;
    cl->prop.ocFlags2 = prop->ocFlags2;
    cl->prop.shape = prop->shape;

    return 1;
}

void ClObj_OCClear(UNUSED struct Game_Play* gamePlay, ClObj* cl) {
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

void ClObjElem_OCClear(UNUSED struct Game_Play* gamePlay, ClObjElem* elem) {
    elem->flags &= ~ELEM_FLAG_2;
}

ClObjJntSphElemAttr default_jntsphelem_attr = { { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, 0.0f, 0 };

s32 ClObjJntSphElemAttr_ct(UNUSED struct Game_Play* gamePlay, ClObjJntSphElemAttr* attr) {
    *attr = default_jntsphelem_attr;

    return 1;
}

s32 ClObjJntSphElemAttr_dt(UNUSED struct Game_Play* gamePlay, UNUSED ClObjJntSphElemAttr* attr) {
    return 1;
}

s32 ClObjJntSphElemAttr_set(UNUSED struct Game_Play* gamePlay, ClObjJntSphElemAttr* attr,
                            ClObjJntSphElemAttr_Init* init) {
    attr->unk_14 = init->unk_0;
    attr->unk_00 = init->unk_2;
    attr->unk_10 = init->unk_A * 0.01f;

    return 1;
}

s32 ClObjJntSphElem_ct(struct Game_Play* gamePlay, ClObjJntSphElem* elem) {
    ClObjElem_ct(&elem->elem);
    ClObjJntSphElemAttr_ct(gamePlay, &elem->attr);

    return 1;
}

s32 ClObjJntSphElem_dt(struct Game_Play* gamePlay, ClObjJntSphElem* elem) {
    ClObjJntSphElemAttr_dt(gamePlay, &elem->attr);

    return 1;
}

s32 ClObjJntSphElem_set(struct Game_Play* gamePlay, ClObjJntSphElem* elem, ClObjJntSphElem_Init* init) {
    ClObjElem_set(&elem->elem, &init->elem);
    ClObjJntSphElemAttr_set(gamePlay, &elem->attr, &init->attr);

    return 1;
}

s32 ClObjJntSphElem_OCClear(struct Game_Play* gamePlay, ClObjJntSphElem* elem) {
    ClObjElem_OCClear(gamePlay, &elem->elem);

    return 1;
}

s32 ClObjJntSph_ct(struct Game_Play* gamePlay, ClObjJntSph* colJntSph) {
    ClObj_ct(gamePlay, &colJntSph->base);
    colJntSph->count = 0;
    colJntSph->elements = NULL;

    return 1;
}

s32 ClObjJntSph_dt_nzf(struct Game_Play* gamePlay, ClObjJntSph* colJntSph) {
    ClObjJntSphElem* element;

    ClObj_dt(gamePlay, &colJntSph->base);

    for (element = colJntSph->elements; element < &colJntSph->elements[colJntSph->count]; element++) {
        ClObjJntSphElem_dt(gamePlay, element);
    }

    colJntSph->count = 0;
    colJntSph->elements = NULL;

    return 1;
}

s32 ClObjJntSph_set5_nzm(struct Game_Play* gamePlay, ClObjJntSph* colJntSph, Actor* actor, ClObjJntSph_Init* init,
                         ClObjJntSphElem elements[]) {
    ClObjJntSphElem_Init* elemInit;
    ClObjJntSphElem* elem;

    ClObj_set4(gamePlay, &colJntSph->base, actor, &init->prop);

    colJntSph->count = init->count;
    colJntSph->elements = elements;

    for (elem = colJntSph->elements, elemInit = init->elements; elem < &colJntSph->elements[colJntSph->count];
         elem++, elemInit++) {
        ClObjJntSphElem_ct(gamePlay, elem);
        ClObjJntSphElem_set(gamePlay, elem, elemInit);
    }

    return 1;
}

s32 ClObjJntSph_OCClear(struct Game_Play* gamePlay, ClObj* cl) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl;
    ClObjJntSphElem* elem;

    ClObj_OCClear(gamePlay, &colJntSph->base);

    for (elem = colJntSph->elements; elem < &colJntSph->elements[colJntSph->count]; elem++) {
        ClObjJntSphElem_OCClear(gamePlay, elem);
    }

    return 1;
}

ClObjPipeAttr default_pipe_attr = { { 0, 0, 0, { 0, 0, 0 } } };

s32 ClObjPipeAttr_ct(UNUSED struct Game_Play* gamePlay, ClObjPipeAttr* attr) {
    *attr = default_pipe_attr;

    return 1;
}

s32 ClObjPipeAttr_dt(UNUSED struct Game_Play* gamePlay, UNUSED ClObjPipeAttr* attr) {
    return 1;
}

s32 ClObjPipeAttr_set(UNUSED struct Game_Play* gamePlay, ClObjPipeAttr* dst, ClObjPipeAttr* src) {
    *dst = *src;

    return 1;
}

s32 ClObjPipe_ct(struct Game_Play* gamePlay, ClObjPipe* colPipe) {
    ClObj_ct(gamePlay, &colPipe->base);
    ClObjElem_ct(&colPipe->element);
    ClObjPipeAttr_ct(gamePlay, &colPipe->attribute);

    return 1;
}

s32 ClObjPipe_dt(struct Game_Play* gamePlay, ClObjPipe* colPipe) {
    ClObj_dt(gamePlay, &colPipe->base);
    ClObjPipeAttr_dt(gamePlay, &colPipe->attribute);

    return 1;
}

s32 ClObjPipe_set5(struct Game_Play* gamePlay, ClObjPipe* colPipe, struct Actor* actor, ClObjPipe_Init* init) {
    ClObj_set4(gamePlay, &colPipe->base, actor, &init->prop);
    ClObjElem_set(&colPipe->element, &init->elem);
    ClObjPipeAttr_set(gamePlay, &colPipe->attribute, &init->attr);
    return 1;
}

s32 ClObjPipe_OCClear(struct Game_Play* gamePlay, ClObj* cl) {
    ClObjPipe* colPipe = (ClObjPipe*)cl;

    ClObj_OCClear(gamePlay, &colPipe->base);
    ClObjElem_OCClear(gamePlay, &colPipe->element);

    return 1;
}

ClObjTrisElemAttr default_clobjtriselem_attr = {
    {
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
    },
    { 0.0f, 0.0f, 0.0f },
};

s32 ClObjTrisElemAttr_ct(UNUSED struct Game_Play* gamePlay, ClObjTrisElemAttr* attr) {
    *attr = default_clobjtriselem_attr;

    return 1;
}

s32 ClObjTrisElemAttr_dt(UNUSED struct Game_Play* gamePlay, UNUSED ClObjTrisElemAttr* attr) {
    return 1;
}

s32 ClObjTrisElemAttr_set(UNUSED struct Game_Play* gamePlay, ClObjTrisElemAttr* attr, ClObjTrisElemAttr_Init* init) {
    Vec3f* var_v0;
    Vec3f* var_v1;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    for (var_v0 = attr->unk_00.unk_00.vertices, var_v1 = init->unk_00.vertices;
         var_v0 < &attr->unk_00.unk_00.vertices[ARRAY_COUNT(attr->unk_00.unk_00.vertices)]; var_v0++, var_v1++) {
        *var_v0 = *var_v1;
    }

    Math3DPlane(&init->unk_00.vertices[0], &init->unk_00.vertices[1], &init->unk_00.vertices[2], &sp44, &sp40, &sp3C,
                &sp38);
    attr->unk_00.unk_24.x = sp44;
    attr->unk_00.unk_24.y = sp40;
    attr->unk_00.unk_24.z = sp3C;
    attr->unk_00.unk_30 = sp38;

    return 1;
}

s32 ClObjTrisElem_ct(struct Game_Play* gamePlay, ClObjTrisElem* elem) {
    ClObjElem_ct(&elem->elem);
    ClObjTrisElemAttr_ct(gamePlay, &elem->attr);

    return 1;
}

s32 ClObjTrisElem_dt(struct Game_Play* gamePlay, ClObjTrisElem* elem) {
    ClObjTrisElemAttr_dt(gamePlay, &elem->attr);

    return 1;
}

s32 ClObjTrisElem_set(struct Game_Play* gamePlay, ClObjTrisElem* elem, ClObjTrisElem_Init* init) {
    ClObjElem_set(&elem->elem, &init->elem);
    ClObjTrisElemAttr_set(gamePlay, &elem->attr, &init->attr);

    return 1;
}

s32 ClObjTrisElem_OCClear(struct Game_Play* gamePlay, ClObjTrisElem* elem) {
    ClObjElem_OCClear(gamePlay, &elem->elem);

    return 1;
}

s32 ClObjTris_ct(struct Game_Play* gamePlay, ClObjTris* colTris) {
    ClObj_ct(gamePlay, &colTris->base);
    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_dt_nzf(struct Game_Play* gamePlay, ClObjTris* colTris) {
    ClObjTrisElem* element;

    ClObj_dt(gamePlay, &colTris->base);

    for (element = colTris->elements; element < &colTris->elements[colTris->count]; element++) {
        ClObjTrisElem_dt(gamePlay, element);
    }

    colTris->count = 0;
    colTris->elements = NULL;

    return 1;
}

s32 ClObjTris_set5_nzm(struct Game_Play* gamePlay, ClObjTris* colTris, Actor* actor, ClObjTris_Init* init,
                       ClObjTrisElem* elements) {
    ClObjTrisElem_Init* elemInit;
    ClObjTrisElem* element;

    ClObj_set4(gamePlay, &colTris->base, actor, &init->prop);

    colTris->count = init->count;
    colTris->elements = elements;

    for (element = elements, elemInit = init->elem; element < &colTris->elements[colTris->count];
         element++, elemInit++) {
        ClObjTrisElem_ct(gamePlay, element);
        ClObjTrisElem_set(gamePlay, element, elemInit);
    }

    return 1;
}

s32 ClObjTris_OCClear(struct Game_Play* gamePlay, ClObj* cl) {
    ClObjTris* colTris = (ClObjTris*)cl;
    ClObjTrisElem* var_s0;

    ClObj_OCClear(gamePlay, &colTris->base);

    for (var_s0 = colTris->elements; var_s0 < &colTris->elements[colTris->count]; var_s0++) {
        ClObjTrisElem_OCClear(gamePlay, var_s0);
    }

    return 1;
}

void CollisionCheck_ct(struct Game_Play* gamePlay, CollisionCheck* colCheck) {
    colCheck->flags = COLCHECK_FLAG_NONE;
    CollisionCheck_clear(gamePlay, colCheck);
}

void CollisionCheck_dt(UNUSED struct Game_Play* gamePlay, UNUSED CollisionCheck* colCheck) {
}

void CollisionCheck_clear(UNUSED struct Game_Play* gamePlay, CollisionCheck* colCheck) {
    ClObj** clP;

    if (colCheck->flags & COLCHECK_FLAG_1) {
        return;
    }

    colCheck->ocColCount = 0;
    for (clP = colCheck->ocColliders; clP < &colCheck->ocColliders[ARRAY_COUNT(colCheck->ocColliders)]; clP++) {
        *clP = NULL;
    }

    mco_work.count = 0;
    for (clP = mco_work.coliders; clP < &mco_work.coliders[ARRAY_COUNT(mco_work.coliders)]; clP++) {
        *clP = NULL;
    }
}

ClearFunc OCClearFunctionTable[COLSHAPE_MAX] = {
    ClObjJntSph_OCClear, // COLSHAPE_JNTSPH
    ClObjPipe_OCClear,   // COLSHAPE_PIPE
    ClObjTris_OCClear,   // COLSHAPE_TRIS
};

s32 CollisionCheck_setOC(struct Game_Play* gamePlay, CollisionCheck* colCheck, ClObj* cl) {
    s32 index;

    if (_Game_play_isPause(gamePlay) == 1) {
        return -1;
    }

    OCClearFunctionTable[cl->prop.shape](gamePlay, cl);

    if ((cl->actor != NULL) && (cl->actor->update == NULL)) {
        return -1;
    }

    if (colCheck->ocColCount >= ARRAY_COUNT(colCheck->ocColliders)) {
        return -1;
    }

    if (colCheck->flags & COLCHECK_FLAG_1) {
        return -1;
    }

    index = colCheck->ocColCount;
    colCheck->ocColliders[colCheck->ocColCount] = cl;
    colCheck->ocColCount++;

    return index;
}

ColMassType get_type(u8 mass) {
    if (mass == MASS_IMMOVABLE) {
        return MASSTYPE_IMMOVABLE;
    }

    if (mass == MASS_HEAVY) {
        return MASSTYPE_HEAVY;
    }

    return MASSTYPE_NORMAL;
}

void CollisionCheck_setOC_HitInfo(ClObj* cl1, ClObjElem* clElem1, Vec3f* pos1, ClObj* cl2, ClObjElem* clElem2,
                                  Vec3f* pos2, f32 overlap) {
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

void CollisionCheck_OC_JntSph_Vs_JntSph(UNUSED struct Game_Play* gamePlay, UNUSED CollisionCheck* colCheck, ClObj* cl1,
                                        ClObj* cl2) {
    ClObjJntSph* jntSph1 = (ClObjJntSph*)cl1;
    ClObjJntSph* jntSph2 = (ClObjJntSph*)cl2;
    ClObjJntSphElem* elem1;
    ClObjJntSphElem* elem2;

    if ((jntSph1->count <= 0) || (jntSph1->elements == NULL) || (jntSph2->count <= 0) || (jntSph2->elements == NULL)) {
        return;
    }

    for (elem1 = jntSph1->elements; elem1 < &jntSph1->elements[jntSph1->count]; elem1++) {
        if (!(elem1->elem.flags & ELEM_FLAG_1)) {
            continue;
        }

        for (elem2 = jntSph2->elements; elem2 < &jntSph2->elements[jntSph2->count]; elem2++) {
            f32 overlap;

            if (!(elem2->elem.flags & ELEM_FLAG_1)) {
                continue;
            }

            if (Math3D_sphereCrossSphere_cl(&elem1->attr.unk_08, &elem2->attr.unk_08, &overlap) == 1) {
                Vec3f pos1;
                Vec3f pos2;

                xyz_t_move_s_xyz(&pos1, &elem1->attr.unk_08.center);
                xyz_t_move_s_xyz(&pos2, &elem2->attr.unk_08.center);
                CollisionCheck_setOC_HitInfo(&jntSph1->base, &elem1->elem, &pos1, &jntSph2->base, &elem2->elem, &pos2,
                                             overlap);
            }
        }
    }
}

void CollisionCheck_OC_JntSph_Vs_Pipe(UNUSED struct Game_Play* gamePlay, UNUSED CollisionCheck* colCheck, ClObj* cl1,
                                      ClObj* cl2) {
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl1;
    ClObjPipe* colPipe = (ClObjPipe*)cl2;
    ClObjJntSphElem* sphElem;

    if ((colJntSph->count <= 0) || (colJntSph->elements == NULL)) {
        return;
    }

    if (!(colJntSph->base.prop.ocFlags1 & OC1_1) || !(colPipe->base.prop.ocFlags1 & OC1_1) ||
        !(colPipe->element.flags & ELEM_FLAG_1)) {
        return;
    }

    for (sphElem = colJntSph->elements; sphElem < &colJntSph->elements[colJntSph->count]; sphElem++) {
        f32 overlap;

        if (!(sphElem->elem.flags & ELEM_FLAG_1)) {
            continue;
        }

        if (Math3D_sphereVsPipe_cl(&sphElem->attr.unk_08, &colPipe->attribute.dim, &overlap) == 1) {
            Vec3f sphPos;
            Vec3f pipePos;

            xyz_t_move_s_xyz(&sphPos, &sphElem->attr.unk_08.center);
            xyz_t_move_s_xyz(&pipePos, &colPipe->attribute.dim.pos);
            CollisionCheck_setOC_HitInfo(&colJntSph->base, &sphElem->elem, &sphPos, &colPipe->base, &colPipe->element,
                                         &pipePos, overlap);
        }
    }
}

void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* gamePlay, CollisionCheck* colCheck, ClObj* cl1, ClObj* cl2) {
    CollisionCheck_OC_JntSph_Vs_Pipe(gamePlay, colCheck, cl2, cl1);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(UNUSED struct Game_Play* gamePlay, UNUSED CollisionCheck* colCheck, ClObj* cl1,
                                    ClObj* cl2) {
    ClObjPipe* pipe1 = (ClObjPipe*)cl1;
    ClObjPipe* pipe2 = (ClObjPipe*)cl2;
    f32 overlap;
    Vec3f pos1;
    Vec3f pos2;

    if ((!(pipe1->base.prop.ocFlags1 & OC1_1) || !(pipe2->base.prop.ocFlags1 & OC1_1) ||
         !(pipe1->element.flags & ELEM_FLAG_1) || !(pipe2->element.flags & ELEM_FLAG_1))) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipe1->attribute.dim, &pipe2->attribute.dim, &overlap) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&pos1, &pipe1->attribute.dim.pos);
    xyz_t_move_s_xyz(&pos2, &pipe2->attribute.dim.pos);
    CollisionCheck_setOC_HitInfo(&pipe1->base, &pipe1->element, &pos1, &pipe2->base, &pipe2->element, &pos2, overlap);
}

s32 CollisionCheck_Check1ClObjNoOC(ClObj* cl) {
    if (!(cl->prop.ocFlags1 & OC1_1)) {
        return 1;
    }
    return 0;
}

s32 CollisionCheck_Check2ClObjNoOC(ClObj* cl1, ClObj* cl2) {
    if (!(cl1->prop.ocFlags1 & cl2->prop.ocFlags2 & OC1_TYPE_ALL) ||
        !(cl1->prop.ocFlags2 & cl2->prop.ocFlags1 & OC1_TYPE_ALL)) {
        return 1;
    }
    if (cl1->actor == cl2->actor) {
        return 1;
    }
    return 0;
}

CollisionVsFunc oc_collision_function[COLSHAPE_MAX][COLSHAPE_MAX] = {
    { CollisionCheck_OC_JntSph_Vs_JntSph, CollisionCheck_OC_JntSph_Vs_Pipe, NULL }, // COLSHAPE_JNTSPH
    { CollisionCheck_OC_Pipe_Vs_JntSph, CollisionCheck_OC_Pipe_Vs_Pipe, NULL },     // COLSHAPE_PIPE
    { NULL, NULL, NULL },                                                           // COLSHAPE_TRIS
};

void CollisionCheck_OC(struct Game_Play* gamePlay, CollisionCheck* colCheck) {
    ClObj** cl1P;

    for (cl1P = colCheck->ocColliders; cl1P < &colCheck->ocColliders[colCheck->ocColCount]; cl1P++) {
        ClObj** cl2P;

        if ((*cl1P == NULL) || (CollisionCheck_Check1ClObjNoOC(*cl1P) == 1)) {
            continue;
        }

        for (cl2P = cl1P + 1; cl2P < &colCheck->ocColliders[colCheck->ocColCount]; cl2P++) {
            CollisionVsFunc func;

            if ((*cl2P == NULL) || (CollisionCheck_Check1ClObjNoOC(*cl2P) == 1) ||
                (CollisionCheck_Check2ClObjNoOC(*cl1P, *cl2P) == 1)) {
                continue;
            }

            func = oc_collision_function[(*cl1P)->prop.shape][(*cl2P)->prop.shape];
            if (func == NULL) {
                continue;
            }

            func(gamePlay, colCheck, *cl1P, *cl2P);
        }
    }

    CollisionCheck_OCC(gamePlay, colCheck);
}

void CollisionCheck_setOCC_HitInfo(UNUSED struct Game_Play* gamePlay, ClObj* cl1, ClObjTrisElem* trisElem,
                                   UNUSED Vec3f* arg3, ClObj* cl2, UNUSED ClObjElem* arg5, UNUSED Vec3f* arg6,
                                   Vec3f* arg7) {
    cl1->oc = cl2->actor;
    cl1->prop.ocFlags2 |= OC2_4;

    trisElem->attr.unk_34.x = arg7->x;
    trisElem->attr.unk_34.y = arg7->y;
    trisElem->attr.unk_34.z = arg7->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* gamePlay, UNUSED CollisionCheck* arg1, ClObj* cl1,
                                       ClObj* cl2) {
    ClObjJntSphElem* sphElem;
    ClObjTris* colTris = (ClObjTris*)cl1;
    ClObjJntSph* colJntSph = (ClObjJntSph*)cl2;

    if ((colTris->count <= 0) || (colTris->elements == NULL) || (colJntSph->count <= 0) ||
        (colJntSph->elements == NULL)) {
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
                Vec3f sphPos;
                Vec3f trisPos;

                xyz_t_move_s_xyz(&sphPos, &sphElem->attr.unk_08.center);
                CollisionCheck_workTrisElemCenter(trisElem, &trisPos);
                CollisionCheck_setOCC_HitInfo(gamePlay, &colTris->base, trisElem, &trisPos, &colJntSph->base,
                                              &sphElem->elem, &sphPos, &sp74);
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* gamePlay, UNUSED CollisionCheck* colCheck, ClObj* cl1,
                                     ClObj* cl2) {
    ClObjTris* colTris = (ClObjTris*)cl1;
    ClObjPipe* colPipe = (ClObjPipe*)cl2;
    ClObjTrisElem* elem;

    if ((colPipe->attribute.dim.radius <= 0) || (colPipe->attribute.dim.unk_2 <= 0) ||
        !(colPipe->element.flags & ELEM_FLAG_1)) {
        return;
    }

    if ((colTris->count <= 0) || (colTris->elements == NULL)) {
        return;
    }

    for (elem = colTris->elements; elem < &colTris->elements[colTris->count]; elem++) {
        Vec3f sp68;

        if (Math3D_pipeCrossTriangle_cp(&colPipe->attribute.dim, &elem->attr.unk_00.unk_00, &sp68) != 0) {
            Vec3f pipePos;
            Vec3f trisPos;

            CollisionCheck_workTrisElemCenter(elem, &trisPos);
            xyz_t_move_s_xyz(&pipePos, &colPipe->attribute.dim.pos);
            CollisionCheck_setOCC_HitInfo(gamePlay, &colTris->base, elem, &trisPos, &colPipe->base, &colPipe->element,
                                          &pipePos, &sp68);
            break;
        }
    }
}

s32 CollisionCheck_Check1ClObjNoOCC(ClObj* cl) {
    if (!(cl->prop.ocFlags2 & OC2_2)) {
        return 1;
    }
    return 0;
}

CollisionVsFunc occ_collision_function[COLSHAPE_MAX][COLSHAPE_MAX] = {
    { NULL, NULL, NULL },                                                         // COLSHAPE_JNTSPH
    { NULL, NULL, NULL },                                                         // COLSHAPE_PIPE
    { CollisionCheck_OCC_Tris_Vs_JntSph, CollisionCheck_OCC_Tris_Vs_Pipe, NULL }, // COLSHAPE_TRIS
};

void CollisionCheck_OCC(struct Game_Play* gamePlay, CollisionCheck* colCheck) {
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

            func(gamePlay, colCheck, *cl1P, *cl2P);
        }
    }
}

s32 ClObjTrisElem_OCCClear(UNUSED struct Game_Play* gamePlay, ClObjTrisElem* arg1) {
    arg1->attr.unk_34.x = 0.0f;
    arg1->attr.unk_34.y = 0.0f;
    arg1->attr.unk_34.z = 0.0f;
    return 1;
}

void ClObj_OCCClear(UNUSED struct Game_Play* gamePlay, ClObj* arg1) {
    arg1->oc = NULL;
    arg1->prop.ocFlags2 &= ~OC2_4;
}

s32 ClObjTris_OCCClear(struct Game_Play* gamePlay, ClObj* cl) {
    ClObjTris* colTris = (ClObjTris*)cl;
    ClObjTrisElem* elem;

    ClObj_OCCClear(gamePlay, &colTris->base);

    for (elem = colTris->elements; elem < &colTris->elements[colTris->count]; elem++) {
        ClObjTrisElem_OCCClear(gamePlay, elem);
    }

    return 1;
}

ClearFunc OCCClearFunctionTable[COLSHAPE_MAX] = {
    NULL,               // COLSHAPE_JNTSPH
    NULL,               // COLSHAPE_PIPE
    ClObjTris_OCCClear, // COLSHAPE_TRIS
};

s32 CollisionCheck_setOCC(struct Game_Play* gamePlay, CollisionCheck* colCheck, ClObj* cl) {
    s32 ret;

    if (_Game_play_isPause(gamePlay) == 1) {
        return -1;
    }

    if ((cl->prop.shape == COLSHAPE_JNTSPH) || (cl->prop.shape == COLSHAPE_PIPE)) {
        return -1;
    }

    OCCClearFunctionTable[cl->prop.shape](gamePlay, cl);

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

CollisionCheck_Status status_org = { { 0.0f, 0.0f, 0.0f }, 0xA, 0xA, 0, 50, 8, 0, 0, 0, 0 };

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
    status->mass = init->mass;
}

void CollisionCheck_Uty_ActorWorldPosSetPipeC(Actor* actor, ClObjPipe* colPipe) {
    colPipe->attribute.dim.pos.x = (s16)(s32)actor->world.pos.x;
    colPipe->attribute.dim.pos.y = (s16)(s32)actor->world.pos.y;
    colPipe->attribute.dim.pos.z = (s16)(s32)actor->world.pos.z;
}

s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* gamePlay, ClObjTris* colTris, s32 index,
                                     ClObjTrisElemAttr_Init* init) {
    ClObjTrisElem* temp = &colTris->elements[index];

    return ClObjTrisElemAttr_set(gamePlay, &temp->attr, init);
}
