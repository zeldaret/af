#ifndef M_CPAK_H
#define M_CPAK_H

#include "ultra64.h"
#include "unk.h"

#include "m_npc.h"
#include "m_private.h"

typedef struct Passport {
    /* 0x0000 */ u16 unk_0000;
    /* 0x0002 */ UNK_TYPE1 unk_0002[0x0006];
    /* 0x0008 */ PrivateInfo priv;
    /* 0x0BD8 */ Animal_c animal;
    /* 0x1100 */ u16 unk_1100;
    /* 0x1102 */ UNK_TYPE1 unk_1102[0x00FE];
} Passport; // size = 0x1200

typedef struct PakCtrl {
    /* 0x0000 */ Passport passport;
    /* 0x1200 */ OSMesgQueue* queue;
    /* 0x1204 */ UNK_TYPE unk_1204;
    /* 0x1208 */ u16 unk_1208;
} PakCtrl; // size = 0x1208

typedef struct D801047A8Struct {
    /* 0x0 */ UNK_TYPE1 unk_0[0x08];
} D801047A8Struct; // size <= 0x8

typedef struct D801047B0Struct {
    /* 0x0000 */ u16 unk_0000;
    /* 0x0002 */ UNK_TYPE1 unk_0002[0x66FE];
} D801047B0Struct; // size = 0x6700;

typedef struct OSPfsInfo {
    /* 0x00 */ OSPfs pfs;
    /* 0x68 */ s32 fileNo;
    /* 0x6C */ s32 err;
} OSPfsInfo; // size = 0x70

typedef struct PakInfo {
    /* 0x000 */ UNK_TYPE unk_00;
    /* 0x004 */ OSPfsInfo pfsInfo;
    /* 0x074 */ OSPfsState pfsState;
    /* 0x094 */ OSPfsState unk_94[16];
    /* 0x294 */ s32 unk_294[16];
    /* 0x2D4 */ s32 freeBytes;
    /* 0x2D8 */ s32 maxFiles;
    /* 0x2DC */ s32 filesUsed;
} PakInfo; // size >= 0x2DC

s32 mCPk_PakOpen(PakInfo* info, s32 channel);
s32 mCPk_NoteNum(PakInfo* info);
s32 mCPk_FreeBlockNum(PakInfo* info);
void mCPk_ClearPassport(Passport* passport);
s32 mCPk_InitPak(s32 channel);
PrivateInfo* mCPk_GetSaveFilePrivateP(void);
s32 mCPk_SavePak(PrivateInfo* priv, Animal_c* animal, PakInfo* info);
s32 mCPk_PakPrivateLoad(PrivateInfo* priv, Animal_c* animal, PakInfo* info);
s32 func_80079760_jp(void);
void* func_80079838_jp(void);
s32 func_800798DC_jp(PakInfo* info);
UNK_RET func_80079AAC_jp(void);
UNK_RET func_80079D00_jp(void);
s32 func_80079E54_jp(D801047B0Struct* arg0, PakInfo* info);
UNK_RET func_80079EA4_jp(UNK_PTR, PakInfo* info);
void func_80079EDC_jp(void);
s32 func_80079F44_jp(void);
void func_8007A008_jp(void);
PakInfo* mCPk_get_pkinfo(void);
s32 func_8007A080_jp(void);

#endif
