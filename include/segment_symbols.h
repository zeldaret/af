#ifndef SEGMENT_SYMBOLS_H
#define SEGMENT_SYMBOLS_H

#include "ultra64.h"
#include "libc/stdint.h"
#include "other_types.h"


#define DECLARE_VRAM_SEGMENT(name) \
    extern u8 name ## _VRAM[]; \
    extern u8 name ## _VRAM_END[]

#define DECLARE_ROM_SEGMENT(name) \
    extern u8 name ## _ROM_START[]; \
    extern u8 name ## _ROM_END[]

#define DECLARE_DATA_SEGMENT(name)   \
    extern u8 name ## _DATA_START[]; \
    extern u8 name ## _DATA_END[]; \
    extern u8 name ## _DATA_SIZE[]

#define DECLARE_BSS_SEGMENT(name)   \
    extern u8 name ## _BSS_START[]; \
    extern u8 name ## _BSS_END[]

#define DECLARE_SEGMENT(name) \
    DECLARE_VRAM_SEGMENT(name); \
    DECLARE_ROM_SEGMENT(name); \
    DECLARE_DATA_SEGMENT(name); \
    DECLARE_BSS_SEGMENT(name)

#define SEGMENT_VRAM_START(segment) (segment ## _VRAM)
#define SEGMENT_VRAM_END(segment)   (segment ## _VRAM_END)
#define SEGMENT_VRAM_SIZE(segment)  ((uintptr_t)SEGMENT_VRAM_END(segment) - (uintptr_t)SEGMENT_VRAM_START(segment))

#define SEGMENT_ROM_START(segment) ((RomOffset)segment ## _ROM_START)
#define SEGMENT_ROM_END(segment)   ((RomOffset)segment ## _ROM_END)
#define SEGMENT_ROM_SIZE(segment)  (SEGMENT_ROM_END(segment) - SEGMENT_ROM_START(segment))
#define SEGMENT_ROM_SIZE_ALT(segment)  ((size_t)(segment ## _ROM_END - segment ## _ROM_START))

#define SEGMENT_DATA_SIZE_CONST(segment) ((RomOffset)segment ## _DATA_SIZE)

#define SEGMENT_BSS_START(segment) (segment ## _BSS_START)
#define SEGMENT_BSS_END(segment)   (segment ## _BSS_END)
#define SEGMENT_BSS_SIZE(segment)  ((uintptr_t)SEGMENT_BSS_END(segment) - (uintptr_t)SEGMENT_BSS_START(segment))


DECLARE_SEGMENT(header);

DECLARE_SEGMENT(ipl3);

DECLARE_SEGMENT(entry);

DECLARE_SEGMENT(boot);

DECLARE_SEGMENT(dmadata);

DECLARE_SEGMENT(segment_027130);

DECLARE_SEGMENT(segment_13D9A0); 

// DECLARE_SEGMENT();

DECLARE_SEGMENT(code);


// TODO: the rest of segments


DECLARE_SEGMENT(submenu_ovl);
DECLARE_SEGMENT(player_actor);

DECLARE_SEGMENT(tag_ovl);
DECLARE_SEGMENT(hand_ovl);
DECLARE_SEGMENT(haniwaPortrait_ovl);
DECLARE_SEGMENT(inventory_ovl);
DECLARE_SEGMENT(ovl__00789B60);
DECLARE_SEGMENT(ovl__0078A560);
DECLARE_SEGMENT(ovl__0078AE30);
DECLARE_SEGMENT(ledit_ovl);
DECLARE_SEGMENT(ovl__0078CB80);
DECLARE_SEGMENT(board_ovl);
DECLARE_SEGMENT(ovl__00792700);
DECLARE_SEGMENT(ovl__00794380);
DECLARE_SEGMENT(map_ovl);
DECLARE_SEGMENT(ovl__00797A50);
DECLARE_SEGMENT(ovl__00799580);
DECLARE_SEGMENT(ovl__0079A290);
DECLARE_SEGMENT(ovl__0079B120);
DECLARE_SEGMENT(ovl__0079C020);
DECLARE_SEGMENT(ovl__0079DA50);
DECLARE_SEGMENT(ovl__0079E430);
DECLARE_SEGMENT(ovl__0079F810);
DECLARE_SEGMENT(ovl__007A10E0);
DECLARE_SEGMENT(catalog_ovl);

DECLARE_SEGMENT(ac_set_ovl_insect);
DECLARE_SEGMENT(ac_set_ovl_gyoei);

DECLARE_SEGMENT(segment_00A58000);

DECLARE_SEGMENT(segment_00E02000);
DECLARE_SEGMENT(segment_00E03000);
DECLARE_SEGMENT(segment_00E04000);
DECLARE_SEGMENT(segment_00E0D000);


#endif
