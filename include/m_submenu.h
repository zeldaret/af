#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "ultra64.h"
#include "6BFE60.h"
#include "z64math.h"
#include "libc/stdint.h"
#include "other_types.h"
#include "unk.h"

struct Game_Play;
struct mSM;

typedef enum mSMMoveProcIndex {
    /* 0 */ MSM_MOVE_PROC_WAIT,
    /* 1 */ MSM_MOVE_PROC_PREWAIT,
    /* 2 */ MSM_MOVE_PROC_LINKWAIT,
    /* 3 */ MSM_MOVE_PROC_PLAY,
    /* 4 */ MSM_MOVE_PROC_END,
    /* 5 */ MSM_MOVE_PROC_MAX
} mSMMoveProcIndex;

typedef enum InventoryItemList {
    /*  0 */ INVENTORY_ITEM_LIST_0,
    /*  1 */ INVENTORY_ITEM_LIST_1,
    /*  2 */ INVENTORY_ITEM_LIST_ENTRUST,
    /*  3 */ INVENTORY_ITEM_LIST_3,
    /*  4 */ INVENTORY_ITEM_LIST_4,
    /*  5 */ INVENTORY_ITEM_LIST_SELL,
    /*  6 */ INVENTORY_ITEM_LIST_GIVE,
    /*  7 */ INVENTORY_ITEM_LIST_7,
    /*  8 */ INVENTORY_ITEM_LIST_TAKE,
    /*  9 */ INVENTORY_ITEM_LIST_FURNITURE,
    /* 10 */ INVENTORY_ITEM_LIST_MINIDISK,
    /* 11 */ INVENTORY_ITEM_LIST_SHRINE,
    /* 12 */ INVENTORY_ITEM_LIST_C,
    /* 13 */ INVENTORY_ITEM_LIST_ECHANGE,
    /* 14 */ INVENTORY_ITEM_LIST_E,
    /* 15 */ INVENTORY_ITEM_LIST_F,
    /* 16 */ INVENTORY_ITEM_LIST_MAX
} InventoryItemList;

typedef void (*struct_8085E9B0_unk_10670_unk_00)(struct mSM*);
typedef void (*struct_8085E9B0_unk_10670_unk_04)(struct mSM*, struct Game_Play*);

typedef struct struct_8085E9B0_unk_10000 {
    /* 0x10000 */ UNK_TYPE4 unk_00;
    /* 0x10004 */ UNK_TYPE1 unk_04[0x60];
    /* 0x10064 */ UNK_TYPE4 unk_64;
    /* 0x10068 */ UNK_TYPE4 unk_68[UNK_SIZE];
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
    /* 0x106CC */ UNK_FUN_PTR unk_106CC;
    /* 0x106D0 */ UNK_TYPE1 unk_106D0[0x5C];
    /* 0x1072C */ Mtx* unk_1072C;
} struct_8085E9B0; // size = 0x10730

typedef void (*mSM_play)(struct mSM*);
typedef void (*mSM_draw)(struct mSM*, struct Game_Play*);

typedef struct mSM {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ mSMMoveProcIndex moveProcIndex;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ void* linkedAllocStart;
    /* 0x28 */ void* linkedAllocEnd;
    /* 0x2C */ struct_8085E9B0* unk_2C;
    /* 0x30 */ mSM_play play; // name based on mSM_move_Play, consider renaming
    /* 0x34 */ mSM_draw draw;
    /* 0x38 */ mMl mail;
    /* 0xDC */ u8 unk_DC;
    /* 0xDD */ u8 unk_DD;
    /* 0xDE */ u8 unk_DE;
    /* 0xDF */ u8 unk_DF;
    /* 0xE0 */ u16 unk_E0;
    /* 0xE2 */ u8 unk_E2;
    /* 0xE3 */ u8 unk_E3;
    /* 0xE4 */ Vec3f unk_E4;
} mSM; // size = 0xF0

s32 SubmenuArea_IsPlayer(void);

void* mSM_ovlptr_dllcnv(void* vram, mSM* submenu);

void mSM_submenu_ovlptr_init(struct Game_Play* game_play);
void mSM_submenu_ovlptr_cleanup(mSM* submenu);

void load_player(mSM* submenu);
void mSM_submenu_ct(mSM* submenu);
void mSM_submenu_dt(mSM* arg0);

void mSM_open_submenu(mSM* submenu, s32 arg1, s32 arg2, s32 arg3);
void mSM_open_submenu_new(mSM* submenu, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void mSM_open_submenu_new2(mSM* submenu, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void mSM_submenu_ctrl(struct Game_Play* game_play);
void mSM_submenu_move(mSM* submenu);
void mSM_submenu_draw(mSM* submenu, struct Game_Play* game_play);

u32 mSM_check_open_inventory_itemlist(InventoryItemList itemlist, s32 arg1) ;

// void mSM_Object_Exchange_keep_new();
// void mSM_Object_Exchange_keep_new_MenuTexAndPallet();
// void mSM_Object_Exchange_keep_new_Menu();
// void mSM_Get_ground_tex_p();
// void mSM_Get_ground_pallet_p();

#endif
