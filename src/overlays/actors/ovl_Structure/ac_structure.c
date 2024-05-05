#include "prevent_bss_reordering.h"
#include "ac_structure.h"
#include "macros.h"
#include "m_actor_dlftbls.h"
#include "m_field_info.h"
#include "m_lib.h"
#include "m_malloc.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "segment_symbols.h"

#define THIS ((Structure*)thisx)

void aSTR_actor_ct(Actor* thisx, Game_Play* game_play);
void aSTR_actor_dt(Actor* thisx, Game_Play* game_play);
void aSTR_actor_move(Actor* thisx, Game_Play* game_play);

void aSTR_init_clip_area(Game_Play* game_play);
void aSTR_free_clip_area(void);

StructureActor aSTR_actor_cl[9];
s8 aSTR_overlay[9][8192];
s8 acStructureBssPadding1[8];
void* B_809FD530_jp[184];
s8 acStructureBssPadding2[8];
void* B_809FD818_jp[184];
s8 acStructureBssPadding3[8];
void* B_809FDB00_jp[364];
s8 acStructureBssPadding4[8];
void* B_809FE0B8_jp[184];
s8 acStructureBssPadding5[8];
void* B_809FE3A0_jp[184];

ActorProfile Structure_Profile = {
    /* */ ACTOR_STRUCTURE,
    /* */ ACTOR_PART_7,
    /* */ ACTOR_FLAG_10 | ACTOR_FLAG_20,
    /* */ 0x0000,
    /* */ GAMEPLAY_KEEP,
    /* */ sizeof(Structure),
    /* */ aSTR_actor_ct,
    /* */ aSTR_actor_dt,
    /* */ aSTR_actor_move,
    /* */ (void*)none_proc1,
    /* */ NULL,
};

void aSTR_actor_ct(Actor* thisx, UNUSED Game_Play* game_play) {
    Structure* this = THIS;

    aSTR_init_clip_area(game_play);
    this->unk_178 = common_data.doorData.fgName;
    this->unk_17A = common_data.doorData.exitType;
}

void aSTR_actor_dt(UNUSED Actor* thisx, UNUSED Game_Play* game_play) {
    aSTR_free_clip_area();
}

void func_809E7F34_jp(Game_Play* game_play) {
    UNUSED s32 pad;
    s32 num = game_play->objectExchangeBank.num;

    if (mSc_secure_exchange_keep_bank(&game_play->objectExchangeBank, 0, (0x2E00 * 8) + (0x20 * 9) + (0x800 * 8))) {
        common_data.clip.structureClip->unk_C0C = num;
    } else {
        common_data.clip.structureClip->unk_C0C = -1;
    }
}

extern u8 test[];           // 0x06000008
extern u8 test2[];          // 0x060000C0
extern void* fake_symbol_1; // 0x06000008
extern void* fake_symbol_2; // 0x06000178
extern void* fake_symbol_3; // 0x060000C0
extern void* fake_symbol_4; // 0x06000230
extern void* fake_symbol_5; // 0x06000008
extern void* fake_symbol_6; // 0x06000174

static void* D_809E9864_jp[] = { &fake_symbol_1, &fake_symbol_2 };
static void* D_809E986C_jp[] = { &fake_symbol_3, &fake_symbol_4 };
static void* D_809E9874_jp[] = { &fake_symbol_5, &fake_symbol_6 };

// TODO: use "real" symbols
void func_809E7F94_jp(void) {
    s32 index = (common_data.time.season == WINTER);

    DmaMgr_RequestSyncDebug(&B_809FD530_jp,
                            ((uintptr_t)D_809E9864_jp[index] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            ARRAY_COUNT(B_809FD530_jp), "../ac_structure_clip.c_inc", 129);
    DmaMgr_RequestSyncDebug(&B_809FD818_jp,
                            ((uintptr_t)D_809E986C_jp[index] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            ARRAY_COUNT(B_809FD818_jp), "../ac_structure_clip.c_inc", 132);
    DmaMgr_RequestSyncDebug(&B_809FDB00_jp,
                            ((uintptr_t)D_809E9874_jp[index] + SEGMENT_ROM_START(object_00D5D000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00D5D000),
                            ARRAY_COUNT(B_809FDB00_jp), "../ac_structure_clip.c_inc", 135);
    DmaMgr_RequestSyncDebug(&B_809FE0B8_jp,
                            ((uintptr_t)test + (uintptr_t)SEGMENT_ROM_START(object_00E00000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
                            ARRAY_COUNT(B_809FE0B8_jp), "../ac_structure_clip.c_inc", 138);
    DmaMgr_RequestSyncDebug(&B_809FE3A0_jp,
                            ((uintptr_t)test2 + (uintptr_t)SEGMENT_ROM_START(object_00E00000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
                            ARRAY_COUNT(B_809FE3A0_jp), "../ac_structure_clip.c_inc", 141);
}

void func_809E8118_jp(ObjectExchangeBank* arg0) {
    StructureClip_unkstruct* ptr = &common_data.clip.structureClip->unk_B0[0];
    u8* var_s1 = arg0->status[common_data.clip.structureClip->unk_C0C].segment;
    s16 temp_t0;
    s32 temp_s3;
    RomOffset vrom;
    size_t size;
    s32 i;

    for (i = 0; i < 8; i++, var_s1 += 0x2E00, ptr++) {
        if (ptr->unk_03 == 1) {
            temp_t0 = ptr->type;
            temp_s3 = (uintptr_t)B_809FD530_jp[temp_t0] - (uintptr_t)SEGMENT_VRAM_START(object_00DF4000) + 8;
            vrom = temp_s3 + SEGMENT_ROM_START(object_00D5E000);
            size = ALIGN16(((uintptr_t)B_809FD818_jp[temp_t0] - (uintptr_t)B_809FD530_jp[temp_t0]) - 8);
            DmaMgr_RequestSyncDebug(var_s1, vrom, size, "../ac_structure_clip.c_inc", 198);
            ptr->segment = (s32)var_s1 - temp_s3;
            ptr->unk_03 = 0;
        }
    }
}

void func_809E823C_jp(ObjectExchangeBank* arg0) {
    StructureClip_unkstruct* ptr = &common_data.clip.structureClip->unk_454[0];
    u8* var_s1 = arg0->status[common_data.clip.structureClip->unk_C0C].segment + (0x2E00 * 8);
    void* test;
    s32 temp;
    s32 i;

    for (i = 0; i < 9; i++, var_s1 += 0x20, ptr++) {
        if (ptr->unk_03 == 1) {
            test = B_809FDB00_jp[ptr->type];
            temp = (uintptr_t)test - (uintptr_t)SEGMENT_VRAM_START(object_00D5D000);
            DmaMgr_RequestSyncDebug(var_s1, temp + (uintptr_t)SEGMENT_ROM_START(object_00D5B000), 32,
                                    "../ac_structure_clip.c_inc", 256);
            ptr->segment = (s32)var_s1;
            ptr->unk_03 = 0;
        }
    }
}

void func_809E8350_jp(ObjectExchangeBank* arg0) {
    StructureClip_unkstruct* ptr = &common_data.clip.structureClip->unk_86C[0];
    u8* var_s1 = arg0->status[common_data.clip.structureClip->unk_C0C].segment + (0x2E00 * 8) + (0x20 * 9);
    s16 temp_t0;
    s32 temp_s3;
    RomOffset vrom;
    size_t size;
    s32 i;

    for (i = 0; i < 8; i++, var_s1 += 0x800, ptr++) {
        if (ptr->unk_03 == 1) {
            temp_t0 = ptr->type;
            temp_s3 = (uintptr_t)B_809FE0B8_jp[temp_t0] - (uintptr_t)SEGMENT_VRAM_START(object_00E00000) + 8;
            vrom = temp_s3 + (uintptr_t)SEGMENT_ROM_START(object_00DF5000);
            size = ALIGN16(((uintptr_t)B_809FE3A0_jp[temp_t0] - (uintptr_t)B_809FE0B8_jp[temp_t0]) - 8);
            DmaMgr_RequestSyncDebug(var_s1, vrom, size, "../ac_structure_clip.c_inc", 321);
            ptr->segment = (s32)var_s1 - temp_s3;
            ptr->unk_03 = 0;
        }
    }
}

void func_809E8480_jp(ObjectExchangeBank* arg0) {
    if ((common_data.clip.structureClip->unk_C0C != -1) && (common_data.clip.structureClip->unk_C10 != 0)) {
        func_809E8118_jp(arg0);
        func_809E823C_jp(arg0);
        func_809E8350_jp(arg0);
        common_data.clip.structureClip->unk_C10 = 0;
    }
}

void func_809E84E4_jp(ObjectExchangeBank* arg0) {
    StructureClip_unkstruct* ptr;
    s32 i;

    ptr = common_data.clip.structureClip->unk_B0;
    for (i = 0; i < 8; i++, ptr++) {
        if ((ptr->type == -1) || (ptr->unk_02 == 0)) {
            ptr->type = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->unk_454;
    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->type == -1) || (ptr->unk_02 == 0)) {
            ptr->type = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->unk_86C;
    for (i = 0; i < 8; i++, ptr++) {
        if ((ptr->type == -1) || (ptr->unk_02 == 0)) {
            ptr->type = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    common_data.clip.structureClip->unk_C10 = 1;
    func_809E8480_jp(arg0);
}

s32 func_809E85FC_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 posX, f32 posZ) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;
    s32 ret = false;

    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->fgName == arg1) && (ptr->posX == posX) && (ptr->posZ == posZ)) {
            ret = true;
            break;
        }
    }

    return ret;
}

s32 func_809E8674_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 posX, f32 posZ) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;

    for (i = 0; i < 9; i++, ptr++) {
        if (ptr->fgName == 0) {
            ptr->fgName = arg1;
            ptr->posX = posX;
            ptr->posZ = posZ;
            ptr->unk_08 = 0;
            return true;
        }
    }

    return false;
}

void func_809E8768_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 posX, f32 posZ) {
    if ((func_809E85FC_jp(arg0, arg1, posX, posZ) == false) && (func_809E8674_jp(arg0, arg1, posX, posZ) == true)) {
        arg0->unk_02++;
    }
}

void func_809E87D4_jp(StructureClip_unkstruct* arg0, s16 arg1, u16 arg2, f32 posX, f32 posZ) {
    if (func_809E8674_jp(arg0, arg2, posX, posZ) == true) {
        arg0->type = arg1;
        arg0->unk_02 = 1;
        arg0->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

void func_809E8838_jp(StructureClip_unkstruct* arg0, s16 arg1, u16 arg2, f32 posX, f32 posZ) {
    if (func_809E8674_jp(arg0, arg2, posX, posZ) == true) {
        arg0->type = arg1;
        arg0->unk_02 = 1;
        arg0->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

void func_809E889C_jp(StructureClip_unkstruct* arg0, s32 arg1, s16 arg2, u16 arg3, f32 posX, f32 posZ) {
    StructureClip_unkstruct* ptr;
    s32 i;

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (arg2 == ptr->type) {
            func_809E8768_jp(ptr, arg3, posX, posZ);
            return;
        }
    }

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (ptr->type == -1) {
            func_809E87D4_jp(ptr, arg2, arg3, posX, posZ);
            return;
        }
    }

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (ptr->unk_02 == 0) {
            func_809E8838_jp(ptr, arg2, arg3, posX, posZ);
            return;
        }
    }
}

s32 func_809E89AC_jp(StructureClip_unkstruct* arg0, Actor* actor) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;

    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->fgName == actor->fgName) && (ptr->posX == actor->home.pos.x) && (ptr->posZ == actor->home.pos.z)) {
            ptr->posX = 0.0f;
            ptr->posZ = 0.0f;
            ptr->fgName = 0;
            ptr->unk_08 = 0;
            arg0->unk_02--;
            return true;
        }
    }

    return false;
}

s32 func_809E8BDC_jp(StructureClip_unkstruct* arg0, Actor* actor) {
    s32 ret = false;

    if (arg0->unk_02 > 0) {
        ret = func_809E89AC_jp(arg0, actor);
    }

    return ret;
}

void func_809E8C14_jp(StructureClip_unkstruct* arg0, s32 arg1, s16 arg2, Actor* arg3) {
    StructureClip_unkstruct* ptr = arg0;
    s32 i;

    for (i = 0; i < arg1; i++, ptr++) {
        if (ptr->type == arg2) {
            if (func_809E8BDC_jp(ptr, arg3) == true) {
                return;
            } else {
                return;
            }
        }
    }
}

s32 func_809E8C80_jp(StructureClip_unkstruct* arg0, s32 size, s16 type) {
    s32 i;
    s32 ret = -1;

    for (i = 0; i < size; i++, arg0++) {
        if ((arg0->type == type) && (arg0->unk_03 != 1)) {
            ret = i;
            break;
        }
    }

    return ret;
}

s32 func_809E8CD4_jp(s16 structureType) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_B0, 8, structureType);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_B0[index];

        return temp->segment;
    }

    return 0;
}

u16* aSTR_get_pal_segment(s16 paletteType) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_454, 9, paletteType);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_454[index];

        return (u16*)temp->segment;
    }

    return NULL;
}

s32 func_809E8DB4_jp(s16 arg0) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_86C, 8, arg0);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_86C[index];

        return temp->segment;
    }

    return 0;
}

// Stolen from GC
typedef struct structure_setup_info_s {
    s16 profile;
    s16 structure_type; // aSTR_TYPE_*
    s16 pal_no;         // aSTR_PAL_*
    s16 pad;
} aSTR_setup_info;

Actor* aSTR_setupActor_proc(Game_Play* game_play, u16 structureName, f32 posX, f32 posZ, s16 params) {
    static aSTR_setup_info setupInfo_table[] = {
        { ACTOR_MY_HOUSE, STRUCTURE_TYPE_MY_HOUSE_1, STRUCTURE_PALETTE_MY_HOUSE_1, 0 },
        { ACTOR_MY_HOUSE, STRUCTURE_TYPE_MY_HOUSE_1, STRUCTURE_PALETTE_MY_HOUSE_2, 0 },
        { ACTOR_MY_HOUSE, STRUCTURE_TYPE_MY_HOUSE_1, STRUCTURE_PALETTE_MY_HOUSE_3, 0 },
        { ACTOR_MY_HOUSE, STRUCTURE_TYPE_MY_HOUSE_1, STRUCTURE_PALETTE_MY_HOUSE_4, 0 },
        { ACTOR_SHOP, STRUCTURE_TYPE_SHOP, STRUCTURE_PALETTE_SHOP, 0 },
        { ACTOR_CONVENI, STRUCTURE_TYPE_CONVENI, STRUCTURE_PALETTE_CONVENI, 0 },
        { ACTOR_SUPER, STRUCTURE_TYPE_SUPER, STRUCTURE_PALETTE_SUPER, 0 },
        { ACTOR_DEPART, STRUCTURE_TYPE_DEPART, STRUCTURE_PALETTE_DEPART, 0 },
        { ACTOR_POST_OFFICE, STRUCTURE_TYPE_POST_OFFICE, STRUCTURE_PALETTE_POST_OFFICE, 0 },
        { ACTOR_STATION, STRUCTURE_TYPE_STATION_1, STRUCTURE_PALETTE_STATION_1_1, 0 },
        { ACTOR_TRAIN0, STRUCTURE_TYPE_TRAIN0, STRUCTURE_PALETTE_TRAIN0, 0 },
        { ACTOR_TRAIN1, STRUCTURE_TYPE_TRAIN1, STRUCTURE_PALETTE_TRAIN1, 0 },
        { ACTOR_POLICE_BOX, STRUCTURE_TYPE_POLICE_BOX, STRUCTURE_PALETTE_POLICE_BOX, 0 },
        { ACTOR_FALL_S, STRUCTURE_TYPE_FALL_S, STRUCTURE_PALETTE_FALL_S, 0 },
        { ACTOR_FALL_SESW, STRUCTURE_TYPE_FALL_SESW, STRUCTURE_PALETTE_FALL_SESW, 0 },
        { ACTOR_FALL_SESW, STRUCTURE_TYPE_FALL_SESW, STRUCTURE_PALETTE_FALL_SESW, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_RESERVE, STRUCTURE_TYPE_RESERVE, STRUCTURE_PALETTE_RESERVE, 0 },
        { ACTOR_SHRINE, STRUCTURE_TYPE_SHRINE, STRUCTURE_PALETTE_SHRINE, 0 },
        { ACTOR_BR_SHOP, STRUCTURE_TYPE_BR_SHOP, STRUCTURE_PALETTE_BR_SHOP, 0 },
        { ACTOR_BUGGY, STRUCTURE_TYPE_BUGGY, STRUCTURE_PALETTE_BUGGY, 0 },
        { ACTOR_S_CAR, STRUCTURE_TYPE_S_CAR, STRUCTURE_PALETTE_S_CAR, 0 },
        { ACTOR_KAMAKURA, STRUCTURE_TYPE_KAMAKURA, STRUCTURE_PALETTE_KAMAKURA, 0 },
        { ACTOR_GOZA, STRUCTURE_TYPE_GOZA, STRUCTURE_PALETTE_GOZA, 0 },
        { ACTOR_RADIO, STRUCTURE_TYPE_RADIO, STRUCTURE_PALETTE_RADIO, 0 },
        { ACTOR_YATAI, STRUCTURE_TYPE_YATAI, STRUCTURE_PALETTE_YATAI, 0 },
        { ACTOR_YATAI, STRUCTURE_TYPE_YATAI, STRUCTURE_PALETTE_YATAI, 0 },
        { ACTOR_TUKIMI, STRUCTURE_TYPE_TUKIMI_1, STRUCTURE_PALETTE_TUKIMI_1, 0 },
        { ACTOR_TUKIMI, STRUCTURE_TYPE_TUKIMI_2, STRUCTURE_PALETTE_TUKIMI_2, 0 },
        { ACTOR_MIKUJI, STRUCTURE_TYPE_MIKUJI, STRUCTURE_PALETTE_MIKUJI, 0 },
        { ACTOR_COUNT, STRUCTURE_TYPE_COUNT, STRUCTURE_PALETTE_COUNT, 0 },
        { ACTOR_COUNT02, STRUCTURE_TYPE_COUNT02, STRUCTURE_PALETTE_COUNT02, 0 },
        { ACTOR_TAMA, STRUCTURE_TYPE_SPORTSFAIR_A, STRUCTURE_PALETTE_SPORTSFAIR_A, 0 },
        { ACTOR_TAMA, STRUCTURE_TYPE_SPORTSFAIR_B, STRUCTURE_PALETTE_SPORTSFAIR_B, 0 },
        { ACTOR_KAGO, STRUCTURE_TYPE_SPORTSFAIR_A, STRUCTURE_PALETTE_SPORTSFAIR_A, 0 },
        { ACTOR_KAGO, STRUCTURE_TYPE_SPORTSFAIR_B, STRUCTURE_PALETTE_SPORTSFAIR_B, 0 },
        { ACTOR_TURI, STRUCTURE_TYPE_TURI_1, STRUCTURE_PALETTE_TURI_1, 0 },
        { ACTOR_TURI, STRUCTURE_TYPE_TURI_2, STRUCTURE_PALETTE_TURI_2, 0 },
        { ACTOR_KOINOBORI, STRUCTURE_TYPE_KOINOBORI, STRUCTURE_PALETTE_KOINOBORI, 0 },
        { ACTOR_DUMP, STRUCTURE_TYPE_DUMP, STRUCTURE_PALETTE_DUMP, 0 },
        { ACTOR_WINDMILL, STRUCTURE_TYPE_WINDMILL, STRUCTURE_PALETTE_WINDMILL_1, 0 },
        { ACTOR_WINDMILL, STRUCTURE_TYPE_WINDMILL, STRUCTURE_PALETTE_WINDMILL_2, 0 },
        { ACTOR_WINDMILL, STRUCTURE_TYPE_WINDMILL, STRUCTURE_PALETTE_WINDMILL_3, 0 },
        { ACTOR_WINDMILL, STRUCTURE_TYPE_WINDMILL, STRUCTURE_PALETTE_WINDMILL_4, 0 },
        { ACTOR_WINDMILL, STRUCTURE_TYPE_WINDMILL, STRUCTURE_PALETTE_WINDMILL_5, 0 },
        { ACTOR_LOTUS, STRUCTURE_TYPE_LOTUS, STRUCTURE_PALETTE_LOTUS, 0 },
        { ACTOR_MIKANBOX, STRUCTURE_TYPE_MIKANBOX, STRUCTURE_PALETTE_MIKANBOX, 0 },
        { ACTOR_DOUZOU, STRUCTURE_TYPE_DOUZOU, STRUCTURE_PALETTE_DOUZOU, 0 },
        { ACTOR_TOUDAI, STRUCTURE_TYPE_TOUDAI, STRUCTURE_PALETTE_TOUDAI, 0 },
    };
    Actor* sp84 = NULL;
    s16 profile;
    s16 structure_type;
    s16 pal_no;

    if (structureName < 0x50DA) {
        s32 index = mNpc_SearchAnimalinfo(common_data.animals, structureName + 0x9000, 0xF);

        profile = ACTOR_HOUSE;
        structure_type = common_data.npclist[index].houseData.type;
        pal_no = common_data.npclist[index].houseData.palette;
        pal_no += structure_type * 5;
    } else if ((structureName >= 0x5800) && (structureName < 0x5804)) {
        s32 index = structureName - 0x5800;
        aSTR_setup_info* info = &setupInfo_table[index];

        profile = info->profile;
        structure_type = common_data.homes[index].unk_022.unk_22_0 + STRUCTURE_TYPE_MY_HOUSE_1;
        pal_no = common_data.homes[index].unk_024 + STRUCTURE_PALETTE_MY_HOUSE_1;
    } else if ((structureName >= 0x5809) && (structureName < 0x580A)) {
        s32 stationType = common_data.stationType;

        profile = ACTOR_STATION;
        structure_type = (stationType / 5) + STRUCTURE_TYPE_STATION_1;
        pal_no = stationType + STRUCTURE_PALETTE_STATION_1_1;
    } else {
        aSTR_setup_info* info = &setupInfo_table[structureName - 0x5800];

        profile = info->profile;
        structure_type = info->structure_type;
        pal_no = info->pal_no;
    }

    func_809E889C_jp(common_data.clip.structureClip->unk_B0, 8, structure_type, structureName, posX, posZ);
    func_809E889C_jp(common_data.clip.structureClip->unk_454, 9, pal_no, structureName, posX, posZ);
    func_809E889C_jp(common_data.clip.structureClip->unk_86C, 8, structure_type, structureName, posX, posZ);

    if (func_809E8CD4_jp(structure_type) && aSTR_get_pal_segment(pal_no) && func_809E8DB4_jp(structure_type)) {
        UNUSED s32 pad;
        xyz_t pos;

        pos.x = posX;
        pos.z = posZ;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
        sp84 = Actor_info_make_actor(&game_play->actorInfo, game_play, profile, pos.x, pos.y, pos.z, 0, 0, 0,
                                     game_play->unk_00E4, game_play->unk_00E5, -1, structureName, params, -1, -1);

        if (sp84 != NULL) {
            mFI_SetFG_common(0xFFFF, pos, 0);
        }
    }

    return sp84;
}

s32 aSTR_get_overlay_free_area_idx(void) {
    StructureOverlayInfo* structureOverlay = common_data.clip.structureClip->overlayArea;
    s32 i;
    s32 ret = -1;

    for (i = 0; i < 9; i++, structureOverlay++) {
        if (!structureOverlay->used) {
            ret = i;
            break;
        }
    }

    return ret;
}

void aSTR_get_overlay_area_proc(ActorOverlay* overlayEntry, UNUSED size_t overlaySize) {
    s32 freeIndex = aSTR_get_overlay_free_area_idx();

    if (freeIndex != -1) {
        overlayEntry->loadedRamAddr = common_data.clip.structureClip->overlayArea[freeIndex].overlayPointer;
        common_data.clip.structureClip->overlayArea[freeIndex].used = true;
    } else {
        overlayEntry->loadedRamAddr = NULL;
    }
}

void aSTR_free_overlay_area_proc(ActorOverlay* overlayEntry) {
    StructureOverlayInfo* structureOverlay = common_data.clip.structureClip->overlayArea;
    s32 i;

    for (i = 0; i < 9; i++, structureOverlay++) {
        if (structureOverlay->overlayPointer == overlayEntry->loadedRamAddr) {
            structureOverlay->used = false;
            overlayEntry->loadedRamAddr = NULL;
            return;
        }
    }
}

Actor* aSTR_get_actor_area_proc(void) {
    StructureActor** actorTableIter = common_data.clip.structureClip->structureActorTable;
    s32* isUsed = common_data.clip.structureClip->structureActorUsedTable;
    s32 i;
    StructureActor* ret = NULL;

    for (i = 0; i < 9; i++, actorTableIter++, isUsed++) {
        if ((*actorTableIter != NULL) && (*isUsed == false)) {
            *isUsed = true;
            ret = *actorTableIter;
            break;
        }
    }

    return &ret->actor;
}

void aSTR_free_actor_area_proc(Actor* actor) {
    StructureActor* structureActor = (StructureActor*)actor;
    StructureActor** actorTableIter = common_data.clip.structureClip->structureActorTable;
    s32* isUsed = common_data.clip.structureClip->structureActorUsedTable;
    s32 i;

    for (i = 0; i < 9; i++, actorTableIter++, isUsed++) {
        if (structureActor == *actorTableIter) {
            *isUsed = false;
            return;
        }
    }
}

void aSTR_init_clip_area(Game_Play* game_play) {
    if (common_data.clip.structureClip == NULL) {
        common_data.clip.structureClip = (StructureClip*)zelda_malloc(sizeof(StructureClip));
        common_data.clip.structureClip->setupActorProc = aSTR_setupActor_proc;
        common_data.clip.structureClip->getOverlayAreaProc = aSTR_get_overlay_area_proc;
        common_data.clip.structureClip->freeOverlayAreaProc = aSTR_free_overlay_area_proc;
        common_data.clip.structureClip->getActorAreaProc = aSTR_get_actor_area_proc;
        common_data.clip.structureClip->freeActorAreaProc = aSTR_free_actor_area_proc;
        common_data.clip.structureClip->unk_A4 = func_809E84E4_jp;
        common_data.clip.structureClip->unk_A8 = func_809E8C14_jp;
        common_data.clip.structureClip->unk_AC = func_809E8CD4_jp;
        common_data.clip.structureClip->getPalSegment = aSTR_get_pal_segment;
        common_data.clip.structureClip->unk_868 = func_809E8DB4_jp;
        common_data.clip.structureClip->unk_C10 = 0;

        {
            StructureActor** actorTableIter = common_data.clip.structureClip->structureActorTable;
            s32* isUsed = common_data.clip.structureClip->structureActorUsedTable;
            StructureOverlayInfo* structureOverlay = common_data.clip.structureClip->overlayArea;
            s32 i;

            for (i = 0; i < 9; i++, actorTableIter++, isUsed++, structureOverlay++) {
                *actorTableIter = &aSTR_actor_cl[i];
                *isUsed = 0;
                structureOverlay->overlayPointer = aSTR_overlay[i];
                structureOverlay->used = 0;
            }
        }

        {
            StructureClip_unkstruct* ptr;
            s32 i;
            s32 j;

            ptr = common_data.clip.structureClip->unk_B0;
            for (i = 0; i < 8; i++, ptr++) {
                ptr->type = -1;
                ptr->unk_02 = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < 9; j++) {
                    ptr->unk_04[j].unk_08 = 0;
                    ptr->unk_04[j].fgName = 0;
                }
            }

            ptr = common_data.clip.structureClip->unk_454;
            for (i = 0; i < 9; i++, ptr++) {
                ptr->type = -1;
                ptr->unk_02 = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < 9; j++) {
                    ptr->unk_04[j].unk_08 = 0;
                    ptr->unk_04[j].fgName = 0;
                }
            }

            ptr = common_data.clip.structureClip->unk_86C;
            for (i = 0; i < 8; i++, ptr++) {
                ptr->type = -1;
                ptr->unk_02 = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < 9; j++) {
                    ptr->unk_04[j].unk_08 = 0;
                    ptr->unk_04[j].fgName = 0;
                }
            }
        }

        func_809E7F34_jp(game_play);
        func_809E7F94_jp();
    }
}

void aSTR_free_clip_area(void) {
    if (common_data.clip.structureClip != NULL) {
        {
            StructureActor** actorTableIter = common_data.clip.structureClip->structureActorTable;
            StructureOverlayInfo* structureOverlay = common_data.clip.structureClip->overlayArea;
            s32 i;

            for (i = 0; i < 9; i++, actorTableIter++, structureOverlay++) {
                if (*actorTableIter != NULL) {
                    *actorTableIter = NULL;
                }

                if (structureOverlay->overlayPointer != NULL) {
                    structureOverlay->overlayPointer = NULL;
                }
            }
        }

        zelda_free(common_data.clip.structureClip);
        common_data.clip.structureClip = NULL;
    }
}

void aSTR_check_door_data(Structure* this, Game_Play* game_play) {
    static s32 request[] = { 4, 5 };

    if (((this->unk_178 & 0xF000) >> 0xC) == 5) {
        StructureActor* structureActor =
            (StructureActor*)Actor_info_fgName_search(&game_play->actorInfo, this->unk_178, ACTOR_PART_0);

        if ((structureActor != NULL) && (structureActor->unk_2B0 == 0)) {
            structureActor->unk_2B0 = request[(this->unk_17A == 1)];
            this->unk_178 = 0;
        }
    } else {
        this->unk_178 = 0;
    }
}

void aSTR_actor_move(Actor* thisx, Game_Play* game_play) {
    Structure* this = THIS;

    if (mFI_GetFieldId() == 0) {
        func_809E8480_jp(&game_play->objectExchangeBank);
        aSTR_check_door_data(this, game_play);
    }
}
