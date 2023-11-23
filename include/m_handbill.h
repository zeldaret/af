#ifndef M_HANDBILL_H
#define M_HANDBILL_H

#include "ultra64.h"

struct Game;
struct Game_Play;


typedef struct HandbillzInfo {
    /* 0x00 */ u8* superBuf;
    /* 0x04 */ size_t superBufSize;
    /* 0x08 */ u8* mailBuf;
    /* 0x0C */ size_t mailBufSize;
    /* 0x10 */ u8* psBuf;
    /* 0x14 */ size_t psBufSize;
    /* 0x18 */ s32 superNo;
    /* 0x1C */ s32 mailANo;
    /* 0x20 */ s32 mailBNo;
    /* 0x24 */ s32 mailCNo;
    /* 0x28 */ s32 psNo;
    /* 0x2C */ s32 headerBackStart;
} HandbillzInfo; // size = 0x30


//TODO: move these out of the handbill header
void Balloon_init(struct Game_Play* game_play);
void Balloon_move(struct Game_Play* game_play);
// void func_80092B7C_jp();
// void func_80092B8C_jp();
// void func_80092BA0_jp();
// void func_80092BE8_jp();
void mHsRm_GetHuusuiRoom(struct Game* game_play, s32 player_no);

void mHandbill_Set_free_str(s32, char*, s32);
// void func_80092E14_jp();
// void func_80092E80_jp();
// void func_80092FC4_jp();
// void func_800930B0_jp();
// void func_800930D8_jp();
// void func_80093104_jp();
// void func_80093130_jp();
// void func_8009315C_jp();
// void func_80093188_jp();
// void func_800931B4_jp();
// void func_800931E0_jp();
// void func_8009320C_jp();
// void func_80093238_jp();
// void func_80093264_jp();
// void func_80093290_jp();
// void func_800932BC_jp();
// void func_800932E8_jp();
// void func_80093314_jp();
// void func_80093340_jp();
// void func_8009336C_jp();
// void func_80093398_jp();
// void func_800933C4_jp();
// void func_800933F0_jp();
// void func_8009341C_jp();
// void func_80093478_jp();
// void func_80093520_jp();
// void func_800935F8_jp();
// void func_80093738_jp();
// void func_80093878_jp();
// void func_800939B8_jp();
// void func_80093B28_jp();
// void func_80093C98_jp();
// void func_80093DA8_jp();
void mHandbill_Load_HandbillFromRom(u8*, s32*, u8*, u8*, s32);
void mHandbill_Load_HandbillFromRom2(u8*, s32, s32*, u8*, s32, u8*, s32);
// void func_80093F94_jp();
// void func_800940A8_jp();
// void func_800941B0_jp();
// void func_800942A0_jp();
// void func_80094400_jp();
s32 mHandbillz_load(HandbillzInfo*);

#endif
