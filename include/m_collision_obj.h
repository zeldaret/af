#ifndef M_COLLISION_OBJ_H
#define M_COLLISION_OBJ_H

#include "ultra64.h"
#include "sys_math3d.h"
#include "z64math.h"
#include "unk.h"

struct Actor;
struct Game_Play;


typedef struct CollisionCheck_Status {
    /* 0x00 */ Vec3f displacement;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x8];
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
} CollisionCheck_Status; // size = 0x18

typedef struct ClObjElem {
    /* 0x0 */ u8 unk_0;
} ClObjElem; // size = 0x1


typedef struct Game_Play2138_unk_08 {
    /* 0x00 */ struct Actor* actor;
    /* 0x00 */ struct Actor* unk_04;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
} Game_Play2138_unk_08; // size >= 0xB, size <= 0xC

typedef struct JntSph_unk_10 {
    /* 0x00 */ ClObjElem unk_00;
    /* 0x01 */ UNK_TYPE1 unk_01[0x3];
    /* 0x04 */ UNK_TYPE1 unk_04[0x8];
    /* 0x0C */ Vec3s unk_0C;
    /* 0x12 */ UNK_TYPE1 unk_12[0x2];
    /* 0x14 */ UNK_TYPE1 unk_14[0x8];
} JntSph_unk_10; // size = 0x1C

// TODO: rename
typedef struct JntSph {
    /* 0x00 */ Game_Play2138_unk_08 unk_00;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ JntSph_unk_10* unk_10;
} JntSph; // size >= 0x14

typedef Math3D_pipeCrossTriangle_cp_arg0 ClObjPipeAttr_set_arg2;

// TODO: rename
typedef struct Pipe {
    /* 0x00 */ Game_Play2138_unk_08 unk_00;
    /* 0x0C */ ClObjElem unk_0C;
    /* 0x0D */ UNK_TYPE1 unk_0D[0x1];
    /* 0x0E */ Math3D_pipeCrossTriangle_cp_arg0 unk_0E;
} Pipe; // size >= 0x1C


typedef struct ClObjTris_set5_nzm_arg3_unk_8_unk_04 {
    /* 0x00 */ Vec3f unk_00[3];
} ClObjTris_set5_nzm_arg3_unk_8_unk_04; // size >= 0x24


typedef struct ClObjTrisElemAttr {
    /* 0x00 */ ClObjTris_set5_nzm_arg3_unk_8_unk_04 unk_00;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ Vec3f unk_34;
} ClObjTrisElemAttr; // size = 0x40


typedef struct Tris_unk_10 {
    /* 0x00 */ ClObjElem unk_00;
    /* 0x01 */ UNK_TYPE1 unk_01[0x03];
    /* 0x04 */ ClObjTrisElemAttr unk_04;
} Tris_unk_10; // size = 0x44

// TODO: rename
typedef struct Tris {
    /* 0x00 */ Game_Play2138_unk_08 unk_00;
    /* 0x0C */ UNK_TYPE unk_0C;
    /* 0x10 */ Tris_unk_10* unk_10;
} Tris; // size >= 0x14

typedef struct Game_Play2138 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ UNK_TYPE1 unk_02[0x2];
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ Game_Play2138_unk_08 *unk_08[50];
} Game_Play2138; // size = 0xD0

typedef struct ClObj_set4_arg3 {
    /* 0x0 */ u8 unk_0;
    /* 0x1 */ u8 unk_1;
    /* 0x2 */ u8 unk_2;
} ClObj_set4_arg3; // size >= 0x3

typedef struct ClObjPipe_set5_arg3 {
    /* 0x0 */ ClObj_set4_arg3 unk_0;
    /* 0x3 */ ClObjElem unk_3;
    /* 0x4 */ ClObjPipeAttr_set_arg2 unk_4;
} ClObjPipe_set5_arg3; // size >= 0x10

typedef struct ClObjTris_set5_nzm_arg3_unk_8 {
    /* 0x00 */ ClObjElem unk_00;
    /* 0x01 */ UNK_TYPE1 unk_01[0x3];
    /* 0x04 */ ClObjTris_set5_nzm_arg3_unk_8_unk_04 unk_04;
} ClObjTris_set5_nzm_arg3_unk_8; // size = 0x28

typedef struct ClObjTris_set5_nzm_arg3 {
    /* 0x0 */ ClObj_set4_arg3 unk_0;
    /* 0x4 */ s32 unk_4;
    /* 0x8 */ ClObjTris_set5_nzm_arg3_unk_8* unk_8;
} ClObjTris_set5_nzm_arg3; // size >= 0x

// void CollisionCheck_workTrisElemCenter();
s32 ClObj_ct(struct Game_Play* game_play, Game_Play2138_unk_08* arg1);
// void func_80076BD4_jp();
s32 ClObj_set4(struct Game_Play* game_play, Game_Play2138_unk_08* arg1, struct Actor* actor, ClObj_set4_arg3* arg3);
// void func_80076C14_jp();
s32 ClObjElem_ct(ClObjElem* arg0);
s32 ClObjElem_set(ClObjElem* arg0, ClObjElem* arg1);
// void func_80076C60_jp();
// void func_80076C78_jp();
// void func_80076CC0_jp();
// void func_80076CD4_jp();
// void func_80076D2C_jp();
// void func_80076D68_jp();
// void func_80076D90_jp();
// void func_80076DDC_jp();
// void func_80076E00_jp();
// void func_80076E2C_jp();
// void func_80076ED0_jp();
s32 ClObjJntSph_OCClear(struct Game_Play* game_play, Game_Play2138*);
s32 ClObjPipeAttr_ct(struct Game_Play* game_play, Math3D_pipeCrossTriangle_cp_arg0* arg1);
// void func_80077078_jp();
// s32 ClObjPipeAttr_set(struct Game_Play* game_play, s16* arg1, ClObjPipeAttr_set_arg2* arg2);
s32 ClObjPipe_ct(struct Game_Play* game_play, Pipe* pipe);
s32 ClObjPipe_dt(struct Game_Play* game_play, Pipe* pipe);
s32 ClObjPipe_set5(struct Game_Play* game_play, Pipe* pipe, struct Actor* actor, ClObjPipe_set5_arg3* arg3);
s32 ClObjPipe_OCClear(struct Game_Play* game_play, Game_Play2138* arg1);
s32 ClObjTrisElemAttr_ct(struct Game_Play* game_play, ClObjTrisElemAttr* arg1);
// void func_80077248_jp();
s32 ClObjTrisElemAttr_set(struct Game_Play* game_play, ClObjTrisElemAttr *arg1, ClObjTris_set5_nzm_arg3_unk_8_unk_04* arg2);
s32 ClObjTrisElem_ct(struct Game_Play* game_play, Tris_unk_10* arg1);
// void func_8007734C_jp();
s32 ClObjTrisElem_set(struct Game_Play* game_play, Tris_unk_10* arg1, ClObjTris_set5_nzm_arg3_unk_8* arg2);
// void func_800773C0_jp();
s32 ClObjTris_ct(struct Game_Play* game_play, Tris* tris);
// void func_80077410_jp();
s32 ClObjTris_set5_nzm(struct Game_Play* game_play, Tris* tris, struct Actor* actor, ClObjTris_set5_nzm_arg3* arg3, Tris_unk_10* arg4);
s32 ClObjTris_OCClear(struct Game_Play* game_play, Game_Play2138* arg1);
void func_80077620_jp(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_dt(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_clear(struct Game_Play* game_play, Game_Play2138* arg1);
s32 CollisionCheck_setOC(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2);
// void get_type();
void CollisionCheck_setOC_HitInfo(Game_Play2138_unk_08* arg0, ClObjElem* arg1, Vec3f* arg2, Game_Play2138_unk_08* arg3, ClObjElem* arg4, Vec3f* arg5, f32 arg6);
void CollisionCheck_OC_JntSph_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_JntSph_Vs_Pipe(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_Pipe_Vs_Pipe(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
s32 CollisionCheck_Check1ClObjNoOC(Game_Play2138_unk_08* arg0);
s32 CollisionCheck_Check2ClObjNoOC(Game_Play2138_unk_08* arg0, Game_Play2138_unk_08* arg1);
void CollisionCheck_OC(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_setOCC_HitInfo(struct Game_Play* game_play, Game_Play2138_unk_08* arg1, Tris_unk_10* arg2, Vec3f* arg3, Game_Play2138_unk_08* arg4, ClObjElem* arg5, Vec3f* arg6, Vec3f* arg7);
void CollisionCheck_OCC_Tris_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OCC_Tris_Vs_Pipe(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
s32 CollisionCheck_Check1ClObjNoOCC(Game_Play2138_unk_08* arg0);
void CollisionCheck_OCC(struct Game_Play* game_play, Game_Play2138* arg1);
// void func_8007870C_jp();
// void func_8007872C_jp();
// void func_80078748_jp();
// void func_800787E8_jp();
void CollisionCheck_Status_ct(CollisionCheck_Status* status);
void CollisionCheck_Status_Clear(CollisionCheck_Status* status);
// void CollisionCheck_Status_set3();
// void CollisionCheck_Uty_ActorWorldPosSetPipeC();
// void func_800789BC_jp();

#endif
