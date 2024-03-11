#ifndef C_68AAF0_H
#define C_68AAF0_H

#include "ultra64.h"
#include "unk.h"

struct Actor;
struct ActorOverlay;
struct struct_801161E8_jp;
struct ObjectStatus;
struct Clip_unk_1004C_unk_14_arg0;
struct Game_Play;
struct struct_809AEFA4;
struct ToolClip;
struct ShadowData;
struct FurnitureActor;

typedef UNK_RET (*Clip_unk_1004C_unk_04)(struct ActorOverlay*, const struct struct_801161E8_jp*, size_t, s32);
typedef UNK_RET (*Clip_unk_1004C_unk_08)(void);
typedef UNK_PTR (*Clip_unk_1004C_unk_0C)(size_t, const struct struct_801161E8_jp*, s32);
typedef UNK_RET (*Clip_unk_1004C_unk_10)(struct Actor*);
typedef UNK_RET (*Clip_unk_1004C_unk_14)(struct Clip_unk_1004C_unk_14_arg0*, u16);
typedef UNK_RET (*Clip_unk_1004C_unk_BC)(struct Actor*, struct Game_Play*);
typedef void (*Clip_unk_1004C_unk_C0)(struct Actor*, struct Game_Play*, struct struct_809AEFA4*);
typedef UNK_RET (*Clip_unk_1004C_unk_C4)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_1004C_unk_C8)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_1004C_unk_CC)(struct Actor*, struct Game_Play*);
typedef UNK_RET (*Clip_unk_1004C_unk_D0)(void);
typedef UNK_RET (*Clip_unk_1004C_unk_E4)(void);
typedef UNK_RET (*Clip_unk_1004C_unk_EC)(struct ObjectStatus*, s16, s16);
typedef UNK_RET (*Clip_unk_1004C_unk_F0)(struct ObjectStatus*, struct Actor*);
typedef s32 (*Clip_unk_1004C_unk_F4)(struct ObjectStatus*, struct Actor*);
typedef UNK_RET (*Clip_unk_1004C_unk_118)(struct Actor*);

typedef struct Clip_unk_1004C {
    /* 0x000 */ UNK_TYPE1 unk_00[0x4];
    /* 0x004 */ Clip_unk_1004C_unk_04 unk_04;
    /* 0x008 */ Clip_unk_1004C_unk_08 unk_08;
    /* 0x00C */ Clip_unk_1004C_unk_0C unk_0C;
    /* 0x010 */ Clip_unk_1004C_unk_10 unk_10;
    /* 0x014 */ Clip_unk_1004C_unk_14 unk_14;
    /* 0x018 */ UNK_TYPE1 unk_18[0xA4];
    /* 0x0BC */ Clip_unk_1004C_unk_BC unk_BC;
    /* 0x0C0 */ Clip_unk_1004C_unk_C0 unk_C0;
    /* 0x0C4 */ Clip_unk_1004C_unk_C4 unk_C4;
    /* 0x0C8 */ Clip_unk_1004C_unk_C8 unk_C8;
    /* 0x0CC */ Clip_unk_1004C_unk_CC unk_CC;
    /* 0x0D0 */ Clip_unk_1004C_unk_D0 unk_D0;
    /* 0x0D4 */ UNK_TYPE1 unk_D4[0x10];
    /* 0x0E4 */ Clip_unk_1004C_unk_E4 unk_E4;
    /* 0x0E8 */ UNK_TYPE1 unk_E8[0x4];
    /* 0x0EC */ Clip_unk_1004C_unk_EC unk_EC;
    /* 0x0F0 */ Clip_unk_1004C_unk_F0 unk_F0;
    /* 0x0F4 */ Clip_unk_1004C_unk_F4 unk_F4;
    /* 0x0F8 */ UNK_TYPE1 unk_F8[0x20];
    /* 0x118 */ Clip_unk_1004C_unk_118 unk_118;
} Clip_unk_1004C; // size >= 0x11C

typedef UNK_RET (*Clip_unk_10078_unk_00)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_10078_unk_04)(UNK_TYPE);
typedef UNK_RET (*Clip_unk_10078_unk_08)(UNK_TYPE);

typedef struct Clip_unk_10078 {
    /* 0x00 */ Clip_unk_10078_unk_00 unk_00;
    /* 0x04 */ Clip_unk_10078_unk_04 unk_04;
    /* 0x08 */ Clip_unk_10078_unk_08 unk_08;
} Clip_unk_10078; // size >= 0xC

typedef UNK_RET (*Clip_unk_10080_unk_00)(UNK_TYPE);
typedef void (*Clip_unk_10080_unk_04)(struct Game_Play* game_play, struct ShadowData* shadowData, s16 unk2);

typedef struct Clip_unk_10080 {
    /* 0x00 */ Clip_unk_10080_unk_00 unk_00;
    /* 0x04 */ Clip_unk_10080_unk_04 unk_04;
} Clip_unk_10080; // size >= 0x8

typedef UNK_RET (*Clip_unk_1008C_unk_34)(struct FurnitureActor* furnitureActor, struct Actor* myHouseActor, struct Game_Play* game_play, f32 arg0, f32 arg1);

typedef struct Clip_unk_1008C {
    /* 0x00 */ UNK_TYPE1 unk_00[0x34];
    /* 0x34 */ Clip_unk_1008C_unk_34 unk_34; // open close proc
} Clip_unk_1008C; // size >= 0x8

typedef UNK_RET (*Clip_unk_10098_unk_4)(struct ActorOverlay*, size_t);
typedef UNK_RET (*Clip_unk_10098_unk_8)(void);
typedef UNK_PTR (*Clip_unk_10098_unk_0C)(void);
typedef UNK_RET (*Clip_unk_10098_unk_10)(struct Actor*);
typedef UNK_RET (*Clip_unk_10098_unk_A8)(UNK_PTR, UNK_TYPE, u16 name, struct Actor* actor);
typedef UNK_RET (*Clip_unk_10098_unk_AC)(u16);
typedef UNK_RET (*Clip_unk_10098_unk_450)(u16);

typedef struct Clip_unk_10098 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ Clip_unk_10098_unk_4 unk_4;
    /* 0x08 */ Clip_unk_10098_unk_8 unk_08;
    /* 0x0C */ Clip_unk_10098_unk_0C unk_0C;
    /* 0x10 */ Clip_unk_10098_unk_10 unk_10;
    /* 0x014 */ UNK_TYPE1 unk_14[0x94];
    /* 0x0A8 */ Clip_unk_10098_unk_A8 unk_A8; // unload object
    /* 0x0AC */ Clip_unk_10098_unk_AC unk_AC; // load object
    /* 0x0B0 */ UNK_TYPE unk_B0;
    /* 0x0B4 */ UNK_TYPE1 pad[0x450 - 0xb4];
    /* 0x450 */ Clip_unk_10098_unk_450 unk_450; // load palette
    /* 0x454 */ UNK_TYPE unk_454;
    /* 0x458 */ UNK_TYPE1 pad2[0x86C - 0x458];
    /* 0x86C */ UNK_TYPE unk_86C;
} Clip_unk_10098; // size >= 0x870

typedef void (*Clip_unk_100E4_unk_00)(struct Game_Play* game_play);
typedef struct Clip_unk_100E4 {
               Clip_unk_100E4_unk_00 unk_00;
} Clip_unk_100E4;


typedef struct Clip {
                  UNK_TYPE1 unk_1000C[0x40];
                  Clip_unk_1004C* unk_1004C;
                  UNK_TYPE1 unk_10050[0x28];
                  Clip_unk_10078* unk_10078;
                  UNK_TYPE1 unk_1007C[0x4];
                  Clip_unk_10080* unk_10080;
                  UNK_TYPE1 unk_10084[0x8];
                  Clip_unk_1008C* unk_1008C;
                  UNK_TYPE1 unk_10090[0x8];
                  Clip_unk_10098* unk_10098;
                  UNK_TYPE1 unk_1009C[0x4];
                  struct ToolClip* toolClip;
                  UNK_TYPE1 unk_100A4[0x40];
                  Clip_unk_100E4* unk_100E4;
                  u8 unk_100E8[0x24];
}Clip;

void clip_clear(void);

#endif
