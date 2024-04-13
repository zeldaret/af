#ifndef M_CLIP_H
#define M_CLIP_H

#include "ultra64.h"
#include "unk.h"
#include "color.h"

struct Actor;
struct ActorOverlay;
struct Clip_unk_040_unk_14_arg0;
struct FurnitureActor;
struct Game_Play;
struct ObjectExchangeBank;
struct ObjectStatus;
struct ShadowData;
struct struct_801161E8_jp;
struct struct_809AEFA4;
struct StructureActor;
struct StructureClip;
struct ToolClip;
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
typedef UNK_RET (*Clip_unk_040_unk_E8)(void);
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
    /* 0x0E8 */ Clip_unk_040_unk_E8 unk_E8;
    /* 0x0EC */ Clip_unk_040_unk_EC unk_EC;
    /* 0x0F0 */ Clip_unk_040_unk_F0 unk_F0;
    /* 0x0F4 */ Clip_unk_040_unk_F4 unk_F4;
    /* 0x0F8 */ UNK_TYPE1 unk_F8[0x20];
    /* 0x118 */ Clip_unk_040_unk_118 unk_118;
} Clip_unk_040; // size >= 0x11C

typedef UNK_RET (*Clip_unk_060_unk_04)(void);
typedef struct Clip_unk_060 {
  /* 0x0 */ UNK_TYPE1 unk_0[0x4];
  /* 0x4 */ Clip_unk_060_unk_04 unk_4;
} Clip_unk_060; // size >= 0x4

typedef UNK_RET (*Clip_unk_068)(void);

typedef UNK_RET (*Clip_unk_06C_unk_00)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_06C_unk_04)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_06C_unk_08)(UNK_TYPE);

typedef struct Clip_unk_078 {
    /* 0x00 */ Clip_unk_06C_unk_00 unk_00;
    /* 0x04 */ Clip_unk_06C_unk_04 unk_04;
    /* 0x08 */ Clip_unk_06C_unk_08 unk_08;
} Clip_unk_06C; // size >= 0xC

typedef s32 (*Clip_unk_070_unk_0C)(void);
typedef struct Clip_unk_070 {
    /* 0x00 */ UNK_TYPE1 unk_0[0xC]; 
    /* 0x04 */ Clip_unk_070_unk_0C unk_C;
} Clip_unk_070; // size >= 0x10

typedef UNK_RET (*Clip_unk_074_unk_00)(UNK_TYPE);
typedef void (*Clip_unk_074_unk_04)(struct Game_Play* game_play, struct ShadowData* shadowData, s16 unk2);

typedef struct Clip_unk_074 {
    /* 0x00 */ Clip_unk_074_unk_00 unk_00;
    /* 0x04 */ Clip_unk_074_unk_04 unk_04;
} Clip_unk_074; // size >= 0x8

typedef void (*Clip_unk_07C_unk_4)(struct ObjectExchangeBank*);
typedef struct Clip_unk_07C {
    /* 0x00 */ s8 unk_0[0x4];
    /* 0x04 */ Clip_unk_07C_unk_4 unk_4;
} Clip_unk_07C; // size >= 0x8
typedef void (*Clip_unk_080_unk_24)(void);
typedef UNK_RET (*Clip_unk_080_unk_34)(struct FurnitureActor* furnitureActor, struct Actor* myHouseActor, struct Game_Play* game_play, f32 arg0, f32 arg1);

typedef struct Clip_unk_080 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x24];
    /* 0x24 */ Clip_unk_080_unk_24 unk_24;
    /* 0x28 */ UNK_TYPE1 unk_28[0xC]; 
    /* 0x34 */ Clip_unk_080_unk_34 unk_34; // open close proc
} Clip_unk_080; // size >= 0x8

typedef struct StructureOverlayInfo {
    /* 0x00 */ s8* overlayPointer;
    /* 0x04 */ s32 used;
} StructureOverlayInfo; // size = 0x8

typedef struct StructureClip_unkstruct_unk_04 {
    /* 0x0 */ f32 unk_00;
    /* 0x4 */ f32 unk_04;
    /* 0x8 */ s16 unk_08;
    /* 0xA */ u16 unk_0A;
} StructureClip_unkstruct_unk_04; // size = 0xC

typedef struct StructureClip_unkstruct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ StructureClip_unkstruct_unk_04 unk_04[9];
    /* 0x70 */ s32 unk_70;
} StructureClip_unkstruct; // size = 0x74

typedef struct Actor* (*StructureClipSetupActorProc)(struct Game_Play*, u16, f32, f32, s16);
typedef void (*StructureClipGetOverlayAreaProc)(struct ActorOverlay*, size_t);
typedef void (*StructureClipFreeOverlayAreaProc)(struct ActorOverlay*);
typedef struct Actor* (*StructureClipGetActorAreaProc)(void);
typedef void (*StructureClipFreeActorAreaProc)(struct Actor*);
typedef void (*StructureClip_unk_A4)(struct ObjectExchangeBank*);
typedef void (*StructureClip_unk_A8)(StructureClip_unkstruct*, s32, s16, struct Actor*);
// TODO: What should these *really* return?
typedef s32 (*StructureClip_unk_AC)(s16);
typedef s32 (*StructureClip_unk_450)(s16);
typedef s32 (*StructureClip_unk_868)(s16);

typedef struct StructureClip {
    /* 0x000 */ StructureClipSetupActorProc setupActorProc;
    /* 0x004 */ StructureClipGetOverlayAreaProc getOverlayAreaProc;
    /* 0x008 */ StructureClipFreeOverlayAreaProc freeOverlayAreaProc;
    /* 0x00C */ StructureClipGetActorAreaProc getActorAreaProc;
    /* 0x010 */ StructureClipFreeActorAreaProc freeActorAreaProc;
    /* 0x014 */ struct StructureActor* structureActorTable[9];
    /* 0x038 */ s32 structureActorUsedTable[9];
    /* 0x05C */ StructureOverlayInfo overlayArea[9];
    /* 0x0A4 */ StructureClip_unk_A4 unk_A4;
    /* 0x0A8 */ StructureClip_unk_A8 unk_A8; // unload object
    /* 0x0AC */ StructureClip_unk_AC unk_AC; // load object
    /* 0x0B0 */ StructureClip_unkstruct unk_B0[8];
    /* 0x450 */ StructureClip_unk_450 unk_450; // load palette
    /* 0x454 */ StructureClip_unkstruct unk_454[9];
    /* 0x868 */ StructureClip_unk_868 unk_868;
    /* 0x86C */ StructureClip_unkstruct unk_86C[8];
    /* 0xC0C */ s32 unk_C0C;
    /* 0xC10 */ s32 unk_C10;
} StructureClip; // size = 0xC14

typedef void (*Clip_unk_090_unk_30)(Color_RGBA8, s16,s16,s32);
typedef struct Clip_unk_090 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x30];
    /* 0x30 */ Clip_unk_090_unk_30 unk_30;
} Clip_unk_090; // size >= 0x34

typedef void (*Clip_unk_09C_unk_C)(void);
typedef struct Clip_unk_09C {
    /* 0x00 */ UNK_TYPE1 unk_00[0xC];
    /* 0x0C */ Clip_unk_09C_unk_C unk_C;
} Clip_unk_09C; // size >= 0x10

typedef void (*Clip_unk_0A4_unk_4)(void);

typedef struct Clip_unk_0A4 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x04];
    /* 0x04 */ Clip_unk_0A4_unk_4 unk_4;
} Clip_unk_0A4;

typedef UNK_RET (*Clip_unk_0A8_unk_4)(void*);
typedef struct Clip_unk_0A8 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x04];
    /* 0x04 */ Clip_unk_0A8_unk_4 unk_4;
} Clip_unk_0A8; // size >= 0x8

typedef void (*Clip_unk_0B4_unk_4)(void);
typedef struct Clip_unk_0B4 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x04];
    /* 0x04 */ Clip_unk_0B4_unk_4 unk_4;
} Clip_unk_0B4; // size >= 0x8

typedef void (*Clip_unk_0B8_unk_4)(void);
typedef struct Clip_unk_0B8 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x04];
    /* 0x04 */ Clip_unk_0B8_unk_4 unk_4; 
} Clip_unk_0B8; // size >= 0x8

typedef void (*Clip_unk_0D0)(void);

typedef void (*Clip_unk_0D8_unk_00)(struct Game_Play* game_play);
typedef struct Clip_unk_0D8 {
    /* 0x00 */ Clip_unk_0D8_unk_00 unk_00;
} Clip_unk_0D8; // size >= 0x4


typedef struct Clip {
    /* 0x000 */ s8 unk000[0x20];
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s8 unk_024[0x1C];
    /* 0x040 */ Clip_unk_040* unk_040;
    /* 0x044 */ s8 unk_044[0x1C]; 
    /* 0x060 */ Clip_unk_060* unk_060;
    /* 0x064 */ s8 unk_064[0x4]; 
    /* 0x068 */ Clip_unk_068 unk_068; 
    /* 0x06C */ Clip_unk_06C* unk_06C;
    /* 0x070 */ Clip_unk_070* unk_070;
    /* 0x074 */ Clip_unk_074* unk_074;
    /* 0x078 */ struct WeatherClip* weatherClip;
    /* 0x07C */ Clip_unk_07C* unk_07C; 
    /* 0x080 */ Clip_unk_080* unk_080;
    /* 0x084 */ s8 unk_084[0x8];
    /* 0x08C */ struct StructureClip* structureClip; 
    /* 0x090 */ Clip_unk_090* unk_090;
    /* 0x094 */ struct ToolClip* toolClip;
    /* 0x098 */ s8 unk_098[0x4];
    /* 0x09C */ Clip_unk_09C* unk_09C;
    /* 0x0A0 */ s8 unk_0A0[0x4];
    /* 0x0A4 */ Clip_unk_0A4* unk_0A4;
    /* 0x0A8 */ Clip_unk_0A8* unk_0A8;
    /* 0x0AC */ s8 unk_0AC[0x8];
    /* 0x0B4 */ Clip_unk_0B4* unk_0B4;
    /* 0x0B8 */ Clip_unk_0B8* unk_0B8;
    /* 0x0BC */ s8 unk_0BC[0x14];
    /* 0x0D0 */ Clip_unk_0D0 unk_0D0; 
    /* 0x0D4 */ s8 unk_0D4[0x4];
    /* 0x0D8 */ Clip_unk_0D8* unk_0D8; 
    /* 0x0DC */ u8 unk_0DC[0x24];
} Clip; // size = 0x100

void clip_clear(void);

#endif
