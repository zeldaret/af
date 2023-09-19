#ifndef M_SCENE_H
#define M_SCENE_H

#include "ultra64.h"
#include "z64math.h"

struct Game_Play;

typedef struct ActorEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ Vec3s pos;
    /* 0x8 */ Vec3s rot;
    /* 0xE */ s16 params;
} ActorEntry; // size = 0x10

typedef struct ObjectStatus {
    /* 0x00 */ s16 id;
    /* 0x04 */ void* segment;
    /* 0x08 */ UNK_TYPE unk_08;
    /* 0x0C */ uintptr_t vrom;
    /* 0x10 */ size_t size;
    /* 0x14 */ UNK_TYPE unk14;
    /* 0x18 */ char pad18[0x1C];
    /* 0x34 */ OSMesgQueue unk34;
    /* 0x4C */ UNK_TYPE unk4C;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
} ObjectStatus; // size = 0x54

#define OBJECT_EXCHANGE_BANK_MAX 73 // Name taken from oot debug string

typedef struct ObjectExchangeBank {
    /* 0x0000 */ ObjectStatus status[OBJECT_EXCHANGE_BANK_MAX]; // Name taken from oot debug string
    /* 0x17F4 */ s32 num; // Name taken from oot debug string
    /* 0x17F8 */ UNK_TYPE unk17F8;
    /* 0x17FC */ UNK_TYPE unk17FC;
    /* 0x1800 */ UNK_TYPE unk1800;
    /* 0x1804 */ UNK_TYPE unk1804;
    /* 0x1808 */ UNK_TYPE unk1808;
    /* 0x180C */ UNK_TYPE unk180C;
    /* 0x1810 */ UNK_TYPE unk1810;
    /* 0x1814 */ UNK_TYPE unk1814;
    /* 0x1818 */ UNK_PTR unk1818;
    /* 0x181C */ UNK_TYPE unk181C;
    /* 0x1820 */ UNK_TYPE unk1820;
} ObjectExchangeBank; // size = 0x1824

typedef struct {
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0004 */ UNK_PTR unk4;
} unkStruct;

s32 func_800C59B0_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5A08_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5A60_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5AA0_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank, s16 objectBankIndex);
void func_800C5B30_jp(ObjectStatus* objectStatus);
void mSc_clear_bank_status(ObjectStatus* objectStatus);
s32 func_800C5B74_jp(ObjectExchangeBank* objectExchangeBank, s16 id);
void Object_Exchange_keep_new_Player(s32 arg0);
u32 mSc_secure_exchange_keep_bank(ObjectExchangeBank* objectExchangeBank, s16 id, s32 size);
void func_800C5D68_jp(ObjectExchangeBank*);
void func_800C5E10_jp(ObjectExchangeBank* objectExchangeBank);
// void func_800C5EA0_jp();
s32 func_800C5F0C_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank);
void mSc_dmacopy_data_bank(ObjectExchangeBank* objectExchangeBank);
s32 mSc_bank_regist_check(ObjectExchangeBank* objectExchangeBank, s16 id);
s32 func_800C6144_jp(ObjectExchangeBank* objectExchangeBank, s16 arg1);
void mSc_regist_initial_exchange_bank(struct Game_Play* game_play);
void func_800C62C4_jp(ObjectStatus*, ObjectExchangeBank*, s32);
void mSc_dmacopy_all_exchange_bank(ObjectExchangeBank* objectExchangeBank);
void mSc_data_bank_ct(struct Game_Play* game_play, ObjectExchangeBank* objectExchangeBank);
void mSc_decide_exchange_bank(ObjectExchangeBank* objectExchangeBank);
// void func_800C6690_jp();
void Scene_ct(struct Game_Play* game_play, void* arg1);
// void func_800C6960_jp();
void Scene_Proc_Ctrl_Actor_Ptr(struct Game_Play* /*game_play*/, unkStruct* /*arg1*/);
void Scene_Proc_Actor_Ptr(struct Game_Play* /*game_play*/, unkStruct* /*arg1*/);
void Scene_Proc_Object_Exchange_Bank_Ptr(struct Game_Play* /*game_play*/, unkStruct* /*arg1*/);
void Scene_Proc_Door_Data_Ptr(struct Game_Play* /*game_play*/, unkStruct* /*arg1*/);
void Door_info_ct(s8* arg0);
void Scene_Proc_Sound(UNK_TYPE arg0, UNK_TYPE arg1);
// void func_800C6AE0_jp();
// void func_800C6B50_jp();
// void func_800C6BB0_jp();
// void func_800C6BD4_jp();
// void func_800C6BF8_jp();
// void func_800C6C10_jp();
// void func_800C6D14_jp();
// void func_800C6D5C_jp();
// void func_800C6E14_jp();

#endif
