#include "ac_structure.h"
#include "macros.h"
#include "m_actor_dlftbls.h"
#include "m_field_info.h"
#include "m_lib.h"
#include "m_malloc.h"
#include "m_object.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "segment_symbols.h"
#include "prevent_bss_reordering2.h"
#include "prevent_bss_reordering.h"

#define THIS ((Structure*)thisx)

void aSTR_actor_ct(Actor* thisx, Game_Play* game_play);
void aSTR_actor_dt(Actor* thisx, Game_Play* game_play);
void aSTR_actor_move(Actor* thisx, Game_Play* game_play);

void aSTR_init_clip_area(Game_Play* game_play);
void aSTR_free_clip_area(void);

StructureActor aSTR_actor_cl[STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT];
s8 aSTR_overlay[STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT][8192];

// Original name unknown. Unused
s8 aSTR_bss_padding_1[8];

// Original name unknown. This array is 4x larger than it needs to be.
void* aSTR_object_start_addresses[STRUCTURE_TYPE_MAX * 4];

// Original name unknown. Unused
s8 aSTR_bss_padding_2[8];

// Original name unknown. This array is 4x larger than it needs to be.
void* aSTR_object_end_addresses[STRUCTURE_TYPE_MAX * 4];

// Original name unknown. Unused
s8 aSTR_bss_padding_3[8];

// Original name unknown. This array is 4x larger than it needs to be.
void* aSTR_palette_addresses[STRUCTURE_PALETTE_MAX * 4];

// Original name unknown. Unused
s8 aSTR_bss_padding_4[8];

// Original name unknown. This array is 4x larger than it needs to be.
void* aSTR_shadow_start_addresses[STRUCTURE_TYPE_MAX * 4];

// Original name unknown. Unused
s8 aSTR_bss_padding_5[8];

// Original name unknown. This array is 4x larger than it needs to be.
void* aSTR_shadow_end_addresses[STRUCTURE_TYPE_MAX * 4];

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
    this->doorFgName = common_data.doorData.fgName;
    this->doorExitType = common_data.doorData.exitType;
}

void aSTR_actor_dt(UNUSED Actor* thisx, UNUSED Game_Play* game_play) {
    aSTR_free_clip_area();
}

void func_809E7F34_jp(Game_Play* game_play) {
    UNUSED s32 pad;
    s32 bankNum = game_play->objectExchangeBank.num;

    if (mSc_secure_exchange_keep_bank(&game_play->objectExchangeBank, 0, (0x2E00 * 8) + (0x20 * 9) + (0x800 * 8))) {
        common_data.clip.structureClip->objectExchangeBankNum = bankNum;
    } else {
        common_data.clip.structureClip->objectExchangeBankNum = -1;
    }
}

// TODO: Replace these with the actual object symbols when the various structure objects are extracted
extern void* structure_object_symbol_1; // 0x06000008 in object_00DF4000, pointer to obj_s_house1
extern void* structure_object_symbol_2; // 0x06000178 in object_00DF4000, pointer to obj_w_house1
extern void* structure_object_symbol_3; // 0x060000C0 in object_00DF4000, pointer to 0x06026380
extern void* structure_object_symbol_4; // 0x06000230 in object_00DF4000, pointer to 0x06032908
extern void* structure_object_symbol_5; // 0x06000008 in object_00D5D000, pointer to obj_s_house1_a_pal
extern void* structure_object_symbol_6; // 0x06000174 in object_00D5D000, pointer to obj_w_house1_a_pal
extern u8 structure_object_symbol_7[];  // 0x06000008 in object_00E00000
extern u8 structure_object_symbol_8[];  // 0x060000C0 in object_00E00000

static void* D_809E9864_jp[] = { &structure_object_symbol_1, &structure_object_symbol_2 };
static void* D_809E986C_jp[] = { &structure_object_symbol_3, &structure_object_symbol_4 };
static void* D_809E9874_jp[] = { &structure_object_symbol_5, &structure_object_symbol_6 };

void func_809E7F94_jp(void) {
    s32 index = (common_data.time.season == WINTER);

    DmaMgr_RequestSyncDebug(&aSTR_object_start_addresses,
                            ((uintptr_t)D_809E9864_jp[index] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            ARRAY_COUNT(aSTR_object_start_addresses), "../ac_structure_clip.c_inc", 129);
    DmaMgr_RequestSyncDebug(&aSTR_object_end_addresses,
                            ((uintptr_t)D_809E986C_jp[index] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            ARRAY_COUNT(aSTR_object_end_addresses), "../ac_structure_clip.c_inc", 132);
    DmaMgr_RequestSyncDebug(&aSTR_palette_addresses,
                            ((uintptr_t)D_809E9874_jp[index] + SEGMENT_ROM_START(object_00D5D000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00D5D000),
                            ARRAY_COUNT(aSTR_palette_addresses), "../ac_structure_clip.c_inc", 135);
    DmaMgr_RequestSyncDebug(&aSTR_shadow_start_addresses,
                            ((uintptr_t)structure_object_symbol_7 + (uintptr_t)SEGMENT_ROM_START(object_00E00000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
                            ARRAY_COUNT(aSTR_shadow_start_addresses), "../ac_structure_clip.c_inc", 138);
    DmaMgr_RequestSyncDebug(&aSTR_shadow_end_addresses,
                            ((uintptr_t)structure_object_symbol_8 + (uintptr_t)SEGMENT_ROM_START(object_00E00000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
                            ARRAY_COUNT(aSTR_shadow_end_addresses), "../ac_structure_clip.c_inc", 141);
}

void func_809E8118_jp(ObjectExchangeBank* objectExchangeBank) {
    StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->objectSegmentTable[0];
    u8* segment = objectExchangeBank->status[common_data.clip.structureClip->objectExchangeBankNum].segment;
    s16 type;
    s32 offset;
    RomOffset vrom;
    size_t size;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable);
         i++, segment += 0x2E00, segmentInfo++) {
        if (segmentInfo->unk_03 == 1) {
            type = segmentInfo->type;
            offset = (uintptr_t)aSTR_object_start_addresses[type] - (uintptr_t)SEGMENT_VRAM_START(object_00DF4000) + 8;
            vrom = offset + SEGMENT_ROM_START(object_00D5E000);
            size = ALIGN16(((uintptr_t)aSTR_object_end_addresses[type] - (uintptr_t)aSTR_object_start_addresses[type]) -
                           8);
            DmaMgr_RequestSyncDebug(segment, vrom, size, "../ac_structure_clip.c_inc", 198);
            segmentInfo->segment = (s32)segment - offset;
            segmentInfo->unk_03 = 0;
        }
    }
}

void func_809E823C_jp(ObjectExchangeBank* objectExchangeBank) {
    StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->paletteSegmentTable[0];
    u8* segment =
        objectExchangeBank->status[common_data.clip.structureClip->objectExchangeBankNum].segment + (0x2E00 * 8);
    void* paletteAddress;
    s32 offset;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable);
         i++, segment += 0x20, segmentInfo++) {
        if (segmentInfo->unk_03 == 1) {
            paletteAddress = aSTR_palette_addresses[segmentInfo->type];
            offset = (uintptr_t)paletteAddress - (uintptr_t)SEGMENT_VRAM_START(object_00D5D000);
            DmaMgr_RequestSyncDebug(segment, offset + (uintptr_t)SEGMENT_ROM_START(object_00D5B000), 32,
                                    "../ac_structure_clip.c_inc", 256);
            segmentInfo->segment = (s32)segment;
            segmentInfo->unk_03 = 0;
        }
    }
}

void func_809E8350_jp(ObjectExchangeBank* objectExchangeBank) {
    StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->shadowSegmentTable[0];
    u8* segment = objectExchangeBank->status[common_data.clip.structureClip->objectExchangeBankNum].segment +
                  (0x2E00 * 8) + (0x20 * 9);
    s16 type;
    s32 offset;
    RomOffset vrom;
    size_t size;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable);
         i++, segment += 0x800, segmentInfo++) {
        if (segmentInfo->unk_03 == 1) {
            type = segmentInfo->type;
            offset = (uintptr_t)aSTR_shadow_start_addresses[type] - (uintptr_t)SEGMENT_VRAM_START(object_00E00000) + 8;
            vrom = offset + (uintptr_t)SEGMENT_ROM_START(object_00DF5000);
            size = ALIGN16(((uintptr_t)aSTR_shadow_end_addresses[type] - (uintptr_t)aSTR_shadow_start_addresses[type]) -
                           8);
            DmaMgr_RequestSyncDebug(segment, vrom, size, "../ac_structure_clip.c_inc", 321);
            segmentInfo->segment = (s32)segment - offset;
            segmentInfo->unk_03 = 0;
        }
    }
}

void func_809E8480_jp(ObjectExchangeBank* objectExchangeBank) {
    if ((common_data.clip.structureClip->objectExchangeBankNum != -1) &&
        (common_data.clip.structureClip->unk_C10 != 0)) {
        func_809E8118_jp(objectExchangeBank);
        func_809E823C_jp(objectExchangeBank);
        func_809E8350_jp(objectExchangeBank);
        common_data.clip.structureClip->unk_C10 = 0;
    }
}

void func_809E84E4_jp(ObjectExchangeBank* objectExchangeBank) {
    StructureClipSegmentInfo* ptr;
    s32 i;

    ptr = common_data.clip.structureClip->objectSegmentTable;
    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable); i++, ptr++) {
        if ((ptr->type == -1) || (ptr->instanceCount == 0)) {
            ptr->type = -1;
            ptr->instanceCount = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->paletteSegmentTable;
    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable); i++, ptr++) {
        if ((ptr->type == -1) || (ptr->instanceCount == 0)) {
            ptr->type = -1;
            ptr->instanceCount = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->shadowSegmentTable;
    for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable); i++, ptr++) {
        if ((ptr->type == -1) || (ptr->instanceCount == 0)) {
            ptr->type = -1;
            ptr->instanceCount = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    common_data.clip.structureClip->unk_C10 = 1;
    func_809E8480_jp(objectExchangeBank);
}

// Original name unknown.
// Returns true if there is an instance in the segment info with a matching position and `fgName`, false otherwise.
s32 aSTR_is_instance_in_segment_info(StructureClipSegmentInfo* segmentInfo, u16 fgName, f32 posX, f32 posZ) {
    StructureClipInstanceInfo* instance = segmentInfo->instances;
    s32 i;
    s32 ret = false;

    for (i = 0; i < ARRAY_COUNT(segmentInfo->instances); i++, instance++) {
        if ((instance->fgName == fgName) && (instance->posX == posX) && (instance->posZ == posZ)) {
            ret = true;
            break;
        }
    }

    return ret;
}

// Original name unknown.
// Attempts to add an instance to the segment info. If all instances in the instance table are currently in use, then
// this function *won't* add anything to the table and will return false. Otherwise, it will put the instance in the
// table and return true.
s32 aSTR_try_add_instance_to_segment_info(StructureClipSegmentInfo* segmentInfo, u16 fgName, f32 posX, f32 posZ) {
    StructureClipInstanceInfo* instance = segmentInfo->instances;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(segmentInfo->instances); i++, instance++) {
        if (instance->fgName == 0) {
            instance->fgName = fgName;
            instance->posX = posX;
            instance->posZ = posZ;
            instance->unk_08 = 0;
            return true;
        }
    }

    return false;
}

// Original name unknown.
void aSTR_try_add_instance_to_segment_info_with_type(StructureClipSegmentInfo* segmentInfo, u16 fgName, f32 posX,
                                                     f32 posZ) {
    if (!aSTR_is_instance_in_segment_info(segmentInfo, fgName, posX, posZ)) {
        if (aSTR_try_add_instance_to_segment_info(segmentInfo, fgName, posX, posZ) == true) {
            segmentInfo->instanceCount++;
        }
    }
}

// Original name unknown.
void aSTR_try_add_instance_to_segment_info_with_uninitialized_type(StructureClipSegmentInfo* segmentInfo, s16 type,
                                                                   u16 fgName, f32 posX, f32 posZ) {
    if (aSTR_try_add_instance_to_segment_info(segmentInfo, fgName, posX, posZ) == true) {
        segmentInfo->type = type;
        segmentInfo->instanceCount = 1;
        segmentInfo->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

// Original name unknown.
void aSTR_try_add_instance_to_segment_info_with_no_instances(StructureClipSegmentInfo* segmentInfo, s16 type,
                                                             u16 fgName, f32 posX, f32 posZ) {
    if (aSTR_try_add_instance_to_segment_info(segmentInfo, fgName, posX, posZ) == true) {
        segmentInfo->type = type;
        segmentInfo->instanceCount = 1;
        segmentInfo->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

// Original name unknown.
// This function looks through the elements of the segment table and attempts to add the instance to the appropriate
// segment info within the table.
void aSTR_try_add_instance_to_segment_table(StructureClipSegmentInfo* table, s32 size, s16 type, u16 fgName, f32 posX,
                                            f32 posZ) {
    StructureClipSegmentInfo* segmentInfo;
    s32 i;

    // Checks to see if one of the segment info within the table already has the same `type` as the instance we're
    // trying to add. If so, add it to that segment info.
    segmentInfo = &table[0];
    for (i = 0; i < size; i++, segmentInfo++) {
        if (segmentInfo->type == type) {
            aSTR_try_add_instance_to_segment_info_with_type(segmentInfo, fgName, posX, posZ);
            return;
        }
    }

    // Checks to see if one of the segment info within the table has an uninitialized `type`. If so, that info is not
    // currently in use, so add the instance to that segment info.
    segmentInfo = &table[0];
    for (i = 0; i < size; i++, segmentInfo++) {
        if (segmentInfo->type == -1) {
            aSTR_try_add_instance_to_segment_info_with_uninitialized_type(segmentInfo, type, fgName, posX, posZ);
            return;
        }
    }

    // Checks to see if one of the segment info within the table has no instances associated with it. If so, that info
    // is not currently in use, so add the instance to that segment info.
    segmentInfo = &table[0];
    for (i = 0; i < size; i++, segmentInfo++) {
        if (segmentInfo->instanceCount == 0) {
            aSTR_try_add_instance_to_segment_info_with_no_instances(segmentInfo, type, fgName, posX, posZ);
            return;
        }
    }
}

// Original name unknown.
// Looks through the segment info to see if it can find an instance that matches the supplied `actor`. If it finds it,
// it will remove that instance from the segment info and return true, otherwise it will return false. Note that this
// function does *not* check if the segment info has any instances in it at all, so calling this might be a waste of
// time; `aSTR_remove_instance_from_segment_info` will check this for you.
s32 aSTR_remove_instance_from_segment_info_unchecked(StructureClipSegmentInfo* segmentInfo, Actor* actor) {
    StructureClipInstanceInfo* instance = segmentInfo->instances;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(segmentInfo->instances); i++, instance++) {
        if ((instance->fgName == actor->fgName) && (instance->posX == actor->home.pos.x) &&
            (instance->posZ == actor->home.pos.z)) {
            instance->posX = 0.0f;
            instance->posZ = 0.0f;
            instance->fgName = 0;
            instance->unk_08 = 0;
            segmentInfo->instanceCount--;
            return true;
        }
    }

    return false;
}

// Original name unknown.
// Returns false if it couldn't find an instance that matches the supplied actor in the segment info or if the segment
// info has no instances in it. Otherwise, it will remove the instance matching the supplied `actor` and return true.
s32 aSTR_remove_instance_from_segment_info(StructureClipSegmentInfo* segmentInfo, Actor* actor) {
    s32 ret = false;

    if (segmentInfo->instanceCount > 0) {
        ret = aSTR_remove_instance_from_segment_info_unchecked(segmentInfo, actor);
    }

    return ret;
}

// Original name unknown.
// This function looks through the elements of the segment table and attempts to remove the instance from the
// appropriate segment info within the table.
void aSTR_remove_instance_proc(StructureClipSegmentInfo* table, s32 tableSize, s16 type, Actor* actor) {
    StructureClipSegmentInfo* segmentInfo = &table[0];
    s32 i;

    for (i = 0; i < tableSize; i++, segmentInfo++) {
        if (segmentInfo->type == type) {
            if (aSTR_remove_instance_from_segment_info(segmentInfo, actor) == true) {
                return;
            } else {
                return;
            }
        }
    }
}

// Original name unknown.
// Returns the index of the segment info within the table whose type matches the supplied `type`. If no segment info
// within the table has that `type`, then this function returns -1.
s32 aSTR_get_index_of_type_in_segment_table(StructureClipSegmentInfo* table, s32 size, s16 type) {
    s32 i;
    s32 ret = -1;

    for (i = 0; i < size; i++, table++) {
        if ((table->type == type) && (table->unk_03 != 1)) {
            ret = i;
            break;
        }
    }

    return ret;
}

// Original name unknown. Named based on the below function
s32 aSTR_get_object_segment(s16 structureType) {
    s32 index = aSTR_get_index_of_type_in_segment_table(common_data.clip.structureClip->objectSegmentTable,
                                                        ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                                        structureType);

    if (index != -1) {
        StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->objectSegmentTable[index];

        return segmentInfo->segment;
    }

    return NULL;
}

u16* aSTR_get_pal_segment(s16 paletteType) {
    s32 index = aSTR_get_index_of_type_in_segment_table(
        common_data.clip.structureClip->paletteSegmentTable,
        ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable), paletteType);

    if (index != -1) {
        StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->paletteSegmentTable[index];

        return (u16*)segmentInfo->segment;
    }

    return NULL;
}

// Original name unknown. Named based on the above function
s32 aSTR_get_shadow_segment(s16 arg0) {
    s32 index =
        aSTR_get_index_of_type_in_segment_table(common_data.clip.structureClip->shadowSegmentTable,
                                                ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable), arg0);

    if (index != -1) {
        StructureClipSegmentInfo* segmentInfo = &common_data.clip.structureClip->shadowSegmentTable[index];

        return segmentInfo->segment;
    }

    return NULL;
}

typedef struct StructureSetupInfo {
    s16 profile;
    s16 structureType; // see `StructureType`
    s16 paletteType;   // see `StructurePalette`
    s16 pad;
} StructureSetupInfo;

Actor* aSTR_setupActor_proc(Game_Play* game_play, u16 structureName, f32 posX, f32 posZ, s16 params) {
    static StructureSetupInfo setupInfo_table[] = {
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
    Actor* ret = NULL;
    s16 profile;
    s16 structureType;
    s16 paletteType;

    if (structureName < 0x50DA) {
        s32 index = mNpc_SearchAnimalinfo(common_data.save.animals, structureName + 0x9000, 0xF);

        profile = ACTOR_HOUSE;
        structureType = common_data.npclist[index].houseData.type;
        paletteType = common_data.npclist[index].houseData.palette;
        paletteType += structureType * 5;
    } else if ((structureName >= 0x5800) && (structureName < 0x5804)) {
        s32 index = structureName - 0x5800;
        StructureSetupInfo* info = &setupInfo_table[index];

        profile = info->profile;
        structureType = common_data.save.homes[index].unk_022.unk_22_0 + STRUCTURE_TYPE_MY_HOUSE_1;
        paletteType = common_data.save.homes[index].unk_024 + STRUCTURE_PALETTE_MY_HOUSE_1;
    } else if ((structureName >= 0x5809) && (structureName < 0x580A)) {
        s32 stationType = common_data.save.stationType;

        profile = ACTOR_STATION;
        structureType = (stationType / 5) + STRUCTURE_TYPE_STATION_1;
        paletteType = stationType + STRUCTURE_PALETTE_STATION_1_1;
    } else {
        StructureSetupInfo* info = &setupInfo_table[structureName - 0x5800];

        profile = info->profile;
        structureType = info->structureType;
        paletteType = info->paletteType;
    }

    aSTR_try_add_instance_to_segment_table(common_data.clip.structureClip->objectSegmentTable,
                                           ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable),
                                           structureType, structureName, posX, posZ);
    aSTR_try_add_instance_to_segment_table(common_data.clip.structureClip->paletteSegmentTable,
                                           ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable),
                                           paletteType, structureName, posX, posZ);
    aSTR_try_add_instance_to_segment_table(common_data.clip.structureClip->shadowSegmentTable,
                                           ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable),
                                           structureType, structureName, posX, posZ);

    if ((aSTR_get_object_segment(structureType) != NULL) && (aSTR_get_pal_segment(paletteType) != NULL) &&
        (aSTR_get_shadow_segment(structureType) != NULL)) {
        UNUSED s32 pad;
        xyz_t pos;

        pos.x = posX;
        pos.z = posZ;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
        ret = Actor_info_make_actor(&game_play->actorInfo, game_play, profile, pos.x, pos.y, pos.z, 0, 0, 0,
                                    game_play->unk_00E4, game_play->unk_00E5, -1, structureName, params, -1, -1);

        if (ret != NULL) {
            mFI_SetFG_common(0xFFFF, pos, 0);
        }
    }

    return ret;
}

s32 aSTR_get_overlay_free_area_idx(void) {
    StructureClipOverlayInfo* overlayIter = common_data.clip.structureClip->overlayArea;
    s32 i;
    s32 ret = -1;

    for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, overlayIter++) {
        if (!overlayIter->used) {
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
    StructureClipOverlayInfo* overlayIter = common_data.clip.structureClip->overlayArea;
    s32 i;

    for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, overlayIter++) {
        if (overlayIter->overlayPointer == overlayEntry->loadedRamAddr) {
            overlayIter->used = false;
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

    for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, actorTableIter++, isUsed++) {
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

    for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, actorTableIter++, isUsed++) {
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
        common_data.clip.structureClip->removeInstanceProc = aSTR_remove_instance_proc;
        common_data.clip.structureClip->getObjectSegment = aSTR_get_object_segment;
        common_data.clip.structureClip->getPalSegment = aSTR_get_pal_segment;
        common_data.clip.structureClip->getShadowSegment = aSTR_get_shadow_segment;
        common_data.clip.structureClip->unk_C10 = 0;

        {
            StructureActor** actorTableIter = common_data.clip.structureClip->structureActorTable;
            s32* isUsed = common_data.clip.structureClip->structureActorUsedTable;
            StructureClipOverlayInfo* overlayIter = common_data.clip.structureClip->overlayArea;
            s32 i;

            for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, actorTableIter++, isUsed++, overlayIter++) {
                *actorTableIter = &aSTR_actor_cl[i];
                *isUsed = false;
                overlayIter->overlayPointer = aSTR_overlay[i];
                overlayIter->used = false;
            }
        }

        {
            StructureClipSegmentInfo* ptr;
            s32 i;
            s32 j;

            ptr = common_data.clip.structureClip->objectSegmentTable;
            for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->objectSegmentTable); i++, ptr++) {
                ptr->type = -1;
                ptr->instanceCount = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < ARRAY_COUNT(ptr->instances); j++) {
                    ptr->instances[j].unk_08 = 0;
                    ptr->instances[j].fgName = 0;
                }
            }

            ptr = common_data.clip.structureClip->paletteSegmentTable;
            for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->paletteSegmentTable); i++, ptr++) {
                ptr->type = -1;
                ptr->instanceCount = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < ARRAY_COUNT(ptr->instances); j++) {
                    ptr->instances[j].unk_08 = 0;
                    ptr->instances[j].fgName = 0;
                }
            }

            ptr = common_data.clip.structureClip->shadowSegmentTable;
            for (i = 0; i < ARRAY_COUNT(common_data.clip.structureClip->shadowSegmentTable); i++, ptr++) {
                ptr->type = -1;
                ptr->instanceCount = 0;
                ptr->unk_03 = 0;
                for (j = 0; j < ARRAY_COUNT(ptr->instances); j++) {
                    ptr->instances[j].unk_08 = 0;
                    ptr->instances[j].fgName = 0;
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
            StructureClipOverlayInfo* overlayIter = common_data.clip.structureClip->overlayArea;
            s32 i;

            for (i = 0; i < STRUCTURE_CLIP_STRUCTURE_ACTOR_COUNT; i++, actorTableIter++, overlayIter++) {
                if (*actorTableIter != NULL) {
                    *actorTableIter = NULL;
                }

                if (overlayIter->overlayPointer != NULL) {
                    overlayIter->overlayPointer = NULL;
                }
            }
        }

        zelda_free(common_data.clip.structureClip);
        common_data.clip.structureClip = NULL;
    }
}

void aSTR_check_door_data(Structure* this, Game_Play* game_play) {
    static s32 request[] = { 4, 5 };

    if (((this->doorFgName & 0xF000) >> 0xC) == 5) {
        StructureActor* structureActor =
            (StructureActor*)Actor_info_fgName_search(&game_play->actorInfo, this->doorFgName, ACTOR_PART_0);

        if ((structureActor != NULL) && (structureActor->unk_2B0 == 0)) {
            structureActor->unk_2B0 = request[(this->doorExitType == 1)];
            this->doorFgName = 0;
        }
    } else {
        this->doorFgName = 0;
    }
}

void aSTR_actor_move(Actor* thisx, Game_Play* game_play) {
    Structure* this = THIS;

    if (mFI_GetFieldId() == 0) {
        func_809E8480_jp(&game_play->objectExchangeBank);
        aSTR_check_door_data(this, game_play);
    }
}
