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
    /* 0x4 */ struct Actor* oc;
    /* 0x8 */ ClObj_Properties prop;
} ClObj; // size = 0xC


typedef struct ClObjJntSphElemAttr_Init {
    /* 0x0 */ u8 unk_0;
    /* 0x2 */ Sphere unk_2;
    /* 0xC */ s16 unk_A;
} ClObjJntSphElemAttr_Init; // size = 0xC

typedef struct ClObjJntSphElem_Init {
    /* 0x0 */ ClObjElem elem;
    /* 0x2 */ ClObjJntSphElemAttr_Init attr;
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
} ClObjPipe_Init; // size = 0x10

typedef struct ClObjPipe {
    /* 0x00 */ ClObj base;
    /* 0x0C */ ClObjElem element;
    /* 0x0E */ ClObjPipeAttr attribute;
} ClObjPipe; // size = 0x1C



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
} ClObjTris_Init; // size = 0xX


typedef struct CollisionCheck {
    /* 0x00 */ u16 flags;
    /* 0x04 */ s32 ocColCount;
    /* 0x08 */ ClObj *ocColliders[50];
} CollisionCheck; // size = 0xD0


typedef struct CollisionCheck_Status_Init {
    /* 0x0 */ u8 unk_0;
    /* 0x0 */ s16 unk_2;
    /* 0x0 */ s16 unk_4;
    /* 0x0 */ s16 unk_6;
    /* 0x0 */ u8 mass;
} CollisionCheck_Status_Init; // size = 0xA

typedef struct CollisionCheck_Status {
    /* 0x00 */ Vec3f displacement;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 mass;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
} CollisionCheck_Status; // size = 0x18


#define COLCHECK_FLAG_NONE (0)
#define COLCHECK_FLAG_1    (1 << 0)

#define OC1_NONE        (0)
#define OC1_1           (1 << 0)
#define OC1_2           (1 << 1)
#define OC1_4           (1 << 2)
#define OC1_TYPE_8      (1 << 3)
#define OC1_TYPE_10     (1 << 4)
#define OC1_TYPE_20     (1 << 5)
#define OC1_40          (1 << 6)

#define OC1_TYPE_ALL (OC1_TYPE_8 | OC1_TYPE_10 | OC1_TYPE_20)

#define OC2_NONE        (0)
#define OC2_1           (1 << 0)
#define OC2_2           (1 << 1)
#define OC2_4           (1 << 2)
#define OC2_TYPE_8      OC1_TYPE_8
#define OC2_TYPE_10     OC1_TYPE_10
#define OC2_TYPE_20     OC1_TYPE_20


#define ELEM_FLAG_NONE   (0)
#define ELEM_FLAG_1      (1 << 0)
#define ELEM_FLAG_2      (1 << 1)


s32 ClObjJntSph_ct(struct Game_Play* game_play, ClObjJntSph* colJntSph);
s32 ClObjJntSph_dt_nzf(struct Game_Play* game_play, ClObjJntSph* colJntSph);
s32 ClObjJntSph_set5_nzm(struct Game_Play* game_play, ClObjJntSph* colJntSph, struct Actor* actor, ClObjJntSph_Init* init, ClObjJntSphElem elements[]);

s32 ClObjPipe_ct(struct Game_Play* game_play, ClObjPipe* colPipe);
s32 ClObjPipe_dt(struct Game_Play* game_play, ClObjPipe* colPipe);
s32 ClObjPipe_set5(struct Game_Play* game_play, ClObjPipe* colPipe, struct Actor* actor, ClObjPipe_Init* init);

s32 ClObjTris_ct(struct Game_Play* game_play, ClObjTris* colTris);
s32 ClObjTris_dt_nzf(struct Game_Play* game_play, ClObjTris* colTris);
s32 ClObjTris_set5_nzm(struct Game_Play* game_play, ClObjTris* colTris, struct Actor* actor, ClObjTris_Init* init, ClObjTrisElem elements[]);

void CollisionCheck_ct(struct Game_Play* game_play, CollisionCheck* colCheck);
void CollisionCheck_dt(struct Game_Play* game_play, CollisionCheck* arg1);
void CollisionCheck_clear(struct Game_Play* game_play, CollisionCheck* colCheck);

s32 CollisionCheck_setOC(struct Game_Play* game_play, CollisionCheck* colCheck, ClObj* cl);

void CollisionCheck_OC(struct Game_Play* game_play, CollisionCheck* colCheck);
void CollisionCheck_OCC(struct Game_Play* game_play, CollisionCheck* colCheck);

s32 CollisionCheck_setOCC(struct Game_Play* game_play, CollisionCheck* colCheck, ClObj* cl);

void CollisionCheck_Status_ct(CollisionCheck_Status* status);
void CollisionCheck_Status_Clear(CollisionCheck_Status* status);
void CollisionCheck_Status_set3(CollisionCheck_Status* status, CollisionCheck_Status_Init* init);

void CollisionCheck_Uty_ActorWorldPosSetPipeC(struct Actor* actor, ClObjPipe* colPipe);
s32 CollisionCheck_Uty_setTrisPos_ad(struct Game_Play* game_play, ClObjTris* colTris, s32 index, ClObjTrisElemAttr_Init* init);

#endif
