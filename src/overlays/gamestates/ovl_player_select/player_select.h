#ifndef PLAYER_SELECT_H
#define PLAYER_SELECT_H

#include "ultra64.h"
#include "game.h"
#include "m_private_internals.h"
#include "m_view.h"

#define SELECT_PLAYER_NUM 5
#define SELECT_PLAYER_NAME_EXTRA 10
#define SELECT_NAME_LEN PLAYER_NAME_LEN + SELECT_PLAYER_NAME_EXTRA

typedef struct Game_PlayerSelect Game_PlayerSelect;
typedef void (*PlayerSelectInitProc)(Game_PlayerSelect*);

struct Game_PlayerSelect {
    /* 0x0000 */ Game game;
    /* 0x00E0 */ View view;
    /* 0x0200 */ PlayerSelectInitProc initProcs[SELECT_PLAYER_NUM];
    /* 0x0214 */ s32 playerNo;
    /* 0x0218 */ s32 status;
    /* 0x021C */ s32 mode;
    /* 0x0220 */ char playerNames[SELECT_PLAYER_NUM][SELECT_NAME_LEN];
    /* 0x027A */ u8 playerTypes[SELECT_PLAYER_NUM];
    /* 0x027F */ char landName[LAND_NAME_SIZE];
    /* 0x0287 */ u8 landExist;
}; // size = 0x288

typedef enum PlayerSelect_Status {
    /* 0 */ PLAYER_SELECT_STATUS_NONE,
    /* 1 */ PLAYER_SELECT_STATUS_SUCCESSFUL,
    /* 2 */ PLAYER_SELECT_STATUS_2,
    /* 3 */ PLAYER_SELECT_STATUS_3,
    /* 4 */ PLAYER_SELECT_STATUS_ERR_SAVE,
    /* 5 */ PLAYER_SELECT_STATUS_5,
    /* 6 */ PLAYER_SELECT_STATUS_ERR_PAK,
    /* 7 */ PLAYER_SELECT_STATUS_MAX,
} PlayerSelect_Status;

typedef enum PlayerSelect_Mode {
    /* 0 */ PLAYER_SELECT_MODE_SELECTION,
    /* 1 */ PLAYER_SELECT_MODE_PLAY,
    /* 2 */ PLAYER_SELECT_MODE_MAX,
} PlayerSelect_Mode;

typedef enum PlayerSelect_PlayerMode {
    /* 0 */ PLAYER_SELECT_PLAYER_MODE_NO_SAVE,
    /* 1 */ PLAYER_SELECT_PLAYER_MODE_UNREGISTERED,
    /* 2 */ PLAYER_SELECT_PLAYER_MODE_HOME,
    /* 3 */ PLAYER_SELECT_PLAYER_MODE_OUT,
    /* 4 */ PLAYER_SELECT_PLAYER_MODE_MAX,
} PlayerSelect_PlayerMode;

void player_select_init(Game *game);
void player_select_cleanup(Game *thisx);

#endif
