#include "game.h"
#include "segment_symbols.h"
#include "overlays/gamestates/ovl_select/select.h"
#include "overlays/gamestates/ovl_first_game/first_game.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl_second_game/second_game.h"
#include "overlays/gamestates/ovl_sys_romcheck/sys_romcheck.h"
#include "overlays/gamestates/ovl_trademark/trademark.h"
#include "overlays/gamestates/ovl_player_select/player_select.h"
#include "overlays/gamestates/ovl_save_menu/save_menu.h"
#include "overlays/gamestates/ovl_famicom_emu/famicom_emu.h"
#include "overlays/gamestates/ovl_prenmi/prenmi.h"

// Linker symbol declarations (used in the table below)
#define DEFINE_GAMESTATE(_typeName, _enumName, segmentName) DECLARE_SEGMENT(ovl_##segmentName);
#define DEFINE_GAMESTATE_INTERNAL(_typeName, _enumName)

#include "tables/gamestate_table.h"

#undef DEFINE_GAMESTATE
#undef DEFINE_GAMESTATE_INTERNAL

// Gamestate Overlay Table definition
#define DEFINE_GAMESTATE_INTERNAL(typeName, _enumName) \
    { NULL, 0, 0, NULL, NULL, NULL, typeName##_Init, typeName##_Destroy, NULL, NULL, 0, sizeof(typeName##State) },

#define DEFINE_GAMESTATE(typeName, _enumName, segmentName) \
    { NULL,                                                \
      SEGMENT_ROM_START(ovl_##segmentName),     \
      SEGMENT_ROM_END(ovl_##segmentName),       \
      SEGMENT_VRAM_START(ovl_##segmentName),                    \
      SEGMENT_VRAM_END(ovl_##segmentName),                      \
      NULL,                                                \
      segmentName##_init,                                     \
      segmentName##_cleanup,                                  \
      NULL,                                                \
      NULL,                                                \
      0,                                                   \
      sizeof(typeName##State) },

GameStateOverlay game_dlftbls[GAMESTATE_ID_MAX] = {
#include "tables/gamestate_table.h"
};

#undef DEFINE_GAMESTATE
#undef DEFINE_GAMESTATE_INTERNAL

GameStateId game_dlftbls_num = GAMESTATE_ID_MAX;
