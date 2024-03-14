#ifndef M_CLIP_H
#define M_CLIP_H

#include "ultra64.h"
#include "unk.h"
#include "color.h"

struct Actor;
struct ActorOverlay;
struct struct_801161E8_jp;
struct ObjectStatus;
struct Clip_unk_040_unk_14_arg0;
struct Game_Play;
struct struct_809AEFA4;
struct ToolClip;
struct ShadowData;
struct FurnitureActor;
struct WeatherClip;

typedef UNK_RET (*Clip_unk_040_unk_04)(struct ActorOverlay*, const struct struct_801161E8_jp*, size_t, s32);
typedef UNK_RET (*Clip_unk_040_unk_08)(void);
typedef UNK_PTR (*Clip_unk_040_unk_0C)(size_t, const struct struct_801161E8_jp*, s32);
typedef UNK_RET (*Clip_unk_040_unk_10)(struct Actor*);
typedef UNK_RET (*Clip_unk_040_unk_14)(struct Clip_unk_040_unk_14_arg0*, u16);
typedef UNK_RET (*Clip_unk_040_unk_BC)(struct Actor*, struct Game_Play*);
typedef void (*Clip_unk_040_unk_C0)(struct Actor*, struct Game_Play*, struct struct_809AEFA4*);
typedef UNK_RET (*Clip_unk_040_unk_C4)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_040_unk_C8)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_040_unk_CC)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_040_unk_D0)(void);
typedef UNK_RET (*Clip_unk_040_unk_E4)(void);
typedef UNK_RET (*Clip_unk_040_unk_EC)(struct ObjectStatus*, s16, s16);
typedef UNK_RET (*Clip_unk_040_unk_F0)(struct ObjectStatus*, struct Actor*);
typedef s32 (*Clip_unk_040_unk_F4)(struct ObjectStatus*, struct Actor*);
typedef UNK_RET (*Clip_unk_040_unk_118)(struct Actor*);

typedef struct Clip_unk_040 {
    /* 0x000 */ UNK_TYPE1 unk_00[0x4];
    /* 0x004 */ Clip_unk_040_unk_04 unk_04;
    /* 0x008 */ Clip_unk_040_unk_08 unk_08;
    /* 0x00C */ Clip_unk_040_unk_0C unk_0C;
    /* 0x010 */ Clip_unk_040_unk_10 unk_10;
    /* 0x014 */ Clip_unk_040_unk_14 unk_14;
    /* 0x018 */ UNK_TYPE1 unk_18[0xA4];
    /* 0x0BC */ Clip_unk_040_unk_BC unk_BC;
    /* 0x0C0 */ Clip_unk_040_unk_C0 unk_C0;
    /* 0x0C4 */ Clip_unk_040_unk_C4 unk_C4;
    /* 0x0C8 */ Clip_unk_040_unk_C8 unk_C8;
    /* 0x0CC */ Clip_unk_040_unk_CC unk_CC;
    /* 0x0D0 */ Clip_unk_040_unk_D0 unk_D0;
    /* 0x0D4 */ UNK_TYPE1 unk_D4[0x10];
    /* 0x0E4 */ Clip_unk_040_unk_E4 unk_E4;
    /* 0x0E8 */ UNK_TYPE1 unk_E8[0x4];
    /* 0x0EC */ Clip_unk_040_unk_EC unk_EC;
    /* 0x0F0 */ Clip_unk_040_unk_F0 unk_F0;
    /* 0x0F4 */ Clip_unk_040_unk_F4 unk_F4;
    /* 0x0F8 */ UNK_TYPE1 unk_F8[0x20];
    /* 0x118 */ Clip_unk_040_unk_118 unk_118;
} Clip_unk_040; // size >= 0x11C

typedef UNK_RET (*Clip_unk_06C_unk_00)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_06C_unk_04)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_06C_unk_08)(UNK_TYPE);

typedef struct Clip_unk_078 {
    /* 0x00 */ Clip_unk_06C_unk_00 unk_00;
    /* 0x04 */ Clip_unk_06C_unk_04 unk_04;
    /* 0x08 */ Clip_unk_06C_unk_08 unk_08;
} Clip_unk_06C; // size >= 0xC

typedef UNK_RET (*Clip_unk_074_unk_00)(UNK_TYPE);
typedef void (*Clip_unk_074_unk_04)(struct Game_Play* game_play, struct ShadowData* shadowData, s16 unk2);

typedef struct Clip_unk_074 {
    /* 0x00 */ Clip_unk_074_unk_00 unk_00;
    /* 0x04 */ Clip_unk_074_unk_04 unk_04;
} Clip_unk_074; // size >= 0x8

typedef UNK_RET (*Clip_unk_080_unk_34)(struct FurnitureActor* furnitureActor, struct Actor* myHouseActor, struct Game_Play* game_play, f32 arg0, f32 arg1);

typedef struct Clip_unk_080 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x34];
    /* 0x34 */ Clip_unk_080_unk_34 unk_34; // open close proc
} Clip_unk_080; // size >= 0x8

typedef UNK_RET (*Clip_unk_08C_unk_4)(struct ActorOverlay*, size_t);
typedef UNK_RET (*Clip_unk_08C_unk_8)(void);
typedef UNK_PTR (*Clip_unk_08C_unk_0C)(void);
typedef UNK_RET (*Clip_unk_08C_unk_10)(struct Actor*);
typedef UNK_RET (*Clip_unk_08C_unk_A8)(UNK_PTR, UNK_TYPE, u16 name, struct Actor* actor);
typedef UNK_RET (*Clip_unk_08C_unk_AC)(u16);
typedef UNK_RET (*Clip_unk_08C_unk_450)(u16);

typedef struct Clip_unk_08C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ Clip_unk_08C_unk_4 unk_4;
    /* 0x08 */ Clip_unk_08C_unk_8 unk_08;
    /* 0x0C */ Clip_unk_08C_unk_0C unk_0C;
    /* 0x10 */ Clip_unk_08C_unk_10 unk_10;
    /* 0x014 */ UNK_TYPE1 unk_14[0x94];
    /* 0x0A8 */ Clip_unk_08C_unk_A8 unk_A8; // unload object
    /* 0x0AC */ Clip_unk_08C_unk_AC unk_AC; // load object
    /* 0x0B0 */ UNK_TYPE unk_B0;
    /* 0x0B4 */ UNK_TYPE1 pad[0x450 - 0xb4];
    /* 0x450 */ Clip_unk_08C_unk_450 unk_450; // load palette
    /* 0x454 */ UNK_TYPE unk_454;
    /* 0x458 */ UNK_TYPE1 pad2[0x86C - 0x458];
    /* 0x86C */ UNK_TYPE unk_86C;
} Clip_unk_08C; // size >= 0x870

typedef void (*Clip_unk_090_unk_30)(Color_RGBA8, s16,s16,s32);
typedef struct Clip_unk_090 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x30];
    /* 0x30 */ Clip_unk_090_unk_30 unk_30;
} Clip_unk_090; // size >= 0x34

typedef void (*Clip_unk_0D8_unk_00)(struct Game_Play* game_play);
typedef struct Clip_unk_0D8 {
    /* 0x00 */ Clip_unk_0D8_unk_00 unk_00;
} Clip_unk_0D8; // size >= 0x4


typedef struct Clip {
    /* 0x000 */ UNK_TYPE1 unk000[0x40];
    /* 0x040 */ Clip_unk_040* unk_040;
    /* 0x044 */ UNK_TYPE1 unk_044[0x28];
    /* 0x06C */ Clip_unk_06C* unk_06C;
    /* 0x070 */ UNK_TYPE1 unk_070[0x4];
    /* 0x074 */ Clip_unk_074* unk_074;
    /* 0x078 */ struct WeatherClip* weatherClip;
    /* 0x07C */ UNK_TYPE1 unk_07C[0x4];
    /* 0x080 */ Clip_unk_080* unk_080;
    /* 0x084 */ UNK_TYPE1 unk_084[0x8];
    /* 0x08C */ Clip_unk_08C* unk_08C;
    /* 0x090 */ Clip_unk_090* unk_090;
    /* 0x094 */ struct ToolClip* toolClip;
    /* 0x098 */ UNK_TYPE1 unk_098[0x40];
    /* 0x0D8 */ Clip_unk_0D8* unk_0D8;
    /* 0x0DC */ u8 unk_0DC[0x24];
} Clip; // size = 0x100

void clip_clear(void);

#endif
