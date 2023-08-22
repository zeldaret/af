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

typedef void (*mSM_unk_30)(struct mSM*);
typedef void (*mSM_unk_34)(struct mSM*, struct Game_Play*);

typedef struct mSM {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ UNK_TYPE unk_10;
    /* 0x14 */ UNK_TYPE unk_14;
    /* 0x18 */ UNK_TYPE unk_18;
    /* 0x1C */ UNK_TYPE unk_1C;
    /* 0x20 */ UNK_TYPE unk_20;
    /* 0x24 */ void* unk_24;
    /* 0x28 */ void* unk_28;
    /* 0x2C */ UNK_TYPE1 unk_2C[0x4];
    /* 0x30 */ mSM_unk_30 unk_30;
    /* 0x34 */ mSM_unk_34 unk_34;
    /* 0x38 */ mMl unk_38;
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

void* mSM_ovlptr_dllcnv(void* vram, mSM* arg1);

void mSM_submenu_ovlptr_init(struct Game_Play* game_play);
void mSM_submenu_ovlptr_cleanup(mSM* arg0);

void load_player(mSM* arg0);
void mSM_submenu_ct(mSM* arg0);
void mSM_submenu_dt(mSM* arg0);

void mSM_open_submenu(mSM* arg0, s32 arg1, s32 arg2, s32 arg3);
void mSM_open_submenu_new(mSM* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void mSM_open_submenu_new2(mSM* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void mSM_submenu_ctrl(struct Game_Play* game_play);
void mSM_submenu_move(mSM* arg0);
void mSM_submenu_draw(mSM* arg0, struct Game_Play* game_play);

u32 mSM_check_open_inventory_itemlist(s32 arg0, s32 arg1) ;

// void mSM_Object_Exchange_keep_new();
// void mSM_Object_Exchange_keep_new_MenuTexAndPallet();
// void mSM_Object_Exchange_keep_new_Menu();
// void mSM_Get_ground_tex_p();
// void mSM_Get_ground_pallet_p();

#endif
