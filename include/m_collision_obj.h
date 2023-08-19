#ifndef M_COLLISION_OBJ_H
#define M_COLLISION_OBJ_H

#include "ultra64.h"
#include "sys_math3d.h"
#include "z64math.h"
#include "unk.h"

struct Actor;
struct Game_Play;


typedef enum ColliderShape {
    /* 0 */ COLSHAPE_JNTSPH,
    /* 1 */ COLSHAPE_PIPE,
    /* 2 */ COLSHAPE_TRIS,
    /* 3 */ COLSHAPE_MAX
} ColliderShape;

#define MASS_IMMOVABLE 0xFF
#define MASS_HEAVY 0xFE

typedef enum ColMassType {
    /* 0 */ MASSTYPE_IMMOVABLE,
    /* 1 */ MASSTYPE_HEAVY,
    /* 2 */ MASSTYPE_NORMAL
} ColMassType;


typedef struct ClObjElem {
    /* 0x0 */ u8 flags;
} ClObjElem; // size = 0x1


typedef struct ClObj_Properties {
    /* 0x0 */ u8 ocFlags1;
    /* 0x1 */ u8 ocFlags2;
    /* 0x2 */ u8 shape;
} ClObj_Properties; // size = 0x3

typedef struct ClObj {
    /* 0x0 */ struct Actor* actor;
    /* 0x4 */ struct Actor* unk_4;
    /* 0x8 */ ClObj_Properties prop;
} ClObj; // size = 0xC


typedef struct ClObjJntSphElemAttr_Init {
    /* 0x0 */ u8 unk_0;
    /* 0x2 */ Sphere unk_2;
    /* 0xC */ s16 unk_A;
} ClObjJntSphElemAttr_Init; // size = 0xC

typedef struct ClObjJntSphElem_Init {
    /* 0x0 */ ClObjElem unk_0;
    /* 0x2 */ ClObjJntSphElemAttr_Init unk_2;
} ClObjJntSphElem_Init; // size = 0xE

typedef struct ClObjJntSph_Init {
    /* 0x0 */ ClObj_Properties prop;
    /* 0x4 */ s32 count;
    /* 0x8 */ ClObjJntSphElem_Init* elements;
} ClObjJntSph_Init; // size = 0xC



typedef struct ClObjJntSphElemAttr {
    /* 0x00 */ Sphere unk_00;
    /* 0x08 */ Sphere unk_08;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u8 unk_14;
} ClObjJntSphElemAttr; // size = 0x18

typedef struct ClObjJntSphElem {
    /* 0x00 */ ClObjElem elem;
    /* 0x04 */ ClObjJntSphElemAttr attr;
} ClObjJntSphElem; // size = 0x1C


typedef struct ClObjJntSph {
    /* 0x00 */ ClObj base;
    /* 0x0C */ s32 count;
    /* 0x10 */ ClObjJntSphElem* elements;
} ClObjJntSph; // size = 0x14



typedef struct ClObjPipeAttr {
    /* 0x0 */ Pipe dim;
} ClObjPipeAttr; // size = 0xC

typedef struct ClObjPipe_Init {
    /* 0x0 */ ClObj_Properties prop;
    /* 0x3 */ ClObjElem elem;
    /* 0x4 */ ClObjPipeAttr attr;
} ClObjPipe_Init; // size >= 0x10

typedef struct ClObjPipe {
    /* 0x00 */ ClObj base;
    /* 0x0C */ ClObjElem element;
    /* 0x0E */ ClObjPipeAttr attribute;
} ClObjPipe; // size >= 0x1C



typedef struct ClObjTrisElemAttr_Init {
    /* 0x00 */ Triangle unk_00;
} ClObjTrisElemAttr_Init; // size = 0x24


typedef struct ClObjTrisElemAttr {
    /* 0x00 */ Triangle3 unk_00;
    /* 0x34 */ Vec3f unk_34;
} ClObjTrisElemAttr; // size = 0x40


typedef struct ClObjTrisElem {
    /* 0x00 */ ClObjElem elem;
    /* 0x04 */ ClObjTrisElemAttr attr;
} ClObjTrisElem; // size = 0x44

typedef struct ClObjTris {
    /* 0x00 */ ClObj base;
    /* 0x0C */ s32 count;
    /* 0x10 */ ClObjTrisElem* elements;
} ClObjTris; // size = 0x14


typedef struct ClObjTrisElem_Init {
    /* 0x00 */ ClObjElem elem;
    /* 0x04 */ ClObjTrisElemAttr_Init attr;
} ClObjTrisElem_Init; // size = 0x28

typedef struct ClObjTris_Init {
    /* 0x0 */ ClObj_Properties prop;
    /* 0x4 */ s32 count;
    /* 0x8 */ ClObjTrisElem_Init* elem;
} ClObjTris_Init; // size >= 0x


typedef struct CollisionCheck {
    /* 0x00 */ u16 unk_00;
    /* 0x04 */ s32 ocColCount;
    /* 0x08 */ ClObj *ocColliders[50];
} CollisionCheck; // size = 0xD0


typedef struct CollisionCheck_Status_Init {
    /* 0x0 */ u8 unk_0;
    /* 0x0 */ s16 unk_2;
    /* 0x0 */ s16 unk_4;
    /* 0x0 */ s16 unk_6;
    /* 0x0 */ u8 unk_8;
} CollisionCheck_Status_Init; // size = 0xA

typedef struct CollisionCheck_Status {
    /* 0x00 */ Vec3f displacement;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
} CollisionCheck_Status; // size = 0x18


#define OC1_NONE        0
#define OC1_1           (1 << 0)
#define OC1_2           (1 << 1)
#define OC1_4           (1 << 2)
#define OC1_TYPE_8      (1 << 3)
#define OC1_TYPE_10     (1 << 4)
#define OC1_TYPE_20     (1 << 5)
#define OC1_40          (1 << 6)

#define OC1_TYPE_ALL (OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20)

#define OC2_NONE        0
#define OC2_1           (1 << 0)
#define OC2_2           (1 << 1)
#define OC2_4           (1 << 2)
#define OC2_TYPE_8      OC1_TYPE_8
#define OC2_TYPE_10     OC1_TYPE_10
#define OC2_TYPE_20     OC1_TYPE_20


#define ELEM_FLAG_NONE   0
#define ELEM_FLAG_1      (1 << 0)
#define ELEM_FLAG_2      (1 << 1)


void CollisionCheck_workTrisElemCenter(ClObjTrisElem* arg0, Vec3f* arg1);
s32 ClObj_ct(struct Game_Play* game_play, ClObj* arg1);
s32 ClObj_dt(struct Game_Play* game_play, ClObj* arg1);
s32 ClObj_set4(struct Game_Play* game_play, ClObj* arg1, struct Actor* actor, ClObj_Properties* arg3);
void ClObj_OCClear(struct Game_Play* game_play, ClObj* arg1);
s32 ClObjElem_ct(ClObjElem* arg0);
s32 ClObjElem_set(ClObjElem* arg0, ClObjElem* arg1);
void ClObjElem_OCClear(struct Game_Play* game_play, ClObjElem* arg1);
s32 ClObjJntSphElemAttr_ct(struct Game_Play* game_play, ClObjJntSphElemAttr* arg1);
s32 ClObjJntSphElemAttr_dt(struct Game_Play* game_play, ClObjJntSphElemAttr* arg1);
s32 ClObjJntSphElemAttr_set(struct Game_Play* game_play, ClObjJntSphElemAttr* arg1, ClObjJntSphElemAttr_Init* arg2);
s32 ClObjJntSphElem_ct(struct Game_Play* game_play, ClObjJntSphElem* arg1);
s32 ClObjJntSphElem_dt(struct Game_Play* game_play, ClObjJntSphElem* arg1);
s32 ClObjJntSphElem_set(struct Game_Play* game_play, ClObjJntSphElem* arg1, ClObjJntSphElem_Init* arg2);
s32 ClObjJntSphElem_OCClear(struct Game_Play* game_play, ClObjJntSphElem* arg1);
s32 ClObjJntSph_ct(struct Game_Play* game_play, ClObjJntSph* jntSph);
s32 ClObjJntSph_dt_nzf(struct Game_Play* game_play, ClObjJntSph* jntSph);
s32 ClObjJntSph_set5_nzm(struct Game_Play* game_play, ClObjJntSph* jntSph, struct Actor* actor, ClObjJntSph_Init* arg3, ClObjJntSphElem arg4[]);
s32 ClObjJntSph_OCClear(struct Game_Play* game_play, ClObj*);
s32 ClObjPipeAttr_ct(struct Game_Play* game_play, ClObjPipeAttr* arg1);
s32 ClObjPipeAttr_dt(struct Game_Play* game_play, ClObjPipeAttr* arg1);
s32 ClObjPipeAttr_set(struct Game_Play* game_play, ClObjPipeAttr* arg1, ClObjPipeAttr* arg2);
s32 ClObjPipe_ct(struct Game_Play* game_play, ClObjPipe* pipe);
s32 ClObjPipe_dt(struct Game_Play* game_play, ClObjPipe* pipe);
s32 ClObjPipe_set5(struct Game_Play* game_play, ClObjPipe* pipe, struct Actor* actor, ClObjPipe_Init* arg3);
s32 ClObjPipe_OCClear(struct Game_Play* game_play, ClObj* arg1);
s32 ClObjTrisElemAttr_ct(struct Game_Play* game_play, ClObjTrisElemAttr* arg1);
s32 ClObjTrisElemAttr_dt(struct Game_Play* game_play, ClObjTrisElemAttr* arg1);
s32 ClObjTrisElemAttr_set(struct Game_Play* game_play, ClObjTrisElemAttr *arg1, ClObjTrisElemAttr_Init* arg2);
s32 ClObjTrisElem_ct(struct Game_Play* game_play, ClObjTrisElem* arg1);
s32 ClObjTrisElem_dt(struct Game_Play* game_play, ClObjTrisElem* arg1);
s32 ClObjTrisElem_set(struct Game_Play* game_play, ClObjTrisElem* arg1, ClObjTrisElem_Init* arg2);
s32 ClObjTrisElem_OCClear(struct Game_Play* game_play, ClObjTrisElem* arg1);
s32 ClObjTris_ct(struct Game_Play* game_play, ClObjTris* tris);
s32 ClObjTris_dt_nzf(struct Game_Play* game_play, ClObjTris* tris);
s32 ClObjTris_set5_nzm(struct Game_Play* game_play, ClObjTris* tris, struct Actor* actor, ClObjTris_Init* arg3, ClObjTrisElem arg4[]);
s32 ClObjTris_OCClear(struct Game_Play* game_play, ClObj* arg1);
void CollisionCheck_ct(struct Game_Play* game_play, CollisionCheck* arg1);
void CollisionCheck_dt(struct Game_Play* game_play, CollisionCheck* arg1);
void CollisionCheck_clear(struct Game_Play* game_play, CollisionCheck* arg1);
s32 CollisionCheck_setOC(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2);
// s32 get_type(u8 arg0);
void CollisionCheck_setOC_HitInfo(ClObj* arg0, ClObjElem* arg1, Vec3f* arg2, ClObj* arg3, ClObjElem* arg4, Vec3f* arg5, f32 arg6);
void CollisionCheck_OC_JntSph_Vs_JntSph(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
void CollisionCheck_OC_JntSph_Vs_Pipe(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
void CollisionCheck_OC_Pipe_Vs_Pipe(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
s32 CollisionCheck_Check1ClObjNoOC(ClObj* arg0);
s32 CollisionCheck_Check2ClObjNoOC(ClObj* arg0, ClObj* arg1);
void CollisionCheck_OC(struct Game_Play* game_play, CollisionCheck* arg1);
void CollisionCheck_setOCC_HitInfo(struct Game_Play* game_play, ClObj* arg1, ClObjTrisElem* arg2, Vec3f* arg3, ClObj* arg4, ClObjElem* arg5, Vec3f* arg6, Vec3f* arg7);
void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2, ClObj* arg3);
s32 CollisionCheck_Check1ClObjNoOCC(ClObj* arg0);
void CollisionCheck_OCC(struct Game_Play* game_play, CollisionCheck* arg1);
s32 ClObjTrisElem_OCCClear(struct Game_Play* game_play, ClObjTrisElem*);
void ClObj_OCCClear(struct Game_Play* game_play, ClObj* arg1);
s32 ClObjTris_OCCClear(struct Game_Play* game_play, ClObj* arg1);
s32 CollisionCheck_setOCC(struct Game_Play* game_play, CollisionCheck* arg1, ClObj* arg2);
void CollisionCheck_Status_ct(CollisionCheck_Status* status);
void CollisionCheck_Status_Clear(CollisionCheck_Status* status);
void CollisionCheck_Status_set3(CollisionCheck_Status* status, CollisionCheck_Status_Init* arg1);
void CollisionCheck_Uty_ActorWorldPosSetPipeC(struct Actor* actor, ClObjPipe* pipe);
s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* game_play, ClObjTris* tris, s32 arg2, ClObjTrisElemAttr_Init* arg3);

#endif
