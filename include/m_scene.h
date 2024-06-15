#ifndef M_SCENE_H
#define M_SCENE_H

#include "ultra64.h"
#include "z64math.h"
#include "libc/stdint.h"
#include "m_std_dma.h"

struct Game_Play;
struct Game;

typedef struct ActorEntry {
    /* 0x0 */ s16 id;
    /* 0x2 */ s_xyz pos;
    /* 0x8 */ s_xyz rot;
    /* 0xE */ s16 params;
} ActorEntry; // size = 0x10

typedef struct ObjectStatus {
    /* 0x00 */ s16 id;
    /* 0x04 */ u8* segment;
    /* 0x08 */ void* vram;
    /* 0x0C */ uintptr_t vrom;
    /* 0x10 */ size_t size;
    /* 0x14 */ DmaRequest unk14;
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
    /* 0x1808 */ s32 unk1808[2];
    /* 0x1810 */ s32 unk1810[2];
    /* 0x1818 */ UNK_PTR unk1818;
    /* 0x181C */ UNK_TYPE unk181C;
    /* 0x1820 */ UNK_TYPE unk1820;
} ObjectExchangeBank; // size = 0x1824

typedef struct DoorData {
    /* 0x00 */ s32 nextSceneId;
    /* 0x04 */ u8 exitOrientation;
    /* 0x05 */ u8 exitType;
    /* 0x06 */ u16 params;
    /* 0x08 */ s_xyz exitPos;
    /* 0x0E */ u16 fgName;
    /* 0x10 */ u8 wipeType;
    /* 0x11 */ u8 alignment[3];
} DoorData; // size = 0x14

typedef struct DoorInfo {
    /* 0x00 */ u8 numDoors;
    /* 0x04 */ DoorData* doorDataPtr;
} DoorInfo; // size = 0x8

typedef struct SceneDataDoor {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 numDoors;
    /* 0x04 */ DoorData* doorDataPtr;
} SceneDataDoor; // size = 0x8

typedef struct SceneDataActor {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 numActors;
    /* 0x04 */ ActorEntry* actorDataPtr; 
} SceneDataActor; // size = 0x8

typedef struct SceneDataCtrlActor {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 numCtrlActors;
    /* 0x04 */ s16* ctrlActorDataPtr; 
} SceneDataCtrlActor; // size = 0x8

typedef struct SceneDataObjectBank {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 numBanks;
    /* 0x04 */ s16* banksDataPtr;
} SceneDataObjectBank; // size = 0x8


typedef struct SceneDataField {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 itemType;
    /* 0x02 */ u8 bgNum;
    /* 0x04 */ u16 bgDispSize;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 drawType;
} SceneDataField; // size = 0x8

typedef struct SceneDataArrangeFtr {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 arrangeFtrNum;
} SceneDataArrangeFtr; // size = 0x2

typedef struct SceneDataMisc {
    /* 0x01 */ u8 type;
} SceneDataMisc; // size = 0x1

typedef union SceneData {
    SceneDataMisc misc;
    SceneDataActor actor;
    SceneDataCtrlActor controlActor;
    SceneDataObjectBank objectBank;
    SceneDataDoor doorData;
    SceneDataField field;
    SceneDataArrangeFtr arrangeFtr;
} SceneData; // size = 0x8

s32 func_800C59B0_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5A08_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5A60_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5AA0_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank, s16 objectBankIndex);
void mSc_set_bank_status_after(ObjectStatus* objectStatus);
void mSc_clear_bank_status(ObjectStatus* objectStatus);
s32 func_800C5B74_jp(ObjectExchangeBank* objectExchangeBank, s16 id);
void Object_Exchange_keep_new_Player(struct Game_Play* arg0);
u32 mSc_secure_exchange_keep_bank(ObjectExchangeBank* objectExchangeBank, s16 id, s32 size);
s32 func_800C5D68_jp(ObjectExchangeBank* objectExchangeBank);
void func_800C5E10_jp(ObjectExchangeBank* objectExchangeBank);
void func_800C5EA0_jp(ObjectExchangeBank* objectExchangeBank);
s32 func_800C5F0C_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank);
void mSc_dmacopy_data_bank(ObjectExchangeBank* objectExchangeBank);
s32 mSc_bank_regist_check(ObjectExchangeBank* objectExchangeBank, s16 id);
s32 func_800C6144_jp(ObjectExchangeBank* objectExchangeBank, s16 arg1);
void mSc_regist_initial_exchange_bank(struct Game_Play* game_play);
void mSc_dmacopy_all_exchange_bank_sub(ObjectStatus* status, ObjectExchangeBank* objectExchangeBank, s32 idx);
void mSc_dmacopy_all_exchange_bank(ObjectExchangeBank* exchange);
void mSc_data_bank_ct(struct Game_Play* game_play, ObjectExchangeBank* objectExchangeBank);
void mSc_decide_exchange_bank(ObjectExchangeBank* objectExchangeBank);
void Scene_player_select(s32 sceneNo, s32 npcActor);
void Scene_ct(struct Game_Play* play, SceneData* sceneData);
void Scene_Proc_Player_Ptr(struct Game_Play* play, SceneData* scene_data);
void Scene_Proc_CtrlActor_Ptr(struct Game_Play* play, SceneData* scene_data);
void Scene_Proc_Actor_Ptr(struct Game_Play* play, SceneData* scene_data);
void Scene_Proc_Object_Exchange_Bank_Ptr(struct Game_Play* play, SceneData* scene_data);
void Scene_Proc_Door_Data_Ptr(struct Game_Play* play, SceneData* scene_data);
void Door_info_ct(DoorInfo* door_info);
void Scene_Proc_Sound(struct Game_Play* play, SceneData* scene_data);
void set_item_info(struct Game_Play* play, SceneDataField* field);
void Scene_Proc_Field_ct(struct Game_Play* play, SceneData* scene_data);
void Scene_Proc_ArrangeRoom_ct(struct Game_Play* play, SceneData* data);
void Scene_Proc_ArrangeFurniture_ct(struct Game_Play* play, SceneData* data);
s32 goto_other_scene(struct Game_Play* play, DoorData* door_data, s32 updatePlayer);
s32 goto_next_scene(struct Game_Play* play, s32 nextScene, s32 updatePlayer);
s32 goto_emu_game(struct Game_Play* play, s16 famicomRomId);
void return_emu_game(struct Game* game);

#endif
