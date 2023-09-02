#include "m_submenu_ovl.h"
#include "m_submenu.h"
#include "m_lib.h"
#include "game.h"
#include "ovlmgr.h"
#include "PreRender.h"
#include "sys_matrix.h"
#include "z_std_dma.h"
#include "6BFE60.h"
#include "6E0F50.h"
#include "segment_symbols.h"

// gamestates
#include "overlays/gamestates/ovl_play/m_play.h"
#include "overlays/gamestates/ovl__00743CD0/_00743CD0.h"

// submenus
#include "overlays/submenu/ovl__00785700/m_inventory_ovl.h"
#include "overlays/submenu/ovl__0078A560/ovl__0078A560.h"
#include "overlays/submenu/ovl__0078AE30/ovl__0078AE30.h"
#include "overlays/submenu/ovl__0078BFB0/m_ledit_ovl.h"
#include "overlays/submenu/ovl__00795350/m_map_ovl.h"
#include "overlays/submenu/ovl__00797A50/ovl__00797A50.h"
#include "overlays/submenu/ovl__0079B120/ovl__0079B120.h"
#include "overlays/submenu/ovl__0079C020/ovl__0079C020.h"
#include "overlays/submenu/ovl__0079DA50/ovl__0079DA50.h"
#include "overlays/submenu/ovl__0078CB80/ovl__0078CB80.h"
#include "overlays/submenu/ovl__00789B60/ovl__00789B60.h"
#include "overlays/submenu/ovl__007908A0/m_board_ovl.h"
#include "overlays/submenu/ovl__00792700/ovl__00792700.h"
#include "overlays/submenu/ovl__00794380/ovl__00794380.h"
#include "overlays/submenu/ovl__00799580/ovl__00799580.h"
#include "overlays/submenu/ovl__0079A290/ovl__0079A290.h"
#include "overlays/submenu/ovl__0079E430/ovl__0079E430.h"
#include "overlays/submenu/ovl__0079F810/ovl__0079F810.h"
#include "overlays/submenu/ovl__007A10E0/ovl__007A10E0.h"
#include "overlays/submenu/ovl__007A28F0/m_catalog_ovl.h"
#include "overlays/submenu/ovl__00777AE0/ovl__00777AE0.h"
#include "overlays/submenu/ovl__007829E0/m_hand_ovl.h"
#include "overlays/submenu/ovl__00784FC0/ovl__00784FC0.h"

extern Gfx D_C012370[]; // inv_item_model

struct_8085E9B0 ovl_base;

typedef struct struct_8085DCF8 {
    /* 0x0 */ UNK_TYPE4 unk_0;
    /* 0x4 */ UNK_TYPE4 unk_4;
} struct_8085DCF8; // size = 0x8

// maybe same struct as struct_8085DCF8?
typedef struct struct_8085E4A0 {
    /* 0x0 */ UNK_PTR unk_0;
    /* 0x4 */ UNK_PTR unk_4;
} struct_8085E4A0; // size = 0x8


Vp D_8085DCD0_jp = { { { 0, 0, 0x1FF, 0 }, { 0, 0, 0x1FF, 0 } } };

Lights1 D_8085DCE0_jp = gdSPDefLights1(0x69, 0x5A, 0x5A, 0xFF, 0xFF, 0xF5, 0, 0x3C, 0x3C);

struct_8085DCF8 D_8085DCF8_jp[] = {{ 0x0C00A620, 0x0C00A6E0 },};
struct_8085DCF8 D_8085DD00_jp[] = {{ 0x0C00B720, 0x0C00B740 },};
struct_8085DCF8 D_8085DD08_jp[] = {{ 0x0C00DD40, 0x0C00DD80 },};
struct_8085DCF8 D_8085DD10_jp[] = {
    { 0x0C010FA0, 0x0C010FC0 },
    { 0x0C012400, 0x0C012420 },
    { 0x0C012620, 0x0C0126A0 },
    { 0x0C012640, 0x0C0128A0 },
    { 0x0C012660, 0x0C012AA0 },
};
struct_8085DCF8 D_8085DD38_jp[] = {{ 0x0C012680, 0x0C012CA0 },};
struct_8085DCF8 D_8085DD40_jp[] = {{ 0x0C00B2E0, 0x0C00B300 },};
struct_8085DCF8 D_8085DD48_jp[] = {
    { 0x0C010780, 0x0C0109A0 },
    { 0x0C010780, 0x0C010BA0 },
    { 0x0C010780, 0x0C010DA0 },
    { 0x0C010780, 0x0C0107A0 },
};
struct_8085DCF8 D_8085DD68_jp[] = {
    { 0x0C00F940, 0x0C00FF60 },
    { 0x0C00F8E0, 0x0C00F960 },
    { 0x0C00F900, 0x0C00FB60 },
    { 0x0C00F920, 0x0C00FD60 },
};
struct_8085DCF8 D_8085DD88_jp[] = {{ 0x0C00A680, 0x0C00ACE0 },};
struct_8085DCF8 D_8085DD90_jp[] = {
    { 0x0C004EA0, 0x0C005860 },
    { 0x0C004EE0, 0x0C005A60 },
    { 0x0C004F20, 0x0C005C60 },
    { 0x0C004F60, 0x0C005E60 },
    { 0x0C005020, 0x0C006460 },
    { 0x0C005160, 0x0C006E60 },
    { 0x0C0051A0, 0x0C007060 },
    { 0x0C0051E0, 0x0C007260 },
    { 0x0C005120, 0x0C006C60 },
    { 0x0C004E60, 0x0C005660 },
    { 0x0C005220, 0x0C007460 },
    { 0x0C004FA0, 0x0C006060 },
    { 0x0C004FE0, 0x0C006260 },
    { 0x0C005060, 0x0C006660 },
    { 0x0C0050A0, 0x0C006860 },
    { 0x0C0050E0, 0x0C006A60 },
    { 0x0C0052E0, 0x0C007A60 },
    { 0x0C005320, 0x0C007C60 },
    { 0x0C005360, 0x0C007E60 },
    { 0x0C0053E0, 0x0C008260 },
    { 0x0C0053A0, 0x0C008060 },
    { 0x0C005420, 0x0C008460 },
    { 0x0C005460, 0x0C008660 },
    { 0x0C0054A0, 0x0C008860 },
    { 0x0C0055A0, 0x0C009060 },
    { 0x0C0055E0, 0x0C009260 },
    { 0x0C005260, 0x0C007660 },
    { 0x0C0052A0, 0x0C007860 },
    { 0x0C005560, 0x0C008E60 },
    { 0x0C005520, 0x0C008C60 },
    { 0x0C0054E0, 0x0C008A60 },
    { 0x0C005620, 0x0C009460 },
};
struct_8085DCF8 D_8085DE90_jp[] = {{ 0x0C009720, 0x0C009740 },};
struct_8085DCF8 D_8085DE98_jp[] = {
    { 0x0C00EC60, 0x0C00F0E0 },
    { 0x0C009720, 0x0C009740 },
    { 0x0C010780, 0x0C0109A0 },
    { 0x0C00C800, 0x0C00C940 },
    { 0x0C00C900, 0x0C00D940 },
    { 0x0C00C8E0, 0x0C00D740 },
    { 0x0C00C8A0, 0x0C00D340 },
    { 0x0C00C880, 0x0C00D140 },
    { 0x0C00C840, 0x0C00CD40 },
    { 0x0C00C820, 0x0C00CB40 },
    { 0x0C00C920, 0x0C00DB40 },
    { 0x0C00C860, 0x0C00CF40 },
    { 0x0C00C8C0, 0x0C00D540 },
    { 0x0C010780, 0x0C0109A0 },
    { 0x0C00B940, 0x0C00B9C0 },
    { 0x0C00B9A0, 0x0C00C1C0 },
    { 0x0C00B9A0, 0x0C00BFC0 },
    { 0x0C00DD60, 0x0C00DF80 },
    { 0x0C00C3C0, 0x0C00C400 },
    { 0x0C00C3C0, 0x0C00C400 },
    { 0x0C0111C0, 0x0C0112C0 },
    { 0x0C0111E0, 0x0C0114C0 },
    { 0x0C011200, 0x0C0116C0 },
    { 0x0C011240, 0x0C011AC0 },
    { 0x0C011260, 0x0C011CC0 },
    { 0x0C0112A0, 0x0C0120C0 },
    { 0x0C011220, 0x0C0118C0 },
    { 0x0C011280, 0x0C011EC0 },
    { 0x0C010FA0, 0x0C010FC0 },
    { 0x0C010FA0, 0x0C010FC0 },
};
struct_8085DCF8 D_8085DF88_jp[] = {{ 0x0C00A6A0, 0x0C00AEE0 },};
struct_8085DCF8 D_8085DF90_jp[] = {{ 0x0C00A6C0, 0x0C00B0E0 },};
struct_8085DCF8 D_8085DF98_jp[] = {
    { 0x0C00E180, 0x0C00E220 },
    { 0x0C00E200, 0x0C00EA20 },
    { 0x0C00E1E0, 0x0C00E820 },
    { 0x0C00E1C0, 0x0C00E620 },
    { 0x0C00E1A0, 0x0C00E420 },
    { 0x0C00B500, 0x0C00B520 },
    { 0x0C009940, 0x0C009960 },
};
struct_8085DCF8 D_8085DFD0_jp[] = {
    { 0x0C00A640, 0x0C00A8E0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
    { 0x0C00A660, 0x0C00AAE0 },
};
struct_8085DCF8 D_8085E020_jp[] = {{ 0x0C00C3E0, 0x0C00C600 },};
struct_8085DCF8 D_8085E028_jp[] = {
    { 0x0C009C00, 0x0C00A420 },
    { 0x0C009C00, 0x0C00A220 },
    { 0x0C009C00, 0x0C009C20 },
    { 0x0C009C00, 0x0C00A020 },
    { 0x0C009C00, 0x0C009E20 },
    { 0x0C009C00, 0x0C00A420 },
    { 0x0C009C00, 0x0C00A420 },
    { 0x0C009C00, 0x0C00A420 },
    { 0x0C009B60, 0x0C00A420 },
    { 0x0C009B60, 0x0C00A220 },
    { 0x0C009B60, 0x0C009C20 },
    { 0x0C009B60, 0x0C00A020 },
    { 0x0C009B60, 0x0C009E20 },
    { 0x0C009B60, 0x0C00A420 },
    { 0x0C009B60, 0x0C00A420 },
    { 0x0C009B60, 0x0C00A420 },
    { 0x0C009B80, 0x0C00A420 },
    { 0x0C009B80, 0x0C00A220 },
    { 0x0C009B80, 0x0C009C20 },
    { 0x0C009B80, 0x0C00A020 },
    { 0x0C009B80, 0x0C009E20 },
    { 0x0C009B80, 0x0C00A420 },
    { 0x0C009B80, 0x0C00A420 },
    { 0x0C009B80, 0x0C00A420 },
    { 0x0C009BA0, 0x0C00A420 },
    { 0x0C009BA0, 0x0C00A220 },
    { 0x0C009BA0, 0x0C009C20 },
    { 0x0C009BA0, 0x0C00A020 },
    { 0x0C009BA0, 0x0C009E20 },
    { 0x0C009BA0, 0x0C00A420 },
    { 0x0C009BA0, 0x0C00A420 },
    { 0x0C009BA0, 0x0C00A420 },
    { 0x0C009BC0, 0x0C00A420 },
    { 0x0C009BC0, 0x0C00A220 },
    { 0x0C009BC0, 0x0C009C20 },
    { 0x0C009BC0, 0x0C00A020 },
    { 0x0C009BC0, 0x0C009E20 },
    { 0x0C009BC0, 0x0C00A420 },
    { 0x0C009BC0, 0x0C00A420 },
    { 0x0C009BC0, 0x0C00A420 },
    { 0x0C009BE0, 0x0C00A420 },
    { 0x0C009BE0, 0x0C00A220 },
    { 0x0C009BE0, 0x0C009C20 },
    { 0x0C009BE0, 0x0C00A020 },
    { 0x0C009BE0, 0x0C009E20 },
    { 0x0C009BE0, 0x0C00A420 },
    { 0x0C009BE0, 0x0C00A420 },
    { 0x0C009BE0, 0x0C00A420 },
    { 0x0C009660, 0x0C00A420 },
    { 0x0C009660, 0x0C00A220 },
    { 0x0C009660, 0x0C009C20 },
    { 0x0C009660, 0x0C00A020 },
    { 0x0C009660, 0x0C009E20 },
    { 0x0C009660, 0x0C00A420 },
    { 0x0C009660, 0x0C00A420 },
    { 0x0C009660, 0x0C00A420 },
    { 0x0C009680, 0x0C00A420 },
    { 0x0C009680, 0x0C00A220 },
    { 0x0C009680, 0x0C009C20 },
    { 0x0C009680, 0x0C00A020 },
    { 0x0C009680, 0x0C009E20 },
    { 0x0C009680, 0x0C00A420 },
    { 0x0C009680, 0x0C00A420 },
    { 0x0C009680, 0x0C00A420 },
    { 0x0C0096A0, 0x0C00A420 },
    { 0x0C0096A0, 0x0C00A220 },
    { 0x0C0096A0, 0x0C009C20 },
    { 0x0C0096A0, 0x0C00A020 },
    { 0x0C0096A0, 0x0C009E20 },
    { 0x0C0096A0, 0x0C00A420 },
    { 0x0C0096A0, 0x0C00A420 },
    { 0x0C0096A0, 0x0C00A420 },
    { 0x0C0096C0, 0x0C00A420 },
    { 0x0C0096C0, 0x0C00A220 },
    { 0x0C0096C0, 0x0C009C20 },
    { 0x0C0096C0, 0x0C00A020 },
    { 0x0C0096C0, 0x0C009E20 },
    { 0x0C0096C0, 0x0C00A420 },
    { 0x0C0096C0, 0x0C00A420 },
    { 0x0C0096C0, 0x0C00A420 },
    { 0x0C0096E0, 0x0C00A420 },
    { 0x0C0096E0, 0x0C00A220 },
    { 0x0C0096E0, 0x0C009C20 },
    { 0x0C0096E0, 0x0C00A020 },
    { 0x0C0096E0, 0x0C009E20 },
    { 0x0C0096E0, 0x0C00A420 },
    { 0x0C0096E0, 0x0C00A420 },
    { 0x0C0096E0, 0x0C00A420 },
    { 0x0C009700, 0x0C00A420 },
    { 0x0C009700, 0x0C00A220 },
    { 0x0C009700, 0x0C009C20 },
    { 0x0C009700, 0x0C00A020 },
    { 0x0C009700, 0x0C009E20 },
    { 0x0C009700, 0x0C00A420 },
    { 0x0C009700, 0x0C00A420 },
    { 0x0C009700, 0x0C00A420 },
};
struct_8085DCF8 D_8085E328_jp[] = {
    { 0x0C000660, 0x0C000E60 },
    { 0x0C0006A0, 0x0C001060 },
    { 0x0C0006E0, 0x0C001260 },
    { 0x0C000720, 0x0C001460 },
    { 0x0C0007A0, 0x0C001860 },
    { 0x0C0007E0, 0x0C001A60 },
    { 0x0C000820, 0x0C001C60 },
    { 0x0C000760, 0x0C001660 },
    { 0x0C000BE0, 0x0C003A60 },
    { 0x0C0008A0, 0x0C002060 },
    { 0x0C000860, 0x0C001E60 },
    { 0x0C0008E0, 0x0C002260 },
    { 0x0C000920, 0x0C002460 },
    { 0x0C000B20, 0x0C003460 },
    { 0x0C000B60, 0x0C003660 },
    { 0x0C000960, 0x0C002660 },
    { 0x0C0009A0, 0x0C002860 },
    { 0x0C000A20, 0x0C002C60 },
    { 0x0C0009E0, 0x0C002A60 },
    { 0x0C000C60, 0x0C003E60 },
    { 0x0C000D20, 0x0C004460 },
    { 0x0C000D60, 0x0C004660 },
    { 0x0C000CE0, 0x0C004260 },
    { 0x0C000CA0, 0x0C004060 },
    { 0x0C000A60, 0x0C002E60 },
    { 0x0C000AA0, 0x0C003060 },
    { 0x0C000AE0, 0x0C003260 },
    { 0x0C000C20, 0x0C003C60 },
    { 0x0C000BA0, 0x0C003860 },
    { 0x0C000DA0, 0x0C004860 },
    { 0x0C000DE0, 0x0C004A60 },
    { 0x0C000E20, 0x0C004C60 },
};
struct_8085DCF8 D_8085E428_jp[] = {
    { 0x0C010160, 0x0C010180 },
    { 0x0C010160, 0x0C010380 },
    { 0x0C010160, 0x0C010580 },
    { 0x0C000000, 0x0C000020 },
};
struct_8085DCF8 D_8085E448_jp[] = {
    { 0x0C00B960, 0x0C00BBC0 },
    { 0x0C000220, 0x0C000240 },
    { 0x0C000440, 0x0C000460 },
};
struct_8085DCF8* D_8085E460_jp[] = {
    D_8085DD40_jp,
    D_8085DD48_jp,
    D_8085DD68_jp,
    D_8085DD90_jp,
    D_8085DE90_jp,
    D_8085DE98_jp,
    D_8085DF88_jp,
    D_8085DF90_jp,
    D_8085DF98_jp,
    D_8085DFD0_jp,
    D_8085E020_jp,
    D_8085E448_jp,
    D_8085E028_jp,
    D_8085E328_jp,
    D_8085E448_jp,
    D_8085E428_jp,
};

struct_8085E4A0 D_8085E4A0_jp[] = {
    { (void* )0x0C00EC60, (void* )0x0C00F0E0 },
    { (void* )0x0C00EC60, (void* )0x0C00F2E0 },
    { (void* )0x0C00ECA0, (void* )0x0C00F4E0 },
    { (void* )0x0C00ECA0, (void* )0x0C00F6E0 },
    { (void* )0x0C00EC20, (void* )0x0C00ECE0 },
    { (void* )0x0C00EC20, (void* )0x0C00EEE0 },
};

#define SUBMENU_PROGRAM(name, construct, destruct, set_proc) \
    { SEGMENT_ROM_START(name), SEGMENT_ROM_END(name), SEGMENT_VRAM_START(name), SEGMENT_VRAM_END(name), construct, destruct, set_proc, false }

struct_8085E4D0 mSM_program_dlftbl[SUBMENU_PROGRAM_MAX] = {
    SUBMENU_PROGRAM(ovl__00785700, mIV_inventory_ovl_construct, mIV_inventory_ovl_destruct, mIV_inventory_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__00785700, mIV_inventory_ovl_construct, mIV_inventory_ovl_destruct, mIV_inventory_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__0078A560, func_8088306C_jp, func_808830E8_jp, func_80882FAC_jp),
    SUBMENU_PROGRAM(ovl__0078AE30, func_80884120_jp, func_808841A8_jp, func_80883F5C_jp),
    SUBMENU_PROGRAM(ovl__0078BFB0, mLE_ledit_ovl_construct, mLE_ledit_ovl_destruct, mLE_ledit_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__00795350, mMP_map_ovl_construct, mMP_map_ovl_destruct, mMP_map_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__00797A50, func_80895B04_jp, func_80895B9C_jp, func_80895A30_jp),
    SUBMENU_PROGRAM(ovl__0079B120, func_80898688_jp, func_80898710_jp, func_80898520_jp),
    SUBMENU_PROGRAM(ovl__0079C020, func_80899E34_jp, func_80899F00_jp, func_80899D84_jp),
    SUBMENU_PROGRAM(ovl__0079DA50, func_8089AB8C_jp, func_8089AC14_jp, func_8089AAE4_jp),
    SUBMENU_PROGRAM(ovl__0078CB80, func_808883F8_jp, func_808884E4_jp, func_80888354_jp),
    SUBMENU_PROGRAM(ovl__00789B60, func_80882778_jp, func_80882818_jp, func_808826B8_jp),
    SUBMENU_PROGRAM(ovl__007908A0, mBD_board_ovl_construct, mBD_board_ovl_destruct, mBD_board_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__00792700, func_8088C4A0_jp, func_8088C548_jp, func_8088C344_jp),
    SUBMENU_PROGRAM(ovl__00794380, func_8088D924_jp, func_8088D9D4_jp, func_8088D81C_jp),
    SUBMENU_PROGRAM(ovl__00799580, func_80896898_jp, func_80896938_jp, func_80896830_jp),
    SUBMENU_PROGRAM(ovl__0079A290, func_8089730C_jp, func_80897394_jp, func_8089728C_jp),
    SUBMENU_PROGRAM(ovl__0079E430, func_8089BE68_jp, func_8089BF10_jp, func_8089BCE0_jp),
    SUBMENU_PROGRAM(ovl__0079F810, func_808A40F0_jp, func_808A4188_jp, func_808A4058_jp),
    SUBMENU_PROGRAM(ovl__007A10E0, func_808A5D7C_jp, func_808A5E14_jp, func_808A5C28_jp),
    SUBMENU_PROGRAM(ovl__007A28F0, mCL_catalog_ovl_construct, mCL_catalog_ovl_destruct, mCL_catalog_ovl_set_proc),
    SUBMENU_PROGRAM(ovl__00777AE0, func_808787A0_jp, func_80878904_jp, func_80878904_jp),
    SUBMENU_PROGRAM(ovl__007829E0, mHD_hand_ovl_construct, mHD_hand_ovl_destruct, mHD_hand_ovl_destruct),
    SUBMENU_PROGRAM(ovl__00784FC0, func_8087D180_jp, func_8087D274_jp, func_8087D274_jp),
};

u8 D_8085E7D0_jp[SUBMENU_PROGRAM_MAX] = {
    0,
    0xE,
    0x10,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0xE,
    0,
    0,
    0x1E,
    0,
    0,
    0xE,
    0,
    0xC,
    0xC,
    0,
    0,
    0,
};

// Indexed by SubmenuProgramId
f32 D_FLT_8085E7E8_jp[][4] = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 75.0f, 0.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, -300.0f, 0.0f, 75.0f },
    { -300.0f, 0.0f, 75.0f, 0.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { -300.0f, 0.0f, 75.0f, 0.0f },
    { 0.0f, -300.0f, 0.0f, 75.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 300.0f, 0.0f, 75.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 300.0f, 0.0f, 75.0f },
    { 300.0f, 0.0f, 75.0f, 0.0f },
};

s32 D_8085E938_jp[] = { 1, 8, 2, 4 };

f32 D_8085E948_jp[][4] = { { 2.0f, 0.0f, 300.0f, 1.0f }, { 0.5f, 120.0f, 0.0f, -1.0f } };


void mSM_setup_view(mSM* arg0, GraphicsContext* gfxCtx, s32 arg1) {
    Mtx* var_t0;
    UNUSED s32 pad;
    Gfx* gfx;

    if (arg1 != 0) {
        var_t0 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        guOrtho(var_t0, -2560.0f, 2560.0f, -1920.0f, 1920.0f, 1.0f, 2000.0f, 1.0f);
        arg0->unk_2C->unk_1072C = var_t0;
    } else {
        var_t0 = arg0->unk_2C->unk_1072C;
    }

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;
    if (arg1 == 0) {
        Game_Play1938* var_a0;

        if (arg0->unk_00 != 4) {
            var_a0 = &((Game_Play*)gamePT)->unk_1938;
        } else {
            var_a0 = &((Game__00743CD0*)gamePT)->unk_00E0;
        }

        gDPPipeSync(gfx++);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, var_a0->unk_010, var_a0->unk_008, var_a0->unk_014, var_a0->unk_00C);
        gSPViewport(gfx++, &var_a0->vp);
        gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, gfxCtx->unk_2E4);
        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    }

    if (1) {}
    if (1) {}
    if (1) {}

    gSPMatrix(gfx++, var_t0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void mSM_set_char_matrix(GraphicsContext* gfxCtx) {
    Gfx* gfx;

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;
    gSPMatrix(gfx++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

#ifdef NON_EQUIVALENT
void mSM_cbuf_copy(GraphicsContext* gfxCtx, PreRender* render, s32 arg2, s32 arg3, s32 arg4) {
    s32 spCC;
    void* sp9C;
    void* sp98;
    Gfx* sp8C;
    // Gfx* temp_v0_11;
    // Gfx* temp_v0_12;
    // Gfx* temp_v0_13;
    // Gfx* temp_v0_14;
    // Gfx* temp_v0_15;
    // Gfx* temp_v0_16;
    // Gfx* temp_v0_17;
    // Gfx* temp_v0_6;
    // Gfx* temp_v0_8;
    // Gfx* temp_v0_9;
    s32 temp_a2;
    s32 temp_v0_7;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_v1;
    u16 temp_a0;
    u16 temp_v0;
    u16 var_ra;
    s32 var_t0;
    u16 var_t4;
    u16 var_t5;

    if (arg2 >= 0x13F) {
        return;
    }

    temp_v0 = render->unk_04;
    if (-(s32)temp_v0 >= arg2) {
        return;
    }

    temp_a0 = render->unk_06;
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (-(s32)temp_a0 >= arg3) {
        return;
    }

    if ((arg3 >= 0xEF)) {
        return;
    }

    if (arg2 < 0) {
        var_t5 = temp_v0 + arg2;
        var_t3 = -arg2;
        arg2 = 0;
    } else {
        var_t3 = 0;
        if ((temp_v0 + arg2) >= 0x140) {
            var_t5 = 0x140 - arg2;
        } else {
            var_t5 = temp_v0;
        }
    }

    var_t4 = 0x140;
    if (arg3 < 0) {
        var_t0 = temp_a0 + arg3;
        var_v1 = -arg3;
        arg3 = 0;
    } else {
        var_v1 = 0;
        if ((temp_a0 + arg3) >= 0xF0) {
            var_t0 = 0xEF - arg3;
        } else {
            var_t0 = temp_a0;
        }
    }

    OPEN_DISPS(gfxCtx);

    var_ra = temp_a0;
    if (arg4 == 0) {
        spCC = 0x140;
        var_t4 = temp_v0;
        sp9C = gfxCtx->unk_2E4;
        var_a1 = arg2;
        var_t1 = arg3;
        var_t2 = var_v1;
        var_a2 = var_t3;
        sp98 = render->unk_14;
    } else {
        spCC = (s32)temp_v0;
        var_ra = 0xF0;
        var_a1 = var_t3;
        var_t1 = var_v1;
        sp9C = render->unk_14;
        var_t2 = arg3;
        var_a2 = arg2;
        sp98 = gfxCtx->unk_2E4;
    }

    var_a3 = 0x1000 / (s32)(((var_t5 + 3) & ~3) * 2);
    if (arg4 != 0) {
        sp8C = POLY_OPA_DISP;
        render->unk_00 = 0x140;
        render->unk_02 = 0xF0;
        render->unk_10 = gfxCtx->unk_2E4;
        PreRender_CopyRGBC(render, &sp8C, arg2 - var_t3, arg3 - var_v1);
        POLY_OPA_DISP = sp8C;
    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                  G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING |
                                                  0x0040F9FA);

        gDPSetOtherMode(POLY_OPA_DISP++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2);

        // temp_v0_5 = gfxCtx->polyOpa.p;
        // gfxCtx->polyOpa.p = temp_v0_5 + 8;
        // temp_v0_5->words.w0 = ((var_t4 - 1) & 0xFFF) | 0xFF100000;
        // temp_v0_5->words.w1 = (u32) sp98;
        gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, var_t4, sp98);

        // temp_v0_6 = gfxCtx->polyOpa.p;
        // gfxCtx->polyOpa.p = temp_v0_6 + 8;
        // temp_v0_6->words.w0 = 0xED000000;
        // temp_v0_6->words.w1 = (((s32) ((f32) var_t4 * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) var_ra * 4.0f) & 0xFFF);
        gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, (s32)var_t4 * 4.0f, (s32)var_ra * 4.0f);

        while ((s32)var_t0 > 0) {
            if ((s32)var_t0 < var_a3) {
                var_a3 = (s32)var_t0;
            }
            var_t0 -= var_a3;

            temp_v0_7 = ((var_t5 + var_a1) - 1);

#if 0
            temp_v0_8 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_8 + 8;
            temp_v0_8->words.w0 = ((spCC - 1) & 0xFFF) | 0xFD100000;
            temp_v0_8->words.w1 = (u32) sp9C;
            // gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0x12345678);

            temp_v0_9 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_9 + 8;
            temp_v0_9->words.w1 = 0x07000000;
            temp_v0_9->words.w0 = ((((s32) (((temp_v0_7 - var_a1) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;

            //temp_v0_10 = gfxCtx->polyOpa.p;
            //gfxCtx->polyOpa.p = temp_v0_10 + 8;
            //temp_v0_10->words.w1 = 0x00000000;
            //temp_v0_10->words.w0 = 0xE6000000;
            gDPLoadSync(POLY_OPA_DISP++);

            temp_v0_11 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_11 + 8;
            temp_a2 = var_t1 + var_a3;
            temp_v0_11->words.w0 = (((var_a1 * 4) & 0xFFF) << 0xC) | 0xF4000000 | ((var_t1 * 4) & 0xFFF);
            temp_v0_11->words.w1 = (((temp_v0_7 * 4) & 0xFFF) << 0xC) | 0x07000000 | (((temp_a2 - 1) * 4) & 0xFFF);

            temp_v0_12 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_12 + 8;
            temp_v0_12->words.w1 = 0x00000000;
            temp_v0_12->words.w0 = 0xE7000000;

            temp_v0_13 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_13 + 8;
            temp_v0_13->words.w1 = 0x00000000;
            temp_v0_13->words.w0 = ((((s32) (((temp_v0_7 - var_a1) * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;

            temp_v0_14 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_14 + 8;
            temp_v0_14->words.w1 = (((temp_v0_7 * 4) & 0xFFF) << 0xC) | (((temp_a2 - 1) * 4) & 0xFFF);
            temp_v0_14->words.w0 = (((var_a1 * 4) & 0xFFF) << 0xC) | 0xF2000000 | ((var_t1 * 4) & 0xFFF);
#endif
            gDPLoadTextureTile(POLY_OPA_DISP++, sp9C, G_IM_FMT_RGBA, G_IM_SIZ_16b, spCC, 0, var_a1, var_t1, temp_v0_7,
                               temp_a2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

#if 0
            temp_v0_15 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_15 + 8;
            temp_v0_15->words.w0 = ((((((var_a2 + var_t5) - 1) * 4) & 0xFFF) << 0xC) | 0xE4000000) | (((var_t2 + var_a3 - 1) * 4) & 0xFFF);
            temp_v0_15->words.w1 = (((var_a2 * 4) & 0xFFF) << 0xC) | ((var_t2 * 4) & 0xFFF);

            temp_v0_16 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_16 + 8;
            temp_v0_16->words.w0 = 0xE1000000;
            temp_v0_16->words.w1 = (var_a1 << 0x15) | ((var_t1 << 5) & 0xFFFF);

            temp_v0_17 = gfxCtx->polyOpa.p;
            gfxCtx->polyOpa.p = temp_v0_17 + 8;
            temp_v0_17->words.w0 = 0xF1000000;
            temp_v0_17->words.w1 = 0x10000400;
#endif
            gSPTextureRectangle(POLY_OPA_DISP++, (var_a2 * 4), (var_t2 * 4), (((var_a2 + var_t5) - 1) * 4),
                                ((var_t2 + var_a3 - 1) * 4), G_TX_RENDERTILE, (var_a1 << 0x5), (var_t1 << 5), 0x1000,
                                0x0400);

            var_t1 = temp_a2;

            var_t2 = var_t2 + var_a3;
        }
    }

    CLOSE_DISPS(gfxCtx);
}
#else
void mSM_cbuf_copy(GraphicsContext* gfxCtx, PreRender* render, s32 arg2, s32 arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_cbuf_copy.s")
#endif

// mSM_set_drawMode?
void func_8085C20C_jp(GraphicsContext* gfxCtx, struct_func_8085C20C_jp_arg1* arg1, f32 arg2, f32 xAt, s16 angle) {
    s32 temp_a3 = arg1->unk_04;
    s32 temp_t1 = arg1->unk_06;
    f32 temp_fv1;
    f32 temp_fa0;

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPClearGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                              G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING |
                                              0x0040F9FA);
    gSPTexture(POLY_OPA_DISP++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_SHADE, G_CC_SHADE);
    gDPSetOtherMode(POLY_OPA_DISP++,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);

    temp_fv1 = temp_a3;
    temp_fa0 = temp_t1;

    gDPSetScissorFrac(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, temp_fv1 * 4.0f, temp_fa0 * 4.0f);

    gSPClipRatio(POLY_OPA_DISP++, FRUSTRATIO_1);

    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a3, arg1->unk_20);

    gDPSetFillColor(POLY_OPA_DISP++, 0xFFFCFFFC);

    gDPFillRectangle(POLY_OPA_DISP++, 0, 0, temp_a3 - 1, temp_t1 - 1);

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetColorImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_a3, arg1->unk_14);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetDepthImage(POLY_OPA_DISP++, arg1->unk_20);

    {
        Vp* vp = GRAPH_ALLOC(gfxCtx, sizeof(Vp));
        Mtx* sp84 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        Mtx* sp54 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
        u16 sp7E;

        if (vp == NULL) {
            vp = &D_8085DCD0_jp;
        } else {
            vp->vp.vtrans[2] = 0x1FF;
            vp->vp.vtrans[3] = 0;
            vp->vp.vscale[0] = vp->vp.vtrans[0] = temp_a3 * 2;
            vp->vp.vscale[1] = vp->vp.vtrans[1] = temp_t1 * 2;
            vp->vp.vscale[2] = vp->vp.vtrans[2];
            vp->vp.vscale[3] = vp->vp.vtrans[3];
        }

        gSPViewport(POLY_OPA_DISP++, vp);

        if (temp_a3 - 1 != 0x7F) {
            guPerspective(sp84, &sp7E, 35.0f, temp_fv1 / temp_fa0, 1.0f, 2000.0f, 1.0f);
        } else {
            guPerspective(sp84, &sp7E, 20.0f, temp_fv1 / temp_fa0, 100.0f, 800.0f, 1.0f);
        }

        gSPPerspNormalize(POLY_OPA_DISP++, sp7E);
        gSPMatrix(POLY_OPA_DISP++, sp84, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        {
            f32 yEye;
            f32 zEye;

            if (angle == 0x4000) {
                angle = 0x4100;
            } else if (angle == -0x4000) {
                angle = -0x3F00;
            }

            yEye = sin_s(angle) * arg2 + xAt;
            zEye = cos_s(angle) * arg2;
            if ((angle < -0x4000) || (angle >= 0x4000)) {
                guLookAt(sp54, 0.0f, yEye, zEye, 0.0f, xAt, 0.0f, 0.0f, -1.0f, 0.0f);
            } else {
                guLookAt(sp54, 0.0f, yEye, zEye, 0.0f, xAt, 0.0f, 0.0f, 1.0f, 0.0f);
            }
        }

        gSPMatrix(POLY_OPA_DISP++, sp54, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        gSPSetLights1(POLY_OPA_DISP++, D_8085DCE0_jp);
    }

    POLY_OPA_DISP = gfx_set_fog_nosync(POLY_OPA_DISP++, 0xFFU, 0xFFU, 0xFFU, 0xFF, 0x3D0, 0x500);

    CLOSE_DISPS(gfxCtx);
}

u8 func_8085C7A4_jp(u16 arg0) {
    return arg0;
}

#ifdef NON_EQUIVALENT
// float messed up
// maybe equivalent, but hard to tell
void mSM_draw_item(GraphicsContext* gfxCtx, f32 arg1, f32 arg2, f32 arg3, u16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    struct_8085DCF8* var_a1; // spAC
    s32 pad;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;
    s32 temp_v0;
    void* var_a2_2;
    s32 temp;

    Gfx* gfx;

    var_a2 = -1;
    var_a3 = 0;
    if (arg3 < 0.05f) {
        return;
    }

    if (arg5 != 0) {
        if (arg7 >= 6) {
            var_a1 = &D_8085DD38_jp;
            if (arg7 >= 0xC) {
                var_a3 = 1;
            }
        } else {
            var_a1 = &D_8085DD10_jp[arg7];
        }
    } else if (((s32) arg4 >= 0x15B0) && ((s32) arg4 < 0x17AC)) {
        var_a1 = &D_8085DD00_jp;
    } else if (((s32) arg4 >= 0x1E3C) && ((s32) arg4 < 0x1EA0)) {
        var_a1 = &D_8085DD08_jp;
    } else if (((s32) (arg4 & 0xF000) >> 0xC) == 1) {
        var_a1 = &D_8085DCF8_jp;
    } else {
        temp_v0 = func_8085C7A4_jp(arg4);

        var_a2 = (s32) (arg4 & 0xF00) >> 8;
        if (var_a2 == 0xE) {
            // var_a1 = *(D_8085E460_jp + (var_a2 * 4)) + (arg7 * 8);
            var_a1 = &D_8085E460_jp[var_a2][arg7];
        } else if ((var_a2 == 0) || (var_a2 == 4) || (var_a2 == 6) || (var_a2 == 7) || (var_a2 == 0xA) || (var_a2 == 0xB)) {
            // var_a1 = *(D_8085E460_jp + (var_a2 * 4));
            var_a1 = &D_8085E460_jp[var_a2][0];
        } else if (var_a2 == 2) {
            if (((s32) arg4 >= 0x2204) && ((s32) arg4 < 0x2224)) {
                var_a1 = &D_8085DD88_jp;
            } else {
                var_a1 = &D_8085DD68_jp[temp_v0];
            }
        } else {
            //var_a1 = *(D_8085E460_jp + (var_a2 * 4)) + (temp_v0 * 8);
            var_a1 = &D_8085E460_jp[var_a2][temp_v0];
        }
    }

    if (((var_a2 == 3) || (var_a2 == 0xD)) && (arg7 != 0)) {
        var_a2_2 = var_a1->unk_0 + 0x20;
    } else {
        var_a2_2 = var_a1->unk_0;
    }

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;

    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);


    if (arg6 != 0) {
        if (var_a3 != 0) {
            var_v1 = (s32) ((arg7 * -0xFF) + 0x17E8) / 13;
        } else {
            var_v1 = 0xFF;
        }

        gDPSetPrimColor(gfx++, 0, 0xFF, 255, 255, 255, var_v1);
    } else {
        var_v1 = 0xFF;

        gDPSetPrimColor(gfx++, 0, 0x64, 115, 160, 255, var_v1);
    }

    if (arg8 != 0) {
        gDPSetBlendColor(gfx++, 255, 255, 255, 40);
    } else if (var_v1 == 0xFF) {
        gDPSetBlendColor(gfx++, 255, 255, 255, 254);
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
    } else {
        gDPSetBlendColor(gfx++, 255, 255, 255, 40);
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    }

    gDPPipeSync(gfx++);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPLoadTLUT_pal16(gfx++, 15, Lib_SegmentedToVirtual(var_a2_2));
    if (arg3) {}
    gDPLoadTextureBlock_4b(gfx++, Lib_SegmentedToVirtual(var_a1->unk_4), G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    {
        s32 ar1;
        s32 ar2;
        s32 ar3;
        s32 ar4;
        s32 ar5;
        s32 ar6;
        s32 ar7;
        s32 ar8;
        s32 ar9;

        temp = (arg1 * 0.975f);

        ar1 = (s32) (((temp + 160.0f) - 12.0f * arg3) * 4.0f);
        ar2 = (s32) (((120.0f - arg2) - 12.0f * arg3) * 4.0f);
        ar3 = (s32) ((24.0f * arg3 + ((temp + 160.0f) - 12.0f * arg3)) * 4.0f);
        ar4 = (s32) ((24.0f * arg3 + ((120.0f - arg2) - 12.0f * arg3)) * 4.0f);
        ar5 = 0;
        ar6 = 0;
        ar7 = 0;
        ar8 = (s32) ((1.0f / arg3) * 1365.3334f);
        ar9 = (s32) ((1.0f / arg3) * 1365.3334f);

        gfx = func_800BE320_jp(gfx, ar1, ar2, ar3, ar4, ar5, ar6, ar7, ar8, ar9);
    }

    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);
    gDPSetTexturePersp(gfx++, G_TP_PERSP);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}
#else
void mSM_draw_item(GraphicsContext* gfxCtx, f32 arg1, f32 arg2, f32 arg3, u16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_draw_item.s")
#endif

#ifdef NON_MATCHING
// stack issues
void mSM_draw_mail(GraphicsContext* arg0, f32 arg1, f32 arg2, f32 arg3, struct_func_8085CE18_jp_arg4* arg4, s32 arg5, s32 arg6) {
    struct_8085E4A0* temp_a1;
    s32 var_t0;
    UNUSED s32 pad;
    Gfx* gfx;

    if (mMl_check_send_mail(arg4) != 0) {
        var_t0 = 2;
    } else if ((arg4->unk_26 == 4) || (arg4->unk_26 == 2)) {
        var_t0 = 4;
    } else {
        var_t0 = 0;
    }

    if (arg4->unk_24 != 0) {
        var_t0 += 1;
    }

    Matrix_scale(16.0f, 16.0f, 1.0f, MTXMODE_NEW);
    Matrix_translate(arg1, arg2, 140.0f, MTXMODE_APPLY);
    Matrix_scale(arg3, arg3, 1.0f, MTXMODE_APPLY);

    if (1) {}

    OPEN_DISPS(arg0);

    gfx = POLY_OPA_DISP;

    gDPPipeSync(gfx++);
    gSPMatrix(gfx++, _Matrix_to_Mtx_new(arg0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    temp_a1 = &D_8085E4A0_jp[var_t0];

    gSPSegment(gfx++, 0x09, Lib_SegmentedToVirtual(temp_a1->unk_0));
    gSPSegment(gfx++, 0x0A, Lib_SegmentedToVirtual(temp_a1->unk_4));
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetBlendColor(gfx++, 255, 255, 255, 40);

    if (arg5 != 0) {
        gDPSetPrimColor(gfx++, 0, 0xFF, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gfx++, 0, 0x82, 255, 110, 105, 255);
    }

    if (arg6 == 0) {
        gDPSetCombineLERP(gfx++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
    }

    gSPDisplayList(gfx++, D_C012370);
    gDPPipeSync(gfx++);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(arg0);
}
#else
void mSM_draw_mail(GraphicsContext* arg0, f32 arg1, f32 arg2, f32 arg3, struct_func_8085CE18_jp_arg4* arg4, s32 arg5, s32 arg6);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_draw_mail.s")
#endif

void func_8085D094_jp(mSM* arg0) {
    struct_8085E9B0_unk_10000* sp2C = &arg0->unk_2C->unk_10000;
    void* vram;
    s32 romStart;

    if (sp2C->unk_04) {
        return;
    }

    //! FAKE: needs s32 instead of unsigned type
    romStart = SEGMENT_ROM_START(segment_00A58000);

    vram = sp2C->unk_00;
    sp2C->unk_08 = vram;

    DmaMgr_RequestSyncDebug(vram, romStart, SEGMENT_ROM_SIZE(segment_00A58000), "../m_submenu_ovl.c", 0x7C0);
    sp2C->unk_00 = (void* ) ALIGN16(SEGMENT_ROM_SIZE(segment_00A58000) + (uintptr_t)vram);

    sp2C->unk_04 = 1;
}

void mSM_ovl_prog_seg(mSM* arg0, struct_8085E4D0* arg1) {
    struct_8085E9B0_unk_10000* temp;
    UNUSED s32 pad;
    void* allocatedVram;
    struct_8085E4D0_unk_10 temp_a1;
    struct_8085E4D0_unk_10 new_var;

    temp = &arg0->unk_2C->unk_10000;
    if (arg1->unk_1C == 1) {
        new_var = arg1->construct;
        new_var(arg0);
        return;
    }

    allocatedVram = arg0->linkedAllocEnd;
    ovlmgr_Load(arg1->vromStart, arg1->vromEnd, arg1->vramStart, arg1->vramEnd, allocatedVram);
    arg0->linkedAllocEnd =
        (void*)((uintptr_t)allocatedVram + ALIGN64((uintptr_t)arg1->vramEnd - (uintptr_t)arg1->vramStart));

    temp_a1 = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->construct - (uintptr_t)arg1->vramStart);
    temp_a1(arg0);
    arg1->construct = temp_a1;

    //! FAKE
dummy_label_595693:
    arg1->destruct = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->destruct - (uintptr_t)arg1->vramStart);
    arg1->set_proc = (void*)((uintptr_t)allocatedVram + (uintptr_t)arg1->set_proc - (uintptr_t)arg1->vramStart);

    arg1->unk_1C = 1;
    temp->unk_68[temp->unk_64] = arg1;
    temp->unk_64++;

    //! FAKE
    if (temp_a1) {}
}

void mSM_set_other_seg(mSM* arg0) {
    s32 temp = arg0->unk_08;
    u32 var_v1 = D_8085E7D0_jp[temp];

    if (var_v1 & 2) {
        func_8085D094_jp(arg0);
    }
    if (var_v1 & 4) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[SUBMENU_PROGRAM_21]);
    }
    if (var_v1 & 8) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[SUBMENU_PROGRAM_HAND]);
    }
    if (var_v1 & 0x10) {
        mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[SUBMENU_PROGRAM_23]);
    }
}

void mSM_set_before_menu_proc(mSM* arg0) {
    SubmenuProgramId programId = arg0->programId;
    struct_8085E9B0_unk_10088* temp;

    mSM_program_dlftbl[programId].set_proc(arg0);
    arg0->unk_08 = programId;

    //! FAKE
    if (((!programId) && (!programId)) && (!programId)) {}

    temp = &arg0->unk_2C->unk_10088[programId];

    temp->unk_14 = NULL;
}

void mSM_set_new_seg(mSM* arg0) {
    SubmenuProgramId programId = arg0->programId;

    mSM_ovl_prog_seg(arg0, &mSM_program_dlftbl[programId]);
    arg0->unk_08 = programId;
}

void mSM_set_new_start_data(mSM* arg0) {
    SubmenuProgramId programId = arg0->programId;
    struct_8085E9B0_unk_10088* temp_v1 = &arg0->unk_2C->unk_10088[programId];
    f32* temp_a1 = D_FLT_8085E7E8_jp[programId];

    temp_v1->unk_00 = programId;
    temp_v1->unk_18 = temp_a1[0];
    temp_v1->unk_1C = temp_a1[1];
    temp_v1->unk_20 = temp_a1[2];
    temp_v1->unk_24 = temp_a1[3];
    temp_v1->unk_38 = arg0->unk_10;
    temp_v1->unk_3C = arg0->unk_14;
    temp_v1->unk_40 = arg0->unk_18;
    temp_v1->unk_44 = arg0->unk_1C;

    if ((programId == SUBMENU_PROGRAM_1) && (arg0->unk_10 == 0xE)) {
        temp_v1->unk_18 = -300.0f;
    }
}

void func_8085D43C_jp(mSM* arg0, void** arg1, func_8085D43C_jp_arg2* arg2) {
    void* temp_a0 = arg0->unk_2C->unk_10000.unk_00;
    size_t size;

    *arg1 = temp_a0;
    size = arg2->vromEnd - arg2->vromStart;
    DmaMgr_RequestSyncDebug(temp_a0, arg2->vromStart, size, "../m_submenu_ovl.c", 2307);
    arg0->unk_2C->unk_10000.unk_00 = (void*)ALIGN16((uintptr_t)size + (uintptr_t)temp_a0);
}

void mSM_move_chg_base(struct_mSM_move_chg_base_arg0* arg0, u32 arg1) {
    arg0->unk_04 = 0;
    arg0->unk_34 = arg1;
    if (arg1 & 1) {
        arg0->unk_30 = 1;
    } else {
        arg0->unk_30 = 4;
    }
}

void mSM_make_trigger_data(mSM* arg0) {
    s32 var_a0 = (getButton() & 0xF) | getTrigger();
    struct_8085E9B0_unk_10670* temp_v1 = &arg0->unk_2C->unk_10670;

    if (gamePT->controller.moveR > 0.5f) {
        u16 temp = gamePT->controller.moveAngle + 0x2000;

        var_a0 |= D_8085E938_jp[temp >> 0xE];
    }

    if (var_a0 == temp_v1->unk_20) {
        if (temp_v1->unk_24 > 0) {
            temp_v1->unk_24--;
            var_a0 = 0;
        } else {
            temp_v1->unk_24 = 1;
        }
    } else {
        temp_v1->unk_20 = var_a0;
        temp_v1->unk_24 = 0xC;
    }

    temp_v1->unk_1C = var_a0;
}

#ifdef NON_MATCHING
// regalloc
void mSM_save_before_func(mSM* arg0) {
    struct_8085E9B0_unk_10088 *new_var2;
    SubmenuProgramId temp_a2;
    struct_8085E9B0* temp_v0;
    struct_8085E9B0_unk_10088* temp_v1;

    temp_v0 = arg0->unk_2C;
    temp_v1 = &temp_v0->unk_10088[arg0->programId];

    temp_a2 = arg0->unk_08;
    temp_v1->unk_08 = temp_a2;
    temp_v1->unk_0C = temp_v0->unk_10670.unk_00;
    temp_v1->unk_10 = temp_v0->unk_10670.unk_04;

    if (arg0->programId) { }
    new_var2 = &temp_v0->unk_10088[temp_v1->unk_08];

    new_var2->unk_14 = arg0->programId;
}
#else
void mSM_save_before_func(mSM* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_save_before_func.s")
#endif

void mSM_set_proc(mSM* arg0) {
    mSM_save_before_func(arg0);
    mSM_set_new_start_data(arg0);
    mSM_set_new_seg(arg0);
    mSM_set_other_seg(arg0);
}

void mSM_tex_move(mSM* arg0) {
    struct_8085E9B0_unk_10670* temp_v0;

    temp_v0 = &arg0->unk_2C->unk_10670;
    temp_v0->unk_28 += 0.707f;
    temp_v0->unk_2C += 0.707f;

    while (temp_v0->unk_28 >= 1024.0f) {
        temp_v0->unk_28 -= 1024.0f;
    }

    while (temp_v0->unk_2C >= 1024.0f) {
        temp_v0->unk_2C -= 1024.0f;
    }
}

#if 0
void mSM_return_func(mSM* arg0, struct_mSM_return_func_arg1* arg1) {
    s32 temp_t6;
    struct_8085E9B0* temp_v1;
    struct_8085E9B0_unk_10088* temp_v0;

    if (arg1->unk_14 != 0) {
        temp_v1 = arg0->unk_2C;
        temp_v0 = &temp_v1->unk_10088[arg1->unk_14];
        temp_v0->unk_08 = arg1->unk_08;
        temp_v0->unk_0C = arg1->unk_0C;
        temp_v0->unk_10 = arg1->unk_10;
        temp_v1->unk_10088[arg1->unk_14].unk_14 = arg1->unk_14;
    } else {
        temp_v1 = arg0->unk_2C;
        arg0->unk_04 = arg1->unk_08;
        if (arg0->unk_04 == 0) {
            while (temp_v1->unk_10000.unk_64 != 0) {
                temp_t6 = temp_v1->unk_10000.unk_64 - 1;
                temp_v1->unk_10000.unk_64 = temp_t6;
                temp_v1->unk_10000.unk_68[temp_t6]->unk_14(arg0);
            }
            arg0->moveProcIndex = MSM_MOVE_PROC_END;
            arg0->play = none_proc1;
            arg0->unk_08 = arg1->unk_08;
            arg0->unk_2C->unk_10670.unk_00 = none_proc1;
            arg0->unk_2C->unk_10670.unk_04 = none_proc1;
        } else {
            mSM_set_before_menu_proc(arg0);
        }
    }

    arg1->unk_2C = 0;
    arg1->unk_08 = 0;
    arg1->unk_14 = 0;
    arg1->unk_04 = 0;
    arg1->unk_30 = 0;
}
#else
void mSM_return_func(mSM* arg0, struct_mSM_return_func_arg1* arg1);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/submenu_ovl/m_submenu_ovl/mSM_return_func.s")
#endif

s32 mSM_move_menu(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    if (((*arg0 - arg3) * arg5) >= 0.0f) {
        *arg1 *= arg2;
        if (*arg1 < 1.0f) {
            *arg1 = 1.0f;
        } else if (*arg1 > 75.0f) {
            *arg1 = 75.0f;
        }
    }

    *arg0 += *arg1 * arg5;
    if (((*arg0 - arg4) * arg5) > 0.0f) {
        *arg0 = arg4;
        return 1;
    }

    return 0;
}

void mSM_move_Move(UNUSED mSM* arg0, struct_mSM_move_Move_arg1* arg1) {
    f32 var_fv0;
    s32 temp_t0 = arg1->unk_34;
    f32* temp_v0 = D_8085E948_jp[temp_t0 & 1];
    s32 index;
    s32 new_var;

    if (temp_t0 & 2) {
        var_fv0 = -1.0f;
    } else {
        var_fv0 = 1.0f;
    }

    index = temp_t0 >> 2;

    if (mSM_move_menu(&arg1->unk_18[index], &arg1->unk_20[index], temp_v0[0], temp_v0[1] * var_fv0, temp_v0[2] * var_fv0, temp_v0[3] * var_fv0) == 1) {
        arg1->unk_04 = arg1->unk_30;
    }

    // truncate
    new_var = arg1->unk_18[index];
    arg1->unk_18[index] = new_var;
}

void mSM_move_End_(mSM* arg0, struct_mSM_return_func_arg1* arg1) {
    mSM_return_func(arg0, arg1);
}

void mSM_menu_ovl_move(mSM* arg0) {
    struct_8085E9B0_unk_10670* sp24 = &arg0->unk_2C->unk_10670;

    mSM_make_trigger_data(arg0);
    if (arg0->programId != arg0->unk_08) {
        mSM_set_proc(arg0);
    }
    mSM_tex_move(arg0);
    sp24->unk_00(arg0);
}

void mSM_menu_ovl_draw(mSM* arg0, Game_Play* game_play) {
    mSM_setup_view(arg0, game_play->state.gfxCtx, 1);
    arg0->unk_2C->unk_10670.unk_04(arg0, game_play);
}

void mSM_menu_ovl_init(mSM* arg0) {
    Game_Play_unk_0110* var_v1;
    void* func = none_proc1;
    u16 temp = 0x2000;

    arg0->unk_2C = &ovl_base;
    bzero(&ovl_base, sizeof(struct_8085E9B0));

dummy_label_55178: ;
    if (arg0->unk_00 != 4) {
        var_v1 = ((Game_Play*)gamePT)->unk_0110;
    } else {
        var_v1 = ((Game__00743CD0*)gamePT)->unk_02FC;
    }

    ovl_base.unk_10000.unk_00 = var_v1[0x49].unk_24;
    arg0->unk_08 = SUBMENU_PROGRAM_0;
    ovl_base.unk_10670.unk_00 = func;
    ovl_base.unk_10670.unk_04 = func;
    ovl_base.unk_10670.unk_08 = func;
    ovl_base.unk_10670.unk_0C = func;
    ovl_base.unk_10670.unk_10 = func;
    ovl_base.unk_10670.unk_14 = func;
    ovl_base.unk_10670.unk_26 = temp;

    arg0->unk_2C->unk_106A4 = mSM_return_func;
    arg0->unk_2C->unk_106A8 = mSM_move_Move;
    arg0->unk_2C->unk_106AC = mSM_move_End_;
    arg0->unk_2C->unk_106B0 = mSM_move_chg_base;
    arg0->unk_2C->unk_106B4 = mSM_set_char_matrix;
    arg0->unk_2C->unk_106B8 = mSM_cbuf_copy;
    arg0->unk_2C->unk_106BC = func_8085C20C_jp;
    arg0->unk_2C->unk_106C0 = mSM_draw_item;
    arg0->unk_2C->unk_106C4 = mSM_draw_mail;
    arg0->unk_2C->unk_106C8 = mSM_setup_view;
    arg0->unk_2C->unk_106CC = func_8085D43C_jp;

    mSM_set_proc(arg0);
    arg0->play = mSM_menu_ovl_move;
    arg0->draw = mSM_menu_ovl_draw;
    mSM_menu_ovl_move(arg0);
}
