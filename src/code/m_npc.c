#include "global.h"
#include "m_npc.h"
#include "game.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "m_common_data.h"
#include "6B8A70.h"
#include "m_npc_schedule.h"
#include "m_npc_walk.h"
#include "m_npc_personal_id.h"
#include "6DB420.h"
#include "6F8A60.h"
#include "6DE300.h"
#include "m_time.h"
#include "m_font.h"
#include "libc64/malloc.h"
#include "m_malloc.h"
#include "z_std_dma.h"
#include "macros.h"
#include "6E7AD0.h"
#include "libu64/gfxprint.h"
#include "6D9D80.h"
#include "m_field_info.h"
#include "m_mail.h"
#include "6BFE60.h"
#include "6DA460.h"
#include "m_handbill.h"
#include "6B81C0.h"
#include "6E30B0.h"
#include "6C05A0.h"
#include "m_item_name.h"
#include "m_actor.h"
#include "overlays/actors/ovl_Npc/ac_npc.h"
#include "6A5B00.h"
#include "6A83A0.h"
#include "prevent_bss_reordering.h"
#include "segment_symbols.h"
#include "libc64/qrand.h"

typedef struct Struct_D_E03000 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} Struct_D_E03000; // size = 0x6
// extern Struct_D_E03000 segment_00E03000[];

typedef struct Struct_D_E04000 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ u8 unk_08[100][PLAYER_NAME_LEN];
} Struct_D_E04000;
// extern Struct_D_E04000 segment_00E04000;

// extern u8 segment_00E0D000[];

u16 D_8010AF00_jp[] = {
    0x0005, 0x0009, 0x000B, 0x000C, 0x000E, 0x0010, 0x0011, 0x0012, 0x0021, 0x0025, 0x0032, 0x0033,
    0x0035, 0x001B, 0x001B, 0x0056, 0x0059, 0x0068, 0x006F, 0x0080, 0x0083, 0x009F, 0x0002, 0x0000,
};

u16 D_8010AF30_jp[] = {
    0x0027, 0x0027, 0x0027, 0x0027, 0x000A, 0x000A, 0x000A, 0x000A, 0x0058, 0x0058,
    0x0058, 0x0058, 0x0058, 0x0058, 0x0058, 0x0058, 0x0058, 0x0013, 0x00A5, 0x0000,
};

u8 D_8010AF58_jp[] = {
    0x02, 0x05, 0x00, 0x00, 0x01, 0x04, 0x01, 0x05, 0x03, 0x05, 0x05, 0x04, 0x01, 0x00, 0x00, 0x01, 0x04, 0x05, 0x03,
    0x04, 0x02, 0x02, 0x04, 0x01, 0x05, 0x04, 0x01, 0x03, 0x01, 0x02, 0x01, 0x04, 0x02, 0x05, 0x00, 0x03, 0x04, 0x04,
    0x02, 0x03, 0x00, 0x03, 0x02, 0x00, 0x03, 0x01, 0x05, 0x04, 0x04, 0x05, 0x03, 0x00, 0x02, 0x00, 0x03, 0x01, 0x01,
    0x05, 0x00, 0x01, 0x02, 0x03, 0x00, 0x02, 0x00, 0x00, 0x02, 0x05, 0x01, 0x04, 0x03, 0x01, 0x02, 0x03, 0x02, 0x01,
    0x02, 0x02, 0x03, 0x00, 0x03, 0x04, 0x03, 0x01, 0x00, 0x02, 0x02, 0x04, 0x03, 0x02, 0x00, 0x03, 0x00, 0x03, 0x04,
    0x02, 0x05, 0x05, 0x04, 0x03, 0x04, 0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x03, 0x05, 0x00, 0x03, 0x00, 0x05, 0x01,
    0x00, 0x05, 0x05, 0x00, 0x04, 0x02, 0x05, 0x01, 0x02, 0x03, 0x03, 0x03, 0x01, 0x00, 0x02, 0x01, 0x04, 0x01, 0x04,
    0x05, 0x04, 0x00, 0x03, 0x01, 0x05, 0x04, 0x04, 0x03, 0x05, 0x03, 0x03, 0x00, 0x04, 0x02, 0x02, 0x05, 0x05, 0x03,
    0x01, 0x02, 0x02, 0x04, 0x05, 0x03, 0x00, 0x03, 0x04, 0x01, 0x02, 0x04, 0x00, 0x01, 0x01, 0x03, 0x03, 0x02, 0x03,
    0x04, 0x05, 0x00, 0x02, 0x00, 0x01, 0x05, 0x04, 0x04, 0x05, 0x01, 0x03, 0x04, 0x01, 0x04, 0x05, 0x04, 0x02, 0x05,
    0x04, 0x02, 0x04, 0x02, 0x03, 0x05, 0x02, 0x00, 0x05, 0x04, 0x01, 0x05, 0x00, 0x00, 0x05, 0x05, 0x01, 0x00, 0x05,
    0x04, 0x00, 0x01, 0x00, 0x05, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00,
};

u32 D_8010B034_jp[] = {
    0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
    0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
};

u32 D_8010B074_jp[] = {
    0x09090909,
};

u32 D_8010B078_jp[] = {
    0x13131313, 0x13131313, 0x13131313, 0x13131313, 0x13131313, 0x13131313, 0x13131313, 0x13131313, 0x13131313,
};

u32 D_8010B09C_jp[] = {
    0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808,
};

u32 D_8010B0BC_jp[] = {
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C00,
};

u32 D_8010B1BC_jp[] = {
    0x160D0D0D, 0x0D0D0D0D, 0x0D0D0D0D, 0x0D091515, 0x15141716, 0x19181818, 0x1919181A, 0x0E0B0000,
};

u32 D_8010B1DC_jp[] = {
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
};

u32 D_8010B21C_jp[] = {
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
};

u32 D_8010B25C_jp[] = {
    0x01050403,
    0x02061100,
};

u32 D_8010B264_jp[] = {
    0x11111111,
    0x11111111,
    0x11110000,
};

u32 D_8010B270_jp[] = {
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C,
    0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C0C, 0x0C0C0C00,
};

u32 D_8010B2A8_jp[] = {
    0x15000000,
};

u32 D_8010B2AC_jp[] = {
    0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
    0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
    0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
};

u32 D_8010B30C_jp[] = {
    0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212, 0x12121212,
};

u32 D_8010B32C_jp[] = {
    0x11110000,
};

u32 D_8010B330_jp[] = {
    0x07070707,
};

u32* D_8010B334_jp[] = {
    D_8010B034_jp, D_8010B074_jp, D_8010B078_jp, D_8010B09C_jp, D_8010B0BC_jp, D_8010B1BC_jp,
    D_8010B1DC_jp, D_8010B21C_jp, D_8010B25C_jp, D_8010B264_jp, D_8010B270_jp, D_8010B2A8_jp,
    D_8010B2AC_jp, D_8010B30C_jp, D_8010B32C_jp, D_8010B330_jp,
};

s16 D_8010B374_jp[] = {
    0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFF, 0x0003, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF,
    0x0001, 0xFFFF, 0x0002, 0xFFFC, 0x0003, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0x0000, 0x0004,
    0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFC, 0x0003, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0xFFFF,
    0x0004, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFC, 0x0003, 0xFFFF, 0x0004,
    0xFFFF, 0x0004, 0xFFFF, 0x0004, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFC,
    0x0003, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001,
    0xFFFF, 0x0002, 0xFFFC, 0x0003, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0xFFFF, 0x0004, 0x0000, 0x0004, 0xFFFF,
    0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFF, 0x0003, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001,
    0xFFFF, 0x0002, 0xFFFF, 0x0003, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFF,
    0x0003, 0x0000, 0x0004, 0xFFFF, 0x0000, 0xFFFF, 0x0001, 0xFFFF, 0x0002, 0xFFFF, 0x0003, 0x0000, 0x0004,
};

u32 D_8010B478_jp[] = {
    0x00000000,
    0x64000000,
    0x00000000,
};

u32 D_8010B484_jp[] = {
    0x00000000,
    0x17040404,
    0x04040000,
};

u32 D_8010B490_jp[] = {
    0x00000000,
    0x17070707,
    0x07070000,
    0x00000000,
};

u32 D_8010B4A0_jp[] = {
    0x0000001E,
    0x0000001F,
    0x00000020,
    0x00000021,
};

u16 D_8010B4B0_jp[] = {
    0x0101, 0x010F, 0x0201, 0x020F, 0x0214, 0x0301, 0x030F, 0x0403, 0x0408, 0x040D, 0x0413, 0x0415, 0x0506,
    0x0514, 0x0608, 0x0617, 0x0701, 0x070F, 0x0719, 0x071F, 0x0809, 0x081E, 0x0901, 0x090F, 0x0A01, 0x0A03,
    0x0A05, 0x0A07, 0x0A0A, 0x0A10, 0x0A14, 0x0A19, 0x0B08, 0x0B0C, 0x0B17, 0x0C09, 0x0C14, 0x0C19,
};

u16 D_8010B4FC_jp[] = {
    0x0C1C,
    0x0000,
};

u8 D_8010B500_jp[] = {
    0x23,
    0x7B,
};

u16 D_8010B504_jp[] = {
    0x076D, 0x080F, 0x076D, 0x090D, 0x0000, 0x0000,
};

typedef struct Struct_D_8010B510_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Struct_D_8010B510_jp; // size = 0xC

Struct_D_8010B510_jp D_8010B510_jp[] = {
    { 0xD008, 0x0000, 0x00000205, 0x00000002 }, { 0xD01E, 0x0000, 0x00000205, 0x00000002 },
    { 0xD03A, 0x0000, 0x00000205, 0x00000002 }, { 0xD03B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD03C, 0x0000, 0x00000205, 0x00000002 }, { 0xD009, 0x0000, 0x00000205, 0x00000002 },
    { 0xD00A, 0x0000, 0x00000205, 0x00000002 }, { 0xD00B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD014, 0x0000, 0x00000205, 0x00000002 }, { 0xD019, 0x0000, 0x00000205, 0x00000002 },
    { 0xD015, 0x0000, 0x00000205, 0x00000002 }, { 0xD01A, 0x0000, 0x00000205, 0x00000002 },
    { 0xD016, 0x0000, 0x00000205, 0x00000002 }, { 0xD01B, 0x0000, 0x00000205, 0x00000002 },
    { 0xD017, 0x0000, 0x00000205, 0x00000002 }, { 0xD01C, 0x0000, 0x00000205, 0x00000002 },
    { 0xD001, 0x0000, 0x00000206, 0x00000002 }, { 0xD013, 0x0000, 0x00000206, 0x00000002 },
    { 0xD02C, 0x0000, 0x00000206, 0x00000002 }, { 0xD039, 0x0000, 0x00000206, 0x00000002 },
    { 0xD00C, 0x0001, 0x00000207, 0x00000002 }, { 0xD03D, 0x0001, 0x00000207, 0x00000002 },
    { 0xD006, 0x0000, 0x00000208, 0x00000002 }, { 0xD000, 0x0000, 0x00000209, 0x00000003 },
    { 0xD00F, 0x0000, 0x0000020A, 0x00000002 }, { 0xD002, 0x0000, 0x0000020B, 0x00000002 },
    { 0xD007, 0x0001, 0x0000020C, 0x00000008 }, { 0xD003, 0x0001, 0x0000020D, 0x00000004 },
    { 0xD012, 0x0001, 0x0000020E, 0x00000004 }, { 0xD011, 0x0000, 0x0000020F, 0x00000003 },
    { 0xD00D, 0x0000, 0x00000210, 0x00000002 }, { 0xD010, 0x0000, 0x00000210, 0x00000003 },
    { 0xD04E, 0x0000, 0x00000210, 0x00000002 }, { 0xD00E, 0x0000, 0x00000211, 0x00000002 },
    { 0xD025, 0x0000, 0x00000212, 0x00000003 }, { 0xA004, 0x0002, 0x00000213, 0x00000002 },
    { 0xA005, 0x0002, 0x00000213, 0x00000002 }, { 0xA006, 0x0002, 0x00000213, 0x00000002 },
    { 0xA007, 0x0002, 0x00000213, 0x00000002 }, { 0xD018, 0x0002, 0x00000214, 0x00000002 },
    { 0xD05D, 0x0002, 0x00000214, 0x00000002 }, { 0xD066, 0x0002, 0x00000214, 0x00000002 },
    { 0xD004, 0x0000, 0x00000215, 0x00000002 }, { 0xD005, 0x0000, 0x00000215, 0x00000002 },
    { 0xD01D, 0x0000, 0x00000216, 0x00000002 }, { 0xD026, 0x0000, 0x00000217, 0x00000002 },
    { 0xD037, 0x0000, 0x00000218, 0x00000002 }, { 0xD03E, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD065, 0x0000, 0x000004E0, 0x00000002 }, { 0xD068, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD069, 0x0000, 0x000004E0, 0x00000002 }, { 0xD06B, 0x0000, 0x000004E0, 0x00000002 },
    { 0xD064, 0x0000, 0x000004E1, 0x00000002 }, { 0x800D, 0x0000, 0x000004E2, 0x00000002 },
    { 0x800E, 0x0000, 0x000004E2, 0x00000002 }, { 0xA008, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA009, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00A, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00B, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00C, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00D, 0x0000, 0x000004E2, 0x00000002 }, { 0xA00E, 0x0000, 0x000004E2, 0x00000002 },
    { 0xA00F, 0x0000, 0x000004E2, 0x00000002 }, { 0xA010, 0x0000, 0x000004E2, 0x00000002 },
};

u8 D_8010B810_jp[PLAYER_NAME_LEN] = { 0xD4, 0x8E, 0xA6, 0x90, 0x85, 0x42 };

u8 D_8010B818_jp[] = { 0xD3, 0xAF, 0x9D, 0x20 };

s32 D_8010B81C_jp[] = { 0, 2 };

s32 D_8010B824_jp[] = { 0x314, 0x334, 0x2F4, 0x219, 0x1E5, 0x354, 0x374, 0x394, 0x3D4, 0x3F4, 0x3B4 };

s32 D_8010B850_jp[] = {
    0x00000020, 0x00000040, 0x00000000, 0x00000060, 0x00000080, 0x000000A0,
};
s32 D_8010B868_jp[] = {
    0x000000E0, 0x00000100, 0x000000C0, 0x00000120, 0x00000140, 0x00000160,
};

s32* D_8010B880_jp[] = { D_8010B850_jp, D_8010B868_jp };

s32 D_8010B888_jp[] = { 0xC5, 0xD8 };

typedef void (*Funcs_D_8010B890_jp)(Mail_c*, Private_c*, AnmPersonalID_c*, Anmremail_c*, u8);
Funcs_D_8010B890_jp D_8010B890_jp[] = {
    func_800A8F30_jp,
    func_800A8DB4_jp,
};

s32 D_8010B898_jp[] = { 5, 2, 0 };
s32 D_8010B8A4_jp[] = { 0, 0, 2 };

s32 D_8010B8B0_jp[] = { 1, 0 };

u8 D_8010B8B8_jp[] = {
    0x00, 0x00, 0x02, 0x02, 0xFF,
};

typedef struct Struct_D_8010B8C0_jp {
    /* 0x00 */ s32 unk_00;
    /* 0x00 */ s32 unk_04;
} Struct_D_8010B8C0_jp; // size = 0x8

Struct_D_8010B8C0_jp D_8010B8C0_jp[] = {
    { 0x00000000, 0x00000000 }, { 0xFFFFFFFF, 0x00000001 }, { 0x00000000, 0x00000001 },
    { 0x00000001, 0x00000001 }, { 0xFFFFFFFF, 0x00000000 }, { 0x00000001, 0x00000000 },
    { 0xFFFFFFFF, 0xFFFFFFFF }, { 0x00000000, 0xFFFFFFFF }, { 0x00000001, 0xFFFFFFFF },
};

u16 D_8010B908_jp[] = { 0, 0xA012, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };

s32 D_8010B91C_jp[] = { 4, 4, 2, 2, 3, 4 };

s32 D_8010B934_jp[] = { 0x28, 0x32, 0x3C, 0x46, 0x50, 0x5A, 0x64 };

typedef struct Struct_D_8010B950_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
} Struct_D_8010B950_jp; // size = 0x4

Struct_D_8010B950_jp D_8010B950_jp[] = {
    { 0x0FA0, 0x0C, 0x0F }, { 0x0BB8, 0x0A, 0x0D }, { 0x0FA0, 0x0C, 0x0F },
    { 0x0FA0, 0x0A, 0x0D }, { 0x1388, 0x09, 0x0C }, { 0x1388, 0x09, 0x0C },
};

s32 D_8010B968_jp = -1;

s32 B_80142C00_jp[60];
u8 B_80142CF0_jp[HANDBILL_HEADER_LEN];

typedef struct Struct_B_80142D08_jp {
    /* 0x00 */ char unk00[0x1];
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
} Struct_B_80142D08_jp; // size = 0x5

Struct_B_80142D08_jp B_80142D08_jp[60];
u8 B_80142E38_jp[HANDBILL_FOOTER_LEN];
u8 B_80142E58_jp[0x1B];
UNK_TYPE1 PAD_80142E73_jp[3];
Struct_D_E03000 B_80142E78_jp;
u8 B_80142E80_jp[HANDBILL_HEADER_LEN];
u8 B_80142E98_jp[HANDBILL_FOOTER_LEN];
u16 B_80142EB8_jp[16];

typedef struct Struct_B_80142ED8_jp {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
} Struct_B_80142ED8_jp; // size = 0x8

Struct_B_80142ED8_jp B_80142ED8_jp[ANIMAL_NUM_MAX];

u8 B_80142F50_jp[PLAYER_NAME_LEN];
u8 B_80142F58_jp[PLAYER_NAME_LEN];
u8 B_80142F60_jp[PLAYER_NAME_LEN];
u8 B_80142F68_jp[PLAYER_NAME_LEN];

typedef struct Struct_B_80142F70_jp {
    /* 0x00 */ AnmPersonalID_c id;
    /* 0x0C */ u8 unk_0C;
} Struct_B_80142F70_jp; // size = 0x10

Struct_B_80142F70_jp B_80142F70_jp;
Mail_c B_80142F80_jp;
s32 B_80143028_jp[216];
Animal_c B_80143388_jp;

void func_800A6810_jp(s32* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;

    for (i = 0; i < arg1; i++) {
        arg0[i] = i;
    }

    while (arg2--) {
        s32 temp;

        i = RANDOM(arg1);
        j = RANDOM(arg1);
        temp = arg0[i];
        arg0[i] = arg0[j];
        arg0[j] = temp;
    }
}

void func_800A6920_jp(u8* catchphrase, s32 len) {
    mem_clear(catchphrase, len, CHAR_SPACE);
}

void func_800A6940_jp(u8* npc_max) {
    if (*npc_max < ANIMAL_NUM_MAX) {
        (*npc_max)++;
    }
}

void func_800A695C_jp(u8* arg0) {
    if (*arg0 >= 6) {
        (*arg0)--;
    }
}

void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* anm_id) {
    anm_id->npc_id = 0;
    anm_id->name_id = 0xFF;
    anm_id->land_id = 0xFFFF;
    anm_id->looks = 6;
    mNPS_reset_schedule_area(anm_id);
    func_80094EE0_jp(anm_id->land_name);
}

s32 mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* anm_id) {
    s32 res = FALSE;

    if (((anm_id->npc_id == 0) && (anm_id->name_id == 0xFF)) ||
        (ACTOR_FGNAME_GET_F000(anm_id->npc_id) != FGNAME_F000_E)) {
        res = TRUE;
    }
    return res;
}

void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src) {
    if (src != NULL) {
        if (ACTOR_FGNAME_GET_F000(src->npc_id) == FGNAME_F000_E) {
            dst->npc_id = src->npc_id;
            dst->name_id = src->name_id;
            dst->land_id = src->land_id;
            dst->looks = src->looks;
            mLd_CopyLandName(dst->land_name, src->land_name);
        }
    }
}

s32 mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* id0, AnmPersonalID_c* id1) {
    s32 res = FALSE;

    if ((id0 != NULL) && (id1 != NULL) && (id0->npc_id == id1->npc_id) && (id0->name_id == id1->name_id) &&
        (id0->land_id == id1->land_id)) {
        if (func_80094E38_jp(id0->land_name, id1->land_name) == TRUE) {
            res = TRUE;
        }
    }
    return res;
}

s32 func_800A6AF0_jp(void) {
    Animal_c* animal = common_data.save.animals;
    s32 res = 0;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == 0) {
            res++;
        }
        animal++;
    }
    return res;
}

s32 func_800A6B58_jp(Animal_c* animal) {
    s32 res = (animal->unk_522 >> 0xD) & 7;
    return res;
}

s32 func_800A6B6C_jp(Animal_c* animal) {
    s32 res = animal->unk_522 & 0x1FFF;
    return res;
}

void func_800A6B7C_jp(Animal_c* animal) {
    if ((animal->unk_522 & 0x1FFF) < 0x1FFF) {
        animal->unk_522++;
    }
}

void func_800A6B9C_jp(Animal_c* animal, u16 arg1) {
    animal->unk_522 = ((((animal->unk_522 >> 0xD) & 7) >> 0xD) | arg1) << 0xD;
}

void func_800A6BC8_jp(Animal_c* animal, PersonalID_c* pid) {
    if ((pid != NULL) && (func_800B7914_jp(pid) == 0)) {
        if (func_800B77C4_jp(animal->parent_name) == 1) {
            mPr_CopyPlayerName(animal->parent_name, pid->player_name);
        }
    }
}

void func_800A6C1C_jp(void) {
    Animal_c* animal = common_data.save.animals;
    Private_c* priv = common_data.now_private;
    s32 i;

    if (priv != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            func_800A6BC8_jp(animal, &priv->player_ID);
            animal++;
        }
    }
}

void func_800A6C84_jp(Anmplmail_c* letter) {
    letter->font = 0xFF;
    letter->paper_type = 0;
    letter->present = 0;
    mem_clear(letter->body, MAIL_BODY_LEN, CHAR_SPACE);
    letter->date.year = mTM_rtcTime_ymd_clear_code.year;
    letter->date.month = mTM_rtcTime_ymd_clear_code.month;
    letter->date.day = mTM_rtcTime_ymd_clear_code.day;
}

void func_800A6CE4_jp(Anmplmail_c* dst, Anmplmail_c* src) {
    mem_copy((void*)dst, (void*)src, sizeof(Anmplmail_c));
}

void func_800A6D04_jp(Anmmem_c* memory, s32 count) {
    while (count) {
        if (memory != NULL) {
            func_800B795C_jp(&memory->memory_player_id);
            lbRTC_TimeCopy(&memory->last_speak_time, &mTM_rtcTime_clear_code);
            func_80094EE0_jp(memory->memuni.land.name);
            memory->memuni.land.id = 0;
            memory->saved_town_tune = 0;
            memory->info.friendship = 0;
            memory->info.exists = FALSE;
            memory->info.password_letter = FALSE;
            memory->info.send_reply = FALSE;
            func_800A6C84_jp(&memory->letter);
        }
        memory++;
        count--;
    }
}

void func_800A6DB0_jp(Anmmem_c* dst, Anmmem_c* src) {
    mem_copy((void*)dst, (void*)src, sizeof(Anmmem_c));
}

void func_800A6DD0_jp(Anmmem_c* memory, s32 arg1) {
    s32 temp_v0 = memory->info.friendship + arg1;

    if (memory != NULL) {
        if (temp_v0 >= 0x80) {
            memory->info.friendship = 0x7F;
            return;
        } else if (temp_v0 < 0) {
            memory->info.friendship = 0;
            return;
        } else {
            memory->info.friendship = temp_v0;
        }
    }
}

s32 func_800A6E0C_jp(PersonalID_c* pid) {
    s32 res = FALSE;
    if (func_800B7914_jp(pid) == TRUE) {
        res = TRUE;
    }
    return res;
}

void mNpc_RenewalAnimalMemory(void) {
    Animal_c* animal = common_data.save.animals;
    Private_c* priv;
    Anmmem_c* memory;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        memory = animal->memories;
        for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
            if (func_800A6E0C_jp(&memory->memory_player_id) == FALSE) {
                if (func_800951E4_jp(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == TRUE) {
                    priv = common_data.save.private;
                    for (k = 0; k < PLAYER_NUM; k++) {
                        if ((func_800B7914_jp(&priv->player_ID) == FALSE) &&
                            (mPr_CheckCmpPersonalID(&priv->player_ID, &memory->memory_player_id) == TRUE)) {
                            break;
                        }
                        priv++;
                    }
                    if (k == PLAYER_NUM) {
                        func_800A6D04_jp(memory, 1);
                    }
                }
            }
            memory++;
        }
        animal++;
    }
}

s32 func_800A6F48_jp(Anmmem_c* memory, s32 count) {
    lbRTC_time_c sp48;
    s32 res;
    s32 i;

    lbRTC_TimeCopy(&sp48, &mTM_rtcTime_clear_code);
    res = 0;

    for (i = 0; i < count; i++) {
        if (func_800D52C0_jp(&sp48, &memory->last_speak_time) == -1) {
            res = i;
            lbRTC_TimeCopy(&sp48, &memory->last_speak_time);
        }
        memory++;
    }

    return res;
}

s32 func_800A6FF4_jp(Anmmem_c* memory, s32 count) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memory_player_id) == TRUE) {
            res = i;
            break;
        }
        memory++;
    }

    return res;
}

s32 func_800A706C_jp(Anmmem_c* memory, s32 count) {
    Anmmem_c* found_memory = NULL;
    s32 found_idx = func_800A6FF4_jp(memory, count);
    s32 i;

    if (found_idx == -1) {
        for (i = 0; i < count; i++) {
            if (func_800951E4_jp(memory->memory_player_id.land_name, memory->memory_player_id.land_id) == 0) {
                if (found_memory != NULL) {
                    if (found_memory->info.exists == memory->info.exists) {
                        if (memory->info.friendship < found_memory->info.friendship) {
                            found_memory = memory;
                            found_idx = i;
                        } else if ((found_memory->info.friendship == memory->info.friendship) &&
                                   (func_800D52C0_jp(&found_memory->last_speak_time, &memory->last_speak_time) == -1)) {
                            found_memory = memory;
                            found_idx = i;
                        }
                    } else if (memory->info.exists == FALSE) {
                        found_memory = memory;
                        found_idx = i;
                    }
                } else {
                    found_memory = memory;
                    found_idx = i;
                }
            }
            memory++;
        }
    } else {
        found_memory = &memory[found_idx];
    }
    func_800A6D04_jp(found_memory, 1);
    return found_idx;
}

void func_800A71AC_jp(Private_c* private, Anmmem_c* memory) {
    if (memory != NULL) {
        func_800A6D04_jp(memory, 1);
        func_800B79E0_jp(&memory->memory_player_id, &private->player_ID);
        memory->info.friendship = 1;
    }
}

void func_800A71F8_jp(Private_c* private, Anmmem_c* memory) {
    if (memory != NULL) {
        func_800A71AC_jp(private, memory);
        lbRTC_TimeCopy(&memory->last_speak_time, &common_data.time.rtc_time);
    }
}

s32 func_800A7238_jp(PersonalID_c* pid, Anmmem_c* memory, s32 count) {
    s32 found_idx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mPr_CheckCmpPersonalID(&memory->memory_player_id, pid) == TRUE) {
            found_idx = i;
            break;
        }
        memory++;
    }

    return found_idx;
}

void func_800A72C0_jp(Animal_c* animal) {
    Private_c* priv;
    Anmmem_c* memory = NULL;
    s32 idx;

    if ((common_data.now_private != NULL) && (animal != NULL)) {
        priv = common_data.now_private;
        idx = func_800A7238_jp(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);
        if (idx != -1) {
            memory = &animal->memories[idx];
        } else {
            idx = func_800A706C_jp(animal->memories, ANIMAL_MEMORY_NUM);
            if (idx != -1) {
                memory = &animal->memories[idx];
                func_800A71F8_jp(priv, memory);
            }
        }

        if (memory != NULL) {
            lbRTC_TimeCopy(&memory->last_speak_time, &common_data.time.rtc_time);
            mLd_CopyLandName(memory->memuni.land.name, common_data.save.land_info.name);
            memory->memuni.land.id = common_data.save.land_info.land_id;
            memory->saved_town_tune = common_data.save.unk_0F428;
        }
    }
}

void func_800A73D8_jp(AnmPersonalID_c* anm_id) {
    Private_c* priv = common_data.now_private;
    Animal_c* animal;
    s32 idx;

    if (priv != NULL) {
        idx = func_800A7D08_jp(anm_id);
        if (idx != -1) {
            animal = &common_data.save.animals[idx];
            idx = func_800A7238_jp(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);
            if (idx == -1) {
                idx = func_800A706C_jp(animal->memories, ANIMAL_MEMORY_NUM);
                if (idx != -1) {
                    func_800A71AC_jp(priv, &animal->memories[idx]);
                }
            }
        }
    }
}

s32 func_800A74A0_jp(Anmmem_c* memory, s32 count) {
    s32 i;
    s8 max_friendship = 0;
    s32 idx = -1;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memory_player_id) == 0) {
            if (memory->info.friendship >= max_friendship) {
                max_friendship = memory->info.friendship;
                idx = i;
            }
        }
        memory++;
    }

    return idx;
}

s32 func_800A7530_jp(Anmmem_c** out_memory, Anmmem_c* memory, s8* arg2) {
    s32 res = FALSE;
    Anmmem_c* out_mem;

    if (*arg2 < memory->info.friendship) {
        *arg2 = memory->info.friendship;
        *out_memory = memory;
        res = TRUE;
    } else if (memory->info.friendship == *arg2) {
        out_mem = *out_memory;
        if (out_mem != NULL) {
            if (out_mem->info.exists == memory->info.exists) {
                if (func_800D52C0_jp(&out_mem->last_speak_time, &memory->last_speak_time) == -1) {
                    *out_memory = memory;
                    res = TRUE;
                }
            } else if (memory->info.exists == TRUE) {
                *out_memory = memory;
                res = TRUE;
            }
        } else {
            *out_memory = memory;
            res = TRUE;
        }
    }
    return res;
}

s32 func_800A75FC_jp(Anmmem_c* memory, s32 count) {
    Anmmem_c* sp4C = memory;
    Anmmem_c* sp48 = 0;
    s8 sp47 = 0;
    s32 found_idx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if ((func_800A6E0C_jp(&memory->memory_player_id) == FALSE) &&
            (func_800A7530_jp(&sp48, memory, &sp47) == TRUE)) {
            found_idx = i;
        }
        memory++;
    }

    if ((found_idx != -1) && (sp4C[found_idx].info.friendship < 0x50)) {
        found_idx = -1;
    }
    return found_idx;
}

s32 func_800A76E4_jp(Anmmem_c* memory, s32 count, s32 arg2) {
    Anmmem_c* sp54 = NULL;
    s8 sp53 = 0;
    s32 priv_idx;
    s32 found_idx = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memory_player_id) == FALSE) {
            priv_idx = func_800B7FD4_jp(memory);
            if ((priv_idx != -1) && (arg2 == common_data.save.private[priv_idx].gender) &&
                (func_800A7530_jp(&sp54, memory, &sp53) == TRUE)) {
                found_idx = i;
            }
        }
        memory++;
    }

    return found_idx;
}

s32 func_800A77F0_jp(Anmmem_c* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memory_player_id) == FALSE) {
            num++;
        }
        memory++;
    }

    return num;
}

s32 func_800A7858_jp(Anmmem_c* memory, s32 count) {
    s32 num = 0;
    s32 i;

    for (i = 0; i < count; i++) {
        if ((func_800A6E0C_jp(&memory->memory_player_id) == FALSE) && (memory->info.exists == TRUE)) {
            num++;
        }
        memory++;
    }

    return num;
}

s32 func_800A78DC_jp(Anmmem_c* memory, s32 count) {
    Anmmem_c* memory2;
    u8 var_s4 = 0xFF;
    s32 res = 0;
    s32 i;
    s32 j;

    for (i = 0; i < count; i++) {
        if (func_800A6E0C_jp(&memory->memory_player_id) == FALSE) {
            if (((var_s4 >> i) & 1) == 1) {
                j = i + 1;
                memory2 = memory + 1;
                for (j = i + 1; j < count; j++) {
                    if ((((var_s4 >> j) & 1) == 1) &&
                        (func_80094E90_jp(memory->memuni.land.name, memory->memuni.land.id, memory2->memuni.land.name,
                                          memory2->memuni.land.id) == TRUE)) {
                        var_s4 &= ~(1 << j);
                    }
                    memory2++;
                }
            }
            res++;
        } else {
            var_s4 &= ~(1 << i);
        }
        memory++;
    }

    return res;
}

void mNpc_ClearAnimalInfo(Animal_c* animal) {
    Anmhome_c* home_info = &animal->home_info;

    bzero(animal, sizeof(Animal_c));
    mNpc_ClearAnimalPersonalID(&animal->id);
    func_800A6D04_jp(animal->memories, ANIMAL_MEMORY_NUM);
    animal->unk_520 = 0;

    home_info->type_unused = 0;
    home_info->block_x = 0xFF;
    home_info->block_z = 0xFF;
    home_info->ut_x = 0xFF;
    home_info->ut_z = 0xFF;

    func_800A6920_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    func_800BA778_jp(&animal->contest_quest);
    func_80094EE0_jp(animal->previous_land_name);
    animal->unk_51C = 0;
    animal->unk_522 = 0;
    animal->unk_524 = 1;
    func_800B7780_jp(animal->parent_name);
}

void mNpc_ClearAnyAnimalInfo(Animal_c* animals, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        mNpc_ClearAnimalInfo(animals);
        animals++;
    }
}

s32 mNpc_CheckFreeAnimalInfo(Animal_c* animal) {
    s32 res = FALSE;

    if ((animal->home_info.block_x == 0xFF) && (animal->home_info.block_z == 0xFF) &&
        (ACTOR_FGNAME_GET_F000(animal->id.npc_id) != FGNAME_F000_E)) {
        res = TRUE;
    }
    return res;
}

s32 mNpc_GetFreeAnimalInfo(Animal_c* animal, s32 count) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < count; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == TRUE) {
            res = i;
            break;
        }
        animal++;
    }

    return res;
}

s32 mNpc_UseFreeAnimalInfo(Animal_c* animal, s32 count) {
    s32 idx = mNpc_GetFreeAnimalInfo(animal, count);

    if (idx != -1) {
        mNpc_ClearAnimalInfo(&animal[idx]);
    }
    return idx;
}

void mNpc_CopyAnimalInfo(Animal_c* dst, Animal_c* src) {
    mem_copy((void*)dst, (void*)src, sizeof(Animal_c));
}

s32 mNpc_SearchAnimalinfo(Animal_c* animal, u16 npc_name, s32 count) {
    s32 idx;

    animal = &animal[count - 1];
    idx = count - 1;

    while (idx >= 0) {
        if (animal->id.npc_id == npc_name) {
            return idx;
        }
        idx--;
        animal--;
    }

    return -1;
}

Animal_c* func_800A7C94_jp(u16 npc_name) {
    UNUSED s32 pad;
    Animal_c* sp18 = NULL;
    s32 temp_v0 = mNpc_SearchAnimalinfo(common_data.save.animals, npc_name, ANIMAL_NUM_MAX);

    if (temp_v0 != -1) {
        sp18 = &common_data.save.animals[temp_v0];
    }
    return sp18;
}

s32 func_800A7D08_jp(AnmPersonalID_c* anm_id) {
    Animal_c* animal = common_data.save.animals;
    s32 res = -1;
    s32 i;

    if (anm_id != NULL) {
        if (mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckCmpAnimalPersonalID(anm_id, &animal->id) == TRUE) {
                    res = i;
                    break;
                }
                animal++;
            }
        }
    }
    return res;
}

AnmPersonalID_c* func_800A7DA0_jp(AnmPersonalID_c* ids, s32 num_ids, s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    AnmPersonalID_c* sp68;
    u8 sp67;
    UNUSED s32 pad1;
    s32 sp5C;
    u16 sp5A;
    s32 j;
    s32 i;
    UNUSED s32 pad2[2];
    s32 sp44;
    Animal_c* var_s4;
    s32 var_fp;
    s32 var_s2;

    var_s4 = common_data.save.animals;
    sp68 = NULL;
    var_s2 = 0;
    sp5C = num_ids;
    sp67 = common_data.save.now_npc_max;
    sp5A = 0xFFFF;

    if ((arg0 == 0xFF) || (arg1 == 0xFF)) {
        arg2 = 0;
    }

    if ((ids == NULL) && (num_ids != 0)) {
        num_ids = 0;
    }

    for (i = 0; i < num_ids; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&ids[i]) == TRUE) {
            sp5C--;
            sp5A &= ~(1 << i);
        }
    }

    if (arg2 == 1) {
        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if (arg0 == var_s4->home_info.block_x) {
                if (arg1 == var_s4->home_info.block_z) {
                    var_s2++;

                    for (i = 0; i < num_ids; i++) {
                        if ((((sp5A >> i) & 1) == TRUE) &&
                            (mNpc_CheckCmpAnimalPersonalID(&var_s4->id, &ids[i]) == TRUE)) {
                            sp5C--;
                            sp5A &= ~(1 << i);
                            break;
                        }
                    }
                }
            }
            var_s4++;
        }
    }

    if (((sp5C + var_s2) < sp67) && (num_ids < ANIMAL_NUM_MAX)) {
        var_s4 = common_data.save.animals;
        var_fp = fqrand() * ((sp67 - sp5C) - var_s2);

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            var_s2 = 0;
            sp44 = 1;

            if (mNpc_CheckFreeAnimalPersonalID(&var_s4->id) == 0) {
                for (i = 0; i < num_ids; i++) {
                    if ((((sp5A >> i) & 1) == 1) && (mNpc_CheckCmpAnimalPersonalID(&var_s4->id, &ids[i]) == FALSE)) {
                        var_s2++;
                    }
                    if (var_s2) {}
                }

                if (var_s2 != sp5C) {
                    sp44 = 0;
                } else if ((arg2 == 1) && (arg0 == var_s4->home_info.block_x) && (arg1 == var_s4->home_info.block_z)) {
                    if (var_fp > 0) {
                        var_fp--;
                    }
                    sp44 = 0;
                }

                if (sp44 == 1) {
                    if (var_fp == 0) {
                        sp68 = &var_s4->id;
                        break;
                    }
                    var_fp--;
                }
            }
            var_s4++;
        }
        j = 0;
    }

    return sp68;
}

AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* ids, s32 num_ids) {
    return func_800A7DA0_jp(ids, num_ids, 0, 0, 0);
}

void func_800A80D8_jp(Animal_c* animal, s32 count) {
    mLd_land_info_c* land_info = &common_data.save.land_info;

    while (count) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            animal->id.land_id = land_info->land_id;
            mLd_CopyLandName(animal->id.land_name, land_info->name);
        }
        count--;
        animal++;
    }
}

s32 func_800A8148_jp(u8 looks) {
    Animal_c* animal = common_data.save.animals;
    s32 i;
    s32 res = 0;

    if (looks < 6) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (looks == animal->id.looks) {
                res++;
            }
            animal++;
        }
    }
    return res;
}

s32 func_800A820C_jp(s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    s32 sp28;
    s32 sp24;
    s32 sp20 = FALSE;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX)) {
        if ((mFI_Wpos2BlockNum(&sp28, &sp24, common_data.npclist[arg0].position) == TRUE) && (sp28 == arg1) &&
            (sp24 == arg2)) {
            sp20 = TRUE;
        }
    }
    return sp20;
}

void func_800A82C8_jp(Anmplmail_c* letter, Mail_c* mail) {
    mem_copy(letter->body, mail->content.body, MAIL_BODY_LEN);
    mem_copy(letter->header, mail->content.header, MAIL_HEADER_LEN);
    mem_copy(letter->footer, mail->content.footer, MAIL_FOOTER_LEN);
    letter->header_back_start = mail->content.header_back_start;
    letter->font = mail->content.font;
    letter->present = mail->present;
    letter->paper_type = mail->content.paper_type;
}

void func_800A8344_jp(Mail_c* mail, Anmplmail_c* letter, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    mem_copy(mail->content.body, letter->body, MAIL_BODY_LEN);
    mem_copy(mail->content.header, letter->header, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, letter->footer, MAIL_FOOTER_LEN);

    mail->content.header_back_start = letter->header_back_start;
    mail->content.font = letter->font;
    mail->present = letter->present;
    mail->content.paper_type = letter->paper_type;

    if (pid != NULL) {
        func_800B79E0_jp(&mail->header.sender.personal_ID, pid);
        mail->header.sender.type = 0;
    }

    if (anm_id != NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.recipient, anm_id);
    }
}

s32 func_800A83F0_jp(u8 c) {
    if ((c == CHAR_EXCLAMATION) || (c == CHAR_QUOTATION) || (c == CHAR_UNDERSCORE) || (c == CHAR_HYPHEN) ||
        (c == CHAR_PLUS) || ((c >= CHAR_PERCENT) && (c <= CHAR_AT_SIGN)) ||
        ((c >= CHAR_7E) && (c <= CHAR_MIDDLE_DOT))) {
        return TRUE;
    }
    return FALSE;
}

s32 func_800A845C_jp(s32* arg0, u8* body) {
    UNUSED s32 pad[2];
    s32 sp3C = 0;
    u8 var_s5 = 0x20;
    s32 var_s2 = 1;
    s32 var_s6 = 0;
    s32 i;

    *arg0 = 0;

    for (i = 0; i < MAIL_BODY_LEN; i++) {
        if (*body != CHAR_SPACE) {
            var_s2++;
            if (var_s5 == *body) {
                if (var_s2 >= 3) {
                    if (func_800A83F0_jp(*body) == TRUE) {
                        if (var_s2 >= 8) {
                            sp3C = 1;
                            break;
                        }
                    } else {
                        sp3C = 1;
                        break;
                    }
                }
            } else {
                var_s2 = 0;
                var_s5 = *body;
            }
            (*arg0)++;
        }
        body++;
        var_s6++;
    }

    for (i = var_s6; i < MAIL_BODY_LEN; i++) {
        if (*body != CHAR_SPACE) {
            (*arg0)++;
        }
        body++;
    }

    return sp3C;
}

u8 func_800A8614_jp(s32* arg0, u8* body) {
    s32 sp24;
    s32 sp20;
    s32 temp_v0;
    u8 sp1B = 2;

    sp24 = func_8009C900_jp(&sp20, body, 0);
    temp_v0 = func_800A845C_jp(arg0, body);

    if (sp20 < 3) {
        if (*arg0 < 5) {
            sp1B = 0;
        } else if (temp_v0 == 1) {
            sp1B = 0;
        }
    } else if (sp24 >= 30) {
        sp1B = 1;
    } else if (temp_v0 == 1) {
        sp1B = 0;
    }
    return sp1B;
}

u8 func_800A86C4_jp(u8* body) {
    s32 sp1C;

    return func_800A8614_jp(&sp1C, body);
}

u8 func_800A86E8_jp(Anmmem_c* memory, u8* body) {
    u8 temp_v0;

    memory->letter.date.year = common_data.time.rtc_time.year;
    memory->letter.date.month = common_data.time.rtc_time.month;
    memory->letter.date.day = common_data.time.rtc_time.day;

    temp_v0 = func_800A86C4_jp(body);
    if (temp_v0 < 2) {
        memory->info.password_letter = temp_v0;
        memory->info.send_reply = 1;
    }
    return temp_v0;
}

s32 func_800A8764_jp(Animal_c* animal, u8* body) {
    Anmremail_c* remail;
    u8 sp1B = func_800A86C4_jp(body);

    if (sp1B < 2) {
        remail = &common_data.now_private->remail;

        remail->date.year = common_data.time.rtc_time.year;
        remail->date.month = common_data.time.rtc_time.month;
        remail->date.day = common_data.time.rtc_time.day;

        remail->flags.password_letter = sp1B;
        remail->flags.looks = animal->id.looks;

        mNpc_GetNpcWorldNameAnm(remail->name, &animal->id);
        mLd_CopyLandName(remail->land_name, func_800950D8_jp()->name);
    }
    return sp1B;
}

s32 func_800A8814_jp(Animal_c* animal, Anmmem_c* memory, u8* body) {
    s32 res;

    if (mLd_PlayerManKindCheck() == FALSE) {
        res = func_800A86E8_jp(memory, body);
    } else {
        res = func_800A8764_jp(animal, body);
    }
    return res;
}

#ifdef NON_MATCHING
s32 func_800A8868_jp(Mail_c* mail) {
    AnmPersonalID_c sp5C;
    s32 sp58 = 0;
    UNUSED s32 pad;
    UNUSED s32 pad1;
    s32 sp4C;
    UNUSED s32 pad2;
    s32 sp44;
    s32 sp40;
    UNUSED s32 pad3;
    UNUSED s32 pad4;
    Animal_c* sp24 = common_data.save.animals;
    Anmmem_c* sp20;

    if (mMl_get_npcinfo_from_mail_name(&sp5C, &mail->header.recipient) == TRUE) {
        sp4C = func_800A7D08_jp(&sp5C);
        if (sp4C != -1) {
            sp24 += sp4C;
            sp40 = func_800A7238_jp(&mail->header.sender.personal_ID, sp24->memories, ANIMAL_MEMORY_NUM);
            if (sp40 == -1) {
                sp40 = func_800A706C_jp(sp24->memories, ANIMAL_MEMORY_NUM);
                if (sp40 >= 0) {
                    func_800B79E0_jp(&sp24->memories[sp40].memory_player_id, &mail->header.sender.personal_ID);
                }
            }
            sp20 = &sp24->memories[sp40];
            sp20->info.exists = TRUE;
            func_800A6C84_jp(&sp24->memories[sp40].letter);
            func_800A82C8_jp(&sp24->memories[sp40].letter, mail);
            sp44 = func_800A8814_jp(sp24, &sp24->memories[sp40], mail->content.body);
            if (mEv_CheckFirstJob() == 1) {
                mQst_errand_c* temp_v0_5 = func_800BBBEC_jp();
                if (((temp_v0_5->base.quest_kind == 6) || (temp_v0_5->base.quest_kind == 0xA)) &&
                    ((temp_v0_5->base.progress != 0))) {
                    temp_v0_5->base.progress = 3;
                    sp20->info.send_reply = 0;
                }
            } else {
                if ((mLd_PlayerManKindCheck() == FALSE) && (func_800BB5DC_jp(6) == sp4C)) {
                    func_800BBB30_jp(&sp24->contest_quest, &mail->header.sender, mail->content.body, mail->present);
                    sp20->info.send_reply = 0;
                }

                sp4C = 3;
                if (sp44 == 0) {
                    sp4C -= 5;
                }

                if (mail->present != 0) {
                    sp4C += 3;
                }
                func_800A6DD0_jp(sp20, sp4C);
            }
            sp58 = 1;
        }
    }
    return sp58;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800A8868_jp.s")
#endif

void func_800A8AB4_jp(Anmremail_c* remail) {
    remail->date = mTM_rtcTime_ymd_clear_code;
    func_800B7780_jp(remail->name);
    func_80094EE0_jp(remail->land_name);
    remail->flags.password_letter = 0;
    remail->flags.looks = 0x7F;
}

void func_800A8B10_jp(u16* present) {
    func_800BFCF0_jp(0, present, 1, 0, 0, D_8010B81C_jp[RANDOM(4.0f) & 1], 8);
}

s32 func_800A8B84_jp(Mail_c* mail, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    mHandbillz_Info_c handbill_info;
    s32 res;

    handbill_info.super_buf_p = B_80142CF0_jp;
    handbill_info.super_buf_size = HANDBILL_HEADER_LEN;
    handbill_info.mail_buf_p = mail->content.body;
    handbill_info.mail_buf_size = HANDBILL_BODY_LEN;
    handbill_info.ps_buf_p = B_80142E38_jp;
    handbill_info.ps_buf_size = HANDBILL_FOOTER_LEN;
    handbill_info.super_no = arg1;
    handbill_info.maila_no = arg2;
    handbill_info.mailb_no = arg3;
    handbill_info.mailc_no = arg4;
    handbill_info.ps_no = arg5;

    res = func_800944B8_jp(&handbill_info);
    if (res == TRUE) {
        mail->content.header_back_start = handbill_info.header_back_start;
        mem_copy(mail->content.header, B_80142CF0_jp, MAIL_HEADER_LEN);
        mem_copy(mail->content.footer, B_80142E38_jp, MAIL_FOOTER_LEN);
    }
    return res;
}

void func_800A8C48_jp(Private_c* private, AnmPersonalID_c* anm_id, Anmremail_c* remail) {
    s32 i;
    u8 sp40[MAIL_HEADER_LEN];

    func_80092D10_jp(0, private->player_ID.player_name, PLAYER_NAME_LEN);
    if (remail == NULL) {
        mNpc_GetNpcWorldNameAnm(sp40, anm_id);
        func_80092D10_jp(1, sp40, PLAYER_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(sp40, mNpc_GetOtherAnimalPersonalID(anm_id, 1));
        func_80092D10_jp(2, sp40, PLAYER_NAME_LEN);
    } else {
        func_80092D10_jp(1, remail->name, PLAYER_NAME_LEN);
        mNpc_GetNpcWorldNameAnm(sp40, mNpc_GetOtherAnimalPersonalID(NULL, 0));
        func_80092D10_jp(2, sp40, PLAYER_NAME_LEN);
        func_80092D10_jp(14, remail->land_name, PLAYER_NAME_LEN);
        func_80092D10_jp(15, func_800950D8_jp()->name, PLAYER_NAME_LEN);
    }

    for (i = 0; i < ARRAY_COUNT(D_8010B824_jp); i++) {
        func_800C3F70_jp(sp40, MAIL_HEADER_LEN, D_8010B824_jp[i] + RANDOM(32));
        func_80092D10_jp(i + 3, sp40, MAIL_HEADER_LEN);
    }
}

void func_800A8DB4_jp(Mail_c* mail, Private_c* private, AnmPersonalID_c* anm_id, Anmremail_c* remail, u8 arg4) {
    s32* sp54;
    s32 sp50;
    u16 sp4E = 0;
    s32 sp48;
    s32 temp;

    if (remail == NULL) {
        sp48 = anm_id->looks;
    } else {
        sp48 = remail->flags.looks;
    }
    sp54 = D_8010B880_jp[arg4];
    sp50 = RANDOM(4.0f) & 1;
    if (sp50 == 0) {
        func_800A8B10_jp(&sp4E);
    }
    func_800A8C48_jp(private, anm_id, remail);
    temp = sp54[sp48];
    func_800A8B84_jp(mail, RANDOM(32.0f) + temp, RANDOM(32.0f) + temp, RANDOM(16.0f) + temp + (sp50 * 0x10),
                     RANDOM(32.0f) + temp, RANDOM(32.0f) + temp);
    mail->present = sp4E;
}

void func_800A8F30_jp(Mail_c* mail, Private_c* private, AnmPersonalID_c* anm_id, Anmremail_c* remail, u8 arg4) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    if (remail == NULL) {
        sp30 = anm_id->looks;
    } else {
        sp30 = remail->flags.looks;
    }
    func_800A8C48_jp(private, anm_id, remail);
    sp34 = D_8010B888_jp[arg4] + (sp30 * 3);
    sp34 += RANDOM2(3.0f);
    func_80093F04_jp(B_80142E80_jp, &sp2C, B_80142E98_jp, mail->content.body, sp34);
    mail->content.header_back_start = sp2C;
    mem_copy(mail->content.header, B_80142E80_jp, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, B_80142E98_jp, MAIL_FOOTER_LEN);
    mail->present = 0;
}

void func_800A9028_jp(Mail_c* mail, Private_c* private, AnmPersonalID_c* anm_id, Anmremail_c* remail, u32 arg4,
                      u8 arg5) {
    u16 sp36;

    D_8010B890_jp[arg4](mail, private, anm_id, remail, arg5);
    mail->content.font = 0;
    mail->content.mail_type = 0;
    func_800B79E0_jp(&mail->header.recipient.personal_ID, &private->player_ID);
    mail->header.recipient.type = 0;
    if (remail == NULL) {
        mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    } else {
        mPr_CopyPlayerName(mail->header.sender.personal_ID.player_name, remail->name);
        mLd_CopyLandName(mail->header.sender.personal_ID.land_name, remail->land_name);
        mail->header.sender.type = 1;
    }
    func_800BFCF0_jp(0, &sp36, 1, 0, 0, 1, 8);
    mail->content.paper_type = (sp36 - 0x2000) & 0xFFFF;
}

s32 func_800A9110_jp(Private_c* private, AnmPersonalID_c* anm_id, Anmremail_c* remail, u32 arg3, u8 arg4) {
    UNUSED s32 pad;
    s32 res = FALSE;

    if (func_800B68E8_jp() < 5) {
        func_800A9028_jp(&B_80142F80_jp, private, anm_id, remail, arg3, arg4);
        res = func_800B6A3C_jp(&B_80142F80_jp, 0);
    }
    return res;
}

s32 func_800A918C_jp(lbRTC_ymd_t* ymd, lbRTC_time_c* time) {
    s32 res = FALSE;

    if ((ymd->day != 0xFF) && ((ymd->year != time->year) || (ymd->month != time->month) || (ymd->day != time->day))) {
        res = TRUE;
    }
    return res;
}

void func_800A91DC_jp(void) {
    Animal_c* animal = common_data.save.animals;
    Anmmem_c* memory;
    Private_c* priv = common_data.now_private;
    Anmremail_c* remail = &priv->remail;
    s32 memory_idx;
    s32 i;

    if (func_800B7914_jp(&priv->player_ID) == FALSE) {
        if (mLd_PlayerManKindCheck() == 0) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    memory_idx = func_800A7238_jp(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM);
                    if (memory_idx != -1) {
                        memory = &animal->memories[memory_idx];
                        //! FAKE, these should be bitfield accesses and 32-bits, but friendship is just an s8.
                        if (memory->info.send_reply &&
                            (func_800A918C_jp(&memory->letter.date, &common_data.time.rtc_time) == TRUE)) {
                            if (func_800A9110_jp(priv, &animal->id, NULL, memory->info.password_letter, 0) == TRUE) {
                                memory->info.send_reply = 0;
                            } else {
                                break;
                            }
                        }
                    }
                }
                animal++;
            }

            if (priv->remail.flags.looks != 0x7F) {
                if (func_800A9110_jp(priv, &animal->id, remail, remail->flags.password_letter, 1) == TRUE) {
                    func_800A8AB4_jp(remail);
                }
            }
        }
    }
}

u8 func_800A9364_jp(void) {
    u16 sp2E;

    func_800BFCF0_jp(0, &sp2E, 1, 0, 0, 1, 8);
    return (sp2E - 0x2000) & 0xFF;
}

void func_800A93AC_jp(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id, u16 arg3, u8 arg4, s32 arg5) {
    UNUSED s32 pad[2];
    u8 sp54[MAIL_HEADER_LEN];
    UNUSED s32 pad2[3];
    u8 sp38[MAIL_FOOTER_LEN];
    s32 header_back_start;

    mMl_clear_mail(mail);
    func_80093F54_jp(sp54, 0x14, &header_back_start, sp38, 0x14, mail->content.body, arg5);
    mem_copy(mail->content.header, sp54, MAIL_HEADER_LEN);
    mem_copy(mail->content.footer, sp38, MAIL_FOOTER_LEN);
    mail->content.header_back_start = header_back_start;
    mail->content.font = 0;
    mail->content.mail_type = 0;
    func_800B79E0_jp(&mail->header.recipient.personal_ID, pid);
    mail->header.recipient.type = 0;
    mMl_set_mail_name_npcinfo(&mail->header.sender, anm_id);
    mail->present = arg3;
    mail->content.paper_type = arg4;
}

void func_800A9468_jp(u16* arg0, s32 arg1) {
    func_800BFCF0_jp(0, arg0, 1, 0, 0, D_8010B8A4_jp[arg1], D_8010B898_jp[arg1]);
}

void func_800A94C8_jp(Mail_c* mail, Anmmem_c* memory, Animal_c* animal, s32 arg3, s32 arg4) {
    u16 sp2E;
    UNUSED s32 pad[2];

    func_80092D10_jp(0, memory->memory_player_id.player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(B_80142F50_jp, &animal->id);
    func_80092D10_jp(6, B_80142F50_jp, PLAYER_NAME_LEN);
    func_800A9468_jp(&sp2E, arg3);
    func_800A93AC_jp(mail, &memory->memory_player_id, &animal->id, sp2E, func_800A9364_jp(),
                     MAIL_BODY_LEN + (arg4 * 3) + arg3);
}

s32 func_800A956C_jp(Anmmem_c* memory, s32 arg1, Animal_c* animal, s32 arg2) {
    UNUSED s32 pad;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 sp28;
    s32 sp24 = animal->id.looks;
    s32 res = FALSE;

    home = &common_data.save.homes[func_80094BF4_jp(arg1)];
    if (mPr_CheckCmpPersonalID(&memory->memory_player_id, &home->ownerID) == TRUE) {
        sp28 = func_8009C534_jp(home->mailbox, MAIL_HEADER_LEN);
        if (sp28 != -1) {
            func_800A94C8_jp(&B_80142F80_jp, memory, animal, arg2, sp24);
            func_8009C67C_jp(&home->mailbox[sp28], &B_80142F80_jp);
            res = TRUE;
        } else if (func_800B68E8_jp() < 5) {
            func_800A94C8_jp(&B_80142F80_jp, memory, animal, arg2, sp24);
            res = func_800B6A3C_jp(&B_80142F80_jp, 0);
        }
    }
    return res;
}

void func_800A96B0_jp(s32* out_idx, u8* arg1, Animal_c* animal, s32 arg3) {
    s32 sp24;
    s32 memory_idx;

    sp24 = func_800A75FC_jp(animal->memories, ANIMAL_MEMORY_NUM);
    memory_idx = func_800A76E4_jp(animal->memories, ANIMAL_MEMORY_NUM, ~arg3 & 1);
    if ((sp24 != -1) && (memory_idx == sp24)) {
        *out_idx = memory_idx;
        *arg1 = 0;
    } else if (memory_idx != -1) {
        *out_idx = memory_idx;
        if (animal->memories[memory_idx].info.friendship >= 0x50) {
            *arg1 = 1;
        } else {
            *arg1 = 2;
        }
    }
}

s32 func_800A9780_jp(s32 arg0) {
    Animal_c* animal = common_data.save.animals;
    Anmmem_c* memory;
    s32 sp74[ANIMAL_NUM_MAX];
    u8 sp64[ANIMAL_NUM_MAX];
    s32 temp_v0_2;
    s32 var_fp = 0;
    u8 var_s4 = 0xF;
    s32 i;
    s32 j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        sp74[i] = -1;
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            if (func_800AD154_jp(&animal->id) == D_8010B8B0_jp[arg0]) {
                func_800A96B0_jp(&sp74[i], &sp64[i], animal, D_8010B8B0_jp[arg0]);
            }
        }
        animal++;
    }

    for (i = 0; i < 3; i++) {
        animal = common_data.save.animals;

        for (j = 0; j < ANIMAL_NUM_MAX; j++) {
            if ((sp74[j] >= 0) && (i == sp64[j])) {
                memory = &animal->memories[sp74[j]];
                temp_v0_2 = func_800B7FD4_jp(memory);
                if (((var_s4 >> temp_v0_2) & 1) == 1) {
                    if (func_800A956C_jp(memory, temp_v0_2, animal, i) == 1) {
                        sp74[j] = -1;
                        var_fp++;
                    } else {
                        var_s4 &= ~(1 << temp_v0_2);
                    }
                }
            }

            if (var_s4 == 0) {
                return var_fp;
            }

            animal++;
        }
    }

    return var_fp;
}

void func_800A992C_jp(u16* arg0) {
    s32 temp_v0 = D_8010B8B8_jp[RANDOM(ARRAY_COUNT(D_8010B8B8_jp))];

    if (temp_v0 == 0xFF) {
        func_800C297C_jp(arg0, 1);
    } else {
        func_800BFCF0_jp(0, arg0, 1, 0, 0, temp_v0, 2);
    }
}

void func_800A99B8_jp(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    u8 sp2C[MAIL_HEADER_LEN];
    s32 sp28 = (RANDOM(3.0f) + (anm_id->looks * 3)) + 0xEA;
    u16 sp26;

    func_80092D10_jp(0, pid->player_name, PLAYER_NAME_LEN);
    mNpc_GetNpcWorldNameAnm(B_80142F58_jp, anm_id);
    func_80092D10_jp(1, B_80142F58_jp, PLAYER_NAME_LEN);
    func_800A992C_jp(&sp26);
    func_80096740_jp(sp2C, sp26);
    func_80092D10_jp(2, sp2C, MAIL_HEADER_LEN);
    func_800A93AC_jp(mail, pid, anm_id, sp26, func_800A9364_jp(), sp28);
}

s32 func_800A9A98_jp(PersonalID_c* pid, s32 player_no, AnmPersonalID_c* anm_id) {
    UNUSED s32 pad;
    mHm_hs_c* sp28;
    s32 home_idx;
    s32 sp20;
    s32 res = FALSE;

    home_idx = func_80094BF4_jp(player_no);
    sp28 = &common_data.save.homes[home_idx];

    if ((func_800B7914_jp(pid) == FALSE) && (mPr_CheckCmpPersonalID(pid, &sp28->ownerID) == TRUE)) {
        sp20 = func_8009C534_jp(sp28->mailbox, MAIL_HEADER_LEN);
        if (sp20 != -1) {
            func_800A99B8_jp(&B_80142F80_jp, pid, anm_id);
            func_8009C67C_jp(&sp28->mailbox[sp20], &B_80142F80_jp);
            res = TRUE;
        } else if (func_800B68E8_jp() < 5) {
            func_800A99B8_jp(&B_80142F80_jp, pid, anm_id);
            res = func_800B6A3C_jp(&B_80142F80_jp, 0);
        }
    }
    return res;
}

s32 func_800A9BC4_jp(UNUSED s32 arg0) {
    return FALSE;
}

s32 func_800A9BD4_jp(PersonalID_c* pid, s32 player_no) {
    Animal_c* animal = common_data.save.animals;
    s32 idx;
    s32 res = FALSE;
    s32 i;

    if (pid != NULL) {
        if (func_800951E4_jp(pid->land_name, pid->land_id) == TRUE) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                    idx = func_800A74A0_jp(animal->memories, ANIMAL_MEMORY_NUM);
                    if ((idx != -1) && (mPr_CheckCmpPersonalID(pid, &animal->memories[idx].memory_player_id) != 0) &&
                        (func_800A9A98_jp(pid, player_no, &animal->id) == 1)) {
                        res = TRUE;
                    }
                }
                animal++;
            }
        }
    }
    return res;
}

void func_800A9CD4_jp(Mail_c* mail, PersonalID_c* pid) {
    UNUSED s32 pad;
    s32 sp30;

    func_80093F04_jp(mail->content.header, &sp30, mail->content.footer, mail->content.body, 0xD7);
    mail->content.header_back_start = sp30;
    mail->content.font = 0;
    mail->content.mail_type = 1;
    func_800B79E0_jp(&mail->header.recipient.personal_ID, pid);
    mail->header.recipient.type = 0;
    func_800BFCF0_jp(0, &mail->present, 1, 0, 0, 0, 3);
    mail->content.paper_type = 0x16;
}

s32 func_800A9D68_jp(PersonalID_c* pid, s32 arg1) {
    UNUSED s32 pad;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 sp20;
    s32 res = FALSE;

    if (func_800B7914_jp(pid) == 0) {
        home = &common_data.save.homes[func_80094BF4_jp(arg1)];
        if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
            sp20 = func_8009C534_jp(home->mailbox, MAIL_HEADER_LEN);
            if (sp20 != -1) {
                func_800A9CD4_jp(&B_80142F80_jp, pid);
                func_8009C67C_jp(&home->mailbox[sp20], &B_80142F80_jp);
                res = TRUE;
            }
        }
    }
    return res;
}

void func_800A9E54_jp(Animal_c* animal, u8* arg1) {
    mem_copy(animal->catchphrase, arg1, ANIMAL_CATCHPHRASE_LEN);
}

u8* func_800A9E7C_jp(Actor* actor) {
    Animal_c* var_a1;
    Animal_c* tmp;
    u8* var_v1;

    if ((actor != NULL) & (actor->part == ACTOR_PART_NPC)) {
        var_a1 = tmp = ((Npc*)actor)->animal;
    } else {
        var_a1 = NULL;
    }

    if ((actor != NULL) && (var_a1 != NULL)) {
        var_v1 = var_a1->catchphrase;
    } else {
        var_v1 = D_8010B818_jp;
    }

    return var_v1;
}

void func_800A9EC8_jp(Actor* actor) {
    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Animal_c* animal = ((Npc*)actor)->animal;
        Struct_D_E03000* sp30;
        u16 idx;

        if (animal != NULL) {
            sp30 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));

            if (0) {}

            if (sp30 != NULL) {
                func_80026E10_jp(sp30, SEGMENT_ROM_START(segment_00E03000), ALIGN16(SEGMENT_ROM_SIZE(segment_00E03000)),
                                 "../m_npc.c", 0xE25);
                idx = animal->id.npc_id & 0xFFF;
                func_800C3F70_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, sp30[idx].unk_02);
                zelda_free(sp30);
            }
        }
    }
}

s32 func_800A9F9C_jp(void) {
    CommonData_unk_10170* var_a2 = common_data.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.unk_10710); i++) {
        if (var_a2->unk_09 == 0) {
            return i;
        }
        var_a2++;
    }
    return -1;
}

s32 func_800AA028_jp(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    s32 idx = func_800A9F9C_jp();
    s32 res = FALSE;

    if (idx != -1) {
        common_data.unk_10710[idx].fg_name = arg0;
        common_data.unk_10710[idx].unk_02 = arg1;
        common_data.unk_10710[idx].npc_id = arg2;
        common_data.unk_10710[idx].unk_06 = arg3;
        common_data.unk_10710[idx].unk_08 = 0;
        common_data.unk_10710[idx].unk_09 = 1;
        res = TRUE;
    }
    return res;
}

void func_800AA0B8_jp(u16 fgname) {
    CommonData_unk_10170* var_a2 = common_data.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.unk_10710); i++) {
        if ((var_a2->unk_09 == 1) && (var_a2->fg_name == fgname)) {
            bzero(var_a2, sizeof(CommonData_unk_10170));
            break;
        }
        var_a2++;
    }
}

void func_800AA124_jp(void) {
    bzero(common_data.unk_10710, sizeof(common_data.unk_10710));
}

CommonData_unk_10170* func_800AA14C_jp(u16 fg_name) {
    CommonData_unk_10170* ptr = common_data.unk_10710;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.unk_10710); i++) {
        if (ptr->fg_name == fg_name) {
            return ptr;
        }
        ptr++;
    }

    return NULL;
}

s32 mNpc_GetLooks(u16 npc_name) {
    u8 res = 0;

    if (ACTOR_FGNAME_GET_F000(npc_name) == FGNAME_F000_E) {
        res = D_8010AF58_jp[mNpc_GET_IDX(npc_name)];
    }
    return res;
}

void func_800AA218_jp(Animal_c* animal, u16 arg1, u8 arg2, Struct_D_E03000* arg3) {
    if (ACTOR_FGNAME_GET_F000(arg1) == FGNAME_F000_E) {
        animal->id.npc_id = arg1;
        animal->id.looks = arg2;
        animal->unk_520 = arg3->unk_00;
        func_800C3F70_jp(animal->catchphrase, ANIMAL_CATCHPHRASE_LEN, arg3->unk_02);
        animal->id.land_id = common_data.save.land_info.land_id;
        mLd_CopyLandName(animal->id.land_name, common_data.save.land_info.name);
    }
}

void func_800AA29C_jp(Animal_c* animal, u16 arg1, Struct_D_E03000 arg2[]) {
    s32 idx = mNpc_GET_IDX(arg1);
    if (ACTOR_FGNAME_GET_F000(arg1) == FGNAME_F000_E) {
        func_800AA218_jp(animal, arg1, D_8010AF58_jp[idx], &arg2[idx]);
    }
}

void func_800AA2F8_jp(u16 arg0) {
    u8* ptr = common_data.save.unk_0F86C;

    if (ACTOR_FGNAME_GET_F000(arg0) == FGNAME_F000_E) {
        s32 idx = mNpc_GET_IDX(arg0);
        s32 temp_a2 = idx / 8;

        if (temp_a2 < ARRAY_COUNT(common_data.save.unk_0F86C)) {
            ptr += temp_a2;
            idx &= 7;
            *ptr |= 1 << idx;
        }
    }
}

s32 func_800AA35C_jp(s32 arg0) {
    s32 res = TRUE;
    u8* ptr = common_data.save.unk_0F86C;
    s32 temp_a1 = arg0 / 8;

    if (temp_a1 < ARRAY_COUNT(common_data.save.unk_0F86C)) {
        ptr += temp_a1;
        res = (*ptr >> (arg0 & 7)) & 1;
    }
    return res;
}

s32 func_800AA3A4_jp(u8 arg0) {
    s32 i;
    s32 count = 0;

    if (arg0 < 6) {
        for (i = 0; i < 0xD8; i++) {
            if ((arg0 == D_8010AF58_jp[i]) && (func_800AA35C_jp(i) == FALSE)) {
                count++;
            }
        }
    }
    return count;
}

void func_800AA438_jp(u8* arg0, Animal_c* animal) {
    s32 i;

    bzero(arg0, sizeof(common_data.save.unk_0F86C));

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            func_800AA2F8_jp(animal->id.npc_id);
        }
        animal++;
    }
}

void func_800AA49C_jp(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(B_80143028_jp); i++) {
        if (func_800AA35C_jp(i) == FALSE) {
            break;
        }
    }

    if (i == ARRAY_COUNT(B_80143028_jp)) {
        func_800AA438_jp(common_data.save.unk_0F86C, common_data.save.animals);
    }
}

s32 func_800AA4FC_jp(s32 arg0, u8* arg1, s32 arg2) {
    s8 res = 1;

    if (arg0 < arg2) {
        res = arg1[arg0];
    }
    return res;
}

void func_800AA51C_jp(Animal_c* animal, u8 arg1, s32 count) {
    UNUSED s32 pad;
    void* sp50;
    void* sp4C;
    u8 var_s7 = 0;
    s32 i = 0;
    u8 temp_s2;

    bzero(B_80143028_jp, sizeof(B_80143028_jp));
    func_800A6810_jp(B_80143028_jp, ARRAY_COUNT(B_80143028_jp), ARRAY_COUNT(B_80143028_jp));

    if (count == 0) {
        sp50 = malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        sp4C = malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    } else {
        sp50 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
        sp4C = zelda_malloc(ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));
    }

    func_80026E10_jp(sp50, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000), "../m_npc.c", 4083);
    func_80026E10_jp(sp4C, SEGMENT_ROM_START(segment_00E0D000), ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)),
                     "../m_npc.c", 4085);

    while (arg1) {
        if (animal == NULL) {
            break;
        }

        if (animal->id.npc_id == 0) {
            s32 temp_s0 = B_80143028_jp[i];
            s32 temp_v0 = func_800AA4FC_jp(temp_s0, sp4C, ALIGN2(SEGMENT_ROM_SIZE(segment_00E0D000)));

            if (temp_v0 == 0) {
                temp_s2 = D_8010AF58_jp[temp_s0];
                if (((var_s7 >> temp_s2) & 1) == 0) {
                    func_800AA29C_jp(animal, temp_s0 | 0xE000, (Struct_D_E03000*)sp50);
                    var_s7 |= (1 << temp_s2);
                    func_800AA2F8_jp(temp_s0 | 0xE000);
                    animal++;
                    arg1--;
                }
            } else if (temp_v0 == -1) {
                func_800AA2F8_jp(temp_s0 | 0xE000);
            }
        } else {
            arg1--;
            animal++;
        }
        i++;
    }

    if (count == 0) {
        free(sp50);
        free(sp4C);
    } else {
        zelda_free(sp50);
        zelda_free(sp4C);
    }
}

void mNpc_SetAnimalTitleDemo(mNpc_demo_npc_c* demo_npc, Animal_c* animal, Game* game) {
    GameAlloc* alloc = NULL;
    Struct_D_E03000* var_v0;
    s32 i;

    if (game != NULL) {
        alloc = &game->alloc;
        var_v0 = gamealloc_malloc(alloc, SEGMENT_ROM_SIZE(segment_00E03000));
    } else {
        var_v0 = zelda_malloc(SEGMENT_ROM_SIZE(segment_00E03000));
    }
    func_80026E10_jp(var_v0, SEGMENT_ROM_START(segment_00E03000), SEGMENT_ROM_SIZE(segment_00E03000), "../m_npc.c",
                     0x1055);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        func_800AA29C_jp(animal, demo_npc->npc_name, var_v0);
        animal->home_info.type_unused = 0;
        animal->home_info.block_x = demo_npc->block_x;
        animal->home_info.block_z = demo_npc->block_z;
        animal->home_info.ut_x = demo_npc->ut_x;
        animal->home_info.ut_z = demo_npc->ut_z;

        animal++;
        demo_npc++;
    }

    if (var_v0 != NULL) {
        if (game != NULL) {
            gamealloc_free(alloc, var_v0);
        } else {
            zelda_free(var_v0);
        }
    }
}

s32 func_800AA8C4_jp(s32* arg0, s32* arg1, u16* arg2) {
    f32 sp24 = 0.0f;
    s32 rand;
    s32 res = FALSE;
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (((*arg2 >= 0x5810) && (*arg2 < 0x5825)) || (*arg2 == 0xF0EE)) {
            sp24++;
        }
        arg2++;
    }

    if (sp24 > 0.0f) {
        arg2 -= 0x100;
        rand = RANDOM(sp24);

        for (i = 0; i < 0x100; i++) {
            if (((*arg2 >= 0x5810) && (*arg2 < 0x5825)) || (*arg2 == 0xF0EE)) {
                if (rand == 0) {
                    *arg0 = i % 16;
                    *arg1 = i / 16;
                    res = TRUE;
                    break;
                } else {
                    rand--;
                }
            }
            arg2++;
        }
    }
    return res;
}

s32 func_800AA9F4_jp(s32* arg0, s32* arg1, UNK_TYPE arg2, UNK_TYPE arg3) {
    u16* temp_v0 = func_8008A33C_jp(arg2, arg3);
    s32 res = FALSE;

    if (temp_v0 != NULL) {
        res = func_800AA8C4_jp(arg0, arg1, temp_v0);
    }
    return res;
}

void func_800AAA40_jp(Struct_B_80142D08_jp* arg0, s32 count, u8* arg2) {
    mFM_fg_c* fg = &common_data.save.fg[0][0];
    Struct_B_80142D08_jp* arg0_backup = arg0;
    u16* item;
    u8 num = 0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < count; i++) {
        arg0->unk_01 = 0xFF;
        arg0->unk_02 = 0xFF;
        arg0->unk_03 = 0xFF;
        arg0->unk_04 = 0xFF;
        arg0++;
    }

    arg0 = arg0_backup;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 5; j++) {
            item = &fg->items[0][0];
            for (k = 0; k < 16; k++) {
                for (l = 0; l < 16; l++) {
                    if ((*item >= 0x5810) && (*item < 0x5825)) {
                        num++;
                        arg0->unk_01 = j + 1;
                        arg0->unk_02 = i + 1;
                        arg0->unk_03 = l;
                        arg0->unk_04 = k;
                        arg0++;
                        if (num >= count) {
                            *arg2 = num;
                            return;
                        }
                    }
                    item++;
                }
            }
            fg++;
        }
    }

    *arg2 = num;
}

void func_800AAB48_jp(Struct_B_80142D08_jp* arg0, s32 arg1, u8* arg2, u8 arg3, u8 arg4) {
    Struct_g_fdinfo_148* var_t1 = func_80087C64_jp();
    Struct_B_80142D08_jp* var_s0 = arg0;
    u8 count = 0;
    u16* var_a0;
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    for (i = 0; i < arg1; i++) {
        arg0->unk_01 = 0xFF;
        arg0->unk_02 = 0xFF;
        arg0->unk_03 = 0xFF;
        arg0->unk_04 = 0xFF;
        arg0++;
    }
    arg0 = var_s0;

    for (i = 0; i < arg4; i++) {
        for (j = 0; j < arg3; j++) {
            var_a0 = var_t1->unk_584;
            for (k = 0; k < 16; k++) {
                for (l = 0; l < 16; l++) {
                    if ((*var_a0 >= 0x5810) && (*var_a0 < 0x5825)) {
                        count++;
                        arg0->unk_01 = j;
                        arg0->unk_02 = i;
                        arg0->unk_03 = l;
                        arg0->unk_04 = k;
                        arg0++;
                        if (count >= arg1) {
                            *arg2 = count;
                            return;
                        }
                    }
                    var_a0++;
                }
            }
            var_t1++;
        }
    }

    *arg2 = count;
}

void func_800AAC88_jp(u16 npc_id, s32 block_x, s32 block_z, s32 ut_x, s32 ut_z) {
    u16* deposit;
    s32 x;
    s32 z;
    s32 i;

    if ((block_x >= 0) && (block_x < 5) && (block_z >= 0) && (block_z < 6) && (ut_x > 0) && (ut_x < 0xF) &&
        (ut_z > 0) && (ut_z < 0xF)) {
        mFM_fg_c* fg = &common_data.save.fg[block_z][block_x];

        D_8010B908_jp[0] = npc_id + 0xFFFF7000;
        deposit = func_8008C1E0_jp(block_x + 1, block_z + 1);

        for (i = 0; i < ARRAY_COUNT(D_8010B908_jp); i++) {
            x = D_8010B8C0_jp[i].unk_00 + ut_x;
            z = D_8010B8C0_jp[i].unk_04 + ut_z;

            mPB_keep_item(fg->items[z][x]);
            if (deposit != NULL) {
                func_8008C478_jp(deposit, x, z);
            }
            fg->items[z][x] = D_8010B908_jp[i];
        }
    }
}

#ifdef NON_MATCHING
void func_800AADE8_jp(Anmhome_c* home_info) {
    u8 block_x = home_info->block_x - 1;
    u8 block_z = home_info->block_z - 1;
    u8 ut_x = home_info->ut_x;
    u8 ut_z = home_info->ut_z - 1;

    if ((block_x < 5) && (block_z < 6) && (ut_x > 0) && (ut_x < 0xF) && (ut_z > 0) && (ut_z < 0xF)) {
        s32 val = func_800879B0_jp(home_info->block_x, home_info->block_z);

        common_data.save.fg[block_z][block_x].items[ut_z][ut_x] = val;    // a8
        common_data.save.fg[block_z][block_x].items[ut_z][ut_x + 15] = 0; // c6
        common_data.save.fg[block_z][block_x].items[ut_z + 1][0] = 0;     // c8
        common_data.save.fg[block_z][block_x].items[ut_z + 1][1] = 0;     // ca

        common_data.save.fg[block_z][block_x].items[ut_z][ut_x - 1] = 0; // a6
        common_data.save.fg[block_z][block_x].items[ut_z][ut_x + 1] = 0; // aa

        common_data.save.fg[block_z][block_x].items[ut_z - 2][15] = 0; // 86
        common_data.save.fg[block_z][block_x].items[ut_z - 1][0] = 0;  // 88
        common_data.save.fg[block_z][block_x].items[ut_z - 1][1] = 0;  // 8a
    }
}
#else
void func_800AADE8_jp(Anmhome_c* home_info);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800AADE8_jp.s")
#endif

void func_800AAEFC_jp(Animal_c* animal, Struct_B_80142D08_jp* arg1, u8 arg2) {
    Anmhome_c* home_info;
    s32 i;
    s32 idx;

    if (arg2 > ARRAY_COUNT(B_80142C00_jp)) {
        arg2 = ARRAY_COUNT(B_80142C00_jp);
    }
    bzero(B_80142C00_jp, sizeof(B_80142C00_jp));
    func_800A6810_jp(B_80142C00_jp, arg2, 30);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (i >= arg2) {
            break;
        }

        home_info = &animal->home_info;
        if ((ACTOR_FGNAME_GET_F000(animal->id.npc_id) == FGNAME_F000_E) && (home_info->block_x == 0xFF) &&
            (home_info->block_z == 0xFF)) {
            idx = B_80142C00_jp[i];
            home_info->block_x = arg1[idx].unk_01;
            home_info->block_z = arg1[idx].unk_02;
            home_info->ut_x = arg1[idx].unk_03;
            home_info->ut_z = arg1[idx].unk_04 + 1;
            func_800AAC88_jp(animal->id.npc_id, home_info->block_x - 1, home_info->block_z - 1, home_info->ut_x,
                             arg1[idx].unk_04);
        }
        animal++;
    }
}

void func_800AB054_jp(void) {
    UNUSED s32 pad;
    u8 sp1B = 0;

    func_800AAA40_jp(B_80142D08_jp, ARRAY_COUNT(B_80142D08_jp), &sp1B);
    func_800AAEFC_jp(common_data.save.animals, B_80142D08_jp, sp1B);
}

void func_800AB09C_jp(void) {
    mNpc_NpcList_c* npclist = common_data.npclist;
    s32 i;

    bzero(npclist, sizeof(mNpc_NpcList_c) * ANIMAL_NUM_MAX);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        npclist->field_name = 0xFFFF;
        func_800BA660_jp(&npclist->quest_info);
        npclist->house_data.type = 0xFF;
        npclist->house_data.palette = 0xFF;
        npclist->house_data.wall_id = 0xFF;
        npclist->house_data.floor_id = 0xFF;
        npclist->house_data.main_layer_id = 0xCB;
        npclist++;
    }
}

void mNpc_SetNpcList(mNpc_NpcList_c* npclist, Animal_c* animal, s32 count, s32 malloc_flag) {
    mNpc_NpcHouseData_c* house_data;
    mNpc_NpcHouseData_c* new_house;
    Vec3f* home_pos;
    Vec3f* pos;
    s32 id;
    f32 z;
    Anmhome_c* home_info;
    f32 x;
    u32 house_data_size;
    s32 i;
    s32 npc_id;

    house_data_size = SEGMENT_ROM_SIZE(segment_00E02000);
    if (malloc_flag == 0) {
        house_data = malloc(house_data_size);
    } else {
        house_data = zelda_malloc(house_data_size);
    }
    func_80026E10_jp(house_data, SEGMENT_ROM_START(segment_00E02000), house_data_size, "../m_npc.c", 0x1328);

    for (i = 0; i < count; i++) {
        home_info = &animal->home_info;
        if ((ACTOR_FGNAME_GET_F000(animal->id.npc_id) == FGNAME_F000_E) && (home_info->block_x != 0xFF)) {
            npc_id = animal->id.npc_id;
            id = animal->id.npc_id & 0xFFF;
            new_house = &npclist->house_data;
            home_pos = &npclist->home_position;
            pos = &npclist->position;
            if (0) {}
            npclist->name = npc_id;

            home_pos->x = home_info->block_x * 640.0f;
            home_pos->z = home_info->block_z * 640.0f;
            func_80088BC0_jp(&x, &z, home_info->ut_x, home_info->ut_z);

            home_pos->x += x;
            home_pos->z += z;
            home_pos->y = 0.0f;

            pos->x = home_pos->x;
            pos->y = home_pos->y;
            pos->z = home_pos->z;

            npclist->flags.unk_31 = 1;
            npclist->reward_furniture = 0;

            new_house->type = house_data[id].type;
            new_house->palette = house_data[id].palette;
            new_house->wall_id = house_data[id].wall_id;
            new_house->floor_id = house_data[id].floor_id;
            new_house->main_layer_id = house_data[id].main_layer_id;
            new_house->secondary_layer_id = house_data[id].secondary_layer_id;
        }
        npclist++;
        animal++;
    }

    if (malloc_flag == 0) {
        free(house_data);
    } else {
        zelda_free(house_data);
    }
}

void mNpc_SetNpcinfo(Actor* actor, s8 npc_info_idx) {
    if (actor->part == ACTOR_PART_NPC) {
        Npc* npc = (Npc*)actor;

        if (ACTOR_FGNAME_GET_F000(npc->actor.fgName) == FGNAME_F000_D) {
            CommonData_unk_10170* temp_v0 = func_800AA14C_jp(npc->actor.fgName);

            if (temp_v0 != NULL) {
                npc_info_idx = mNpc_SearchAnimalinfo(common_data.save.animals, temp_v0->npc_id, ANIMAL_NUM_MAX);
            }
        }

        if ((npc_info_idx >= 0) && (npc_info_idx < ANIMAL_NUM_MAX)) {
            npc->animal = &common_data.save.animals[npc_info_idx];
            npc->npclist = &common_data.npclist[npc_info_idx];
        } else {
            npc->animal = NULL;
            npc->npclist = NULL;
        }
    }
}

void func_800AB498_jp(FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2) {
    s32 temp_v0;
    s32 sp38;
    u16 field_id;
    u16 sp34;
    u8* temp_v0_3;
    UNUSED s32 pad;
    u16 sp2A;
    s32 sp24;

    if (arg0 != NULL) {
        field_id = mFI_GetFieldId();
        sp38 = func_8008BE00_jp(arg0, 16);
        if (sp38 != -1) {
            arg0 = &arg0[sp38];
            if (mNpc_GET_TYPE(field_id) == 0x4000) {
                sp34 = common_data.house_owner_name;
                if ((sp38 < ANIMAL_NUM_MAX) && (sp34 != 0xFFFF) && (sp34 != 0)) {
                    if (func_80082CC8_jp(sp34) != 1) {
                        temp_v0 = mNpc_SearchAnimalinfo(common_data.save.animals, sp34, ANIMAL_NUM_MAX);
                        if (temp_v0 != -1) {
                            arg0->house_owner_name = sp34;
                            arg0->unk_02 = 4;
                            arg0->unk_03 = 7;
                            arg0->npc_id = temp_v0;
                            arg0->unk_06 = -1;
                            func_8008BC64_jp(sp38, arg1, arg2);
                        }
                    }
                }
            } else if (field_id == 0x300A) {
                temp_v0_3 = func_8008033C_jp(0xE, 0xF);
                if (temp_v0_3 != NULL) {
                    sp24 = *temp_v0_3;
                    sp2A = common_data.save.animals[sp24].id.npc_id;
                    func_80082BD8_jp(&sp2A, 0xE, sp24, 0);
                    arg0->house_owner_name = sp2A;
                    arg0->unk_02 = 4;
                    arg0->unk_03 = 7;
                    arg0->npc_id = sp24;
                    arg0->unk_06 = -1;
                    func_8008BC64_jp(sp38, arg1, arg2);
                }
            }
        }
    }
}

void func_800AB62C_jp(s16* arg0) {
    s32 field_id = mFI_GetFieldId();
    u16 owner_name = common_data.house_owner_name;
    s32 wall_id;
    s32 floor_id;
    s32 npc_idx;

    if (mNpc_GET_TYPE(field_id) == 0x4000) {
        if ((owner_name != 0) && (owner_name != 0xFFFF)) {
            npc_idx = mNpc_SearchAnimalinfo(common_data.save.animals, owner_name, ANIMAL_NUM_MAX);
            wall_id = common_data.npclist[npc_idx].house_data.wall_id;
            floor_id = common_data.npclist[npc_idx].house_data.floor_id;
            *arg0 = floor_id | (wall_id << 8);
        label:;
            return;
        }
    }
    *arg0 = 0;
}

void func_800AB6C8_jp(Actor* actor) {
    Npc* npc = (Npc*)actor;

    if (npc->npclist != NULL) {
        s32 field_id = mFI_GetFieldId();
        mNpc_NpcList_c* npclist = npc->npclist;

        if ((mNpc_GET_TYPE(field_id)) == 0) {
            xyz_t_move(&npclist->position, &npc->actor.world.pos);
            npclist->flags.unk_31 = 1;
        }
    } else {
        func_8008BD98_jp(actor);
    }
}

s32 func_800AB734_jp(Private_c* private) {
    Animal_c* animal = common_data.save.animals;
    s32 count = 0;
    s32 i;

    if (private != NULL) {

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if ((mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) &&
                (func_800A7238_jp(&private->player_ID, animal->memories, ANIMAL_MEMORY_NUM) != -1)) {
                count++;
            }
            animal++;
        }
    }
    return count;
}

s32 func_800AB7D0_jp(Private_c* private) {
    s32 npc_max = common_data.save.now_npc_max;

    if (func_800AB734_jp(private) >= npc_max) {
        return TRUE;
    }
    return FALSE;
}

s32 func_800AB80C_jp(u16 arg0) {
    s32 res = FALSE;

    if (((arg0 < 0x17AC) || (arg0 >= 0x1BA8)) && ((arg0 < 0x1CA8) || (arg0 >= 0x1D28)) &&
        ((arg0 < 0x1BA8) || (arg0 >= 0x1C28)) && ((arg0 < 0x1C28) || (arg0 >= 0x1CA8)) &&
        ((arg0 < 0x15B0) || (arg0 >= 0x17AC)) && ((arg0 < 0x1E3C) || (arg0 >= 0x1EA0)) &&
        ((arg0 < 0x1D28) || (arg0 >= 0x1D44))) {
        res = TRUE;
    }
    return res;
}

u16 func_800AB8A0_jp(FieldMake_Unk_Struct* arg0, mNpc_NpcList_c* npclist, s32 count) {
    u16 layer_id = npclist->house_data.main_layer_id;
    s32 idx = layer_id - count;
    u16* var_s1;
    s32 i;
    s32 j;
    u8 var_s2 = 0;

    if (idx < 0) {
        idx = 0;
    }
    var_s1 = arg0->unk_000[idx] + 1;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if ((ACTOR_FGNAME_GET_F000(*var_s1) == FGNAME_F000_1) && (func_800AB80C_jp(*var_s1) == TRUE)) {
                var_s2++;
            }
            var_s1++;
        }
        var_s1 += 6;
    }

    if (var_s2 > 0) {
        var_s2 = RANDOM(var_s2);
        var_s1 = arg0->unk_000[idx] + 1;

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                if ((ACTOR_FGNAME_GET_F000(*var_s1) == FGNAME_F000_1) && (func_800AB80C_jp(*var_s1) == TRUE)) {
                    if (var_s2 <= 0) {
                        return *var_s1;
                    }
                    var_s2--;
                }
                var_s1++;
            }
            var_s1 += 6;
        }
    }

    return 0;
}

void func_800ABA14_jp(FieldMake_Unk_Struct* arg0, s32 count) {
    mNpc_NpcList_c* npclist = common_data.npclist;
    Animal_c* animal = common_data.save.animals;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            npclist->reward_furniture = func_800AB8A0_jp(arg0, npclist, count);
        }
        npclist++;
        animal++;
    }
}

u16 func_800ABAA8_jp(AnmPersonalID_c* anm_id) {
    u16 res = 0;
    s32 idx = func_800A7D08_jp(anm_id);

    if (idx != -1) {
        res = common_data.npclist[idx].reward_furniture;
    }
    return res;
}

void func_800ABAF0_jp(void) {
    mNpc_ClearAnimalInfo(&B_80143388_jp);
}

Animal_c* mNpc_GetInAnimalP(void) {
    return &B_80143388_jp;
}

s32 func_800ABB24_jp(Animal_c* animal, s32 arg1) {
    Private_c* priv = common_data.save.private;
    s32 res = -1;
    s32 sp44 = 0;
    s32 var_s7 = 0;
    s32 var_s2;
    s32 i;
    s32 j;
    u16 var_fp = 0;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (func_800B7914_jp(&priv->player_ID) == 0) {
            sp44++;
        }
        priv++;
    }

    if (sp44 > 0) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                priv = common_data.save.private;
                var_s2 = 0;

                for (j = 0; j != PLAYER_NUM; j++) {
                    if (func_800B7914_jp(&priv->player_ID) == FALSE) {
                        if (func_800A7238_jp(&priv->player_ID, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
                            break;
                        }
                        var_s2++;
                    }
                    priv++;
                }

                if (arg1 == 1) {
                    if (var_s2 == sp44) {
                        var_s7++;
                        var_fp |= (1 << i);
                    }
                } else if (var_s2 > 0) {
                    var_s7++;
                    var_fp |= (1 << i);
                }
            }
            animal++;
        }
    }

    if (var_s7 > 0) {
        s32 rand = RANDOM(var_s7);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((var_fp >> i) & 1) == 1) {
                if (rand <= 0) {
                    res = i;
                    break;
                }
                rand--;
            }
        }
    }
    return res;
}

u8 func_800ABCF8_jp(Animal_c* animal, s32 arg1) {
    u8 count = 0;
    s32 rand = RANDOM(arg1);
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            rand--;
        }
        if (rand <= 0) {
            break;
        }
        count++;
        animal++;
    }

    return count;
}

void mNpc_SetRemoveAnimalNo(Animal_c* animal) {
    u8* removal_idx = &common_data.save.remove_animal_idx;
    u8 now_max = common_data.save.now_npc_max;

    if ((now_max >= 6) && (*removal_idx == 0xFF)) {
        s32 var_v1 = func_800ABB24_jp(animal, 1);

        if (var_v1 == -1) {
            var_v1 = func_800ABB24_jp(animal, 0);
            if (var_v1 == -1) {
                var_v1 = func_800ABCF8_jp(animal, now_max);
            }
        }

        if (var_v1 != -1) {
            *removal_idx = var_v1;
        }
    }
}

s32 func_800ABE30_jp(Animal_c* animal1, Animal_c* animal2) {
    Anmmem_c* sp28 = animal1->memories;
    Anmmem_c* sp24 = animal2->memories;
    s32 res = 0;
    s32 temp_s0 = func_800A77F0_jp(sp28, ANIMAL_MEMORY_NUM);
    s32 temp_v0 = func_800A77F0_jp(sp24, ANIMAL_MEMORY_NUM);

    if (temp_s0 < temp_v0) {
        res = 1;
    } else if (temp_v0 == temp_s0) {
        temp_s0 = func_800A7858_jp(sp28, ANIMAL_MEMORY_NUM);
        temp_v0 = func_800A7858_jp(sp24, ANIMAL_MEMORY_NUM);
        if (temp_s0 < temp_v0) {
            res = 1;
        } else if (temp_v0 == temp_s0) {
            temp_s0 = func_800A78DC_jp(sp28, ANIMAL_MEMORY_NUM);
            temp_v0 = func_800A78DC_jp(sp24, ANIMAL_MEMORY_NUM);
            if (temp_s0 < temp_v0) {
                res = 1;
            } else if (temp_v0 == temp_s0) {
                temp_s0 = func_800A8148_jp(animal1->id.looks);
                if (func_800A8148_jp(animal2->id.looks) < temp_s0) {
                    res = 1;
                } else {
                    res = -1;
                }
            }
        }
    }

    return res;
}

s32 func_800ABF40_jp(void) {
    UNUSED s32 pad;
    Animal_c* animal = common_data.save.animals;
    Animal_c* found_animal = NULL;
    s32 temp_s1;
    s32 temp_v0;
    u16 var_s4 = 0;
    s32 var_s5 = 0;
    s32 found_idx = -1;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
        if ((i != (u32)&common_data.save.remove_animal_idx) && (mNpc_CheckFreeAnimalInfo(animal) == FALSE)) {
            if (found_animal != NULL) {
                if (func_800A6B58_jp(animal) == 0) {
                    if (func_800A6B58_jp(found_animal) != 0) {
                        var_s5 = 1;
                        var_s4 = (1 << i);
                        found_animal = animal;
                        found_idx = i;
                    } else {
                        temp_v0 = func_800ABE30_jp(animal, found_animal);
                        switch (temp_v0) {
                            case -1:
                                var_s5++;
                                var_s4 |= (1 << i);
                                break;
                            case 1:
                                var_s5 = 1;
                                var_s4 = (1 << i);
                                found_animal = animal;
                                found_idx = i;
                                break;
                        }
                    }
                } else if (func_800A6B58_jp(found_animal) != 0) {
                    temp_s1 = func_800A6B6C_jp(animal);
                    temp_v0 = func_800A6B6C_jp(found_animal);
                    if (temp_s1 < temp_v0) {
                        var_s5 = 1;
                        var_s4 = (1 << i);
                        found_animal = animal;
                        found_idx = i;
                    } else if (temp_v0 == temp_s1) {
                        temp_v0 = func_800ABE30_jp(animal, found_animal);
                        switch (temp_v0) {
                            case -1:
                                var_s5++;
                                var_s4 |= (1 << i);
                                break;
                            case 1:
                                var_s5 = 1;
                                var_s4 = (1 << i);
                                found_animal = animal;
                                found_idx = i;
                                break;
                        }
                    }
                }
            } else {
                var_s5 = 1;
                var_s4 = (1 << i);
                found_animal = animal;
                found_idx = i;
            }
        }
    }

    if (var_s5 >= 2) {
        s32 rand = RANDOM(var_s5);

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((var_s5 >> i) & 1) == 1) {
                if (rand == 0) {
                    found_idx = i;
                    break;
                } else {
                    rand--;
                }
            }
        }
    }
    return found_idx;
}

void func_800AC1A0_jp(Struct_B_80142F70_jp* arg0) {
    mNpc_ClearAnimalPersonalID(&arg0->id);
    arg0->unk_0C = 0;
}

void func_800AC1C8_jp(void) {
    func_800AC1A0_jp(&B_80142F70_jp);
}

void func_800AC1EC_jp(Struct_B_80142F70_jp* arg0, Animal_c* animal) {
    Private_c* priv = common_data.save.private;
    s32 i;

    if ((animal != NULL) && (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE)) {
        mNpc_CopyAnimalPersonalID(&arg0->id, &animal->id);

        for (i = 0; i < PLAYER_NUM; i++) {
            if (func_800B7914_jp(&priv->player_ID) == FALSE) {
                arg0->unk_0C |= 1 << i;
            }
            priv++;
        }
    }
}

s32 func_800AC284_jp(Mail_c* mail, PersonalID_c* pid, AnmPersonalID_c* anm_id) {
    s32 sp24;
    s32 res = FALSE;

    if (anm_id->looks < 6) {
        sp24 = (anm_id->looks * 3) + 0x20E;
        sp24 += func_800BC414_jp(3);
        mNpc_GetNpcWorldNameAnm(B_80142F60_jp, anm_id);
        func_80092D10_jp(0, pid->player_name, PLAYER_NAME_LEN);
        func_80092D10_jp(1, B_80142F60_jp, PLAYER_NAME_LEN);
        func_80092D10_jp(3, common_data.save.land_info.name, LAND_NAME_SIZE);
        func_800A93AC_jp(mail, pid, anm_id, 0, func_800A9364_jp(), sp24);
        res = TRUE;
    }
    return res;
}

s32 func_800AC358_jp(Mail_c* mail, Private_c* priv, s32 player_no, AnmPersonalID_c* anm_id) {
    mHm_hs_c* home;
    UNUSED s32 pad;
    s32 res = FALSE;

    home = &common_data.save.homes[func_80094BF4_jp(player_no)];

    if ((func_800B7914_jp(&priv->player_ID) == FALSE) &&
        (mPr_CheckCmpPersonalID(&priv->player_ID, &home->ownerID) == TRUE)) {
        s32 sp18 = func_8009C534_jp(home->mailbox, HOME_MAILBOX_SIZE);
        if (sp18 != -1) {
            if (func_800AC284_jp(mail, &priv->player_ID, anm_id) == TRUE) {
                func_8009C67C_jp(&home->mailbox[sp18], mail);
                res = TRUE;
            }
        } else if ((func_800B68E8_jp() < 5) && (func_800AC284_jp(mail, &priv->player_ID, anm_id) == TRUE)) {
            res = func_800B6A3C_jp(mail, 0);
        }
    }
    return res;
}

void func_800AC488_jp(Struct_B_80142F70_jp* arg0) {
    Private_c* priv = common_data.save.private;
    s32 i;

    if (mNpc_CheckFreeAnimalPersonalID(&arg0->id) == FALSE) {
        for (i = 0; i < PLAYER_NUM; i++) {
            if ((((arg0->unk_0C >> i) & 1) == 1) && (func_800AC358_jp(&B_80142F80_jp, priv, i, &arg0->id) == TRUE)) {
                arg0->unk_0C &= ~(1 << i);
            }
            priv++;
        }

        if (arg0->unk_0C == 0) {
            func_800AC1A0_jp(arg0);
        }
    }
}

void mNpc_SendRegisteredGoodbyMail(void) {
    func_800AC488_jp(&B_80142F70_jp);
}

void func_800AC57C_jp(Animal_c* in_animal, s32 arg1) {
    Private_c* priv;
    UNUSED s32 pad[4];
    s32 sp20;
    Animal_c* animal;
    s32 free_animal_idx;
    u8* remove_animal_idx = &common_data.save.remove_animal_idx;
    u8* now_max = &common_data.save.now_npc_max;
    s32 i;

    animal = common_data.save.animals;
    sp20 = 1;
    priv = common_data.now_private;
    if (mLd_PlayerManKindCheck() == 0) {
        if (arg1 == 1) {
            if (*remove_animal_idx != 0xFF) {
                animal = &common_data.save.animals[*remove_animal_idx];
                animal->unk_526 = 0;
                mNpc_CopyAnimalInfo(in_animal, animal);
                func_800AADE8_jp(&animal->home_info);
                mNpc_ClearAnimalInfo(animal);
                *remove_animal_idx = 0xFF;
                (*now_max)--;
            }
        }
    } else {
        if ((mNpc_CheckFreeAnimalInfo(in_animal) == FALSE) && (in_animal->unk_526 == 0)) {
            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (in_animal->id.npc_id == animal->id.npc_id) {
                    sp20 = 0;
                    break;
                }
                animal++;
            }

            if (in_animal->id.npc_id == common_data.save.last_removed_animal_id.npc_id) {
                sp20 = 0;
            }
        } else {
            sp20 = 0;
        }

        if (sp20 == 1) {
            animal = common_data.save.animals;
            free_animal_idx = mNpc_GetFreeAnimalInfo(common_data.save.animals, ANIMAL_NUM_MAX);
            if (free_animal_idx == -1) {
                animal += func_800ABF40_jp();
                func_800AADE8_jp(&animal->home_info);
                func_800AC1EC_jp(&B_80142F70_jp, animal);
                mNpc_SendRegisteredGoodbyMail();
            } else {
                animal += free_animal_idx;
                func_800A6940_jp(&common_data.save.now_npc_max);
            }
            mNpc_ClearAnimalInfo(animal);
            mNpc_CopyAnimalInfo(animal, in_animal);
            animal->home_info.block_x = 0xFF;
            animal->home_info.block_z = 0xFF;
            animal->home_info.ut_x = 0xFF;
            animal->home_info.ut_z = 0xFF;
            mLd_CopyLandName(animal->previous_land_name, common_data.now_private->player_ID.land_name);
            animal->unk_51C = common_data.now_private->player_ID.land_id;
            func_800BA778_jp(&animal->contest_quest);
            in_animal->unk_526 = 1;
            priv->animal_memory.npc_id = animal->id.npc_id;
            mLd_CopyLandName(priv->animal_memory.land_name, func_800950D8_jp()->name);
            func_800AA2F8_jp(animal->id.npc_id);
        }
    }
}

s32 func_800AC804_jp(s32 block_x, s32 block_z, u8 ut_x, u8 ut_z) {
    s32 res = FALSE;

    if ((block_x >= 0) && (block_x < 5) && (block_z >= 0) && (block_z < 6) && (ut_x < 0x10) && (ut_z < 0x10)) {
        u16 item = common_data.save.fg[block_z][block_x].items[ut_z][ut_x];

        if ((item >= 0x5810) && (item < 0x5825)) {
            res = TRUE;
        }
    }
    return res;
}

void mNpc_SetReturnAnimal(Animal_c* animal) {
    Anmhome_c* home_info;
    Animal_c* found_animal = NULL;
    u8* now_max = &common_data.save.now_npc_max;
    Animal_c* common_animal;
    s32 found_animal_idx;

    if (mLd_PlayerManKindCheck() || mNpc_CheckFreeAnimalInfo(animal)) {
        return;
    }

    if (animal->unk_526 == 0) {
        common_animal = common_data.save.animals;
        found_animal_idx = mNpc_SearchAnimalinfo(common_animal, animal->id.npc_id, ANIMAL_NUM_MAX);
        if (found_animal_idx != -1) {
            found_animal = &common_animal[found_animal_idx];
            func_800AADE8_jp(&found_animal->home_info);
            (*now_max)--;
            if (found_animal_idx == common_data.save.remove_animal_idx) {
                common_data.save.remove_animal_idx = 0xFF;
            }
        } else if ((*now_max) >= ANIMAL_NUM_MAX) {
            found_animal_idx = func_800ABF40_jp();
            found_animal = &common_animal[found_animal_idx];
            func_800AC1EC_jp(&B_80142F70_jp, found_animal);
            func_800AADE8_jp(&found_animal->home_info);
            (*now_max)--;
            if (found_animal_idx == common_data.save.remove_animal_idx) {
                common_data.save.remove_animal_idx = 0xFF;
            }
        } else {
            found_animal_idx = mNpc_GetFreeAnimalInfo(common_animal, ANIMAL_NUM_MAX);
            if (found_animal_idx != -1) {
                found_animal = &common_animal[found_animal_idx];
            }
        }

        if (found_animal != NULL) {
            home_info = &found_animal->home_info;
            mNpc_ClearAnimalInfo(found_animal);
            mNpc_CopyAnimalInfo(found_animal, animal);
            if (func_800AC804_jp(found_animal->home_info.block_x - 1, found_animal->home_info.block_z - 1,
                                 found_animal->home_info.ut_x, found_animal->home_info.ut_z - 1) == TRUE) {
                func_800AAC88_jp(found_animal->id.npc_id, home_info->block_x - 1, home_info->block_z - 1,
                                 home_info->ut_x, home_info->ut_z - 1);
            } else {
                home_info->block_x = 0xFF;
                home_info->block_z = 0xFF;
                home_info->ut_x = 0xFF;
                home_info->ut_z = 0xFF;
            }
            (*now_max)++;
            if ((*now_max) > ANIMAL_NUM_MAX) {
                (*now_max) = ANIMAL_NUM_MAX;
            }
        }
    } else {
        mNpc_CopyAnimalPersonalID(&common_data.save.last_removed_animal_id, &animal->id);
    }
    mNpc_ClearAnimalInfo(animal);
}

void func_800ACB24_jp(FieldInfo_Unk_Struct* arg0, u8 arg1, u8 arg2) {
    func_800AB498_jp(arg0, arg1, arg2);
}

void func_800ACB54_jp(Animal_c* animal, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (animal != NULL) {
            if (ACTOR_FGNAME_GET_F000(animal->id.npc_id) == FGNAME_F000_E) {
                animal->id.name_id = animal->id.npc_id & 0xFF;
            }
        }
        animal++;
    }
}

void func_800ACC38_jp(u8* name, u8 npc_id) {
    u8 sp28[PLAYER_NAME_LEN];
    s32 id = npc_id;

    if (id < 0xFF) {
        func_80026E10_jp(sp28, (RomOffset)((Struct_D_E04000*)SEGMENT_ROM_START(segment_00E04000))->unk_08[id], 8,
                         "../m_npc.c", 0x1916);
        mem_copy(name, sp28, PLAYER_NAME_LEN);
    }
}

void func_800ACCAC_jp(u8* name, u16 npc_id) {
    u8* var_a2 = D_8010B810_jp;
    u8 sp24[PLAYER_NAME_LEN];

    if (name != NULL) {
        u8 id = npc_id & 0xFF;

        if ((ACTOR_FGNAME_GET_F000(npc_id) == FGNAME_F000_E) && (id < 0xFF)) {
            func_800ACC38_jp(sp24, id);
            var_a2 = sp24;
        }
    }
    mPr_CopyPlayerName(name, var_a2);
}

void mNpc_GetNpcWorldNameAnm(u8* name, AnmPersonalID_c* anm_id) {
    u8* var_a2 = D_8010B810_jp;
    u8 sp1C[PLAYER_NAME_LEN];

    if (anm_id != NULL) {
        if (ACTOR_FGNAME_GET_F000(anm_id->npc_id) == FGNAME_F000_E) {
            func_800ACCAC_jp(sp1C, anm_id->npc_id);
            var_a2 = sp1C;
        }
    }
    mPr_CopyPlayerName(name, var_a2);
}

void func_800ACD74_jp(u8* arg0, u16 name) {
    s32 i;
    Struct_D_8010B510_jp* var_v0 = D_8010B510_jp;
    u8* var_a3 = D_8010B810_jp;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_v0->unk_00) {
            func_800C3F70_jp(B_80142F68_jp, PLAYER_NAME_LEN, var_v0->unk_04);
            var_a3 = B_80142F68_jp;
            break;
        }
        var_v0++;
    }

    mPr_CopyPlayerName(arg0, var_a3);
}

void func_800ACDF8_jp(u8* arg0, Npc* npc) {
    u8* var_a3 = D_8010B810_jp;
    u8 sp1C[PLAYER_NAME_LEN];

    if ((arg0 != NULL) && (npc != NULL)) {
        if (npc->actor.part == ACTOR_PART_NPC) {
            if (npc->animal != NULL) {
                mNpc_GetNpcWorldNameAnm(sp1C, &npc->animal->id);
            } else {
                func_800ACD74_jp(sp1C, npc->actor.fgName);
            }
        } else {
            func_800ACD74_jp(sp1C, npc->actor.fgName);
        }
        var_a3 = sp1C;
    }
    mPr_CopyPlayerName(arg0, var_a3);
}

void func_800ACE90_jp(u8* arg0) {
    Animal_c* animal = common_data.save.animals;
    u16 var_s3 = 0;
    s32 var_s2 = 0;
    s32 rand;
    s32 i;

    if (arg0 != NULL) {

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                var_s2++;
                var_s3 |= (1 << i);
            }
            animal++;
        }

        if (var_s2 > 0) {
            animal = common_data.save.animals;
            rand = RANDOM(var_s2);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if (((var_s3 >> i) & 1) == 1) {
                    if (rand == 0) {
                        mNpc_GetNpcWorldNameAnm(arg0, &animal->id);
                        break;
                    } else {
                        rand--;
                    }
                }
                animal++;
            }
        }
    }
}

void func_800ACF84_jp(u8* arg0, Vec3f arg1) {
    UNUSED s32 pad;
    Animal_c* animal = common_data.save.animals;
    s32 block_x;
    s32 block_z;
    s32 ut_x;
    s32 ut_z;
    Anmhome_c* home_info;
    s32 i;

    if (func_80088780_jp(&block_x, &block_z, &ut_x, &ut_z, arg1) == 1) {
        ut_x++;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                home_info = &animal->home_info;
                if ((block_x == home_info->block_x) && (block_z == home_info->block_z) && (ut_x == home_info->ut_x) &&
                    (ut_z == home_info->ut_z)) {
                    mNpc_GetNpcWorldNameAnm(arg0, &animal->id);
                    break;
                }
            }
            animal++;
        }
    }
}

s32 func_800AD084_jp(Actor* actor) {
    u8 looks = 2;

    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Npc* npc = (Npc*)actor;

        if (npc->animal != NULL) {
            looks = npc->animal->id.looks;
        }
    }
    return looks;
}

s32 func_800AD0B8_jp(u16 name) {
    Struct_D_8010B510_jp* var_v0 = D_8010B510_jp;
    u16 var_v1 = 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_v0->unk_00) {
            var_v1 = var_v0->unk_02;
            break;
        }
        var_v0++;
    }

    return var_v1;
}

s32 func_800AD104_jp(s32 arg0) {
    s32 var_v1 = 2;

    if ((arg0 == 0) || (arg0 == 1) || (arg0 == 5)) {
        var_v1 = 1;
    } else if ((arg0 == 2) || (arg0 == 3) || (arg0 == 4)) {
        var_v1 = 0;
    }
    return var_v1;
}

s32 func_800AD154_jp(AnmPersonalID_c* anm_id) {
    s32 var_v1 = 2;

    if (anm_id != NULL) {
        var_v1 = func_800AD104_jp(anm_id->looks);
    }
    return var_v1;
}

s32 func_800AD188_jp(Actor* actor) {
    s32 var_v1;

    if ((actor != NULL) && (actor->part == ACTOR_PART_NPC)) {
        Npc* npc = (Npc*)actor;

        var_v1 = func_800AD154_jp(&npc->animal->id);
    } else {
        var_v1 = func_800AD0B8_jp(actor->fgName);
    }
    return var_v1;
}

s32 func_800AD1E0_jp(u16 name) {
    Struct_D_8010B510_jp* var_a1 = D_8010B510_jp;
    s32 var_v1 = 2;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010B510_jp); i++) {
        if (name == var_a1->unk_00) {
            var_v1 = var_a1->unk_08;
            break;
        }
        var_a1++;
    }

    return var_v1;
}

s32 func_800AD22C_jp(Actor* actor) {
    s32 var_v1 = 2;
    u8 var_v0;

    if (actor != NULL) {
        if (actor->part == ACTOR_PART_NPC) {
            Npc* npc = (Npc*)actor;

            if (npc->animal != NULL) {
                var_v0 = npc->animal->id.looks;
                if (var_v0 >= 6) {
                    var_v0 = 2;
                }
                var_v1 = D_8010B91C_jp[var_v0];
            } else {
                var_v1 = func_800AD1E0_jp(npc->actor.fgName);
            }
        } else {
            var_v1 = func_800AD1E0_jp(actor->fgName);
        }
    }
    return var_v1;
}

void func_800AD2B8_jp(UNUSED UNK_TYPE arg0) {
}

void mNpc_InitNpcAllInfo(s32 malloc_flag) {
    common_data.save.now_npc_max = 6;
    common_data.save.remove_animal_idx = 0xFF;
    mNpc_ClearAnimalPersonalID(&common_data.save.last_removed_animal_id);
    mNpc_ClearAnyAnimalInfo(common_data.save.animals, ANIMAL_NUM_MAX);
    func_800AA51C_jp(common_data.save.animals, 6, malloc_flag);
    func_800ACB54_jp(common_data.save.animals, ANIMAL_NUM_MAX);
}

s32 func_800AD338_jp(void) {
    s32 sp24 = func_80084DE0_jp();
    UNUSED s32 pad;
    s32 res = FALSE;

    if ((sp24 >= 0) && (sp24 < 7)) {
        if (RANDOM(100) < D_8010B934_jp[sp24]) {
            res = TRUE;
        }
    }
    return res;
}

s32 func_800AD3BC_jp(void) {
    UNUSED s32 pad[3];
    s32 res = FALSE;
    u32 var_v0;

    if (common_data.save.now_npc_max < ANIMAL_NUM_MAX) {
        if (func_800D51E0_jp(&mTM_rtcTime_clear_code, &common_data.save.unk_0F7FC, 0x7F) == TRUE) {
            lbRTC_TimeCopy(&common_data.save.unk_0F7FC, &common_data.time.rtc_time);
        } else if (func_800AD338_jp() == TRUE) {
            if (func_800D52C0_jp(&common_data.save.unk_0F7FC, &common_data.time.rtc_time) == TRUE) {
                var_v0 = func_800D5480_jp(&common_data.time.rtc_time, &common_data.save.unk_0F7FC);
            } else {
                var_v0 = func_800D5480_jp(&common_data.save.unk_0F7FC, &common_data.time.rtc_time);
            }

            if ((var_v0 >= 0x5A0) && (mLd_PlayerManKindCheck() == FALSE) &&
                (func_800AB7D0_jp(common_data.now_private) == TRUE)) {
                res = TRUE;
            }
        }
    }
    return res;
}

u8 func_800AD4B8_jp(u8* arg0, s32* arg1) {
    s32 temp_v0;
    s32 var_s3 = 0xF;
    u8 var_s5 = 6;
    u8 i;

    *arg0 = 0;
    *arg1 = 0;

    for (i = 0; i < 6; i++) {
        if (func_800AA3A4_jp(i) > 0) {
            temp_v0 = func_800A8148_jp(i);
            if (temp_v0 < var_s3) {
                *arg0 = 0;
                *arg0 |= (1 << i);
                var_s3 = temp_v0;
                var_s5 = i;
                *arg1 = 1;
            } else if (var_s3 == temp_v0) {
                *arg0 |= 1 << i;
                (*arg1)++;
            }
        }
    }

    if ((*arg0 == 0) && (*arg1 == 0)) {
        func_800AA438_jp(common_data.save.unk_0F86C, common_data.save.animals);

        for (i = 0; i < 6; i++) {
            *arg0 |= 1 << i;
            (*arg1)++;
        }
    }

    if (*arg1 >= 2) {
        var_s5 = 6;
    }
    return var_s5;
}

s32 func_800AD614_jp(void) {
    Animal_c* animal = common_data.save.animals;
    s32 i;
    s32 var_s2 = 0;
    s32 var_s3 = 0;
    s32 res;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            switch (func_800AD154_jp(&animal->id)) {
                case 0:
                    var_s2++;
                    break;
                case 1:
                    var_s3++;
                    break;
            }
        }
        animal++;
    }

    if (var_s3 < var_s2) {
        res = FALSE;
    } else {
        res = TRUE;
    }
    return res;
}

s32 func_800AD6D4_jp(u8 arg0) {
    UNUSED s32 pad[3];
    s32 sp40;
    u8* var_s2 = D_8010AF58_jp;
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    s32 var_s1;
    s32 var_v0;

    sp40 = -1;
    var_s1 = 0;

    if (arg0 < 6) {
        bzero(B_80142E58_jp, sizeof(B_80142E58_jp));

        for (i = 0; i < ARRAY_COUNT(B_80142E58_jp); i++) {
            for (j = 0; j < 8; j++) {
                if ((arg0 == *var_s2) &&
                    (mNpc_SearchAnimalinfo(common_data.save.animals, ((i * 8) + j) | 0xE000, 0xF) == -1) &&
                    (func_800AA35C_jp(var_s1) == FALSE)) {
                    var_s4++;
                    B_80142E58_jp[i] |= 1 << j;
                }
                var_s1++;
                var_s2++;
                if (var_s1 >= 0xD8) {
                    break;
                }
            }

            if (var_s1 >= 0xD8) {
                break;
            }
        }
    }

    if (var_s4 > 0) {
        var_s1 = 0;
        var_v0 = RANDOM(var_s4);

        for (i = 0; i < ARRAY_COUNT(B_80142E58_jp); i++) {
            if (var_s1 >= 0xD8) {
                break;
            }

            for (j = 0; j < 8; j++) {
                if (var_s1 >= 0xD8) {
                    break;
                }
                if (((B_80142E58_jp[i] >> j) & 1) == 1) {
                    if (var_v0 <= 0) {
                        sp40 = var_s1;
                        break;
                    } else {
                        var_v0--;
                    }
                }
                var_s1++;
            }

            if (sp40 != -1) {
                break;
            }
        }
    }
    return sp40;
}

void func_800AD8C4_jp(Animal_c* animal, s32 arg1) {
    if ((arg1 >= 0) && (arg1 < 0xD8)) {
        Struct_D_E03000* ptr = (Struct_D_E03000*)SEGMENT_ROM_START(segment_00E03000);

        func_80026E10_jp(&B_80142E78_jp, (RomOffset)&ptr[arg1], 8, "../m_npc.c", 0x1CB3);
        func_800AA218_jp(animal, arg1 | 0xE000, D_8010AF58_jp[arg1], &B_80142E78_jp);
    }
}

s32 func_800AD954_jp(u8 arg0) {
    Animal_c* animal = common_data.save.animals;
    UNUSED s32 pad;
    s32 free_animal_idx;
    s32 temp_v0_2;

    free_animal_idx = mNpc_UseFreeAnimalInfo(animal, ANIMAL_NUM_MAX);
    if (free_animal_idx != -1) {
        animal += free_animal_idx;
        temp_v0_2 = func_800AD6D4_jp(arg0);
        if (temp_v0_2 != -1) {
            func_800AD8C4_jp(animal, temp_v0_2);
            animal->unk_525 = 1;
        } else {
            free_animal_idx = -1;
        }
    }
    return free_animal_idx;
}

void func_800AD9FC_jp(void) {
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    u8 sp47;
    s32 sp40;
    s32 temp_v0_2;
    s32 var_v0;
    u8 i;

    if (func_800AD3BC_jp() == TRUE) {
        func_800AA49C_jp();
        lbRTC_TimeCopy(&common_data.save.unk_0F7FC, &common_data.time.rtc_time);
        sp4F = func_800AD4B8_jp(&sp4E, &sp48);
        if (sp4F == 6) {
            temp_v0_2 = func_800AD614_jp();
            if (temp_v0_2 != 2) {
                sp47 = sp4E;
                sp40 = sp48;

                for (i = 0; i < 6; i++) {
                    if ((((sp4E >> i) & 1) == 1) && (func_800AD104_jp(i) != temp_v0_2)) {
                        sp4E &= ~(1 << i);
                        sp48--;
                    }
                }

                if ((sp48 == 0) || (sp48 == sp40)) {
                    sp4E = sp47;
                    sp48 = sp40;
                }
            }

            var_v0 = RANDOM(sp48);
            for (i = 0; i < 6; i++) {
                if (((sp4E >> i) & 1) == 1) {
                    if (var_v0 <= 0) {
                        sp4F = i;
                        break;
                    } else {
                        var_v0--;
                    }
                }
            }
        }

        temp_v0_2 = func_800AD954_jp(sp4F);
        if ((temp_v0_2 >= 0) && (temp_v0_2 < ANIMAL_NUM_MAX)) {
            func_800ACB54_jp(&common_data.save.animals[temp_v0_2], 1);
            func_800A6940_jp(&common_data.save.now_npc_max);
        }
    }
}

s32 func_800ADBE4_jp(u16 arg0, s32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0)) {
        res = func_8007244C_jp(arg1);
    }
    return res;
}

s32 func_800ADC28_jp(u16 arg0, u32 arg1) {
    s32 res = FALSE;

    if (func_8008D7B0_jp(arg0) && ((arg1 < 3) || ((arg1 >= 4) && (arg1 < 7)) || (arg1 == 7))) {
        res = TRUE;
    }
    return res;
}

s32 func_800ADC8C_jp(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32* sp1C = func_80089538_jp(arg0, arg1);
    u16* temp_a2 = func_8008A33C_jp(arg0, arg1);
    s32 res = FALSE;

    if ((sp1C != NULL) && (temp_a2 != NULL)) {
        res = func_800ADBE4_jp(temp_a2[arg3 * 16 + arg2], sp1C[arg3 * 16 + arg2] & 0x3F);
    }
    return res;
}

#ifdef NON_MATCHING
s32 func_800ADD20_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32* sp5C;
    u16* sp58;
    s32 res;
    s32 var_a0;
    s32 var_a1;
    s32 var_s5;
    s32 var_s6;
    u32 temp_v0_3;
    s32 i;
    s32 j;
    u32* temp_v1;
    u16* temp_v2;

    sp5C = func_80089538_jp(arg2, arg3);
    sp58 = func_8008A33C_jp(arg2, arg3);
    var_s5 = 0x10;
    var_s6 = 0x10;
    res = FALSE;
    if ((arg4 < 0) || (arg4 >= 10)) {
        return 0;
    }

    if ((sp58 != NULL) && (sp5C != NULL)) {
        for (i = 0; i < 16 - arg4; i++) {
            temp_v2 = &sp58[i * 16];
            temp_v1 = &sp5C[i * 16];
            for (j = 0; j < 16 - arg4; j++) {
                if (func_800ADC28_jp(temp_v2[0], temp_v1[0] & 0x3F) == 1) {
                    temp_v0_3 = (temp_v1[0] * 2) >> 0x1B;
                    if ((temp_v0_3 == ((temp_v1[0] << 6) >> 0x1B)) && (temp_v0_3 == (*(u16*)temp_v1 & 0x1F)) &&
                        (temp_v0_3 == (*((u16*)temp_v1 + 1) >> 0xB))) {

                        if (temp_v0_3 == ((temp_v1[0] << 0x15) >> 0x1B)) {
                            var_a0 = 8 - j;
                            if (var_a0 < 0) {
                                var_a0 = -var_a0;
                            }

                            var_a1 = 8 - i;
                            if (var_a1 < 0) {
                                var_a1 = -var_a1;
                            }

                            if ((var_a0 < var_s5) && (var_a1 < var_s6)) {
                                *arg0 = j;
                                *arg1 = i;
                                var_s5 = var_a0;
                                var_s6 = var_a1;
                                res = TRUE;
                            }
                        }
                    }
                }
                temp_v2++;
                temp_v1++;
            }
        }
    }
    return res;
}
#else
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800ADD20_jp.s")
#endif

s32 func_800ADEFC_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_s4;
    u32* sp58;
    u16* sp54;
    s32 i;
    s32 j;
    s32 rand;
    s32 res;
    u16* var_s6 = B_80142EB8_jp;

    sp58 = func_80089538_jp(arg2, arg3);
    sp54 = func_8008A33C_jp(arg2, arg3);
    var_s4 = 0;
    res = 0;

    if ((arg4 < 0) || (arg4 >= 0xA)) {
        return FALSE;
    }

    bzero(B_80142EB8_jp, sizeof(B_80142EB8_jp));

    if ((sp54 != NULL) && (sp58 != 0)) {
        for (i = arg4; i < 16 - arg4; i++) {
            for (j = arg4; j < 16 - arg4; j++) {
                if (func_800ADBE4_jp(sp54[i * 16 + j], sp58[i * 16 + j] & 0x3F) == TRUE) {
                    *var_s6 |= 1 << j;
                    var_s4++;
                }
            }
            var_s6++;
        }

        var_s6 = B_80142EB8_jp;
    }

    if (var_s4 > 0) {
        rand = RANDOM(var_s4);

        for (i = arg4; i < 16 - arg4; i++) {
            for (j = arg4; j < 16 - arg4; j++) {
                if (((*var_s6 >> j) & 1) == 1) {
                    if (rand == 0) {
                        *arg0 = j;
                        *arg1 = i;
                        res = TRUE;
                        break;
                    } else {
                        rand--;
                    }
                }
            }
            if (res == TRUE) {
                break;
            }
            var_s6++;
        }
    }
    return res;
}

void func_800AE110_jp(s32* arg0, s32* arg1, s32 arg2, s32 arg3) {
    func_800ADEFC_jp(arg0, arg1, arg2, arg3, 1);
}

void mNpc_ClearTalkInfo(void) {
    s32 i;
    Struct_B_80142ED8_jp* ptr = B_80142ED8_jp;

    bzero(B_80142ED8_jp, sizeof(B_80142ED8_jp));

    for (i = 0; i < ANIMAL_NUM_MAX; i++, ptr++) {
        ptr->unk_03 = 1;
    }
}

void func_800AE1A0_jp(Struct_B_80142ED8_jp* arg0) {
    if (arg0->unk_00 > 0) {
        arg0->unk_00--;
    }
}

#ifdef NON_MATCHING
void func_800AE1B8_jp(u16* arg0, u16* arg1, s32 arg2) {
    *arg0 = D_8010B950_jp[arg2].unk_00;
    *arg1 = D_8010B950_jp[arg2].unk_00;
}
#else
void func_800AE1B8_jp(u16* arg0, u16* arg1, s32 arg2);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_npc/func_800AE1B8_jp.s")
#endif

s32 func_800AE1D8_jp(s32 arg0, s32 arg1) {
    s32 res = FALSE;

    if (arg0 != -1) {
        if ((B_80142ED8_jp[arg0].unk_02 < D_8010B950_jp[arg1].unk_03) && (B_80142ED8_jp[arg0].unk_00 > 0)) {
            B_80142ED8_jp[arg0].unk_02++;
            res = TRUE;
        }
    }
    return res;
}

s32 func_800AE23C_jp(s32 arg0, s32 arg1) {
    s32 res = FALSE;

    if (arg0 != -1 && B_80142ED8_jp[arg0].unk_02 >= D_8010B950_jp[arg1].unk_02) {
        res = TRUE;
    }
    return res;
}

s32 func_800AE284_jp(s32 arg0, s32 arg1) {
    s32 var_v1 = 2;

    if (arg0 != -1) {
        if (B_80142ED8_jp[arg0].unk_02 >= D_8010B950_jp[arg1].unk_02) {
            if (B_80142ED8_jp[arg0].unk_02 >= D_8010B950_jp[arg1].unk_03) {
                var_v1 = 1;
            } else {
                var_v1 = 0;
            }
        }
    }
    return var_v1;
}

s32 func_800AE2E8_jp(s32 arg0) {
    s32 res = FALSE;

    if ((arg0 != -1) && (B_80142ED8_jp[arg0].unk_03 == 1)) {
        res = TRUE;
    }
    return res;
}

void func_800AE320_jp(s32 arg0, s32 arg1) {
    UNUSED s32 pad;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX)) {
        if (B_80142ED8_jp[arg0].unk_03 == 1) {
            func_800AE1B8_jp(&B_80142ED8_jp[arg0].unk_04, &B_80142ED8_jp[arg0].unk_06, arg1);
        }
        B_80142ED8_jp[arg0].unk_03 = 0;
    }
}

void func_800AE37C_jp(Struct_B_80142ED8_jp* arg0) {
    if (arg0 != NULL) {
        if ((arg0->unk_04 > 0) && ((arg0->unk_06 - 1000) < arg0->unk_04)) {
            arg0->unk_04--;
        }
    }
}

void func_800AE3B4_jp(void) {
    Struct_B_80142ED8_jp* var_s0;
    s32 i;

    var_s0 = B_80142ED8_jp;
    if (func_8008C0FC_jp(1) == 1) {
        for (i = 0; i < ARRAY_COUNT(B_80142ED8_jp); i++) {
            var_s0->unk_06 = var_s0->unk_04;
            var_s0++;
        }
    }

    var_s0 = B_80142ED8_jp;
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        func_800AE1A0_jp(var_s0);
        func_800AE37C_jp(var_s0);
        if ((var_s0->unk_04 == 0) && (var_s0->unk_06 != 0)) {
            var_s0->unk_02 = 0;
            var_s0->unk_03 = 1;
            var_s0->unk_06 = 0;
        }
        var_s0++;
    }
}

void func_800AE4B4_jp(s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    Struct_B_80142ED8_jp* sp1C;

    if ((arg0 >= 0) && (arg0 < ANIMAL_NUM_MAX) && (arg1 >= 0) && (arg1 < 6)) {
        sp1C = &B_80142ED8_jp[arg0];
        sp1C->unk_00 = 1000;
        if (func_800AE1D8_jp(arg0, arg1) == TRUE) {
            if (func_800AE23C_jp(arg0, arg1) == TRUE) {
                func_800AE1B8_jp(&sp1C->unk_04, &sp1C->unk_06, arg1);
            }
        }
    }
}

s32 func_800AE558_jp(void) {
    u16 field_id = mFI_GetFieldId();
    u16 house_owner_name = common_data.house_owner_name;
    s32 floor_id = -1;

    if ((mNpc_GET_TYPE(field_id) == 0x4000) && (house_owner_name != 0) && (house_owner_name != 0xFFFF)) {
        s32 idx = mNpc_SearchAnimalinfo(common_data.save.animals, house_owner_name, ANIMAL_NUM_MAX);

        floor_id = common_data.npclist[idx].house_data.floor_id;
    }
    return floor_id;
}

void func_800AE5C8_jp(void) {
    if (common_data.unk_10A38 != 1) {
        Animal_c* animal = common_data.save.animals;
        mNpc_NpcList_c* npclist = common_data.npclist;
        s32 i;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
                npclist->flags.unk_23 = TRUE;
            }
            animal++;
            npclist++;
        }
    }
}

u8 func_800AE64C_jp(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->flags.unk_22;
    }
    return res;
}

u8 func_800AE670_jp(mNpc_NpcList_c* npclist) {
    u8 res = TRUE;

    if (npclist != NULL) {
        res = npclist->flags.unk_21;
    }
    return res;
}

void func_800AE694_jp(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->flags.unk_22 = TRUE;
    }
}

void func_800AE6B0_jp(mNpc_NpcList_c* npclist) {
    if (npclist != NULL) {
        npclist->flags.unk_21 = TRUE;
    }
}

void func_800AE6CC_jp(void) {
    Animal_c* animal = common_data.save.animals;
    mNpc_NpcList_c* npclist = common_data.npclist;
    s32 i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
            npclist->home_position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(npclist->home_position, 0.0f);
        }
        animal++;
        npclist++;
    }
}

void func_800AE76C_jp(gfxprint* print) {
    Animal_c* sp34 = NULL;
    Animal_c* sp30 = mNpc_GetInAnimalP();
    u8 sp2F = common_data.save.remove_animal_idx;

    gfxprint_color(print, 0xC8, 0x96, 0x32, 0xFF);
    gfxprint_locate8x8(print, 3, 0xA);
    if (sp2F < ANIMAL_NUM_MAX) {
        sp34 = &common_data.save.animals[sp2F];
    }

    if (sp34 != NULL) {
        if (sp30 != NULL) {
            gfxprint_printf(print, "%4x %3d %3d", sp2F, sp34->id.name_id, sp30->id.name_id);
        } else {
            gfxprint_printf(print, "%4x %3d ---", sp2F, sp34->id.name_id);
        }
    } else if (sp30 != NULL) {
        gfxprint_printf(print, "%4x --- %3d", sp2F, sp30->id.name_id);
    } else {
        gfxprint_printf(print, "%4x --- ---", sp2F);
    }
}

void func_800AE898_jp(AnmPersonalID_c* anm_id) {
    if (anm_id != NULL) {
        D_8010B968_jp = func_800A7D08_jp(anm_id);
    }
}

void mNpc_PrintFriendship_fdebug(gfxprint* gfxprint) {
    Anmmem_c* memory;
    Private_c* priv;
    s32 i;
    s32 var_s2 = 3;
    s32 var_s4 = 19;

    if ((D_8010B968_jp >= 0) && (D_8010B968_jp < ANIMAL_NUM_MAX)) {
        memory = common_data.save.animals[D_8010B968_jp].memories;
        if (memory != NULL) {
            gfxprint_color(gfxprint, 0xFA, 0x64, 0xAA, 0xFF);
            gfxprint_locate8x8(gfxprint, 3, 0x12);
            priv = common_data.now_private;
            if (priv != NULL) {
                gfxprint_printf(gfxprint, "%4x ", priv->player_ID.player_id);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }
            gfxprint_color(gfxprint, 0x32, 0x96, 0x32, 0xFF);

            for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
                if (i == 4) {
                    var_s4++;
                    var_s2 = 3;
                }
                gfxprint_locate8x8(gfxprint, var_s2, var_s4);
                if (func_800A6E0C_jp(&memory->memory_player_id) == FALSE) {
                    gfxprint_printf(gfxprint, "%4x %3d ", memory->memory_player_id.player_id, memory->info.friendship);
                } else {
                    gfxprint_printf(gfxprint, "**** *** ");
                }
                memory++;
                var_s2 += 9;
            }
        }
    }
}
