#include "overlays/actors/ovl_Weather/ac_weather.h"
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
#include "m_scene_table.h"
#include "m_scene_ftr.h"
#include "m_player_lib.h"
#include "overlays/actors/player_actor/m_player.h"

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
    s32 ret;

    ret = func_800C59B0_jp(objectExchangeBank);

    if (ret == -1) {
        ret = func_800C5A08_jp(objectExchangeBank);
    }

    return ret;
}

s32 func_800C5AA0_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank, s16 objectBankIndex) {
    s32 ret = 1;
    s32 objectSize = gObjectTable[objectBankIndex].vromEnd - gObjectTable[objectBankIndex].vromStart;
    u32 alignedSize = ALIGN16(objectExchangeBank->unk1800 + objectSize);

    if (alignedSize >= objectExchangeBank->unk1804) {
        ret = 0;

    } else {
        objectStatus->id = -objectBankIndex;
        objectStatus->vram = (void*)objectExchangeBank->unk1800;
        objectStatus->segment = 0;
        objectStatus->vrom = gObjectTable[objectBankIndex].vromStart;
        objectStatus->size = objectSize;
        objectStatus->unk50 = 0;
        objectStatus->unk53 = 1;
        objectExchangeBank->unk1800 = alignedSize;
    }

    return ret;
}

void mSc_set_bank_status_after(ObjectStatus* objectStatus) {
    objectStatus->id = (objectStatus->id >= 0) ? objectStatus->id : -objectStatus->id;
    objectStatus->unk53 = 0;
    objectStatus->segment = objectStatus->vram;
}

void mSc_clear_bank_status(ObjectStatus* objectStatus) {
    objectStatus->id = 0;
    objectStatus->size = 0;
    objectStatus->vram = NULL;
    objectStatus->segment = NULL;
}

s32 func_800C5B74_jp(ObjectExchangeBank* objectExchangeBank, s16 id) {
    s32 ret = 0;

    if (objectExchangeBank->num < OBJECT_EXCHANGE_BANK_MAX) {
        ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->num];

        if (func_800C5AA0_jp(objectStatus, objectExchangeBank, id) == 1) {
            DmaMgr_RequestSyncDebug(objectStatus->vram, objectStatus->vrom, objectStatus->size, "../m_scene.c", 317);
            mSc_set_bank_status_after(objectStatus);
            objectStatus->unk50 = 1;
            objectExchangeBank->num++;
            ret = 1;
        }
    }

    return ret;
}

void Object_Exchange_keep_new_Player(Game_Play* arg0) {
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
        ret = ALIGN16(objectExchangeBank->unk1800 + size);
        if (ret >= objectExchangeBank->unk1804) {
            ret = 0;

        } else {
            objectStatus->id = id;
            objectStatus->segment = (u8*)objectExchangeBank->unk1800;
            objectStatus->vram = (void*)objectExchangeBank->unk1800;
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

s32 func_800C5D68_jp(ObjectExchangeBank* objectExchangeBank) {
    ObjectStatus* objectStatus;
    s32 res = objectExchangeBank->unk181C;

    if (common_data.unk_10001 == 0) {
        s32 i;
        objectStatus = &objectExchangeBank->status[objectExchangeBank->unk17FC];
        res = (objectExchangeBank->unk181C + 1) % 2;
        for (i = objectExchangeBank->unk17FC; i < OBJECT_EXCHANGE_BANK_MAX; i++) {
            if ((objectStatus->id != 0) && (res == objectStatus->unk52) &&
                ((objectStatus->unk50 != 0) || (objectStatus->unk53 != 0))) {
                res = objectExchangeBank->unk181C;
                break;
            }

            objectStatus++;
        }
    }

    return res;
}

void func_800C5E10_jp(ObjectExchangeBank* objectExchangeBank) {
    s32 temp_s3 = objectExchangeBank->unk181C;
    s32 statusIndex = objectExchangeBank->unk17FC;
    ObjectStatus* objectStatus = &objectExchangeBank->status[objectExchangeBank->unk17FC];

    if (statusIndex < OBJECT_EXCHANGE_BANK_MAX) {
        do {
            if ((objectStatus->id != 0) && (temp_s3 == objectStatus->unk52)) {
                mSc_clear_bank_status(objectStatus);
                objectStatus++;
            }
            statusIndex++;
        } while (statusIndex < OBJECT_EXCHANGE_BANK_MAX);
    }
}

void func_800C5EA0_jp(ObjectExchangeBank* objectExchangeBank) {
    if (objectExchangeBank->unk1820 == 1) {
        s32 res = func_800C5D68_jp(objectExchangeBank);
        if (res != objectExchangeBank->unk181C) {
            objectExchangeBank->unk181C = res;

            objectExchangeBank->unk1800 = objectExchangeBank->unk1808[res];
            objectExchangeBank->unk1804 = objectExchangeBank->unk1810[res];

            func_800C5E10_jp(objectExchangeBank);
        }
        objectExchangeBank->unk1820 = 0;
    }
}

s32 func_800C5F0C_jp(ObjectStatus* objectStatus, ObjectExchangeBank* objectExchangeBank) {
    s32 res = 1;
    u32 alignedRam = ALIGN16(objectExchangeBank->unk1800 + objectStatus->size);

    if (alignedRam >= (u32)objectExchangeBank->unk1804) {
        res = 0;

    } else {
        objectStatus->vram = (void*)objectExchangeBank->unk1800;
        objectStatus->unk52 = objectExchangeBank->unk181C;
        objectStatus->unk53 = 1;
        objectStatus->unk14.vrom = 0;
        objectExchangeBank->unk1800 = alignedRam;
    }

    return res;
}

void mSc_dmacopy_data_bank(ObjectExchangeBank* objectExchangeBank) {
    s32 i;
    OSMesgQueue* msgq;
    ObjectStatus* objectStatus = objectExchangeBank->status;

    func_800C5EA0_jp(objectExchangeBank);

    for (i = 0; i < OBJECT_EXCHANGE_BANK_MAX; i++) {
        if ((i >= objectExchangeBank->unk17FC) && (objectStatus->id != 0) &&
            (objectStatus->unk52 != objectExchangeBank->unk181C)) {
            if (objectStatus->unk50 != 0) {
                if (objectStatus->unk53 != 2) {
                    func_800C5F0C_jp(objectStatus, objectExchangeBank);
                }
            } else if (objectStatus->unk53 == 0) {
                mSc_clear_bank_status(objectStatus);
            }
        }

        switch (objectStatus->unk53) {
            case 1:
                msgq = &objectStatus->unk34;
                if (objectStatus->unk14.vrom == 0) {
                    osCreateMesgQueue(msgq, (OSMesg)&objectStatus->unk4C, 1);
                    DmaMgr_RequestAsync(&objectStatus->unk14, objectStatus->vram, objectStatus->vrom,
                                        objectStatus->size, 0, msgq, NULL, "../m_scene.c", 613);
                    objectStatus->unk53 = 2;
                }
                break;
            case 2:
                msgq = &objectStatus->unk34;
                if (osRecvMesg(msgq, NULL, OS_MESG_NOBLOCK) == 0) {
                    mSc_set_bank_status_after(objectStatus);
                }
                break;
        }
        objectStatus++;
    }
}

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
    s32 idx;
    s32 ret = 0;

    idx = func_800C5A60_jp(objectExchangeBank);

    if (idx != -1) {
        ObjectStatus* status = &objectExchangeBank->status[idx];

        if (func_800C5AA0_jp(status, objectExchangeBank, arg1) == 1) {
            status->unk14.vrom = 0;
            status->unk52 = objectExchangeBank->unk181C;
            ret = 1;
        }
    }

    return ret;
}

void mSc_regist_initial_exchange_bank(Game_Play* game_play) {
    ObjectExchangeBank* objectExchangeBank = &game_play->objectExchangeBank;
    s16* var_s1 = game_play->unk_1EB4;
    s32 i;

    objectExchangeBank->unk181C = 0;
    i = 0;
    objectExchangeBank->unk17FC = objectExchangeBank->num;

    if (game_play->unk_1EA7 > 0) {
        do {
            func_800C6144_jp(objectExchangeBank, *var_s1);
            i += 1;
            var_s1 += 1;
            objectExchangeBank->num += 1;
        } while (i < game_play->unk_1EA7);
    }

    if (common_data.unk_10001 == 0) {
        u32 size = ((u32)(objectExchangeBank->unk1804 - objectExchangeBank->unk1800) / 2);
        s32 ram = ALIGN16(objectExchangeBank->unk1800 + size);

        objectExchangeBank->unk1810[1] = objectExchangeBank->unk1804;
        objectExchangeBank->unk1810[0] = ram;
        objectExchangeBank->unk1808[1] = ram;
        objectExchangeBank->unk1804 = ram;
        size = objectExchangeBank->unk1800;
        objectExchangeBank->unk1808[0] = size;

    } else {
        objectExchangeBank->unk1808[0] = objectExchangeBank->unk1800;
        objectExchangeBank->unk1808[1] = objectExchangeBank->unk1800;
        objectExchangeBank->unk1810[0] = objectExchangeBank->unk1804;
        objectExchangeBank->unk1810[1] = objectExchangeBank->unk1804;
    }

    objectExchangeBank->unk17FC = objectExchangeBank->num;
}

void mSc_dmacopy_all_exchange_bank_sub(ObjectStatus* status, ObjectExchangeBank* objectExchangeBank, s32 idx) {
    if (idx >= objectExchangeBank->unk17FC) {
        u32 area = (u32)ALIGN16(objectExchangeBank->unk1800 + status->size);

        if (area >= objectExchangeBank->unk1804) {
            objectExchangeBank->unk181C = (objectExchangeBank->unk181C + 1) % 2;
            objectExchangeBank->unk1800 = objectExchangeBank->unk1808[objectExchangeBank->unk181C];
            objectExchangeBank->unk1804 = objectExchangeBank->unk1810[objectExchangeBank->unk181C];
            area = (u32)ALIGN16(objectExchangeBank->unk1800 + status->size);
        }
        status->vram = (void*)objectExchangeBank->unk1800;
        status->unk52 = objectExchangeBank->unk181C;
        objectExchangeBank->unk1800 = area;
    }
    DmaMgr_RequestSyncDebug(status->vram, status->vrom, status->size, "../m_scene.c", 828);
    mSc_set_bank_status_after(status);
}

void mSc_dmacopy_all_exchange_bank(ObjectExchangeBank* exchange) {
    ObjectStatus* bank;
    s32 i;

    bank = &exchange->status[exchange->unk17F8];
    exchange->unk1800 = exchange->unk1808[exchange->unk181C];

    for (i = exchange->unk17F8; i < OBJECT_EXCHANGE_BANK_MAX; i++) {
        if (bank->id != 0 && bank->unk53 != 3) {
            if (bank->id < 0) {
                mSc_dmacopy_all_exchange_bank_sub(bank, exchange, i);
            } else if (bank->unk50 != 0) {
                mSc_dmacopy_all_exchange_bank_sub(bank, exchange, i);
            } else if (i >= exchange->unk17FC) {
                mSc_clear_bank_status(bank);
            } else {
                bank->id = 0;
            }
        }

        bank++;
    }

    if (common_data.clip.unk_08C != NULL) {
        if (common_data.clip.unk_08C->unk_A4 != NULL) {
            common_data.clip.unk_08C->unk_A4(exchange);
        }
    }
    if (common_data.clip.unk_040 != NULL) {
        common_data.clip.unk_040->unk_E8();
    }
    if (common_data.clip.unk_07C != NULL) {
        if (common_data.clip.unk_07C->unk_4 != NULL) {
            common_data.clip.unk_07C->unk_4(exchange);
        }
    }
    if (common_data.clip.unk_0A8 != NULL) {
        if (common_data.clip.unk_0A8->unk_04 != NULL) {
            common_data.clip.unk_0A8->unk_04(exchange);
        }
    }

    if (common_data.clip.unk_068 != NULL) {
        common_data.clip.unk_068();
    }
    if (common_data.clip.unk_060 != NULL) {
        common_data.clip.unk_060->unk_4();
    }
    if (common_data.clip.unk_070 != NULL) {
        common_data.clip.unk_070->unk_C();
    }
    if (common_data.clip.weatherClip != NULL) {
        common_data.clip.weatherClip->changingWeather();
    }
    if (common_data.clip.unk_080 != NULL) {
        common_data.clip.unk_080->unk_24();
    }
    if (common_data.clip.unk_09C != NULL) {
        common_data.clip.unk_09C->unk_C();
    }
    if (common_data.clip.unk_0B8 != NULL) {
        common_data.clip.unk_0B8->unk_4();
    }
    if (common_data.clip.unk_0B4 != NULL) {
        common_data.clip.unk_0B4->unk_4();
    }
    if (common_data.clip.unk_0D0 != NULL) {
        common_data.clip.unk_0D0();
    }
}

void mSc_data_bank_ct(Game_Play* game_play, ObjectExchangeBank* objectExchangeBank) {
    u32 temp_v0;

    bzero(objectExchangeBank, sizeof(ObjectExchangeBank));
    objectExchangeBank->unk17F8 = -1;
    objectExchangeBank->unk17FC = -1;
    temp_v0 = (u32)THA_alloc16(&game_play->state.heap, 0x93400);
    objectExchangeBank->unk1800 = temp_v0;
    objectExchangeBank->unk1808[0] = temp_v0;
    objectExchangeBank->unk1808[1] = temp_v0;

    temp_v0 = temp_v0 + 0x93400;
    objectExchangeBank->unk1804 = temp_v0;
    objectExchangeBank->unk1810[0] = temp_v0;
    objectExchangeBank->unk1810[1] = temp_v0;
    func_800C5B74_jp(objectExchangeBank, GAMEPLAY_KEEP);
    gSegments[4] = (uintptr_t)OS_PHYSICAL_TO_K0(objectExchangeBank->status[0].segment);
}

void mSc_decide_exchange_bank(ObjectExchangeBank* objectExchangeBank) {
    objectExchangeBank->unk17F8 = objectExchangeBank->num;
    objectExchangeBank->unk1818 = (void*)objectExchangeBank->unk1800;
}

void Scene_player_select(s32 sceneNo, s32 npcActor) {
    Animal_c* animal;
    s32 metVillagersNum;
    s32 i;
    u16 npcId;
    s32 found;
    s32 j;
    s32 metVillagersBitfield;
    s32 selected;

    metVillagersBitfield = 0;
    animal = common_data.animals;
    if (sceneNo != common_data.sceneNo) {
        return;
    }

    metVillagersNum = 0;
    { UNUSED s32 scopedTemp; }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            Anmmem_c* memory = animal->memories;

            for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
                if (memory->memoryPlayerId.landId == common_data.landInfo.id &&
                    mLd_CheckCmpLandName(memory->memoryPlayerId.landName, common_data.landInfo.name) == TRUE) {
                    metVillagersBitfield |= 1 << i;
                    metVillagersNum++;
                    break;
                }

                memory++;
            }
        }

        animal++;
    }

    /* Roll a random villager if none have met a player in town before */
    if (metVillagersNum == 0) {
        do {
            selected = RANDOM(ANIMAL_NUM_MAX);
        } while (mNpc_CheckFreeAnimalPersonalID(&common_data.animals[selected].id));
        if (1) {};
        npcId = common_data.animals[selected].id.npcId;
        found = mNpc_SearchAnimalinfo(common_data.animals, npcId, ANIMAL_NUM_MAX);
    } else {
        /* Pick a random villager which has met a player in town */

        selected = RANDOM(metVillagersNum);

        for (found = 0; found < ANIMAL_NUM_MAX; found++) {
            if (metVillagersBitfield & 1) {
                if (selected == 0) {
                    break;
                }
                selected--;
            }
            metVillagersBitfield >>= 1;
        }
        npcId = common_data.animals[found].id.npcId;
    }

    mNpc_RegistEventNpc(npcActor, npcId, npcId, common_data.animals[found].cloth);
}

void Scene_Proc_Player_Ptr(Game_Play* play, SceneData* data);
void Scene_Proc_Ctrl_Actor_Ptr(Game_Play* play, SceneData* data);
void Scene_Proc_Actor_Ptr(Game_Play* play, SceneData* data);
void Scene_Proc_Object_Exchange_Bank_Ptr(Game_Play* play, SceneData* data);
void Scene_Proc_Door_Data_Ptr(Game_Play* play, SceneData* data);
void Scene_Proc_Field_ct(Game_Play* play, SceneData* data);
void Scene_Proc_MyRoom_ct(Game_Play* play, SceneData* data);
void Scene_Proc_ArrangeRoom_ct(Game_Play* play, SceneData* data);
void Scene_Proc_ArrangeFurniture_ct(Game_Play* play, SceneData* data);
void Scene_Proc_Sound(Game_Play* play, SceneData* data);

typedef void (*SceneDataProc)(Game_Play*, SceneData*);

void Scene_ct(Game_Play* play, SceneData* sceneData) {
    static SceneDataProc Scene_Proc[] = {
        &Scene_Proc_Player_Ptr,
        &Scene_Proc_Ctrl_Actor_Ptr,
        &Scene_Proc_Actor_Ptr,
        &Scene_Proc_Object_Exchange_Bank_Ptr,
        &Scene_Proc_Door_Data_Ptr,
        &Scene_Proc_Field_ct,
        &Scene_Proc_MyRoom_ct,
        &Scene_Proc_ArrangeRoom_ct,
        &Scene_Proc_ArrangeFurniture_ct,
        &Scene_Proc_Sound,
        NULL,
    };

    while (TRUE) {
        u32 type = sceneData->misc.type;

        if (type == 10) {
            break;
        }

        if (type < 11) {
            Scene_Proc[type](play, sceneData);
        }

        sceneData++;
    }

    /* Setup player select actors */
    Scene_player_select(SCENE_PLAYERSELECT_2, 0xD01F);    // load
    Scene_player_select(SCENE_PLAYERSELECT_SAVE, 0xD06A); // save
}

void Scene_Proc_Player_Ptr(Game_Play* play, SceneData* scene_data) {
    static s16 angle_table[] = {
        0x0000, 0x2000, 0x4000, 0x6000, 0x8000, 0xA000, 0xC000, 0xE000,
    };

    ActorEntry* data = Lib_SegmentedToVirtual(scene_data->actor.actorDataPtr);

    play->unk_1EA8 = data;

    if (common_data.doorData.nextSceneId != 0) {
        mem_copy((u8*)&data->pos, (u8*)&common_data.doorData.exitPos, sizeof(s_xyz));
        data->rot.y = angle_table[common_data.doorData.exitOrientation];
    }

    data->params = common_data.doorData.params;
    Object_Exchange_keep_new_Player(play);
    mSM_Object_Exchange_keep_new_Menu(play);
}

void Scene_Proc_Ctrl_Actor_Ptr(Game_Play* play, SceneData* scene_data) {
    s16* data = scene_data->controlActor.ctrlActorDataPtr;

    play->unk_1EA6 = scene_data->controlActor.numCtrlActors;
    play->unk_1EB0 = Lib_SegmentedToVirtual(data);
}

void Scene_Proc_Actor_Ptr(Game_Play* play, SceneData* scene_data) {
    ActorEntry* data = scene_data->actor.actorDataPtr;

    play->unk_1EA5 = scene_data->actor.numActors;
    play->unk_1EAC = Lib_SegmentedToVirtual(data);
}

void Scene_Proc_Object_Exchange_Bank_Ptr(Game_Play* play, SceneData* scene_data) {

    play->unk_1EA7 = scene_data->objectBank.numBanks;
    play->unk_1EB4 = Lib_SegmentedToVirtual(scene_data->objectBank.banksDataPtr);
}

void Scene_Proc_Door_Data_Ptr(Game_Play* play, SceneData* scene_data) {
    DoorData* data = scene_data->doorData.doorDataPtr;

    play->sceneDoorInfo.numDoors = scene_data->doorData.numDoors;
    play->sceneDoorInfo.doorDataPtr = Lib_SegmentedToVirtual(data);
}

void Door_info_ct(DoorInfo* door_info) {
    door_info->numDoors = 0;
}

void Scene_Proc_Sound(UNUSED Game_Play* play, UNUSED SceneData* scene_data) {
}

void set_item_info(Game_Play* play, SceneDataField* field) {
    s16 bank;

    static s16 profile_table[4] = { 0x1, 0xB4, 0x4E, 0x52 };
    s32 itemType = field->itemType;

    if (itemType == 0) {
        bank = common_data.time.bgitemBank;
        common_data.unk_1014E = common_data.time.bgitemProfile;
    } else {
        bank = -1;
        common_data.unk_1014E = profile_table[itemType];
    }

    common_data.unk_1014C = itemType;

    if (bank != -1) {
        func_800C5B74_jp(&play->objectExchangeBank, bank);
    }
}

void Scene_Proc_Field_ct(Game_Play* play, SceneData* scene_data) {
    mFM_SetFieldInitData(scene_data->field.bgNum, scene_data->field.bgDispSize);
    set_item_info(play, &scene_data->field);
    common_data.unk_10002 = scene_data->field.drawType;
    common_data.unk_10000 = FALSE;
    common_data.unk_104AC = TRUE;
    common_data.sunlightFlag = TRUE;
}

void Scene_Proc_MyRoom_ct(Game_Play* play, UNUSED SceneData* data) {
    mScn_ObtainMyRoomBank(play);
}

void Scene_Proc_ArrangeRoom_ct(Game_Play* play, UNUSED SceneData* data) {
    mScn_ObtainCarpetBank(play);
}

void Scene_Proc_ArrangeFurniture_ct(UNUSED Game_Play* play, SceneData* data) {
    common_data.clip.unk_020 = data->arrangeFtr.arrangeFtrNum;
}

s32 goto_other_scene(Game_Play* play, DoorData* door_data, s32 updatePlayer) {
    Player* player = get_player_actor_withoutCheck(play);
    s32 res = 0;

    if (player != NULL) {
        if (play->unk_1EE3 == 0) {
            play->unk_1EE0 = 2;

            if (door_data->wipeType == 0) {
                play->unk_1EE1 = 3;
            } else {
                play->unk_1EE1 = door_data->wipeType;
            }

            if (common_data.unk_1014B == 0xFF) {
                common_data.unk_1014B = play->unk_1EE1;
            }

            common_data.doorData = *door_data;
            common_data.doorData.nextSceneId = door_data->nextSceneId + 1;
            play->unk_1E18 = door_data->nextSceneId;

            if (updatePlayer) {
                mPlib_request_main_invade_type1(play);
            }

            restore_fgdata_all(play);
            play->state.unk_74 = FALSE;
            res = 1;
        } else {
            res = 2;
        }
    }

    return res;
}

s32 goto_next_scene(Game_Play* play, s32 nextScene, s32 updatePlayer) {
    s32 res = FALSE;

    if (play->sceneDoorInfo.numDoors != 0) {
        res = goto_other_scene(play, play->sceneDoorInfo.doorDataPtr + nextScene, updatePlayer);
    }

    return res;
}

s32 goto_emu_game(Game_Play* play, s16 famicomRomId) {
    Player* player = get_player_actor_withoutCheck(play);
    s32 res = FALSE;

    if (player != NULL) {
        DoorData* door_data;

        play->unk_1EE0 = 3;
        play->unk_1EE1 = 3;
        res = TRUE;

        door_data = &common_data.famicomEmuDoorData;
        door_data->nextSceneId = common_data.sceneNo;
        door_data->exitOrientation = 0;
        door_data->exitType = 0;
        door_data->params = 0;
        door_data->exitPos.x = player->actor.world.pos.x;
        door_data->exitPos.y = player->actor.world.pos.y;
        door_data->exitPos.z = player->actor.world.pos.z;
        door_data->fgName = 0;
        common_data.unk109F8 = famicomRomId;
    }

    return res;
}

void return_emu_game(Game* game) {
    mem_copy((u8*)&common_data.doorData, (u8*)&common_data.famicomEmuDoorData, sizeof(DoorData));
    common_data.doorData.nextSceneId = common_data.famicomEmuDoorData.nextSceneId + 1;
    game->unk_74 = FALSE;
    game_goto_next_game_play(game);
    common_data.sceneNo = common_data.famicomEmuDoorData.nextSceneId;
}
