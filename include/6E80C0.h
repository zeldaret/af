#ifndef C_6E80C0_H
#define C_6E80C0_H

#include "ultra64.h"

struct Game_Play;

typedef struct Game_Play1CBC {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0xE0];
} Game_Play1CBC; // size = 0xF0

// void func_800C4420_jp();
// void func_800C4440_jp();
// void func_800C453C_jp();
// void func_800C4648_jp();
// void func_800C46AC_jp();
// void mSM_ovlptr_dllcnv();
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
void mSM_submenu_draw(Game_Play1CBC* arg0, struct Game_Play* game_play);
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
