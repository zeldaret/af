#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "ultra64.h"
#include "unk.h"

struct Actor;
struct Global_light;
struct Lights;

typedef void (*Kankyo_unk_C0)(struct Actor*);

typedef struct Kankyo {
    /* 0x00 */ UNK_TYPE1 unk_00[0x2];
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ UNK_TYPE1 unk_05[0x3];
    /* 0x08 */ UNK_TYPE1 unk_08[0x14];
    /* 0x1C */ struct Lights* unk_1C;
    /* 0x2C */ UNK_TYPE1 unk_20[0x72];
    /* 0x92 */ u8 sunColor[3];
    /* 0x95 */ UNK_TYPE1 unk_95[0x19];
    /* 0xAE */ u8 unk_AE;
    /* 0xAF */ u8 unk_AF;
    /* 0xB0 */ u8 unk_B0;
    /* 0xB1 */ UNK_TYPE1 unk_B1[0xF];
    /* 0xC0 */ Kankyo_unk_C0 unk_C0;
    /* 0xC4 */ UNK_TYPE1 unk_C4[0x4];
} Kankyo; // size = 0xC8

// void mEnv_regist_nature();
// void func_80096CA0_jp();
// void func_80096CDC_jp();
// void func_80096D60_jp();
// void func_80096F5C_jp();
// void func_80097048_jp();
// void mEnv_RoomTypeLightSet();
void Global_kankyo_ct(struct Game_Play* game_play, struct Kankyo* kankyo);
// void mEnv_MakeShadowInfo();
// void mEnv_set_time();
// void func_800976BC_jp();
// void func_80097738_jp();
// void func_800978EC_jp();
// void func_80097AE8_jp();
// void func_80097BB0_jp();
// void func_80097C54_jp();
// void func_80097D40_jp();
// void func_80097F88_jp();
// void func_80097FB4_jp();
// void func_8009802C_jp();
// void func_800980C0_jp();
// void func_80098158_jp();
// void func_800981B8_jp();
// void func_8009836C_jp();
// void func_800983F0_jp();
void Global_kankyo_set(struct Game_Play* game_play, struct Kankyo* kankyo, struct Global_light* arg2);
// void func_80098558_jp();
// void func_8009867C_jp();
// void func_80098794_jp();
// void func_8009895C_jp();
// void func_80098980_jp();
// void func_80098990_jp();
// void func_80098A90_jp();
void mEnv_WindMove(void);
// void func_80098CCC_jp();
// void func_80098D88_jp();
void mEnv_DecideWeather_NormalGameStart(void);
// void mEnv_NowWeather();
// void func_80098F68_jp();
// void func_80098FF0_jp();
// void func_800990A8_jp();
// void func_8009915C_jp();
// void func_800991EC_jp();
// void func_800992C8_jp();
// void func_80099378_jp();
// void func_8009944C_jp();
// void func_8009949C_jp();
// void func_80099594_jp();
// void func_800996CC_jp();
// void mEnv_GetShadowPrimColor_Light();
// void func_80099718_jp();
// void func_80099728_jp();
// void mEnv_MakeWindowLightAlpha();
// void func_800998AC_jp();

#endif
