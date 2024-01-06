#ifndef EVW_ANIME_H
#define EVW_ANIME_H

#include "ultra64.h"

struct Game;

typedef struct EvwAnimeUnk {
  s8 unk_0;
  s16 unk1;
  void* unk_4;
} EvwAnimeUnk;

// void func_800549C0_jp();
// void func_80054A28_jp();
// void func_80054A94_jp();
// void func_80054B44_jp();
// void func_80054BB0_jp();
// void func_80054C88_jp();
// void morf_calc();
// void func_80054D3C_jp();
// void func_80054F10_jp();
// void func_80055214_jp();
// void func_80055248_jp();
// void func_800554D8_jp();
void Evw_Anime_Set(struct Game*,EvwAnimeUnk*);

#endif
