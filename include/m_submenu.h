#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "ultra64.h"
#include "other_types.h"
#include "unk.h"

struct Game_Play;

typedef struct Game_Play1CBC {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ UNK_TYPE1 unk_10[0x10];
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ void* unk_24;
    /* 0x28 */ void* unk_28;
    /* 0x2C */ UNK_TYPE1 unk_2C[0x4];
    /* 0x30 */ UNK_FUN_PTR unk_30;
    /* 0x34 */ UNK_FUN_PTR unk_34;
    /* 0x38 */ UNK_TYPE1 unk_38[0xA8];
    /* 0xE0 */ UNK_TYPE1 unk_E0[0x2];
    /* 0xE2 */ u8 unk_E2;
    /* 0xE3 */ UNK_TYPE1 unk_E3[0x1];
    /* 0xE4 */ UNK_TYPE1 unk_E4[0xC];
} Game_Play1CBC; // size = 0xF0

typedef struct SubmenuArea {
    /* 0x00 */ void* allocatedRamAddr;
    /* 0x04 */ RomOffset vromStart;
    /* 0x08 */ RomOffset vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
} SubmenuArea; // size = 0x1C

// void func_800C4420_jp();
// void func_800C4440_jp();
void SubmenuArea_DoLink(SubmenuArea* area, Game_Play1CBC* arg1, s32 arg2);
void SubmenuArea_DoUnlink(SubmenuArea* area, Game_Play1CBC* arg1);
// void func_800C46AC_jp();
void* mSM_ovlptr_dllcnv(void* vram, Game_Play1CBC* arg1);
// void func_800C47B4_jp();
// void func_800C497C_jp();
void func_800C49D4_jp(struct Game_Play* game_play);
void mSM_submenu_ovlptr_cleanup(Game_Play1CBC* arg0);
void load_player(Game_Play1CBC* arg0);
void mSM_submenu_ct(Game_Play1CBC* arg0);
void mSM_submenu_dt(Game_Play1CBC* arg0);
// void func_800C4D8C_jp();
// void func_800C4DB0_jp();
// void func_800C4DD8_jp();
// void func_800C4DFC_jp();
// void func_800C4E2C_jp();
void mSM_submenu_ctrl(struct Game_Play* game_play);
// void func_800C50C4_jp();
// void func_800C50EC_jp();
// void func_800C510C_jp();
// void func_800C5228_jp();
// void func_800C524C_jp();
void mSM_submenu_move(Game_Play1CBC* arg0);
// void mSM_submenu_draw(Game_Play1CBC* arg0);
// void func_800C53B8_jp();
// void func_800C543C_jp();
// void func_800C54A8_jp();
// void func_800C54F4_jp();
// void func_800C557C_jp();
// void func_800C55E4_jp();
// void func_800C5640_jp();
// void func_800C56AC_jp();
// void func_800C5798_jp();
// void func_800C582C_jp();
// void func_800C58B4_jp();
// void func_800C592C_jp();
// void func_800C5960_jp();
// void func_800C5984_jp();

#endif
