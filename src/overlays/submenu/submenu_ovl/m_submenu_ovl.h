#ifndef M_SUBMENU_OVL
#define M_SUBMENU_OVL

#include "ultra64.h"
#include "other_types.h"
#include "unk.h"

struct GraphicsContext;
struct Game_Play;
struct mSM;

typedef void (*struct_8085E4D0_unk_10)(struct mSM*);

typedef void (*struct_8085E4D0_unk_18)(struct mSM*);

typedef struct struct_8085E4D0 {
    /* 0x00 */ RomOffset vromStart;
    /* 0x00 */ RomOffset vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x08 */ void* vramEnd;
    /* 0x08 */ struct_8085E4D0_unk_10 unk_10;
    /* 0x08 */ UNK_FUN_PTR unk_14;
    /* 0x08 */ struct_8085E4D0_unk_18 unk_18;
    /* 0x08 */ UNK_TYPE4 unk_1C;
} struct_8085E4D0; // size = 0x20

typedef struct struct_mSM_move_Move_arg1 {
    /* 0x00 */ UNK_TYPE1 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x10];
    /* 0x18 */ f32 unk_18[2];
    /* 0x20 */ f32 unk_20[2];
    /* 0x28 */ UNK_TYPE1 unk_28[0x8];
    /* 0x30 */ UNK_TYPE4 unk_30;
    /* 0x34 */ UNK_TYPE4 unk_34;
} struct_mSM_move_Move_arg1; // size >= 0x38

typedef void (*struct_8085E9B0_unk_10670_unk_00)(struct mSM*);
typedef void (*struct_8085E9B0_unk_10670_unk_04)(struct mSM*, struct Game_Play*);

typedef struct func_8085D43C_jp_arg2 {
    /* 0x0 */ RomOffset vromStart;
    /* 0x4 */ RomOffset vromEnd;
} func_8085D43C_jp_arg2; // size = 0x8

typedef struct struct_8085E9B0_unk_10000 {
    /* 0x10000 */ void* unk_00;
    /* 0x10004 */ s32 unk_04;
    /* 0x10008 */ void* unk_08;
    /* 0x1000C */ UNK_TYPE1 unk_0C[0x58];
    /* 0x10064 */ UNK_TYPE4 unk_64;
    /* 0x10068 */ struct_8085E4D0* unk_68[UNK_SIZE];
} struct_8085E9B0_unk_10000; // size >= 0x6C

typedef struct struct_8085E9B0_unk_10088 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ UNK_TYPE1 unk_04[0x4];
    /* 0x08 */ UNK_TYPE4 unk_08;
    /* 0x0C */ struct_8085E9B0_unk_10670_unk_00 unk_0C;
    /* 0x10 */ struct_8085E9B0_unk_10670_unk_04 unk_10;
    /* 0x14 */ UNK_TYPE4 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ UNK_TYPE1 unk_28[0x10];
    /* 0x38 */ UNK_TYPE4 unk_38;
    /* 0x3C */ UNK_TYPE4 unk_3C;
    /* 0x40 */ UNK_TYPE4 unk_40;
    /* 0x44 */ UNK_TYPE4 unk_44;
} struct_8085E9B0_unk_10088; // size = 0x48

typedef struct struct_8085E9B0_unk_10670 {
    /* 0x00 */ struct_8085E9B0_unk_10670_unk_00 unk_00;
    /* 0x04 */ struct_8085E9B0_unk_10670_unk_04 unk_04;
    /* 0x08 */ UNK_FUN_PTR unk_08;
    /* 0x0C */ UNK_FUN_PTR unk_0C;
    /* 0x10 */ UNK_FUN_PTR unk_10;
    /* 0x14 */ UNK_FUN_PTR unk_14;
    /* 0x18 */ UNK_TYPE1 unk_18[0x4];
    /* 0x1C */ UNK_TYPE4 unk_1C;
    /* 0x20 */ UNK_TYPE4 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
} struct_8085E9B0_unk_10670; // size >= 0x30

typedef void (*struct_8085E9B0_unk_106B4)(struct GraphicsContext*);
typedef void (*struct_8085E9B0_unk_106CC)(struct mSM*, void**, func_8085D43C_jp_arg2*);

typedef struct struct_8085E9B0 {
    /* 0x00000 */ UNK_TYPE1 unk_00000[0x10000];
    /* 0x10000 */ struct_8085E9B0_unk_10000 unk_10000;
    /* 0x1006C */ UNK_TYPE1 unk_1006C[0x1C];
    /* 0x10088 */ struct_8085E9B0_unk_10088 unk_10088[UNK_SIZE];
    /* 0x100D0 */ UNK_TYPE1 unk_100D0[0x5A0];
    /* 0x10670 */ struct_8085E9B0_unk_10670 unk_10670;
    /* 0x106A0 */ UNK_TYPE1 unk_106A0[0x4];
    /* 0x106A4 */ UNK_FUN_PTR unk_106A4;
    /* 0x106A8 */ UNK_FUN_PTR unk_106A8;
    /* 0x106AC */ UNK_FUN_PTR unk_106AC;
    /* 0x106B0 */ UNK_FUN_PTR unk_106B0;
    /* 0x106B4 */ UNK_FUN_PTR unk_106B4;
    /* 0x106B8 */ UNK_FUN_PTR unk_106B8;
    /* 0x106BC */ UNK_FUN_PTR unk_106BC;
    /* 0x106C0 */ UNK_FUN_PTR unk_106C0;
    /* 0x106C4 */ UNK_FUN_PTR unk_106C4;
    /* 0x106C8 */ UNK_FUN_PTR unk_106C8;
    /* 0x106CC */ struct_8085E9B0_unk_106CC unk_106CC;
    /* 0x106D0 */ UNK_TYPE1 unk_106D0[0x5C];
    /* 0x1072C */ Mtx* unk_1072C;
} struct_8085E9B0; // size = 0x10730

void mSM_menu_ovl_init(struct mSM* arg0);

#endif
