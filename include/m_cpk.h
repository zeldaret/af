#ifndef M_CPK_H
#define M_CPK_H

#include "ultra64.h"
#include "unk.h"

struct Animal_c;
struct PrivateInfo;

// For alignment this can only have members of size 1 or 2
typedef struct D80104798Struct {
    /* 0x0 */ UNK_TYPE1 unk0[0x10];
} D80104798Struct; // size 0x10

typedef struct PakInfo74Struct {
    /* 0x00 */ UNK_TYPE1 unk_00[0xE];
    /* 0x0E */ D80104798Struct unk_0E;
    /* 0x1E */ UNK_TYPE1 unk_1E[0x2];
} PakInfo74Struct; // size = 0x20

// Same as PakInfo74Struct?
typedef struct PakInfo94Struct {
    /* 0x00 */ UNK_TYPE1 unk_00[0x20];
} PakInfo94Struct; // size = 0x20

typedef struct B80137C40Struct {
    /* 0x0000 */ UNK_TYPE1 unk_0000[0x1200];
    /* 0x1200 */ UNK_TYPE unk_1200;
    /* 0x1204 */ UNK_TYPE unk_1204;
    /* 0x1208 */ u16 unk_1208;
} B80137C40Struct; // size = 0x1208

typedef struct PakInfo {
    /* 0x00 */ UNK_TYPE unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x6C];
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ PakInfo74Struct unk_74;
    /* 0x90 */ PakInfo94Struct unk_94[16];
} PakInfo; // size >= 0x294

s32 mCPk_PakOpen(PakInfo* info, s32 arg1);
// void func_80078EB4_jp();
// void func_80078EE0_jp();
// void func_80078F08_jp();
// void func_80078F34_jp();
// void func_80078FE8_jp();
// void func_80079030_jp();
void func_80079080_jp(B80137C40Struct* arg0);
UNK_RET mCPk_InitPak(UNK_TYPE arg0);
// void func_8007919C_jp();
// void func_8007920C_jp();
// void func_800792FC_jp();
// void func_80079378_jp();
// void func_800793A8_jp();
s32 mCPk_SavePak(struct PrivateInfo*, struct Animal_c*, PakInfo*);
s32 func_8007942C_jp(struct PrivateInfo*, struct Animal_c*, PakInfo*);
// void func_800794E4_jp();
// void func_8007967C_jp();
// void func_80079708_jp();
// void func_80079760_jp();
// void func_80079838_jp();
// void func_800798DC_jp();
// void func_80079A24_jp();
// void func_80079AAC_jp();
// void func_80079B28_jp();
// void func_80079BF8_jp();
// void func_80079D00_jp();
// void func_80079D50_jp();
// void func_80079E14_jp();
// void func_80079E54_jp();
// void func_80079EA4_jp();
// void func_80079EDC_jp();
// void func_80079F44_jp();
// void func_8007A008_jp();
PakInfo* mCPk_get_pkinfo(void);
// void func_8007A080_jp();

#endif
