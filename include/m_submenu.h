#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "ultra64.h"
#include "z64math.h"
#include "libc/stdint.h"
#include "other_types.h"
#include "unk.h"

struct Game_Play;
struct Game_Play1CBC;

typedef void (*Game_Play1CBC_unk_30)(struct Game_Play1CBC*);

typedef struct Game_Play1CBC {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_TYPE unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ UNK_TYPE1 unk_10[0x10];
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ void* unk_24;
    /* 0x28 */ void* unk_28;
    /* 0x2C */ UNK_TYPE1 unk_2C[0x4];
    /* 0x30 */ Game_Play1CBC_unk_30 unk_30;
    /* 0x34 */ UNK_FUN_PTR unk_34;
    /* 0x38 */ UNK_TYPE1 unk_38[0xA4];
    /* 0xDC */ u8 unk_DC;
    /* 0xDD */ u8 unk_DD;
    /* 0xDE */ u8 unk_DE;
    /* 0xDF */ u8 unk_DF;
    /* 0xE0 */ u16 unk_E0;
    /* 0xE2 */ u8 unk_E2;
    /* 0xE3 */ u8 unk_E3;
    /* 0xE4 */ Vec3f unk_E4;
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

s32 SubmenuArea_IsPlayer(void);
// void mSM_load_player_anime();
void SubmenuArea_DoLink(SubmenuArea* area, Game_Play1CBC* arg1, s32 arg2);
void SubmenuArea_DoUnlink(SubmenuArea* area, Game_Play1CBC* arg1);
// void func_800C46AC_jp();
void* mSM_ovlptr_dllcnv(void* vram, Game_Play1CBC* arg1);
void func_800C47B4_jp(void*, void*);
uintptr_t func_800C497C_jp(uintptr_t, void*);
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
void mSM_move_Wait(Game_Play1CBC* arg0);
void mSM_move_PREWait(Game_Play1CBC* arg0);
void mSM_move_LINKWait(Game_Play1CBC* arg0);
void mSM_move_Play(Game_Play1CBC* arg0);
void mSM_move_End(Game_Play1CBC* arg0);
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
