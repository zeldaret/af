#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "ultra64.h"
#include "m_mail.h"
#include "z64math.h"
#include "libc/stdint.h"
#include "other_types.h"
#include "unk.h"

struct Game_Play;
struct Submenu;
struct struct_8085E9B0;

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

typedef enum SubmenuProgramId {
    /*  0 */ SUBMENU_PROGRAM_0, // inventory, NONE? DEFAULT?
    /*  1 */ SUBMENU_PROGRAM_1, // inventory
    /*  2 */ SUBMENU_PROGRAM_2,
    /*  3 */ SUBMENU_PROGRAM_3,
    /*  4 */ SUBMENU_PROGRAM_LEDIT,
    /*  5 */ SUBMENU_PROGRAM_MAP,
    /*  6 */ SUBMENU_PROGRAM_6,
    /*  7 */ SUBMENU_PROGRAM_7,
    /*  8 */ SUBMENU_PROGRAM_8,
    /*  9 */ SUBMENU_PROGRAM_9,
    /* 10 */ SUBMENU_PROGRAM_10,
    /* 11 */ SUBMENU_PROGRAM_11,
    /* 12 */ SUBMENU_PROGRAM_BOARD,
    /* 13 */ SUBMENU_PROGRAM_13,
    /* 14 */ SUBMENU_PROGRAM_14,
    /* 15 */ SUBMENU_PROGRAM_15,
    /* 16 */ SUBMENU_PROGRAM_16,
    /* 17 */ SUBMENU_PROGRAM_17,
    /* 18 */ SUBMENU_PROGRAM_18,
    /* 19 */ SUBMENU_PROGRAM_19,
    /* 20 */ SUBMENU_PROGRAM_CATALOG,
    /* 21 */ SUBMENU_PROGRAM_MAX
} SubmenuProgramId;

typedef void (*SubmenuMoveFunc)(struct Submenu*);
typedef void (*SubmenuDrawFunc)(struct Submenu*, struct Game_Play*);

typedef struct Submenu {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ SubmenuProgramId programId;
    /* 0x08 */ SubmenuProgramId unk_08;
    /* 0x0C */ mSMMoveProcIndex moveProcIndex;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ void* linkedAllocStart;
    /* 0x28 */ void* linkedAllocEnd;
    /* 0x2C */ struct struct_8085E9B0* unk_2C;
    /* 0x30 */ SubmenuMoveFunc move;
    /* 0x34 */ SubmenuDrawFunc draw;
    /* 0x38 */ Mail_c mail;
    /* 0xDC */ u8 unk_DC;
    /* 0xDD */ u8 unk_DD;
    /* 0xDE */ u8 unk_DE;
    /* 0xDF */ u8 unk_DF;
    /* 0xE0 */ u16 unk_E0;
    /* 0xE2 */ u8 unk_E2;
    /* 0xE3 */ u8 unk_E3;
    /* 0xE4 */ xyz_t unk_E4;
} Submenu; // size = 0xF0

s32 SubmenuArea_IsPlayer(void);

void* mSM_ovlptr_dllcnv(void* vram, Submenu* submenu);

void mSM_submenu_ovlptr_init(struct Game_Play* game_play);
void mSM_submenu_ovlptr_cleanup(Submenu* submenu);

void load_player(Submenu* submenu);
void mSM_submenu_ct(Submenu* submenu);
void mSM_submenu_dt(Submenu* submenu);

void mSM_open_submenu(Submenu* submenu, SubmenuProgramId programId, s32 arg2, s32 arg3);
void mSM_open_submenu_new(Submenu* submenu, SubmenuProgramId programId, s32 arg2, s32 arg3, s32 arg4);
void mSM_open_submenu_new2(Submenu* submenu, SubmenuProgramId programId, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void mSM_submenu_ctrl(struct Game_Play* game_play);
void mSM_submenu_move(Submenu* submenu);
void mSM_submenu_draw(Submenu* submenu, struct Game_Play* game_play);

u32 mSM_check_open_inventory_itemlist(InventoryItemList itemlist, s32 arg1) ;

// void mSM_Object_Exchange_keep_new();
// void mSM_Object_Exchange_keep_new_MenuTexAndPallet();
// void mSM_Object_Exchange_keep_new_Menu();
// void mSM_Get_ground_tex_p();
// void mSM_Get_ground_pallet_p();

#endif
