#ifndef C_6E9650_H
#define C_6E9650_H

#include "ultra64.h"

typedef struct PlayState_unk_0110 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ UNK_TYPE1 unk_02[0x2];
    /* 0x04 */ void* unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x48];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ UNK_TYPE1 unk_52[0x2];
} PlayState_unk_0110; // size = 0x54

// void func_800C59B0_jp();
// void func_800C5A08_jp();
// void func_800C5A60_jp();
// void func_800C5AA0_jp();
// void func_800C5B30_jp();
// void func_800C5B5C_jp();
// void func_800C5B74_jp();
// void func_800C5C30_jp();
// void func_800C5CC4_jp();
// void func_800C5D68_jp();
// void func_800C5E10_jp();
// void func_800C5EA0_jp();
// void func_800C5F0C_jp();
void func_800C5F64_jp(PlayState_unk_0110 arg0[]);
// void mSc_bank_regist_check();
// void func_800C6144_jp();
// void mSc_regist_initial_exchange_bank();
// void func_800C62C4_jp();
// void func_800C639C_jp();
void func_800C65E4_jp(struct PlayState* play, PlayState_unk_0110 arg1[]);
void func_800C6678_jp(PlayState_unk_0110 arg0[]);
// void func_800C6690_jp();
void func_800C68C8_jp(struct PlayState* play, void* arg1);
// void func_800C6960_jp();
// void func_800C69F4_jp();
// void func_800C6A28_jp();
// void func_800C6A5C_jp();
// void func_800C6A90_jp();
void func_800C6AC4_jp(s32* arg0);
// void func_800C6AD0_jp();
// void func_800C6AE0_jp();
// void func_800C6B50_jp();
// void func_800C6BB0_jp();
// void func_800C6BD4_jp();
// void func_800C6BF8_jp();
// void func_800C6C10_jp();
// void func_800C6D14_jp();
// void func_800C6D5C_jp();
// void func_800C6E14_jp();

#endif
