#ifndef M_COLLISION_OBJ_H
#define M_COLLISION_OBJ_H

#include "ultra64.h"
#include "z64math.h"
#include "unk.h"


typedef struct CollisionCheck_Status {
    /* 0x00 */ Vec3f displacement;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x8];
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
} CollisionCheck_Status; // size = 0x18


typedef struct Game_Play2138_unk_08 {
    /* 0x00 */ UNK_TYPE4 unk_00;
    /* 0x00 */ UNK_TYPE1 unk_04[0x4];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
} Game_Play2138_unk_08; // size >= 0xB, size <= 0xC

typedef struct JntSph_unk_10 {
    /* 0x00 */ u8 unk_00;
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

// TODO: rename
typedef struct Pipe {
    /* 0x00 */ Game_Play2138_unk_08 unk_00;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ UNK_TYPE1 unk_0D[0x1];
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ UNK_TYPE1 unk_12[0x2];
    /* 0x14 */ Vec3s unk_14;
} Pipe; // size >= 0x1C


typedef struct Tris_unk_10 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x04];
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ UNK_TYPE1 unk_28[0x1C];
} Tris_unk_10; // size = 0x44

// TODO: rename
typedef struct Tris {
    /* 0x00 */ Game_Play2138_unk_08 unk_00;

    UNK_TYPE unk_0C;
    Tris_unk_10* unk_10;
} Tris; // size >= 0x

typedef struct Game_Play2138 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ UNK_TYPE1 unk_02[0x2];
    /* 0x04 */ UNK_TYPE4 unk_04;
    /* 0x08 */ Game_Play2138_unk_08 *unk_08[50];
} Game_Play2138; // size = 0xD0

struct Game_Play;

// void CollisionCheck_workTrisElemCenter();
// void func_80076BA4_jp();
// void func_80076BD4_jp();
// void func_80076BE8_jp();
// void func_80076C14_jp();
// void func_80076C3C_jp();
// void func_80076C4C_jp();
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
// void func_80076F9C_jp();
// void func_8007703C_jp();
// void func_80077078_jp();
// void func_8007708C_jp();
// void func_800770CC_jp();
// void func_80077118_jp();
// void func_80077158_jp();
// void func_800771BC_jp();
// void func_800771FC_jp();
// void func_80077248_jp();
// void func_8007725C_jp();
// void func_80077310_jp();
// void func_8007734C_jp();
// void func_80077374_jp();
// void func_800773C0_jp();
// void func_800773E4_jp();
// void func_80077410_jp();
// void func_800774B4_jp();
// void func_80077580_jp();
void func_80077620_jp(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_dt(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_clear(struct Game_Play* game_play, Game_Play2138* arg1);
// void CollisionCheck_setOC();
// void get_type();
void CollisionCheck_setOC_HitInfo(Game_Play2138_unk_08* arg0, u8* arg1, Vec3f* arg2, Game_Play2138_unk_08* arg3, u8* arg4, Vec3f* arg5, f32 arg6);
void CollisionCheck_OC_JntSph_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_JntSph_Vs_Pipe(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_Pipe_Vs_JntSph(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
void CollisionCheck_OC_Pipe_Vs_Pipe(struct Game_Play* game_play, Game_Play2138* arg1, Game_Play2138_unk_08* arg2, Game_Play2138_unk_08* arg3);
s32 CollisionCheck_Check1ClObjNoOC(Game_Play2138_unk_08* arg0);
s32 CollisionCheck_Check2ClObjNoOC(Game_Play2138_unk_08* arg0, Game_Play2138_unk_08* arg1);
void CollisionCheck_OC(struct Game_Play* game_play, Game_Play2138* arg1);
void CollisionCheck_setOCC_HitInfo(struct Game_Play* game_play, Game_Play2138_unk_08* arg1, Tris_unk_10* arg2, Vec3f* arg3, Game_Play2138_unk_08* arg4, u8* arg5, Vec3f* arg6, Vec3f* arg7);
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
