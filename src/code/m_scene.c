#include "global.h"
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

// mSc_set_bank_status_after
// mSc_clear_bank_status
// Object_Exchange_keep_new_Player
// mSc_secure_exchange_keep_bank
// mSc_background_dmacopy_controller
// mSc_dmacopy_data_bank
// mSc_bank_regist_check
// mSc_regist_initial_exchange_bank
// mSc_dmacopy_all_exchange_bank_sub
// mSc_dmacopy_all_exchange_bank
// mSc_data_bank_ct
// mSc_decide_exchange_bank
// Scene_player_select
// Scene_ct
// Scene_Proc_Player_Ptr
// Scene_Proc_Ctrl_Actor_Ptr
// Scene_Proc_Actor_Ptr
// Scene_Proc_Object_Exchange_Bank_Ptr
// Scene_Proc_Door_Data_Ptr
// Door_info_ct
// Scene_Proc_Sound
// set_item_info
// Scene_Proc_Field_ct
// Scene_Proc_MyRoom_ct
// Scene_Proc_ArrangeRoom_ct
// Scene_Proc_ArrangeFurniture_ct
// goto_other_scene
// goto_next_scene
// goto_emu_game
// return_emu_game

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
        } while (statusIndex != OBJECT_EXCHANGE_BANK_MAX);
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

void func_800C5B30_jp(ObjectStatus* objectStatus) {
    objectStatus->id = (objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id;
    objectStatus->unk53 = 0;
    objectStatus->segment = objectStatus->unk_08;
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

            DmaMgr_RequestSyncDebug(objectStatus->unk_08, objectStatus->vrom, objectStatus->size, "../m_scene.c", 317);
            func_800C5B30_jp(objectStatus);
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
    u32 var_a3 = 0;

    if (objectExchangeBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        var_a3 = (objectExchangeBank->unk1800 + size + 0xF) & ~0xF;
        if (var_a3 >= objectExchangeBank->unk1804) {
            var_a3 = 0;

        } else {
            objectStatus->id = id;
            objectStatus->segment = objectExchangeBank->unk1800;
            objectStatus->unk_08 = objectExchangeBank->unk1800;
            objectStatus->vrom = 0;
            objectStatus->size = size;
            objectStatus->unk50 = 0;
            objectStatus->unk53 = 3;
            objectExchangeBank->unk1800 = var_a3;
            objectExchangeBank->num++;
        }
    }

    return var_a3;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5D68_jp.s")
// s32 func_800C5D68_jp(ObjectExchangeBank* objectExchangeBank) {
//     s32 temp_a2;
//     s32 temp_v0;
//     s32 var_a3;
//     s32 var_v1;
//     ObjectStatus* var_a1;

//     temp_v0 = objectExchangeBank->unk181C;
//     var_v1 = temp_v0;
//     if (common_data.unk10001 == 0) {
//         temp_a2 = objectExchangeBank->unk17FC;
//         var_a1 = &objectExchangeBank->status[temp_a2];
//         var_v1 = (s32) (temp_v0 + 1) % 2;
//         var_a3 = temp_a2;
//         if (temp_a2 < 0x49) {
// loop_3:
//             var_a3 += 1;
//             if ((var_a1->id != 0) && (var_v1 == var_a1->unk52) && ((var_a1->unk50 != 0) || (var_a1->unk53 != 0))) {
//                 var_v1 = temp_v0;
//             } else {
//                 var_a1++;
//                 if (var_a3 != OBJECT_EXCHANGE_BANK_MAX) {
//                     goto loop_3;
//                 }
//             }
//         }
//     }
//     return var_v1;
// }

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
        } while (var_s1 != OBJECT_EXCHANGE_BANK_MAX);
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
// ? func_80026DCC_jp(s32 *, void *, u32, u32, s32, OSMesgQueue *, s32, ? *, s32); /* extern */
// ? func_800C5EA0_jp(ObjectExchangeBank *);               /* extern */

// void mSc_dmacopy_data_bank(ObjectExchangeBank *arg0)
// {
//     OSMesgQueue *temp_s1;
//     ObjectExchangeBank *var_s0;
//     s32 var_s2;
//     u8 temp_v0;

//     var_s0 = arg0;
//     func_800C5EA0_jp(arg0);
//     var_s2 = 0;
//     do
//     {
//         if ((var_s2 >= arg0->unk17FC) && (var_s0->status[0].id != 0) && (arg0->unk181C != var_s0->status[0].unk52))
//         {
//             if (var_s0->status[0].unk50 != 0)
//             {
//                 if (var_s0->status[0].unk53 != 2)
//                 {
//                     func_800C5F0C_jp(var_s0->status, arg0);
//                 }
//             }
//             else if (var_s0->status[0].unk53 == 0)
//             {
//                 mSc_clear_bank_status(var_s0->status);
//             }
//         }
//         temp_v0 = var_s0->status[0].unk53;
//         switch (temp_v0)                            /* irregular */
//         {
//         case 1:
//             temp_s1 = &var_s0->status[0].unk34;
//             if (var_s0->status[0].unk14 == 0)
//             {
//                 osCreateMesgQueue(temp_s1, &var_s0->status[0].unk4C, 1);
//                 func_80026DCC_jp(&var_s0->status[0].unk14, var_s0->status[0].unk_08, var_s0->status[0].vrom,
//                 var_s0->status[0].size, 0, temp_s1, 0, "../m_scene.c", 0x265); var_s0->status[0].unk53 = 2;
//             }
//             break;
//         case 2:
//             if (osRecvMesg(&var_s0->status[0].unk34, NULL, 0) == 0)
//             {
//                 func_800C5B30_jp(var_s0->status);
//             }
//             break;
//         }
//         var_s2 += 1;
//         var_s0 += 0x54;
//     } while (var_s2 != 0x49);
// }

s32 mSc_bank_regist_check(ObjectExchangeBank* objectExchangeBank, s16 arg1) {
    ObjectStatus* objectStatus;
    s32 i;
    s32 ret = -1;

    for (i = 0; i != OBJECT_EXCHANGE_BANK_MAX; i++) {
        objectStatus = &objectExchangeBank->status[i];

        if (((objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id) == arg1) {
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
// void func_800C62C4_jp(ObjectStatus *objectStatus, ObjectExchangeBank *objectExchangeBank, s32 arg2)
// {
//     s32 temp_t3;
//     u32 var_a0;
//     u32 var_v1;
//     ObjectExchangeBank* temp_v0;

//     if (arg2 >= objectExchangeBank->unk17FC)
//     {
//         var_v1 = objectExchangeBank->unk1800;
//         var_a0 = (var_v1 + objectStatus->size + 0xF) & ~0xF;
//         if (var_a0 >= (u32) objectExchangeBank->unk1804)
//         {
//             temp_t3 = (s32) (objectExchangeBank->unk181C + 1) % 2;
//             objectExchangeBank->unk181C = temp_t3;
//             temp_v0 = objectExchangeBank + (temp_t3 * 4);
//             var_v1 = temp_v0->unk1808;
//             objectExchangeBank->unk1800 = var_v1;
//             objectExchangeBank->unk1804 = (u32) temp_v0->unk1810;
//             var_a0 = (var_v1 + objectStatus->size + 0xF) & ~0xF;
//         }
//         objectStatus->unk_08 = var_v1;
//         objectStatus->unk52 = (u8) objectExchangeBank->unk181C;
//         objectExchangeBank->unk1800 = var_a0;
//     }
//     func_80026E10_jp((void *)objectStatus->unk_08, objectStatus->vrom, objectStatus->size, "../m_scene.c", 828);
//     func_800C5B30_jp(objectStatus);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_dmacopy_all_exchange_bank.s")

void mSc_data_bank_ct(Game_Play* game_play, ObjectExchangeBank* objectExchangeBank) {
    s32 temp_v0;
    u32 temp_v1;

    bzero(objectExchangeBank, 0x1824);
    objectExchangeBank->unk17F8 = -1;
    objectExchangeBank->unk17FC = -1;
    temp_v0 = THA_alloc16(&game_play->state.heap, 0x93400);
    temp_v1 = temp_v0 + 0x93400;
    objectExchangeBank->unk1800 = temp_v0;
    objectExchangeBank->unk1808 = temp_v0;
    objectExchangeBank->unk180C = temp_v0;
    objectExchangeBank->unk1804 = temp_v1;
    objectExchangeBank->unk1810 = temp_v1;
    objectExchangeBank->unk1814 = temp_v1;
    func_800C5B74_jp(objectExchangeBank, GAMEPLAY_KEEP);
    gSegments[4] = OS_PHYSICAL_TO_K0(objectExchangeBank->status[0].segment);
}

void mSc_decide_exchange_bank(ObjectExchangeBank* objectExchangeBank) {
    objectExchangeBank->unk17F8 = objectExchangeBank->num;
    objectExchangeBank->unk1818 = objectExchangeBank->unk1800;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6690_jp.s")
// Scene_player_select

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/Scene_ct.s")
// void func_800C6690_jp(s32, u16);
// extern UNK_TYPE D_8010DD80_jp;

// void Scene_ct(s32 arg0, u8 *arg1)
// {
//     u8 *var_s0;
//     u8 temp_v0;

//     var_s0 = arg1;
// loop_1:
//     temp_v0 = *var_s0;
//     if (temp_v0 != 0xA)
//     {
//         if (temp_v0 < 0xBU)
//         {
//             *(&D_8010DD80_jp + (temp_v0 * 4))(arg0, var_s0);
//         }
//         var_s0 += 8;
//         goto loop_1;
//     }
//     func_800C6690_jp(0x1B, 0xD01F);
//     func_800C6690_jp(0x22, 0xD06A);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C69F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6A28_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6A5C_jp.s")

typedef struct {
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0004 */ UNK_PTR unk4;
} unkStruct2;

// Scene_Proc_Door_Data_Ptr
void func_800C6A90_jp(Game_Play* game_play, unkStruct2* arg1) {
    UNK_PTR temp = arg1->unk4;

    game_play->unk_1E10 = arg1->unk1;
    game_play->unk_1E14 = Lib_SegmentedToVirtual(temp);
}

void Door_info_ct(s8* arg0) {
    *arg0 = 0;
}

void func_800C6AD0_jp(s32 arg0 UNUSED, UNK_TYPE arg1 UNUSED) {
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D5C_jp.s")

void func_800C6E14_jp(Game* arg0) {
    mem_copy(&common_data.unk_10754, &common_data.unk_107A0, 0x14U);
    common_data.unk_10754 = common_data.unk_107A0 + 1;
    arg0->unk_74 = 0;
    game_goto_next_game_play(arg0);
    common_data.unk_00014 = common_data.unk_107A0;
}
