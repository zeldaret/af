#include "unk.h"
#include "libc/stdint.h"
#include "m_scene.h"
#include "m_common_data.h"
#include "TwoHeadArena.h"
#include "m_lib.h"
#include "m_submenu.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "game.h"
#include "code_variables.h"
#include "m_object.h"
#include "m_player_lib.h"
#include "m_std_dma.h"

s32 func_800C59B0_jp(ObjectExchangeBank* objectExchangeBank) {
    ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->unk17FC];
    s32 ret = -1;
    s32 statusIndex = objectExchangeBank->unk17FC;

    if (statusIndex < OBJECT_EXCHANGE_BANK_MAX) {
        do {
            if (objectStatus->id == 0) {
                ret = statusIndex;
                break;
            }
            objectStatus++;
            statusIndex++;
        } while (statusIndex != OBJECT_EXCHANGE_BANK_MAX);
    }

    return ret;
}

s32 func_800C5A08_jp(ObjectExchangeBank* objectExchangeBank) {
    ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->unk17FC];
    s32 ret = -1;
    s32 statusIndex = objectExchangeBank->unk17FC;

    if (statusIndex < OBJECT_EXCHANGE_BANK_MAX) {
        do {
            if (objectStatus->unk50 == 0) {
                ret = statusIndex;
                break;
            }
            objectStatus++;
            statusIndex++;
        } while (statusIndex < OBJECT_EXCHANGE_BANK_MAX);
    }

    return ret;
}

s32 func_800C5A60_jp(ObjectExchangeBank* objectExchangeBank) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_800C59B0_jp(objectExchangeBank);
    var_v1 = temp_v0;

    if (temp_v0 == -1) {
        var_v1 = func_800C5A08_jp(objectExchangeBank);
    }

    return var_v1;
}

s32 func_800C5AA0_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank, s16 objectBankIndex) {
    s32 ret = 1;
    s32 objectSize = gObjectTable[objectBankIndex].vromEnd - gObjectTable[objectBankIndex].vromStart;
    u32 temp_t0 = (objectExchangeBank->unk1800 + objectSize + 0xF) & ~0xF;

    if (temp_t0 >= objectExchangeBank->unk1804) {
        ret = 0;

    } else {
        objectStatus->id = -objectBankIndex;
        objectStatus->unk_08 = objectExchangeBank->unk1800;
        objectStatus->segment = 0;
        objectStatus->vrom = gObjectTable[objectBankIndex].vromStart;
        objectStatus->size = objectSize;
        objectStatus->unk50 = 0;
        objectStatus->unk53 = 1;
        objectExchangeBank->unk1800 = temp_t0;
    }

    return ret;
}

void mSc_set_bank_status_after(ObjectStatus* objectStatus) {
    objectStatus->id = (objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id;
    objectStatus->unk53 = 0;
    objectStatus->segment = (void*)objectStatus->unk_08;
}

void mSc_clear_bank_status(ObjectStatus* objectStatus) {
    objectStatus->id = 0;
    objectStatus->size = 0;
    objectStatus->unk_08 = 0;
    objectStatus->segment = 0;
}

// object_spawn equivalent
s32 func_800C5B74_jp(ObjectExchangeBank* objectExchangeBank, s16 id) {
    s32 ret = 0;

    if (objectExchangeBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->num];

        if (func_800C5AA0_jp(objectStatus, objectExchangeBank, id) == 1) {

            DmaMgr_RequestSyncDebug((void*)objectStatus->unk_08, objectStatus->vrom, objectStatus->size, "../m_scene.c",
                                    317);
            mSc_set_bank_status_after(objectStatus);
            objectStatus->unk50 = 1;
            objectExchangeBank->num++;
            ret = 1;
        }
    }

    return ret;
}

void Object_Exchange_keep_new_Player(s32 arg0) {
    func_800B1784_jp(arg0);
    func_800B190C_jp(arg0);
    func_800B190C_jp(arg0);
    func_800B1960_jp(arg0, 0, 0);
    func_800B19C4_jp(arg0, 0, 0);
    func_800B1960_jp(arg0, 1, 2);
    func_800B19C4_jp(arg0, 1, 2);
    func_800B1A28_jp(arg0);
    func_800B1A28_jp(arg0);
    func_800B1A60_jp(arg0);
}

u32 mSc_secure_exchange_keep_bank(ObjectExchangeBank* objectExchangeBank, s16 id, s32 size) {
    ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->num];
    u32 ret = 0;

    if (objectExchangeBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        ret = (objectExchangeBank->unk1800 + size + 0xF) & ~0xF;
        if (ret >= objectExchangeBank->unk1804) {
            ret = 0;

        } else {
            objectStatus->id = id;
            objectStatus->segment = (void*)objectExchangeBank->unk1800;
            objectStatus->unk_08 = objectExchangeBank->unk1800;
            objectStatus->vrom = 0;
            objectStatus->size = size;
            objectStatus->unk50 = 0;
            objectStatus->unk53 = 3;
            objectExchangeBank->unk1800 = ret;
            objectExchangeBank->num++;
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5D68_jp.s")

void func_800C5E10_jp(ObjectExchangeBank* objectExchangeBank) {
    s32 temp_s3 = objectExchangeBank->unk181C;
    s32 var_s1 = objectExchangeBank->unk17FC;
    ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->unk17FC];

    if (var_s1 < OBJECT_EXCHANGE_BANK_MAX) {
        do {
            if ((objectStatus->id != 0) && (temp_s3 == objectStatus->unk52)) {
                mSc_clear_bank_status(objectStatus);
                objectStatus++;
            }
            var_s1++;
        } while (var_s1 < OBJECT_EXCHANGE_BANK_MAX);
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5EA0_jp.s")

s32 func_800C5F0C_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank) {
    s32 var_v1 = 1;
    u32 temp_v0 = (objectExchangeBank->unk1800 + objectStatus->size + 0xF) & ~0xF;

    if (temp_v0 >= (u32)objectExchangeBank->unk1804) {
        var_v1 = 0;

    } else {
        objectStatus->unk_08 = objectExchangeBank->unk1800;
        objectStatus->unk52 = objectExchangeBank->unk181C;
        objectStatus->unk53 = 1;
        objectStatus->unk14 = 0;
        objectExchangeBank->unk1800 = temp_v0;
    }

    return var_v1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_dmacopy_data_bank.s")

s32 mSc_bank_regist_check(ObjectExchangeBank* objectExchangeBank, s16 id) {
    ObjectStatus* objectStatus;
    s32 i;
    s32 ret = -1;

    for (i = 0; i < OBJECT_EXCHANGE_BANK_MAX; i++) {
        objectStatus = &objectExchangeBank->status[i];

        if (((objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id) == id) {
            ret = i;
            break;
        }
    }

    return ret;
}

s32 func_800C6144_jp(ObjectExchangeBank* objectExchangeBank, s16 arg1) {
    s32 temp_v0;
    s32 ret = 0;

    temp_v0 = func_800C5A60_jp(objectExchangeBank);

    if (temp_v0 != -1) {
        ObjectStatus* temp_a0 = &objectExchangeBank->status[temp_v0];

        if (func_800C5AA0_jp(temp_a0, objectExchangeBank, arg1) == 1) {
            temp_a0->unk14 = 0;
            temp_a0->unk52 = objectExchangeBank->unk181C;
            ret = 1;
        }
    }

    return ret;
}

void mSc_regist_initial_exchange_bank(Game_Play* game_play) {
    ObjectExchangeBank* objectExchangeBank = &game_play->objectExchangeBank;
    s16* var_s1 = game_play->unk_1EB4;
    s32 var_s2;

    objectExchangeBank->unk181C = 0;
    var_s2 = 0;
    objectExchangeBank->unk17FC = objectExchangeBank->num;

    if (game_play->unk_1EA7 > 0) {
        do {
            func_800C6144_jp(objectExchangeBank, *var_s1);
            var_s2 += 1;
            var_s1 += 1;
            objectExchangeBank->num += 1;
        } while (var_s2 < game_play->unk_1EA7);
    }

    if (common_data.unk_10001 == 0) {
        //! FAKE
        u32 temp = ((u32)(objectExchangeBank->unk1804 - objectExchangeBank->unk1800) >> 1);
        s32 temp_v0 = (objectExchangeBank->unk1800 + temp + 0xF) & ~0xF;

        objectExchangeBank->unk1814 = objectExchangeBank->unk1804;
        objectExchangeBank->unk1810 = temp_v0;
        objectExchangeBank->unk180C = temp_v0;
        objectExchangeBank->unk1804 = temp_v0;
        temp = objectExchangeBank->unk1800;
        objectExchangeBank->unk1808 = temp;

    } else {
        objectExchangeBank->unk1808 = objectExchangeBank->unk1800;
        objectExchangeBank->unk180C = objectExchangeBank->unk1800;
        objectExchangeBank->unk1810 = objectExchangeBank->unk1804;
        objectExchangeBank->unk1814 = objectExchangeBank->unk1804;
    }

    objectExchangeBank->unk17FC = objectExchangeBank->num;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C62C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_dmacopy_all_exchange_bank.s")

void mSc_data_bank_ct(Game_Play* game_play, ObjectExchangeBank* objectExchangeBank) {
    u32 temp_v0;
    u32 temp_v1;

    bzero(objectExchangeBank, 0x1824);
    objectExchangeBank->unk17F8 = -1;
    objectExchangeBank->unk17FC = -1;
    temp_v0 = (u32)THA_alloc16(&game_play->state.heap, 0x93400);
    temp_v1 = temp_v0 + 0x93400;
    objectExchangeBank->unk1800 = temp_v0;
    objectExchangeBank->unk1808 = temp_v0;
    objectExchangeBank->unk180C = temp_v0;
    objectExchangeBank->unk1804 = temp_v1;
    objectExchangeBank->unk1810 = temp_v1;
    objectExchangeBank->unk1814 = temp_v1;
    func_800C5B74_jp(objectExchangeBank, GAMEPLAY_KEEP);
    gSegments[4] = (uintptr_t)OS_PHYSICAL_TO_K0(objectExchangeBank->status[0].segment);
}

void mSc_decide_exchange_bank(ObjectExchangeBank* objectExchangeBank) {
    objectExchangeBank->unk17F8 = objectExchangeBank->num;
    objectExchangeBank->unk1818 = (void*)objectExchangeBank->unk1800;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/Scene_ct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/Scene_Proc_Player_Ptr.s")

void Scene_Proc_Ctrl_Actor_Ptr(Game_Play* game_play, MSceneUnkStruct* arg1) {
    void* temp = arg1->unk4;

    game_play->unk_1EA6 = arg1->unk1;
    game_play->unk_1EB0 = Lib_SegmentedToVirtual(temp);
}

void Scene_Proc_Actor_Ptr(Game_Play* game_play, MSceneUnkStruct* arg1) {
    void* temp = arg1->unk4;

    game_play->unk_1EA5 = arg1->unk1;
    game_play->unk_1EAC = Lib_SegmentedToVirtual(temp);
}

void Scene_Proc_Object_Exchange_Bank_Ptr(Game_Play* game_play, MSceneUnkStruct* arg1) {
    game_play->unk_1EA7 = arg1->unk1;
    game_play->unk_1EB4 = Lib_SegmentedToVirtual(arg1->unk4);
}

void Scene_Proc_Door_Data_Ptr(Game_Play* game_play, MSceneUnkStruct* arg1) {
    UNK_PTR temp = arg1->unk4;

    game_play->unk_1E10 = arg1->unk1;
    game_play->unk_1E14 = Lib_SegmentedToVirtual(temp);
}

void Door_info_ct(s8* arg0) {
    *arg0 = 0;
}

void Scene_Proc_Sound(UNK_TYPE arg0 UNUSED, UNK_TYPE arg1 UNUSED) {
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D5C_jp.s")

void return_emu_game(Game* game) {
    mem_copy((u8*)&common_data.unk_10754, (u8*)&common_data.unk_107A0, 0x14);
    common_data.unk_10754 = common_data.unk_107A0 + 1;
    game->unk_74 = 0;
    game_goto_next_game_play(game);
    common_data.sceneNo = common_data.unk_107A0;
}
