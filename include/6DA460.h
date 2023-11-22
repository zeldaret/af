#ifndef C_6DA460_H
#define C_6DA460_H

#include "ultra64.h"

struct Mail_c;
struct Game_Play;

// void func_800B67C0_jp();
// void func_800B6838_jp();
s32 mPO_get_keep_mail_sum(void);
// void func_800B690C_jp();
s32 mPO_receipt_proc(Mail_c*, s32);
// void func_800B6AC8_jp();
// void func_800B6B94_jp();
// void func_800B6C14_jp();
// void func_800B6C88_jp();
// void func_800B6D40_jp();
// void func_800B6D80_jp();
// void func_800B6DCC_jp();
// void func_800B6EBC_jp();
// void func_800B6FD4_jp();
// void func_800B702C_jp();
// void func_800B706C_jp();
// void func_800B7164_jp();
// void func_800B71D4_jp();
// void func_800B7218_jp();
// void func_800B72B8_jp();
// void func_800B7328_jp();
// void func_800B7350_jp();
// void func_800B7468_jp();
// void func_800B74E8_jp();
// void func_800B7560_jp();
void mPO_business_proc(struct Game_Play* game_play);
void func_800B7680_jp(struct Game_Play* game_play);
// void func_800B7700_jp();

#endif
