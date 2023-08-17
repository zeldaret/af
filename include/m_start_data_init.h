#ifndef M_START_DATA_INIT_H
#define M_START_DATA_INIT_H

#include "ultra64.h"
#include "game.h"
#include "m_actor.h"

enum {
    mSDI_INIT_MODE_NEW,
    mSDI_INIT_MODE_NEW_PLAYER,
    mSDI_INIT_MODE_FROM,
    mSDI_INIT_MODE_PAK,
    mSDI_INIT_MODE_ERR,
    
    mSDI_INIT_MODE_NUM
};

enum {
    mSDI_MALLOC_FLAG_GAME,
    mSDI_MALLOC_FLAG_ZELDA,

    mSDI_MALLOC_FLAG_NUM
};

void famicom_emu_initial_common_data(void);
void decide_fruit(mActor_name_t* fruit);
void decide_fish_location(u8* fish_location);
void title_game_haniwa_data_init(void);
void mSDI_ClearMoneyPlayerHomeStationBlock(void);
void mSDI_PullTreeUT(mActor_name_t* item_p);
void mSDI_PullTreeBlock(u16* items_p, s32 ut);
void mSDI_PullTree(void);
void mSDI_PullTreeUnderPlayerBlock(void);
s32 mSDI_StartInitNew(Game* game, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitFrom(Game* game, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitNewPlayer(Game* game, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitPak(Game* game, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitErr(Game* game, s32 player_no, s32 malloc_flag);
void mSDI_StartInitAfter(Game* game, s32 renewal_reserve_flag, s32 malloc_flag);
s32 mSDI_StartInitBefore(Game* game, s32 player_no, s32 init_mode, s32 malloc_flag);
s32 mSDI_StartDataInit(Game* game, s32 player_no, s32 init_mode);

#endif
