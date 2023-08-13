#ifndef C_6A8180_H
#define C_6A8180_H

#include "ultra64.h"

typedef struct PlayState2128 {
    /* 0x00 */ char unk00[0x10];
} PlayState2128; // size = 0x10

void func_800844E0_jp(PlayState2128* arg0);
void func_8008450C_jp(PlayState2128* arg0, u8 arg1);
void func_800845EC_jp(PlayState2128* arg0, Gfx** gfx);
void func_8008468C_jp(PlayState2128* arg0);
void func_800846D4_jp(PlayState2128* arg0, s32 arg1);
void func_800846E0_jp(PlayState2128* arg0, s32 arg1);
void func_800846EC_jp(PlayState2128* arg0);

#endif
