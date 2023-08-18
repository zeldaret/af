#ifndef M_HANDBILL_H
#define M_HANDBILL_H

#include "ultra64.h"

struct Game;
struct Game_Play;

#define HANDBILL_HEADER_LEN MAIL_HEADER_LEN*2
#define HANDBILL_FOOTER_LEN MAIL_HEADER_LEN+MAIL_FOOTER_LEN
#define HANDBILL_BODY_LEN MAIL_BODY_LEN

typedef struct mHandbillz_info_s {
    /* 0x00 */ u8* super_buf_p;
    /* 0x04 */ size_t super_buf_size;
    /* 0x08 */ u8* mail_buf_p;
    /* 0x0C */ size_t mail_buf_size;
    /* 0x10 */ u8* ps_buf_p;
    /* 0x14 */ size_t ps_buf_size;
    /* 0x18 */ s32 super_no;
    /* 0x1C */ s32 maila_no;
    /* 0x20 */ s32 mailb_no;
    /* 0x24 */ s32 mailc_no;
    /* 0x28 */ s32 ps_no;
    /* 0x2C */ s32 header_back_start;
} mHandbillz_Info_c; // size = 0x30

void Balloon_init(struct Game_Play* game_play);
void Balloon_move(struct Game_Play* game_play);
// void func_80092B7C_jp();
// void func_80092B8C_jp();
// void func_80092BA0_jp();
// void func_80092BE8_jp();
void mHsRm_GetHuusuiRoom(struct Game* game_play, s32 player_no);
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
void func_80093F04_jp(u8* header, s32* header_back_start, u8* footer, u8* body, s32 mail_no);
void func_80093F54_jp(u8* header, s32 header_size, s32* header_back_start, u8* footer, s32 footer_size, u8* body, s32 mail_no);
// void func_80093F94_jp();
// void func_800940A8_jp();
// void func_800941B0_jp();
// void func_800942A0_jp();
// void func_80094400_jp();
s32 func_800944B8_jp(mHandbillz_Info_c* info);

#endif
