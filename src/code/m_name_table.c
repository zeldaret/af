#include "m_common_data.h"
#include "m_name_table.h"
#include "m_npc_base.h"
#include "sys_math.h"
#include "m_actor_dlftbls.h"

s16 move_obj_profile_table[] = {
    ACTOR_AIRPLANE,        ACTOR_BALL,         ACTOR_MY_ROOM,      ACTOR_MBG,
    ACTOR_BOX_MANAGER,     ACTOR_BOX_TRICK_01, ACTOR_ARRANGE_ROOM, ACTOR_ARRANGE_FURNITURE,
    ACTOR_EFFECT_CONTROL,  ACTOR_SHOP_DESIGN,  ACTOR_SHOP_MANEKIN, ACTOR_SHOP_INDOOR,
    ACTOR_SHOP_GOODS,      ACTOR_SNOWMAN,      ACTOR_SNOWMAN,      ACTOR_BROKER_DESIGN,
    ACTOR_MY_INDOOR,       ACTOR_TRAIN_WINDOW, ACTOR_UKI,          ACTOR_SHOP_UMBRELLA,
    ACTOR_KAMAKURA_INDOOR, ACTOR_HOUSE_CLOCK,
};

s16 actor_profile_table[] = {
    ACTOR_SAMPLE,
};

s16 props_profile_table[] = {
    ACTOR_MAIL_BOX, ACTOR_MAIL_BOX, ACTOR_MAIL_BOX, ACTOR_MAIL_BOX,   ACTOR_HANIWA,    ACTOR_HANIWA,   ACTOR_HANIWA,
    ACTOR_HANIWA,   ACTOR_PSNOWMAN, ACTOR_PSNOWMAN, ACTOR_PSNOWMAN,   ACTOR_PSNOWMAN,  ACTOR_PSNOWMAN, ACTOR_PSNOWMAN,
    ACTOR_PSNOWMAN, ACTOR_PSNOWMAN, ACTOR_PSNOWMAN, ACTOR_TRAIN_DOOR, ACTOR_NAMEPLATE,
};

u8 npc_looks_table[] = {
    NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,        NPC_LOOKS_GIRL,        NPC_LOOKS_KO_GIRL,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_GIRL,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_BOY,         NPC_LOOKS_BOY,         NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_BOY,         NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,         NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,        NPC_LOOKS_KO_GIRL,
    NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,         NPC_LOOKS_GIRL,
    NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_BOY,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,         NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,
    NPC_LOOKS_BOY,         NPC_LOOKS_BOY,         NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_BOY,
    NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,        NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,        NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,         NPC_LOOKS_KO_GIRL,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_GIRL,        NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,         NPC_LOOKS_BOY,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GIRL,        NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_BOY,         NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_GIRL,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_KO_GIRL,     NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_BOY,
    NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,        NPC_LOOKS_BOY,
    NPC_LOOKS_GIRL,        NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_KO_GIRL,     NPC_LOOKS_SPORT_MAN,   NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_KO_GIRL,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_GRIM_MAN,    NPC_LOOKS_BOY,         NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_BOY,         NPC_LOOKS_GIRL,        NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GIRL,        NPC_LOOKS_GIRL,        NPC_LOOKS_NANIWA_LADY,
    NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_GRIM_MAN,
    NPC_LOOKS_GIRL,        NPC_LOOKS_KO_GIRL,     NPC_LOOKS_GIRL,        NPC_LOOKS_NANIWA_LADY, NPC_LOOKS_SPORT_MAN,
    NPC_LOOKS_KO_GIRL,     NPC_LOOKS_KO_GIRL,     NPC_LOOKS_KO_GIRL,
};

u8 item1_0_tableNo[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
};

u8 item1_1_tableNo[] = {
    9,
    9,
    9,
    9,
};

u8 item1_2_tableNo[] = {
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
    19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
};

u8 item1_3_tableNo[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

u8 item1_4_tableNo[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

u8 item1_5_tableNo[] = {
    22, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 9,  21,
    21, 21, 20, 23, 22, 25, 24, 24, 24, 25, 25, 24, 26, 14, 11,
};

u8 item1_6_tableNo[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

u8 item1_7_tableNo[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

u8 item1_8_tableNo[] = {
    1, 5, 4, 3, 2, 6, 17,
};

u8 item1_9_tableNo[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
};

u8 item1_A_tableNo[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

u8 item1_B_tableNo[] = {
    21,
};

u8 item1_C_tableNo[] = {
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
    17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,
};

u8 item1_D_tableNo[] = {
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
    18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
};

u8 item1_E_tableNo[] = {
    17,
    17,
};

u8 item1_F_tableNo[] = {
    7,
    7,
    7,
    7,
};

s32 mNT_get_itemTableNo(u16 item) {
    static u8* item1_tableNo[] = {
        item1_0_tableNo, item1_1_tableNo, item1_2_tableNo, item1_3_tableNo, item1_4_tableNo, item1_5_tableNo,
        item1_6_tableNo, item1_7_tableNo, item1_8_tableNo, item1_9_tableNo, item1_A_tableNo, item1_B_tableNo,
        item1_C_tableNo, item1_D_tableNo, item1_E_tableNo, item1_F_tableNo,
    };
    s32 ret;

    s32 type = GET_NAME_ITEM_TYPE(item);
    s32 category;
    s32 idx;

    switch (type) {
        case 1:
            if ((item >= 0x1E3C) && (item < 0x1EA0)) {
                ret = 0x14;
            } else if ((item >= 0x15B0) && (item < 0x17AC)) {
                ret = 0x10;
            } else {
                ret = 0xA;
            }
            break;

        case 2:
            category = GET_NAME_ITEM_CATEGORY((u16)item);
            idx = GET_NAME_ITEM_INDEX((u16)item);

            ret = item1_tableNo[category][idx];
            break;

        default:
            ret = 0;
            break;
    }

    return ret;
}

u16 mNT_FishIdx2FishItemNo(s32 idx) {
    if (idx >= 0 && idx <= (0x1E + 1)) {
        return 0x2300 + idx;
    }

    return EMPTY_NO;
}

u16 bg_item_fg_sub(u16 item, s16 flag) {
    u16 stump = item;

    if (flag == 0) {
        if ((item == 0x804) || (item == 0x80C) || (item == 0x814) || (item == 0x81C) || (item == 0x824) ||
            (item == 0x82C) || (item == 0x831) || (item == 0x836) || (item == 0x83B) || (item == 0x853) ||
            (item == 0x809) || (item == 0x811) || (item == 0x819) || (item == 0x821) || (item == 0x829) ||
            (item == 0x80A) || (item == 0x812) || (item == 0x81A) || (item == 0x822) || (item == 0x82A) ||
            (item == 0x80B) || (item == 0x813) || (item == 0x81B) || (item == 0x823) || (item == 0x82B) ||
            (item == 0x5E) || (item == 0x5F) || (item == 0x60) || (item == 0x61) || (item == 0x69)) {
            stump = 4;
        } else if ((item == 0x803) || (item == 0x808) || (item == 0x810) || (item == 0x818) || (item == 0x820) ||
                   (item == 0x828) || (item == 0x830) || (item == 0x835) || (item == 0x83A) || (item == 0x830) ||
                   (item == 0x835) || (item == 0x83A) || (item == 0x852)) {
            stump = 3;
        } else if ((item == 0x802) || (item == 0x807) || (item == 0x80F) || (item == 0x817) || (item == 0x81F) ||
                   (item == 0x827) || (item == 0x82F) || (item == 0x834) || (item == 0x839) || (item == 0x82F) ||
                   (item == 0x834) || (item == 0x839) || (item == 0x851)) {
            stump = 2;
        } else if ((item == 0x801) || (item == 0x806) || (item == 0x80E) || (item == 0x816) || (item == 0x81E) ||
                   (item == 0x826) || (item == 0x82E) || (item == 0x833) || (item == 0x838) || (item == 0x82E) ||
                   (item == 0x833) || (item == 0x838) || (item == 0x850)) {
            stump = 1;
        }
    }

    return stump;
}

u16 bg_item_fg_sub_tree_grow(u16 item, s32 pastDays, s32 checkPlant) {
    static s16 grow_check[][2] = {
        { -1, 0 }, { -1, 1 }, { -1, 2 }, { -1, 3 }, { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 }, { -4, 3 }, { -1, 4 },
        { -1, 4 }, { -1, 4 }, { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 }, { -4, 3 }, { -1, 4 }, { -1, 4 }, { -1, 4 },
        { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 }, { -4, 3 }, { -1, 4 }, { -1, 4 }, { -1, 4 }, { 0, 4 },  { -1, 0 },
        { -1, 1 }, { -1, 2 }, { -4, 3 }, { -1, 4 }, { -1, 4 }, { -1, 4 }, { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 },
        { -4, 3 }, { -1, 4 }, { -1, 4 }, { -1, 4 }, { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 }, { -1, 3 }, { 0, 4 },
        { -1, 0 }, { -1, 1 }, { -1, 2 }, { -1, 3 }, { 0, 4 },  { -1, 0 }, { -1, 1 }, { -1, 2 }, { -1, 3 }, { 0, 4 },
        { -1, 0 }, { -1, 1 }, { -1, 2 }, { -1, 3 }, { 0, 4 },
    };

    s32 idx;
    s32 diff;

    if ((item >= 0x800 && item <= 0x83B) || (item >= 0x84F && item <= 0x853)) {
        if (item >= 0x84F) {
            idx = item - 0x0813;
        } else {
            idx = item - 0x0800;
        }

        for (; pastDays >= 0; item += diff) {
            diff = -grow_check[idx][0];

            if (grow_check[idx + diff][1] > checkPlant) {
                break;
            }
            idx += diff;
            pastDays--;
        }
    }

    return item;
}

u16 bg_item_fg_sub_dig2take_conv(u16 item) {
    u16 digItem;

    digItem = item;
    if ((item >= 0x2A) && (item <= 0x42)) {
        digItem = 0x2512;
    }

    if (item == 0x5C) {
        {
            if (common_data.privateInfo->destiny.type == 4) {
                digItem = 0x2102;
            } else {
                s32 selectedRand = RANDOM(35);
                if (selectedRand == 0) {
                    digItem = 0x2102;
                } else if ((selectedRand > 0) && (selectedRand < 4)) {
                    digItem = 0x2101;
                } else {
                    digItem = 0x2100;
                }
            }
        }
    }
    return digItem;
}

NameTableOffsetTable height_table[3] = {
    { 0, { 100, 0, 0, 0, 0, 0, 0 } },
    { 0, { 23, 4, 4, 4, 4, 4, 0 } },
    { 0, { 23, 7, 7, 7, 7, 7, 0 } },
};

NameTableOffsetTable* obj_hight_table_item0_nogrow(u16 item) {
    NameTableOffsetTable* table = &height_table[0];

    if ((item == 5) || (item == 6) || (item == 7) || (item == 0xB) || (item == 0x10)) {
        table = &height_table[1];
    } else if ((item == 0xC) || (item == 0xD) || (item == 0xE) || (item == 0xF)) {
        table = &height_table[2];
    }

    return table;
}
