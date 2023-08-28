#ifndef M_HANDBILL_H
#define M_HANDBILL_H

#include "ultra64.h"

struct Game;
struct Game_Play;

#define HANDBILL_HEADER_LEN MAIL_HEADER_LEN*2
#define HANDBILL_FOOTER_LEN MAIL_HEADER_LEN+MAIL_FOOTER_LEN
#define HANDBILL_BODY_LEN MAIL_BODY_LEN

typedef struct Handbill_Unk_Struct {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ size_t unk_04;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ size_t unk_0C;
    /* 0x10 */ u8* unk_10;
    /* 0x14 */ size_t unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} Handbill_Unk_Struct; // size = 0x30

void Balloon_init(struct Game_Play* game_play);
void Balloon_move(struct Game_Play* game_play);
// void func_80092B7C_jp();
// void func_80092B8C_jp();
// void func_80092BA0_jp();
// void func_80092BE8_jp();
void mHsRm_GetHuusuiRoom(struct Game* game_play, s32 playerNo);
void func_80092D10_jp(s32 arg0, u8* name, s32 arg2);
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
void func_80093F04_jp(u8* header, s32* headerBackStart, u8* footer, u8* body, s32 mailNo);
void func_80093F54_jp(u8* header, s32 headerSize, s32* headerBackStart, u8* footer, s32 footerSize, u8* body, s32 mailNo);
// void func_80093F94_jp();
// void func_800940A8_jp();
// void func_800941B0_jp();
// void func_800942A0_jp();
// void func_80094400_jp();
s32 func_800944B8_jp(Handbill_Unk_Struct* info);

#endif
