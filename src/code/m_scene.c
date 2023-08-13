#include "global.h"
#include "m_scene.h"
//todo remove this
#include "m_common_data.h"
#include "TwoHeadArena.h"


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

//todo: maybe _MAX is better than _COUNT?
#define OBJECT_BANK_COUNT 73

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x04 */ s32 unk4; //ram_start
    /* 0x08 */ s32 segment;
    /* 0x0C */ uintptr_t vrom;
    /* 0x10 */ size_t size;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ char pad18[0x1C];
    /* 0x34 */ OSMesgQueue unk34;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
} ObjectBank; // size = 0x54

typedef struct {
    /* 0x0000 */ ObjectBank bank[OBJECT_BANK_COUNT];
    /* 0x17F4 */ s32 numberOfBanks;
    /* 0x17F8 */ s32 unk17F8;
    /* 0x17FC */ s32 unk17FC;
    /* 0x1800 */ s32 unk1800;
    /* 0x1804 */ u32 unk1804;
    /* 0x1808 */ s32 unk1808;
    /* 0x180C */ s32 unk180C;
    /* 0x1810 */ u32 unk1810;
    /* 0x1814 */ s32 unk1814;
    /* 0x1818 */ s32 unk1818;
    /* 0x181C */ s32 unk181C;
    /* 0x1820 */ s32 unk1820;
} ObjectExchange; // size = 

typedef struct {
    /* 0x0000 */ char unk0;
} DoorInfo;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C59B0_jp.s")
s32 func_800C59B0_jp(ObjectExchange *objectExchange)
{
    ObjectBank *bank = &objectExchange->bank[objectExchange->unk17FC];
    s32 ret = -1;
    s32 bankIndex = objectExchange->unk17FC;
    
    if (bankIndex < OBJECT_BANK_COUNT)
    {
        do {
            if (bank->id == 0)
            {
                ret = bankIndex;
                break;
            }
            bank++;
            bankIndex++;
        } while (bankIndex != OBJECT_BANK_COUNT);
    }
  return ret;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5A08_jp.s")


s32 func_800C5A08_jp(ObjectExchange* objectExchange);                          /* extern */

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5A60_jp.s")
s32 func_800C5A60_jp(ObjectExchange* objectExchange) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_800C59B0_jp(objectExchange);
    var_v1 = temp_v0;
    if (temp_v0 == -1) {
        var_v1 = func_800C5A08_jp(objectExchange);
    }
    return var_v1;
}

// s32 func_800C5AA0_jp(ObjectBank* objectBank, ObjectExchange* objectExchange, s16 arg2);
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5AA0_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B30_jp.s")
void func_800C5B30_jp(ObjectBank* objectBank) {
    objectBank->id = (objectBank->id >= 0) ? objectBank->id : -objectBank->id;
    objectBank->unk53 = 0;
    objectBank->unk4 = objectBank->segment;
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B5C_jp.s")
//mSc_clear_bank_status
void func_800C5B5C_jp(ObjectBank *objectBank)
{
    objectBank->id = 0;
    objectBank->size = 0;
    objectBank->segment = 0;
    objectBank->unk4 = 0;
}

void func_80026E10_jp(void*, uintptr_t, size_t, const char *file, s32);         /* extern */
s32 func_800C5AA0_jp(void*, void*, s16);            /* extern */

//objectspawn?
// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5B74_jp.s")
s32 func_800C5B74_jp(ObjectExchange* objectExchange, s16 id) {
    s32 ret = 0;

    if (objectExchange->numberOfBanks < OBJECT_BANK_COUNT) {
        ObjectBank* objectBank = &objectExchange->bank[objectExchange->numberOfBanks];

        if (func_800C5AA0_jp(objectBank, objectExchange, id) == 1)
        {
            //DmaMgr_RequestSyncDebug
            //TODO set the right types for these pointers in the structs
            func_80026E10_jp((void*)objectBank->segment, objectBank->vrom, objectBank->size, "../m_scene.c", 317);
            func_800C5B30_jp(objectBank);
            objectBank->unk50 = 1;
            objectExchange->numberOfBanks++;
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
u32 func_800C5CC4_jp(ObjectExchange* objectExchange, s16 id, s32 size) {
    ObjectBank* objectBank = &objectExchange->bank[objectExchange->numberOfBanks];
    u32 var_a3 = 0;
    
    if (objectExchange->numberOfBanks < OBJECT_BANK_COUNT) {
        var_a3 = (objectExchange->unk1800 + size + 0xF) & ~0xF;
        if (var_a3 >= objectExchange->unk1804) {
            var_a3 = 0;
        } else {
            objectBank->id = id;
            objectBank->unk4 = objectExchange->unk1800;
            objectBank->segment = objectExchange->unk1800;
            objectBank->vrom = 0;
            objectBank->size = size;
            objectBank->unk50 = 0;
            objectBank->unk53 = 3;
            objectExchange->unk1800 = var_a3;
            objectExchange->numberOfBanks++;
        }
    }
    return var_a3;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5D68_jp.s")
// s32 func_800C5D68_jp(ObjectExchange* objectExchange) {
//     s32 temp_a2;
//     s32 temp_v0;
//     s32 var_a3;
//     s32 var_v1;
//     ObjectBank* var_a1;

//     temp_v0 = objectExchange->unk181C;
//     var_v1 = temp_v0;
//     if (common_data.unk10001 == 0) {
//         temp_a2 = objectExchange->unk17FC;
//         var_a1 = &objectExchange->bank[temp_a2];
//         var_v1 = (s32) (temp_v0 + 1) % 2;
//         var_a3 = temp_a2;
//         if (temp_a2 < 0x49) {
// loop_3:
//             var_a3 += 1;
//             if ((var_a1->id != 0) && (var_v1 == var_a1->unk52) && ((var_a1->unk50 != 0) || (var_a1->unk53 != 0))) {
//                 var_v1 = temp_v0;
//             } else {
//                 var_a1++;
//                 if (var_a3 != OBJECT_BANK_COUNT) {
//                     goto loop_3;
//                 }
//             }
//         }
//     }
//     return var_v1;
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5E10_jp.s")
void func_800C5E10_jp(ObjectExchange *objectExchange) {
    s32 temp_s3 = objectExchange->unk181C;
    s32 var_s1 = objectExchange->unk17FC;
    ObjectBank* objectBank = &objectExchange->bank[objectExchange->unk17FC];
    
    if (var_s1 < OBJECT_BANK_COUNT) {
        do {
            if ((objectBank->id != 0) && (temp_s3 == objectBank->unk52)) {
                func_800C5B5C_jp(objectBank);
                objectBank++;
            }
            var_s1++;
        } while (var_s1 != OBJECT_BANK_COUNT);
    }
}

// s32 func_800C5D68_jp(ObjectExchange* objectExchange);

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5EA0_jp.s")
// void func_800C5EA0_jp(ObjectExchange* objectExchange) {
//     s32 temp_v0;
//     UNK_PTR* temp_v0_2;

//     if (objectExchange->unk1820 == 1) {
//         temp_v0 = func_800C5D68_jp();
//         if (temp_v0 != objectExchange->unk181C) {
//             objectExchange->unk181C = temp_v0;
//             temp_v0_2 = objectExchange + (temp_v0 * 4);
//             objectExchange->unk1800 = temp_v0_2->unk1808;
//             objectExchange->unk1804 = temp_v0_2->unk1810;
//             func_800C5E10_jp(objectExchange);
//         }
//         objectExchange->unk1820 = 0;
//     }
// }

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5F0C_jp.s")
s32 func_800C5F0C_jp(ObjectBank* objectBank, ObjectExchange* objectExchange) {
    s32 var_v1 = 1;
    u32 temp_v0 = (objectExchange->unk1800 + objectBank->size + 0xF) & ~0xF;
    
    if (temp_v0 >= (u32) objectExchange->unk1804) {
        var_v1 = 0;
    } else {
        objectBank->segment = objectExchange->unk1800;
        objectBank->unk52 = objectExchange->unk181C;
        objectBank->unk53 = 1;
        objectBank->unk14 = 0;
        objectExchange->unk1800 = temp_v0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C5F64_jp.s")
// ? func_80026DCC_jp(s32 *, void *, u32, u32, s32, OSMesgQueue *, s32, ? *, s32); /* extern */
// ? func_800C5EA0_jp(ObjectExchange *);               /* extern */

// void func_800C5F64_jp(ObjectExchange *arg0)
// {
//     OSMesgQueue *temp_s1;
//     ObjectExchange *var_s0;
//     s32 var_s2;
//     u8 temp_v0;

//     var_s0 = arg0;
//     func_800C5EA0_jp(arg0);
//     var_s2 = 0;
//     do
//     {
//         if ((var_s2 >= arg0->unk17FC) && (var_s0->bank[0].id != 0) && (arg0->unk181C != var_s0->bank[0].unk52))
//         {
//             if (var_s0->bank[0].unk50 != 0)
//             {
//                 if (var_s0->bank[0].unk53 != 2)
//                 {
//                     func_800C5F0C_jp(var_s0->bank, arg0);
//                 }
//             }
//             else if (var_s0->bank[0].unk53 == 0)
//             {
//                 func_800C5B5C_jp(var_s0->bank);
//             }
//         }
//         temp_v0 = var_s0->bank[0].unk53;
//         switch (temp_v0)                            /* irregular */
//         {
//         case 1:
//             temp_s1 = &var_s0->bank[0].unk34;
//             if (var_s0->bank[0].unk14 == 0)
//             {
//                 osCreateMesgQueue(temp_s1, &var_s0->bank[0].unk4C, 1);
//                 func_80026DCC_jp(&var_s0->bank[0].unk14, var_s0->bank[0].segment, var_s0->bank[0].vrom, var_s0->bank[0].size, 0, temp_s1, 0, "../m_scene.c", 0x265);
//                 var_s0->bank[0].unk53 = 2;
//             }
//             break;
//         case 2:
//             if (osRecvMesg(&var_s0->bank[0].unk34, NULL, 0) == 0)
//             {
//                 func_800C5B30_jp(var_s0->bank);
//             }
//             break;
//         }
//         var_s2 += 1;
//         var_s0 += 0x54;
//     } while (var_s2 != 0x49);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/mSc_bank_regist_check.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6144_jp.s")
s32 func_800C6144_jp(ObjectExchange* objectExchange, s16 arg1)
{
    s32 temp_v0;
    s32 ret = 0;

    temp_v0 = func_800C5A60_jp(objectExchange);

    if (temp_v0 != -1)
    {
        ObjectBank* temp_a0 = &objectExchange->bank[temp_v0];
        
        if (func_800C5AA0_jp(temp_a0, objectExchange, arg1) == 1)
        {
            temp_a0->unk14 = 0;
            temp_a0->unk52 = objectExchange->unk181C;
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
//     ObjectExchange *temp_s0;
//     s16 *var_s1;
//     s32 temp_a0;
//     s32 temp_a0_2;
//     s32 temp_v0;
//     s32 temp_v1;
//     s32 temp_v1_2;
//     s32 var_s2;
//     ObjectExchange *temp_s0_2;

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
//             temp_s0->numberOfBanks += 1;
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
//     temp_s0_2->unk17FC = temp_s0_2->numberOfBanks;
// }


#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C62C4_jp.s")
// void func_800C62C4_jp(ObjectBank *objectBank, ObjectExchange *objectExchange, s32 arg2)
// {
//     s32 temp_t3;
//     u32 var_a0;
//     u32 var_v1;
//     ObjectExchange* temp_v0;

//     if (arg2 >= objectExchange->unk17FC)
//     {
//         var_v1 = objectExchange->unk1800;
//         var_a0 = (var_v1 + objectBank->size + 0xF) & ~0xF;
//         if (var_a0 >= (u32) objectExchange->unk1804)
//         {
//             temp_t3 = (s32) (objectExchange->unk181C + 1) % 2;
//             objectExchange->unk181C = temp_t3;
//             temp_v0 = objectExchange + (temp_t3 * 4);
//             var_v1 = temp_v0->unk1808;
//             objectExchange->unk1800 = var_v1;
//             objectExchange->unk1804 = (u32) temp_v0->unk1810;
//             var_a0 = (var_v1 + objectBank->size + 0xF) & ~0xF;
//         }
//         objectBank->segment = var_v1;
//         objectBank->unk52 = (u8) objectExchange->unk181C;
//         objectExchange->unk1800 = var_a0;
//     }
//     func_80026E10_jp((void *)objectBank->segment, objectBank->vrom, objectBank->size, "../m_scene.c", 828);
//     func_800C5B30_jp(objectBank);
// }

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C639C_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C65E4_jp.s")
extern s32 B_801458B0_jp;

typedef struct {
    /* 0x00 */ char pad0[0x78];
    /* 0x78 */ TwoHeadArena tha;
} unkStruct2; // size = 0x54

void func_800C65E4_jp(s32 arg0, ObjectExchange *arg1)
{
    s32 temp_v0;
    u32 temp_v1;

    bzero(arg1, 0x1824);
    arg1->unk17F8 = -1;
    arg1->unk17FC = -1;
    temp_v0 = THA_alloc16(arg0 + 0x78, 0x93400);
    temp_v1 = temp_v0 + 0x93400;
    arg1->unk1800 = temp_v0;
    arg1->unk1808 = temp_v0;
    arg1->unk180C = temp_v0;
    arg1->unk1804 = temp_v1;
    arg1->unk1810 = temp_v1;
    arg1->unk1814 = temp_v1;
    func_800C5B74_jp(arg1, 3);
    B_801458B0_jp = OS_PHYSICAL_TO_K0(arg1->bank[0].unk4);
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6678_jp.s")
void func_800C6678_jp(ObjectExchange *objectExchange)
{
    objectExchange->unk17F8 = objectExchange->numberOfBanks;
    objectExchange->unk1818 = objectExchange->unk1800;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C68C8_jp.s")
// void func_800C6690_jp(s32, u16);
// extern UNK_TYPE D_8010DD80_jp;

// void func_800C68C8_jp(s32 arg0, u8 *arg1)
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6A90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6AE0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6B50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6BF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6C10_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D14_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_scene/func_800C6E14_jp.s")
