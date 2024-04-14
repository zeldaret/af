#include "ac_structure.h"
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

#if 0
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
#endif

extern s32 D_809E9A9C_jp[];

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

    if (mSc_secure_exchange_keep_bank(&game_play->objectExchangeBank, 0, 0x1B120)) {
        common_data.clip.structureClip->unk_C0C = num;
    } else {
        common_data.clip.structureClip->unk_C0C = -1;
    }
}

// .bss
extern void* B_809FD530_jp[];
extern void* B_809FD818_jp[];
extern void* B_809FDB00_jp[];
extern void* B_809FE0B8_jp[];
extern void* B_809FE3A0_jp[];

// .data
extern void* D_809E9864_jp[];
extern void* D_809E986C_jp[];
extern void* D_809E9874_jp[];

extern u8 test[]; // 0x06000008
extern u8 test2[]; // 0x060000C0

// TODO: Fix warnings, use "real" symbols
void func_809E7F94_jp(void) {
    s32 temp_t1 = (common_data.time.season == 3);

    DmaMgr_RequestSyncDebug(&B_809FD530_jp,
                            ((uintptr_t)D_809E9864_jp[temp_t1] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            184, "../ac_structure_clip.c_inc", 129);
    DmaMgr_RequestSyncDebug(&B_809FD818_jp,
                            ((uintptr_t)D_809E986C_jp[temp_t1] + SEGMENT_ROM_START(object_00DF4000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00DF4000),
                            184, "../ac_structure_clip.c_inc", 132);
    DmaMgr_RequestSyncDebug(&B_809FDB00_jp,
                            ((uintptr_t)D_809E9874_jp[temp_t1] + SEGMENT_ROM_START(object_00D5D000)) -
                                (uintptr_t)SEGMENT_VRAM_START(object_00D5D000),
                            364, "../ac_structure_clip.c_inc", 135);
    DmaMgr_RequestSyncDebug(
        &B_809FE0B8_jp, (test + SEGMENT_ROM_START(object_00E00000)) - (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
        184, "../ac_structure_clip.c_inc", 138);
    DmaMgr_RequestSyncDebug(
        &B_809FE3A0_jp, (test2 + SEGMENT_ROM_START(object_00E00000)) - (uintptr_t)SEGMENT_VRAM_START(object_00E00000),
        184, "../ac_structure_clip.c_inc", 141);
}

void func_809E8118_jp(ObjectExchangeBank* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Structure/ac_structure/func_809E8118_jp.s")

void func_809E823C_jp(ObjectExchangeBank* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Structure/ac_structure/func_809E823C_jp.s")

void func_809E8350_jp(ObjectExchangeBank* arg0);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Structure/ac_structure/func_809E8350_jp.s")

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
        if ((ptr->unk_00 == -1) || (ptr->unk_02 == 0)) {
            ptr->unk_00 = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->unk_454;
    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->unk_00 == -1) || (ptr->unk_02 == 0)) {
            ptr->unk_00 = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    ptr = common_data.clip.structureClip->unk_86C;
    for (i = 0; i < 8; i++, ptr++) {
        if ((ptr->unk_00 == -1) || (ptr->unk_02 == 0)) {
            ptr->unk_00 = -1;
            ptr->unk_02 = 0;
            ptr->unk_03 = 0;
        } else {
            ptr->unk_03 = 1;
        }
    }

    common_data.clip.structureClip->unk_C10 = 1;
    func_809E8480_jp(arg0);
}

s32 func_809E85FC_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 arg2, f32 arg3) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;
    s32 ret = false;

    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->unk_0A == arg1) && (ptr->unk_00 == arg2) && (ptr->unk_04 == arg3)) {
            ret = true;
            break;
        }
    }

    return ret;
}

s32 func_809E8674_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 arg2, f32 arg3) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;

    for (i = 0; i < 9; i++, ptr++) {
        if (ptr->unk_0A == 0) {
            ptr->unk_0A = arg1;
            ptr->unk_00 = arg2;
            ptr->unk_04 = arg3;
            ptr->unk_08 = 0;
            return true;
        }
    }

    return false;
}

void func_809E8768_jp(StructureClip_unkstruct* arg0, u16 arg1, f32 arg2, f32 arg3) {
    if ((func_809E85FC_jp(arg0, arg1, arg2, arg3) == false) && (func_809E8674_jp(arg0, arg1, arg2, arg3) == true)) {
        arg0->unk_02++;
    }
}

void func_809E87D4_jp(StructureClip_unkstruct* arg0, s16 arg1, u16 arg2, f32 arg3, f32 arg4) {
    if (func_809E8674_jp(arg0, arg2, arg3, arg4) == true) {
        arg0->unk_00 = arg1;
        arg0->unk_02 = 1;
        arg0->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

void func_809E8838_jp(StructureClip_unkstruct* arg0, s16 arg1, u16 arg2, f32 arg3, f32 arg4) {
    if (func_809E8674_jp(arg0, arg2, arg3, arg4) == true) {
        arg0->unk_00 = arg1;
        arg0->unk_02 = 1;
        arg0->unk_03 = 1;
        common_data.clip.structureClip->unk_C10 = 1;
    }
}

void func_809E889C_jp(StructureClip_unkstruct* arg0, s32 arg1, s16 arg2, u16 arg3, f32 arg4, f32 arg5) {
    StructureClip_unkstruct* ptr;
    s32 i;

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (arg2 == ptr->unk_00) {
            func_809E8768_jp(ptr, arg3, arg4, arg5);
            return;
        }
    }

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (ptr->unk_00 == -1) {
            func_809E87D4_jp(ptr, arg2, arg3, arg4, arg5);
            return;
        }
    }

    ptr = arg0;
    for (i = 0; i < arg1; i++, ptr++) {
        if (ptr->unk_02 == 0) {
            func_809E8838_jp(ptr, arg2, arg3, arg4, arg5);
            return;
        }
    }
}

s32 func_809E89AC_jp(StructureClip_unkstruct* arg0, Actor* actor) {
    StructureClip_unkstruct_unk_04* ptr = arg0->unk_04;
    s32 i;

    for (i = 0; i < 9; i++, ptr++) {
        if ((ptr->unk_0A == actor->fgName) && (ptr->unk_00 == actor->home.pos.x) &&
            (ptr->unk_04 == actor->home.pos.z)) {
            ptr->unk_00 = 0.0f;
            ptr->unk_04 = 0.0f;
            ptr->unk_0A = 0;
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
        if (ptr->unk_00 == arg2) {
            if (func_809E8BDC_jp(ptr, arg3) == true) {
                return;
            } else {
                return;
            }
        }
    }
}

s32 func_809E8C80_jp(StructureClip_unkstruct* arg0, s32 arg1, s16 arg2) {
    s32 i;
    s32 ret = -1;

    for (i = 0; i < arg1; i++, arg0++) {
        if ((arg0->unk_00 == arg2) && (arg0->unk_03 != 1)) {
            ret = i;
            break;
        }
    }

    return ret;
}

s32 func_809E8CD4_jp(s16 arg0) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_B0, 8, arg0);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_B0[index];

        return temp->unk_70;
    }

    return 0;
}

s32 func_809E8D44_jp(s16 arg0) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_454, 9, arg0);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_454[index];

        return temp->unk_70;
    }

    return 0;
}

s32 func_809E8DB4_jp(s16 arg0) {
    s32 index = func_809E8C80_jp(common_data.clip.structureClip->unk_86C, 8, arg0);

    if (index != -1) {
        StructureClip_unkstruct* temp = &common_data.clip.structureClip->unk_86C[index];

        return temp->unk_70;
    }

    return 0;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Structure/ac_structure/aSTR_setupActor_proc.s")

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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/actors/ovl_Structure/ac_structure/aSTR_init_clip_area.s")

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
    if (((this->unk_178 & 0xF000) >> 0xC) == 5) {
        StructureActor* structureActor =
            (StructureActor*)Actor_info_fgName_search(&game_play->actorInfo, this->unk_178, ACTOR_PART_0);

        if ((structureActor != NULL) && (structureActor->unk_2B0 == 0)) {
            structureActor->unk_2B0 = D_809E9A9C_jp[(this->unk_17A == 1)];
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
