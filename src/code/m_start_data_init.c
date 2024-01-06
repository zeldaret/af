#include "m_start_data_init.h"
#include "6792F0.h"
#include "m_cockroach.h"
#include "69CB30.h"
#include "6A83A0.h"
#include "6B81C0.h"
#include "m_land.h"
#include "6BA500.h"
#include "6C0690.h"
#include "6C97F0.h"
#include "m_npc_schedule.h"
#include "6D9D80.h"
#include "6DA460.h"
#include "m_quest.h"
#include "6E30B0.h"
#include "6E7AD0.h"
#include "6ECD90.h"
#include "6EDD10.h"
#include "lb_rtc.h"
#include "global.h"
#include "libc64/qrand.h"
#include "m_all_grow.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "m_handbill.h"
#include "m_home.h"
#include "m_house.h"
#include "m_kankyo.h"
#include "m_lib.h"
#include "m_msg_main.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_scene_table.h"
#include "m_snowman.h"
#include "m_time.h"
#include "overlays/gamestates/ovl_play/m_play.h"
#include "sys_math.h"
#include "m_flashrom.h"

void famicom_emu_initial_common_data(void) {
    FamicomEmuCommonData* famicom = &common_data.famicomEmuCommonData;

    famicom->unk00 = 0;
    famicom->unk02 = 0x3E8;
    famicom->unk04 = 0x3E8;
    famicom->unk06 = 0x9C4;
    famicom->unk08 = 0;
    famicom->unk0A = 0;
    famicom->unk0C = 0;
    famicom->unk0E = 0;
    famicom->unk10 = 0x64;
    famicom->unk14 = 0;
    famicom->unk16 = 0;
    famicom->unk18 = 0;
    famicom->unk1A = 0;
    famicom->unk1C = 0;
    famicom->unk1E = 0;
    famicom->unk20 = 0;
    famicom->unk22 = 0;
    famicom->unk24 = 0;
}

void decide_fruit(u16* fruit) {
    u16 n = mAGrw_FRUIT_NUM;

    *fruit = ITM_FOOD_START | (u16)RANDOM_F(n);
}

void decide_fish_location(u8* fishLocation) {
    *fishLocation = RANDOM_F(3);
}

void title_game_haniwa_data_init(void) {
    s32 i;
    char haniwaBuf[HANIWA_MESSAGE_LEN];
    s32 j;
    Haniwa_c* haniwa;

    mString_Load_StringFromRom(haniwaBuf, HANIWA_MESSAGE_LEN, 0x55C);

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        haniwa = &common_data.homes[i].haniwa;

        mem_copy(common_data.homes[i].haniwa.message, (u8*)haniwaBuf, HANIWA_MESSAGE_LEN);

        for (j = 0; j < HANIWA_ITEM_HOLD_NUM; j++) {
            haniwa->items[j].item = EMPTY_NO;
        }
        haniwa->bells = 0;
    }
}

void mSDI_ClearMoneyPlayerHomeStationBlock(void) {
    static s32 block_num[2][2] = {
        { 2, 1 }, // Player home
        { 2, 0 }  // Station
    };

    s32 blockZ;
    s32 blockX;
    u16* items;
    s32 utX;
    s32 utZ;
    u16 item;
    s32 i;
    s32 depositOffset;

    for (i = 0; i < 2; i++) {
        blockZ = block_num[i][1];
        blockX = block_num[i][0];

        depositOffset = block_num[i][1] * FG_BLOCK_X_NUM + blockX;
        items = common_data.foreground[blockZ][blockX].items[0];

        if (items != NULL) {
            for (utZ = 0; utZ < UT_Z_NUM; utZ++) {
                for (utX = 0; utX < UT_X_NUM; utX++) {
                    item = *items;

                    if (item >= ITM_MONEY_START && item <= ITM_MONEY_END) {
                        u16* deposit = common_data.deposit[depositOffset];

                        mPB_keep_item(item);
                        *items = EMPTY_NO;

                        if (deposit != NULL) {
                            mFI_BlockDepositOFF(deposit, utX, utZ);
                        }
                    }

                    items++;
                }
            }
        }
    }
}

void mSDI_PullTreeUT(u16* itemP) {
    if ((*itemP >= TREE_SAPLING && *itemP <= TREE_30000BELLS) ||
        (*itemP >= TREE_100BELLS_SAPLING && *itemP <= TREE_100BELLS)) {
        *itemP = EMPTY_NO;
    }
}

void mSDI_PullTreeBlock(u16* itemsP, s32 ut) {
    s32 i;

    for (i = ut; i < UT_TOTAL_NUM; i += UT_X_NUM) {
        mSDI_PullTreeUT(&itemsP[i]);
    }
}

void mSDI_PullTree(void) {
    Foreground* fgBlock;
    s32 blockZ;

    for (blockZ = 0; blockZ < FG_BLOCK_Z_NUM; blockZ++) {
        // Clear trees against the cliffs on the left and right town cliff borders
        fgBlock = &common_data.foreground[blockZ][0];
        mSDI_PullTreeBlock(fgBlock->items[0], 0);
        mSDI_PullTreeBlock((fgBlock + FG_BLOCK_X_NUM - 1)->items[0], UT_X_NUM - 1);
    }

    if (fgBlock) {}
}

void mSDI_PullTreeUnderPlayerBlock(void) {
    /**
     * Cleared tree diagram
     *
     * -------xx-------
     * -------xx-------
     * ----------------
     * ...
     **/

    u16* items = &common_data.foreground[2][2].items[0][0];

    mSDI_PullTreeUT(&items[7]);
    mSDI_PullTreeUT(&items[8]);
    mSDI_PullTreeUT(&items[16 + 7]);
    mSDI_PullTreeUT(&items[16 + 8]);
}

s32 mSDI_StartInitNew(Game* game2, s32 playerNumber, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game2;
    PrivateInfo* privateInfo;
    PrivateInfo* privateInfoPointer;
    Game* game = NULL;
    s32 i;
    UNUSED s32 pad[2];

    common_data.sceneFromTitleDemo = SCENE_START_DEMO;
    lbRTC_GetTime(&common_data.time.rtcTime);

    privateInfo = &common_data.saveFilePrivateInfo[playerNumber];
    common_data.privateInfo = privateInfo;
    common_data.playerNumber = playerNumber;

    common_data.privateInfo->gender = mPr_SEX_MALE;

    decide_fruit(&common_data.fruit);
    if (mallocFlag == 0) {
        game = game2;
    }

    bzero(&common_data.deposit, sizeof(common_data.deposit));

    mFM_InitFgCombiSaveData(game);
    mSDI_PullTree();
    mSDI_PullTreeUnderPlayerBlock();
    mFM_SetBlockKindLoadCombi(game);
    mAGrw_ChangeTree2FruitTree();

    privateInfoPointer = &common_data.saveFilePrivateInfo[0];

    mMld_SetDefaultMelody();
    mLd_LandDataInit();
    mEv_ClearEventSaveInfo(&common_data.eventSaveInfo);
    mEv_init(&game_play->event);
    mNpc_InitNpcAllInfo(mallocFlag);

    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearPrivateInfo(privateInfoPointer);
        privateInfoPointer++;
    }

    privateInfoPointer += playerNumber;
    privateInfoPointer -= PLAYER_NUM;
    mPr_InitPrivateInfo(privateInfoPointer);
    mNpc_SetRemoveAnimalNo(common_data.animals);
    title_game_haniwa_data_init();
    mPB_police_box_init(game);
    mSN_snowman_init();
    mHS_house_init();

    lbRTC_TimeCopy(&common_data.lastGrowTime, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&common_data.unk_0F89C, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&common_data.unk_0F8A4, &mTM_rtcTime_clear_code);

    for (i = 0; i < PLAYER_NUM; i++) {
        common_data.homes[i].unk_022 &= (u16)~0xC0;
        common_data.homes[i].unk_022 &= 0xCF;
        common_data.homes[i].unk_022 &= 0xF7;
        common_data.homes[i].unk_024 = i;
    }

    common_data.stationType = RANDOM_F(15);

    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearMotherMailInfo(&common_data.motherMailInfo[i]);
    }

    mPr_SetPossessionItem(common_data.privateInfo, 0, ITM_MONEY_1000, mPr_ITEM_COND_QUEST);
    mCkRh_InitGokiSaveData_InitNewPlayer();
    mEv_2nd_init(&game_play->event);
    famicom_emu_initial_common_data();
    return TRUE;
}

s32 mSDI_StartInitFrom(Game* game2, s32 playerNumber, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game2;
    PrivateInfo* privateInfo;
    Game* game = game2;
    s32 res = FALSE;

    if (mallocFlag != 0) {
        game = NULL;
    }

    common_data.sceneFromTitleDemo = SCENE_FG;
    lbRTC_GetTime(&common_data.time.rtcTime);

    if (mFRm_CheckSaveData() == TRUE) {
        privateInfo = &common_data.saveFilePrivateInfo[playerNumber];
        if (mPr_CheckPrivate(privateInfo) == TRUE) {
            if (privateInfo->exists == TRUE) {
                common_data.privateInfo = privateInfo;
                common_data.playerNumber = playerNumber;
                mFM_SetBlockKindLoadCombi(game);
                mEv_init_force(&game_play->event);
                mHsRm_GetHuusuiRoom(game, playerNumber);
                mSP_ExchangeLineUp_InGame(game);
                mNpc_SetRemoveAnimalNo(common_data.animals);
                mCkRh_DecideNowGokiFamilyCount(playerNumber);
                mMkRm_MarkRoom(game);
                res = TRUE;
            } else {
                common_data.playerDecoyFlag = TRUE;
                privateInfo->exists = TRUE;
                common_data.privateInfo = privateInfo;
                common_data.playerNumber = playerNumber;
                mFM_SetBlockKindLoadCombi(game);
                mHsRm_GetHuusuiRoom(game, playerNumber);
                mSP_ExchangeLineUp_InGame(game);
                mNpc_SetRemoveAnimalNo(common_data.animals);

                bzero(privateInfo->inventory.pockets, sizeof(privateInfo->inventory.pockets));
                privateInfo->inventory.lotto_ticket_expiry_month = 0;
                privateInfo->inventory.lotto_ticket_mail_storage = 0;
                privateInfo->inventory.item_conditions = 0;
                privateInfo->inventory.wallet = 0;
                mQst_ClearDelivery(privateInfo->deliveries, mPr_DELIVERY_QUEST_NUM);
                mQst_ClearErrand(privateInfo->errands, mPr_ERRAND_QUEST_NUM);
                mCkRh_DecideNowGokiFamilyCount(playerNumber);
                mMkRm_MarkRoom(game);
                res = TRUE;
            }
        }
    }
    return res;
}

s32 mSDI_StartInitNewPlayer(Game* game, s32 playerNumber, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game;
    PrivateInfo* privateInfo;
    s32 res = FALSE;
    UNUSED s32 pad;

    common_data.sceneFromTitleDemo = SCENE_START_DEMO2;
    lbRTC_GetTime(&common_data.time.rtcTime);

    privateInfo = &common_data.saveFilePrivateInfo[playerNumber];
    if (mFRm_CheckSaveData() == TRUE) {
        if (mPr_CheckPrivate(privateInfo) != TRUE) {
            mPr_InitPrivateInfo(privateInfo);
            common_data.privateInfo = privateInfo;
            mPr_SetPossessionItem(common_data.privateInfo, 0, ITM_MONEY_1000, mPr_ITEM_COND_QUEST);
            common_data.playerNumber = playerNumber;
            common_data.privateInfo->gender = mPr_SEX_MALE;
            if (mallocFlag == 0) {
                mFM_SetBlockKindLoadCombi(game);
                mEv_init_force(&game_play->event);
                mSP_ExchangeLineUp_InGame(game);
            } else {
                mFM_SetBlockKindLoadCombi(NULL);
                mEv_init_force(&game_play->event);
                mSP_ExchangeLineUp_InGame(NULL);
            }
            mNpc_SetRemoveAnimalNo(common_data.animals);
            mSDI_ClearMoneyPlayerHomeStationBlock();
            res = TRUE;
        }
    }
    return res;
}

s32 mSDI_StartInitPak(Game* game2, s32 playerNumber, s32 mallocFlag) {
    Game* game = game2;
    Game_Play* game_play = (Game_Play*)game;
    UNUSED s32 pad;
    s32 res = FALSE;
    s32 sp1C;

    if (mallocFlag == 1) {
        game = NULL;
    }

    if (playerNumber < 5) {
        common_data.sceneFromTitleDemo = SCENE_FG;
    }

    if (mFRm_CheckSaveData() == TRUE) {
        sp1C = mCPk_get_pkinfo();
        if ((func_80078E90_jp(sp1C, 0) == TRUE) && (func_800B8D64_jp(playerNumber, sp1C) == TRUE)) {
            mFM_SetBlockKindLoadCombi(game);
            mEv_init_force(&game_play->event);
            mHsRm_GetHuusuiRoom(game, playerNumber);
            mSP_ExchangeLineUp_InGame(game);
            mNpc_SetRemoveAnimalNo(common_data.animals);
            mNpc_SetReturnAnimal(mNpc_GetInAnimalP());
            mNpc_SendRegisteredGoodbyMail();
            mCkRh_DecideNowGokiFamilyCount(playerNumber);
            mMkRm_MarkRoom(game);
            mEv_SetGateway();
            res = TRUE;
        }
    }
    return res;
}

s32 mSDI_StartInitErr(UNUSED Game* game, UNUSED s32 playerNumber, UNUSED s32 mallocFlag) {
    return TRUE;
}

void mSDI_StartInitAfter(Game* game, s32 renewalReserveFlag, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game;

    common_data.houseOwnerName = -1;
    common_data.lastFieldId = -1;

    mHm_SetNowHome();
    mNpc_RenewalAnimalMemory();
    mTM_renewal_renew_time();
    mEv_ClearEventInfo();
    mEnv_DecideWeather_NormalGameStart();
    func_800B7680_jp(game_play);
    mTM_set_season();
    func_80084DA4_jp();
    mEv_2nd_init(&game_play->event);
    mNpc_Grow();
    func_80096B64_jp();
    mNpc_InitNpcData();
    mNpc_InitNpcList();
    mNpc_SetNpcList(common_data.npclist, common_data.animals, ANIMAL_NUM_MAX, mallocFlag);
    mNpc_ClearTalkInfo();
    if (renewalReserveFlag == 1) {
        mFM_RenewalReserve();
    }
    mQst_ClearNotSaveQuest(&common_data.quest);
    mNPS_set_all_schedule_area();
    mNpcW_InitNpcWalk(&common_data.npcWalk);
    mHm_CheckRehouseOrder();
    decide_fish_location(&common_data.fish_location);
    mTRC_init(game_play);
    common_data.gokiShockedFlag = FALSE;
    func_800A6548_jp();
    func_800B9B2C_jp();
    mNpc_Remail();
    mPr_SendForeingerAnimalMail(common_data.privateInfo);
    mPr_StartSetCompleteTalkInfo();
    mMsm_SendInformationMail();
    func_8008DCF8_jp();
    func_800A4D10_jp();
    mSN_decide_msg();
    mPr_RenewalMapInfo(common_data.privateInfo->maps, mPr_FOREIGN_MAP_COUNT, &common_data.landInfo);
}

typedef s32 (*StartDataInitProcess)(Game*, s32, s32);

s32 mSDI_StartInitBefore(Game* game, s32 playerNumber, s32 initMode, s32 mallocFlag) {
    static StartDataInitProcess init_proc[] = {
        mSDI_StartInitNew, mSDI_StartInitNewPlayer, mSDI_StartInitFrom, mSDI_StartInitPak, mSDI_StartInitErr,
    };

    mEv_UnSetGateway();
    return init_proc[initMode](game, playerNumber, mallocFlag);
}

s32 mSDI_StartDataInit(Game* game, s32 playerNumber, s32 initMode) {
    static int renew_reserve_mode_table[] = {
        TRUE, FALSE, FALSE, FALSE, FALSE,
    };
    s32 res;

    if ((initMode < mSDI_INIT_MODE_NEW) || (initMode >= mSDI_INIT_MODE_NUM)) {
        initMode = mSDI_INIT_MODE_NEW;
    }

    res = mSDI_StartInitBefore(game, playerNumber, initMode, mSDI_MALLOC_FLAG_ZELDA);
    if (res == TRUE) {
        mSDI_StartInitAfter(game, renew_reserve_mode_table[initMode], mSDI_MALLOC_FLAG_ZELDA);
    }

    return res;
}
