#ifndef EVW_ANIME_H
#define EVW_ANIME_H

#include "ultra64.h"

struct Game;

typedef struct EvwAnimeScroll {
    /* 0x0 */ s8 x; /* x (s) texture position */
    /* 0x1 */ s8 y; /* y (t) texture position */
    /* 0x2 */ u8 width; /* texture width */
    /* 0x3 */ u8 height; /* texture height */
} EvwAnimeScroll; // size = 0x4

typedef struct EvwAnimeColPrim {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
    /* 0x4 */ u8 l;
} EvwAnimeColPrim; // size = 0x5

typedef struct EvwAnimeColEnv {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} EvwAnimeColEnv; // size = 0x4

typedef struct EvwAnimeColReg {
    /* 0x0 */ u16 frameCount;
    /* 0x2 */ u16 keyframeCount;
    /* 0x4 */ EvwAnimeColPrim* prim;
    /* 0x8 */ EvwAnimeColEnv* env;
    /* 0xC */ u16* keyframes;
} EvwAnimeColReg; // size = 0x10

typedef struct EvwAnimeTexAnime {
    /* 0x0 */ u16 frameCount; /* total frames in the animation */
    /* 0x2 */ u16 keyframeCount; /* number of animation keyframes */
    /* 0x4 */ void** textureTable; /* list of each texture */
    /* 0x8 */ u8* animationPattern; /* list of which texture to use per keyframe (runs at 30 FPS) */
    /* 0xC */ u16* keyframes; /* list of keyframe frame indices */
} EvwAnimeTexAnime; // size = 0x10

typedef struct EvwAnimeData {
    /* 0x0 */ s8 segment; /* Negative segments signal the end of the animation data array */
    /* 0x2 */ s16 type;
    /* 0x4 */ void* dataPtr;
} EvwAnimeData; // size = 0x8

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
void Evw_Anime_Set(struct Game*,EvwAnimeData*);

#endif
