#ifndef SPEED_METER_H
#define SPEED_METER_H

#include "ultra64.h"
#include "unk.h"

struct GameState;
struct GraphicsContext;

typedef struct struct_80145020_jp {
    /* 0x0 */ UNK_TYPE1 unk_0[UNK_SIZE];
} struct_80145020_jp; // size = ?, maybe 0x20?

// void func_800D88A0_jp();
void func_800D88B0_jp(struct_80145020_jp *arg0);
void func_800D88D4_jp(struct_80145020_jp *arg0);
void func_800D88E0_jp(struct_80145020_jp *arg0);
void func_800D8A54_jp(struct_80145020_jp *arg0, struct GraphicsContext* gfxCtx);
// void func_800D8DD4_jp();
// void func_800D8E18_jp();
void func_800D9018_jp(struct_80145020_jp *arg0, struct GraphicsContext* gfxCtx, struct GameState *gameState);
// void func_800D93F4_jp();

#endif
