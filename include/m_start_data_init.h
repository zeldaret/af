#ifndef M_START_DATA_INIT_H
#define M_START_DATA_INIT_H

#include "ultra64.h"
#include "game.h"
#include "m_actor.h"

typedef enum mSDI_INIT_MODE {
    /* 0 */ mSDI_INIT_MODE_NEW,
    /* 1 */ mSDI_INIT_MODE_NEW_PLAYER,
    /* 2 */ mSDI_INIT_MODE_FROM,
    /* 3 */ mSDI_INIT_MODE_PAK,
    /* 4 */ mSDI_INIT_MODE_ERR,

    /* 5 */ mSDI_INIT_MODE_NUM
} mSDI_INIT_MODE;

typedef enum mSDI_MALLOC_FLAG {
    /* 0 */ mSDI_MALLOC_FLAG_GAME,
    /* 1 */ mSDI_MALLOC_FLAG_ZELDA,
    
    /* 2 */ mSDI_MALLOC_FLAG_NUM
} mSDI_MALLOC_FLAG;

void famicom_emu_initial_common_data(void);
void decide_fruit(u16* fruit);
void decide_fish_location(u8* fish_location);
void title_game_haniwa_data_init(void);
void mSDI_ClearMoneyPlayerHomeStationBlock(void);
void mSDI_PullTreeUT(u16* item_p);
void mSDI_PullTreeBlock(u16* items_p, s32 ut);
void mSDI_PullTree(void);
void mSDI_PullTreeUnderPlayerBlock(void);
s32 mSDI_StartInitNew(Game* game2, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitFrom(Game* game2, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitNewPlayer(Game* game, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitPak(Game* game2, s32 player_no, s32 malloc_flag);
s32 mSDI_StartInitErr(Game* game, s32 player_no, s32 malloc_flag);
void mSDI_StartInitAfter(Game* game, s32 renewal_reserve_flag, s32 malloc_flag);
s32 mSDI_StartInitBefore(Game* game, s32 player_no, s32 init_mode, s32 malloc_flag);
s32 mSDI_StartDataInit(Game* game, s32 player_no, s32 init_mode);

#endif
