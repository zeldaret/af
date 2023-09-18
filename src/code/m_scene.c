#include "global.h"
#include "m_scene.h"
//todo remove this
#include "m_common_data.h"
#include "TwoHeadArena.h"
#include "m_lib.h"
#include "m_submenu.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "game.h"
#include "code_variables.h"

//   mSc_set_bank_status_after
//   mSc_clear_bank_status
//   Object_Exchange_keep_new_Player
//   mSc_secure_exchange_keep_bank 
//   mSc_background_dmacopy_controller 
//   mSc_dmacopy_data_bank 
//   mSc_bank_regist_check 
//   mSc_regist_initial_exchange_bank 
//   mSc_dmacopy_all_exchange_bank_sub
//   mSc_dmacopy_all_exchange_bank 
//   mSc_data_bank_ct 
//   mSc_decide_exchange_bank 
//   Scene_player_select 
//   Scene_ct 
//   Scene_Proc_Player_Ptr 
//   Scene_Proc_Ctrl_Actor_Ptr 
//   Scene_Proc_Actor_Ptr 
//   Scene_Proc_Object_Exchange_Bank_Ptr 
//   Scene_Proc_Door_Data_Ptr 
//   Door_info_ct 
//   Scene_Proc_Sound 
//   set_item_info
//   Scene_Proc_Field_ct 
//   Scene_Proc_MyRoom_ct 
//   Scene_Proc_ArrangeRoom_ct 
//   Scene_Proc_ArrangeFurniture_ct 
//   goto_other_scene 
//   goto_next_scene 
//   goto_emu_game 
//   return_emu_game 

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C59B0_jp.s")
s32 func_800C59B0_jp(ObjectExchangeBank *objectBank)
{
    ObjectStatus *objectStatus = &objectBank->status[objectBank->unk17FC];
    s32 ret = -1;
    s32 statusIndex = objectBank->unk17FC;
    
    if (statusIndex < OBJECT_EXCHANGE_BANK_MAX)
    {
        do {
            if (objectStatus->id == 0)
            {
                ret = statusIndex;
                break;
            }
            objectStatus++;
            statusIndex++;
        } while (statusIndex != OBJECT_EXCHANGE_BANK_MAX);
    }
    return ret;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5A08_jp.s")
s32 func_800C5A08_jp(ObjectExchangeBank *objectBank)
{
    ObjectStatus* objectStatus = &objectBank->status[objectBank->unk17FC];
    s32 ret = -1;
    s32 statusIndex = objectBank->unk17FC;
    
    if (statusIndex < OBJECT_EXCHANGE_BANK_MAX)
    {
        do {
            if (objectStatus->unk50 == 0)
            {
                ret = statusIndex;
                break;
            }
            objectStatus++;
            statusIndex++;
        } while (statusIndex != OBJECT_EXCHANGE_BANK_MAX);
    }
    return ret;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5A60_jp.s")
s32 func_800C5A60_jp(ObjectExchangeBank* objectBank) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_800C59B0_jp(objectBank);
    var_v1 = temp_v0;
    if (temp_v0 == -1) {
        var_v1 = func_800C5A08_jp(objectBank);
    }
    return var_v1;
}

// s32 func_800C5AA0_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectBank, s16 arg2);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5AA0_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B30_jp.s")
void func_800C5B30_jp(ObjectStatus* objectStatus) {
    objectStatus->id = (objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id;
    objectStatus->unk53 = 0;
    objectStatus->segment = objectStatus->unk_08;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B5C_jp.s")
//mSc_clear_bank_status
void func_800C5B5C_jp(ObjectStatus *objectStatus)
{
    objectStatus->id = 0;
    objectStatus->size = 0;
    objectStatus->unk_08 = 0;
    objectStatus->segment = 0;
}

void func_80026E10_jp(void*, uintptr_t, size_t, const char *file, s32);         /* extern */
s32 func_800C5AA0_jp(void*, void*, s16);            /* extern */

//objectspawn equivalent
// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B74_jp.s")
s32 func_800C5B74_jp(ObjectExchangeBank* objectBank, s16 id) {
    s32 ret = 0;

    if (objectBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        ObjectStatus* objectStatus = &objectBank->status[objectBank->num];

        if (func_800C5AA0_jp(objectStatus, objectBank, id) == 1)
        {
            //DmaMgr_RequestSyncDebug
            //TODO set the right types for these pointers in the structs
            DmaMgr_RequestSyncDebug((void*)objectStatus->unk_08, objectStatus->vrom, objectStatus->size, "../m_scene.c", 317);
            func_800C5B30_jp(objectStatus);
            objectStatus->unk50 = 1;
            objectBank->num++;
            ret = 1;
        }
    }
    return ret;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5C30_jp.s")
void func_800B1784_jp(s32);                            /* extern */
void func_800B190C_jp(s32);                            /* extern */
void func_800B1960_jp(s32, s32, s32);                      /* extern */
void func_800B19C4_jp(s32, s32, s32);                      /* extern */
void func_800B1A28_jp(s32);                            /* extern */
void func_800B1A60_jp(s32);                            /* extern */

//Object_Exchange_keep_new_Player
void func_800C5C30_jp(s32 arg0)
{
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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5CC4_jp.s")
u32 func_800C5CC4_jp(ObjectExchangeBank* objectBank, s16 id, s32 size) {
    ObjectStatus* objectStatus = &objectBank->status[objectBank->num];
    u32 var_a3 = 0;
    
    if (objectBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        var_a3 = (objectBank->unk1800 + size + 0xF) & ~0xF;
        if (var_a3 >= objectBank->unk1804) {
            var_a3 = 0;
        } else {
            objectStatus->id = id;
            objectStatus->segment = objectBank->unk1800;
            objectStatus->unk_08 = objectBank->unk1800;
            objectStatus->vrom = 0;
            objectStatus->size = size;
            objectStatus->unk50 = 0;
            objectStatus->unk53 = 3;
            objectBank->unk1800 = var_a3;
            objectBank->num++;
        }
    }
    return var_a3;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5D68_jp.s")
// s32 func_800C5D68_jp(ObjectExchangeBank* objectBank) {
//     s32 temp_a2;
//     s32 temp_v0;
//     s32 var_a3;
//     s32 var_v1;
//     ObjectStatus* var_a1;

//     temp_v0 = objectBank->unk181C;
//     var_v1 = temp_v0;
//     if (common_data.unk10001 == 0) {
//         temp_a2 = objectBank->unk17FC;
//         var_a1 = &objectBank->status[temp_a2];
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

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5E10_jp.s")
void func_800C5E10_jp(ObjectExchangeBank *objectBank) {
    s32 temp_s3 = objectBank->unk181C;
    s32 var_s1 = objectBank->unk17FC;
    ObjectStatus* objectStatus = &objectBank->status[objectBank->unk17FC];
    
    if (var_s1 < OBJECT_EXCHANGE_BANK_MAX) {
        do {
            if ((objectStatus->id != 0) && (temp_s3 == objectStatus->unk52)) {
                func_800C5B5C_jp(objectStatus);
                objectStatus++;
            }
            var_s1++;
        } while (var_s1 != OBJECT_EXCHANGE_BANK_MAX);
    }
}

// s32 func_800C5D68_jp(ObjectExchangeBank* objectBank);

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5EA0_jp.s")
// void func_800C5EA0_jp(ObjectExchangeBank* objectBank) {
//     s32 temp_v0;
//     UNK_PTR* temp_v0_2;

//     if (objectBank->unk1820 == 1) {
//         temp_v0 = func_800C5D68_jp();
//         if (temp_v0 != objectBank->unk181C) {
//             objectBank->unk181C = temp_v0;
//             temp_v0_2 = objectBank + (temp_v0 * 4);
//             objectBank->unk1800 = temp_v0_2->unk1808;
//             objectBank->unk1804 = temp_v0_2->unk1810;
//             func_800C5E10_jp(objectBank);
//         }
//         objectBank->unk1820 = 0;
//     }
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5F0C_jp.s")
s32 func_800C5F0C_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectBank) {
    s32 var_v1 = 1;
    u32 temp_v0 = (objectBank->unk1800 + objectStatus->size + 0xF) & ~0xF;
    
    if (temp_v0 >= (u32) objectBank->unk1804) {
        var_v1 = 0;
    } else {
        objectStatus->unk_08 = objectBank->unk1800;
        objectStatus->unk52 = objectBank->unk181C;
        objectStatus->unk53 = 1;
        objectStatus->unk14 = 0;
        objectBank->unk1800 = temp_v0;
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
//                 func_800C5B5C_jp(var_s0->status);
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
//                 func_80026DCC_jp(&var_s0->status[0].unk14, var_s0->status[0].unk_08, var_s0->status[0].vrom, var_s0->status[0].size, 0, temp_s1, 0, "../m_scene.c", 0x265);
//                 var_s0->status[0].unk53 = 2;
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_bank_regist_check.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6144_jp.s")
s32 func_800C6144_jp(ObjectExchangeBank* objectBank, s16 arg1)
{
    s32 temp_v0;
    s32 ret = 0;

    temp_v0 = func_800C5A60_jp(objectBank);

    if (temp_v0 != -1)
    {
        ObjectStatus* temp_a0 = &objectBank->status[temp_v0];
        
        if (func_800C5AA0_jp(temp_a0, objectBank, arg1) == 1)
        {
            temp_a0->unk14 = 0;
            temp_a0->unk52 = objectBank->unk181C;
            ret = 1;
        }
    }

    return ret;
}

//playstate maybe??
typedef struct {
    /* 0x0000 */ char pad0[0x1EA7];
    /* 0x1EA7 */ UNK_TYPE unk1EA7;
    /* 0x1EA7 */ char pad[0x1EB4 - 0x1EA7];
    /* 0x1EB4 */ s16 unk1EB4;
    /* 0x1904 */ UNK_TYPE unk1904;
    /* 0x190C */ UNK_TYPE unk190C;
    /* 0x192C */ UNK_TYPE unk192C;

} unkStruct; // size = 

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_regist_initial_exchange_bank.s")
// void mSc_regist_initial_exchange_bank(unkStruct *arg0)
// {
//     ObjectExchangeBank *temp_s0;
//     s16 *var_s1;
//     s32 temp_a0;
//     s32 temp_a0_2;
//     s32 temp_v0;
//     s32 temp_v1;
//     s32 temp_v1_2;
//     s32 var_s2;
//     ObjectExchangeBank *temp_s0_2;

//     var_s1 = arg0->unk1EB4;
//     arg0->unk192C = 0;
//     var_s2 = 0;
//     arg0->unk190C = (s32) arg0->unk1904;
//     // if ((s32) arg0->unk1EA7 > 0)
//     // {
//         temp_s0 = arg0 + 0x110;
//         do
//         {
//             func_800C6144_jp(temp_s0, *var_s1);
//             var_s2 += 1;
//             var_s1 += 2;
//             temp_s0->num += 1;
//         } while (var_s2 < arg0->unk1EA7);
//     // }
//     temp_s0_2 = arg0 + 0x110;
//     if (common_data.unk_10001[0] == 0)
//     {
//         temp_a0 = temp_s0_2->unk1804;
//         temp_v1 = temp_s0_2->unk1800;
//         temp_s0_2->unk1814 = temp_a0;
//         temp_v0 = (temp_v1 + ((u32) (temp_a0 - temp_v1) >> 1) + 0xF) & ~0xF;
//         temp_s0_2->unk1810 = temp_v0;
//         temp_s0_2->unk180C = temp_v0;
//         temp_s0_2->unk1804 = temp_v0;
//         temp_s0_2->unk1808 = temp_v1;
//     }
//     else
//     {
//         temp_v1_2 = temp_s0_2->unk1800;
//         temp_a0_2 = temp_s0_2->unk1804;
//         temp_s0_2->unk1808 = temp_v1_2;
//         temp_s0_2->unk180C = temp_v1_2;
//         temp_s0_2->unk1810 = temp_a0_2;
//         temp_s0_2->unk1814 = temp_a0_2;
//     }
//     temp_s0_2->unk17FC = temp_s0_2->num;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C62C4_jp.s")
// void func_800C62C4_jp(ObjectStatus *objectStatus, ObjectExchangeBank *objectBank, s32 arg2)
// {
//     s32 temp_t3;
//     u32 var_a0;
//     u32 var_v1;
//     ObjectExchangeBank* temp_v0;

//     if (arg2 >= objectBank->unk17FC)
//     {
//         var_v1 = objectBank->unk1800;
//         var_a0 = (var_v1 + objectStatus->size + 0xF) & ~0xF;
//         if (var_a0 >= (u32) objectBank->unk1804)
//         {
//             temp_t3 = (s32) (objectBank->unk181C + 1) % 2;
//             objectBank->unk181C = temp_t3;
//             temp_v0 = objectBank + (temp_t3 * 4);
//             var_v1 = temp_v0->unk1808;
//             objectBank->unk1800 = var_v1;
//             objectBank->unk1804 = (u32) temp_v0->unk1810;
//             var_a0 = (var_v1 + objectStatus->size + 0xF) & ~0xF;
//         }
//         objectStatus->unk_08 = var_v1;
//         objectStatus->unk52 = (u8) objectBank->unk181C;
//         objectBank->unk1800 = var_a0;
//     }
//     func_80026E10_jp((void *)objectStatus->unk_08, objectStatus->vrom, objectStatus->size, "../m_scene.c", 828);
//     func_800C5B30_jp(objectStatus);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_dmacopy_all_exchange_bank.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_data_bank_ct.s")
void mSc_data_bank_ct(Game_Play* game_play, ObjectExchangeBank *objectBank)
{
    s32 temp_v0;
    u32 temp_v1;

    bzero(objectBank, 0x1824);
    objectBank->unk17F8 = -1;
    objectBank->unk17FC = -1;
    temp_v0 = THA_alloc16(&game_play->state.heap, 0x93400);
    temp_v1 = temp_v0 + 0x93400;
    objectBank->unk1800 = temp_v0;
    objectBank->unk1808 = temp_v0;
    objectBank->unk180C = temp_v0;
    objectBank->unk1804 = temp_v1;
    objectBank->unk1810 = temp_v1;
    objectBank->unk1814 = temp_v1;
    func_800C5B74_jp(objectBank, 3); //gameplay_keep object 3
    gSegments[4] = OS_PHYSICAL_TO_K0(objectBank->status[0].segment); 
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_decide_exchange_bank.s")
void mSc_decide_exchange_bank(ObjectExchangeBank *objectBank)
{
    objectBank->unk17F8 = objectBank->num;
    objectBank->unk1818 = objectBank->unk1800;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6690_jp.s")

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

//Scene_Proc_Door_Data_Ptr 
// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6A90_jp.s")
void func_800C6A90_jp(Game_Play *game_play, unkStruct2* arg1)
{
    UNK_PTR temp = arg1->unk4;

    game_play->unk_1E10 = arg1->unk1;
    game_play->unk_1E14 = Lib_SegmentedToVirtual(temp);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/Door_info_ct.s")
void Door_info_ct(s8 *arg0)
{
    *arg0 = 0;
}


// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AD0_jp.s")
void func_800C6AD0_jp(s32 arg0 UNUSED, UNK_TYPE arg1 UNUSED)
{

}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D5C_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6E14_jp.s")

void func_800C6E14_jp(Game *arg0)
{
    mem_copy(&common_data.unk_10754, &common_data.unk_107A0, 0x14U);
    common_data.unk_10754 = common_data.unk_107A0 + 1;
    arg0->unk_74 = 0;
    game_goto_next_game_play(arg0);
    common_data.unk_00014 = common_data.unk_107A0;
}

