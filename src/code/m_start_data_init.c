#include "m_start_data_init.h"
#include "6792F0.h"
#include "68AB30.h"
#include "69CB30.h"
#include "6A83A0.h"
#include "6B81C0.h"
#include "6B8A70.h"
#include "6BA500.h"
#include "6C0690.h"
#include "6C97F0.h"
#include "6D9D80.h"
#include "6DA460.h"
#include "6DB420.h"
#include "6DE300.h"
#include "6E30B0.h"
#include "6E7AD0.h"
#include "6ECD90.h"
#include "6EDD10.h"
#include "6F8A60.h"
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

void famicom_emu_initial_common_data(void) {
    FamicomEmuCommonData* famicom = &gCommonData.save.famicomEmuCommonData;

    famicom->unk_00 = 0;
    famicom->unk_02 = 0x3E8;
    famicom->unk_04 = 0x3E8;
    famicom->unk_06 = 0x9C4;
    famicom->unk_08 = 0;
    famicom->unk_0A = 0;
    famicom->unk_0C = 0;
    famicom->unk_0E = 0;
    famicom->unk_10 = 0x64;
    famicom->unk_14 = 0;
    famicom->unk_16 = 0;
    famicom->unk_18 = 0;
    famicom->unk_1A = 0;
    famicom->unk_1C = 0;
    famicom->unk_1E = 0;
    famicom->unk_20 = 0;
    famicom->unk_22 = 0;
    famicom->unk_24 = 0;
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
    u8 haniwa_buf[HANIWA_MESSAGE_LEN];
    s32 j;
    Haniwa* haniwa;

    func_800C3F70_jp(haniwa_buf, HANIWA_MESSAGE_LEN, 0x55C);

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        haniwa = &gCommonData.save.homes[i].haniwa;

        mem_copy(gCommonData.save.homes[i].haniwa.message, haniwa_buf, HANIWA_MESSAGE_LEN);

        for (j = 0; j < HANIWA_ITEM_HOLD_NUM; j++) {
            haniwa->items[j].item = EMPTY_NO;
        }
        haniwa->bells = 0;
    }
}

void mSDI_ClearMoneyPlayerHomeStationBlock(void) {
    static s32 block_num[2][2] = {
        { 2, 1 }, /* Player home */
        { 2, 0 }  /* Station */
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
        items = gCommonData.save.fg[blockZ][blockX].items[0];

        if (items != NULL) {
            for (utZ = 0; utZ < UT_Z_NUM; utZ++) {
                for (utX = 0; utX < UT_X_NUM; utX++) {
                    item = *items;

                    if (item >= ITM_MONEY_START && item <= ITM_MONEY_END) {
                        u16* deposit = gCommonData.save.deposit[depositOffset];

                        mPB_keep_item(item);
                        *items = EMPTY_NO;

                        if (deposit != NULL) {
                            func_8008C478_jp(deposit, utX, utZ);
                        }
                    }

                    items++;
                }
            }
        }
    }
}

void mSDI_PullTreeUT(u16* item_p) {
    if ((*item_p >= TREE_SAPLING && *item_p <= TREE_30000BELLS) ||
        (*item_p >= TREE_100BELLS_SAPLING && *item_p <= TREE_100BELLS)) {
        *item_p = EMPTY_NO;
    }
}

void mSDI_PullTreeBlock(u16* items_p, s32 ut) {
    s32 i;

    for (i = ut; i < UT_TOTAL_NUM; i += UT_X_NUM) {
        mSDI_PullTreeUT(&items_p[i]);
    }
}

void mSDI_PullTree(void) {
    Fg* fg_block;
    s32 blockZ;

    for (blockZ = 0; blockZ < FG_BLOCK_Z_NUM; blockZ++) {
        /* Clear trees against the cliffs on the left and right town cliff borders */
        fg_block = &gCommonData.save.fg[blockZ][0];
        mSDI_PullTreeBlock(fg_block->items[0], 0);
        mSDI_PullTreeBlock((fg_block + FG_BLOCK_X_NUM - 1)->items[0], UT_X_NUM - 1);
    }

    if (fg_block) {}
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

    u16* items = &gCommonData.save.fg[2][2].items[0][0];

    mSDI_PullTreeUT(&items[7]);
    mSDI_PullTreeUT(&items[8]);
    mSDI_PullTreeUT(&items[16 + 7]);
    mSDI_PullTreeUT(&items[16 + 8]);
}

s32 mSDI_StartInitNew(Game* game2, s32 playerNo, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game2;
    Private* priv;
    Private* priv_p;
    Game* game = NULL;
    s32 i;
    UNUSED s32 pad[2];

    gCommonData.sceneFromTitleDemo = SCENE_START_DEMO;
    lbRTC_GetTime(&gCommonData.time.rtcTime);

    priv = &gCommonData.save.private[playerNo];
    gCommonData.nowPrivate = priv;
    gCommonData.playerNo = playerNo;

    gCommonData.nowPrivate->gender = SEX_MALE;

    decide_fruit(&gCommonData.save.fruit);
    if (mallocFlag == 0) {
        game = game2;
    }

    bzero(&gCommonData.save.deposit, sizeof(gCommonData.save.deposit));

    mFM_InitFgCombiSaveData(game);
    mSDI_PullTree();
    mSDI_PullTreeUnderPlayerBlock();
    mFM_SetBlockKindLoadCombi(game);
    mAGrw_ChangeTree2FruitTree();

    priv_p = &gCommonData.save.private[0];

    mMld_SetDefaultMelody();
    mLd_LandDataInit();
    mEv_ClearEventSaveInfo(&gCommonData.save.eventSaveData);
    mEv_init(&game_play->event);
    mNpc_InitNpcAllInfo(mallocFlag);

    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearPrivateInfo(priv_p);
        priv_p++;
    }

    priv_p += playerNo;
    priv_p -= PLAYER_NUM;
    mPr_InitPrivateInfo(priv_p);
    mNpc_SetRemoveAnimalNo(gCommonData.save.animals);
    title_game_haniwa_data_init();
    mPB_police_box_init(game);
    mSN_snowman_init();
    mHS_house_init();

    lbRTC_TimeCopy(&gCommonData.save.unk_0F7FC, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&gCommonData.save.unk_0F89C, &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(&gCommonData.save.unk_0F8A4, &mTM_rtcTime_clear_code);

    for (i = 0; i < PLAYER_NUM; i++) {
        gCommonData.save.homes[i].unk_022 &= (u16)~0xC0;
        gCommonData.save.homes[i].unk_022 &= 0xCF;
        gCommonData.save.homes[i].unk_022 &= 0xF7;
        gCommonData.save.homes[i].unk_024 = i;
    }

    gCommonData.save.stationType = RANDOM_F(15);

    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearMotherMailInfo(&gCommonData.save.motherMail[i]);
    }

    mPr_SetPossessionItem(gCommonData.nowPrivate, 0, ITM_MONEY_1000, ITEM_COND_QUEST);
    mNW_InitMyOriginal();
    mEv_2nd_init(&game_play->event);
    famicom_emu_initial_common_data();
    return TRUE;
}

s32 mSDI_StartInitFrom(Game* game2, s32 playerNo, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game2;
    Private* priv;
    Game* game = game2;
    s32 res = FALSE;

    if (mallocFlag != 0) {
        game = NULL;
    }

    gCommonData.sceneFromTitleDemo = SCENE_FG;
    lbRTC_GetTime(&gCommonData.time.rtcTime);

    if (mFRm_CheckSaveData() == TRUE) {
        priv = &gCommonData.save.private[playerNo];
        if (mPr_CheckPrivate(priv) == TRUE) {
            if (priv->exists == TRUE) {
                gCommonData.nowPrivate = priv;
                gCommonData.playerNo = playerNo;
                mFM_SetBlockKindLoadCombi(game);
                mEv_init_force(&game_play->event);
                mHsRm_GetHuusuiRoom(game, playerNo);
                mSP_ExchangeLineUp_InGame(game);
                mNpc_SetRemoveAnimalNo(gCommonData.save.animals);
                mCkRh_DecideNowGokiFamilyCount(playerNo);
                mMkRm_MarkRoom(game);
                res = TRUE;
            } else {
                gCommonData.playerDecoyFlag = TRUE;
                priv->exists = TRUE;
                gCommonData.nowPrivate = priv;
                gCommonData.playerNo = playerNo;
                mFM_SetBlockKindLoadCombi(game);
                mHsRm_GetHuusuiRoom(game, playerNo);
                mSP_ExchangeLineUp_InGame(game);
                mNpc_SetRemoveAnimalNo(gCommonData.save.animals);

                bzero(priv->inventory.pockets, sizeof(priv->inventory.pockets));
                priv->inventory.lottoTicketExpiryMonth = 0;
                priv->inventory.lottoTicketMailStorage = 0;
                priv->inventory.itemConditions = 0;
                priv->inventory.wallet = 0;
                mQst_ClearDelivery(priv->deliveries, DELIVERY_QUEST_NUM);
                mQst_ClearErrand(priv->errands, ERRAND_QUEST_NUM);
                mCkRh_DecideNowGokiFamilyCount(playerNo);
                mMkRm_MarkRoom(game);
                res = TRUE;
            }
        }
    }
    return res;
}

s32 mSDI_StartInitNewPlayer(Game* game, s32 playerNo, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game;
    Private* priv;
    s32 res = FALSE;
    UNUSED s32 pad;

    gCommonData.sceneFromTitleDemo = SCENE_START_DEMO2;
    lbRTC_GetTime(&gCommonData.time.rtcTime);

    priv = &gCommonData.save.private[playerNo];
    if (mFRm_CheckSaveData() == TRUE) {
        if (mPr_CheckPrivate(priv) != TRUE) {
            mPr_InitPrivateInfo(priv);
            gCommonData.nowPrivate = priv;
            mPr_SetPossessionItem(gCommonData.nowPrivate, 0, ITM_MONEY_1000, ITEM_COND_QUEST);
            gCommonData.playerNo = playerNo;
            gCommonData.nowPrivate->gender = SEX_MALE;
            if (mallocFlag == 0) {
                mFM_SetBlockKindLoadCombi(game);
                mEv_init_force(&game_play->event);
                mSP_ExchangeLineUp_InGame(game);
            } else {
                mFM_SetBlockKindLoadCombi(NULL);
                mEv_init_force(&game_play->event);
                mSP_ExchangeLineUp_InGame(NULL);
            }
            mNpc_SetRemoveAnimalNo(gCommonData.save.animals);
            mSDI_ClearMoneyPlayerHomeStationBlock();
            res = TRUE;
        }
    }
    return res;
}

s32 mSDI_StartInitPak(Game* game2, s32 playerNo, s32 mallocFlag) {
    Game* game = game2;
    Game_Play* game_play = (Game_Play*)game;
    UNUSED s32 pad;
    s32 res = FALSE;
    s32 sp1C;

    if (mallocFlag == 1) {
        game = NULL;
    }

    if (playerNo < 5) {
        gCommonData.sceneFromTitleDemo = SCENE_FG;
    }

    if (mFRm_CheckSaveData() == TRUE) {
        sp1C = mCPk_get_pkinfo();
        if ((func_80078E90_jp(sp1C, 0) == TRUE) && (func_800B8D64_jp(playerNo, sp1C) == TRUE)) {
            mFM_SetBlockKindLoadCombi(game);
            mEv_init_force(&game_play->event);
            mHsRm_GetHuusuiRoom(game, playerNo);
            mSP_ExchangeLineUp_InGame(game);
            mNpc_SetRemoveAnimalNo(gCommonData.save.animals);
            mNpc_SetReturnAnimal(mNpc_GetInAnimalP());
            mNpc_SendRegisteredGoodbyMail();
            mCkRh_DecideNowGokiFamilyCount(playerNo);
            mMkRm_MarkRoom(game);
            mEv_SetGateway();
            res = TRUE;
        }
    }
    return res;
}

s32 mSDI_StartInitErr(UNUSED Game* game, UNUSED s32 playerNo, UNUSED s32 mallocFlag) {
    return TRUE;
}

void mSDI_StartInitAfter(Game* game, s32 renewal_reserve_flag, s32 mallocFlag) {
    Game_Play* game_play = (Game_Play*)game;

    gCommonData.houseOwnerName = -1;
    gCommonData.lastFieldId = -1;

    mHm_SetNowHome();
    mNpc_RenewalAnimalMemory();
    mTM_renewal_renew_time();
    mEv_ClearEventInfo();
    mEnv_DecideWeather_NormalGameStart();
    func_800B7680_jp(game_play);
    mTM_set_season();
    func_80084DA4_jp();
    mEv_2nd_init(&game_play->event);
    func_800AD9FC_jp();
    func_80096B64_jp();
    func_800AB054_jp();
    func_800AB09C_jp();
    mNpc_SetNpcList(gCommonData.npcList, gCommonData.save.animals, ANIMAL_NUM_MAX, mallocFlag);
    mNpc_ClearTalkInfo();
    if (renewal_reserve_flag == 1) {
        mFM_RenewalReserve();
    }
    mQst_ClearNotSaveQuest(&gCommonData.quest);
    mNPS_set_all_schedule_area();
    mNpcW_InitNpcWalk(&gCommonData.npcWalk);
    mHm_CheckRehouseOrder();
    decide_fish_location(&gCommonData.fishLocation);
    mTRC_init(game_play);
    gCommonData.gokiShockedFlag = FALSE;
    func_800A6548_jp();
    func_800B9B2C_jp();
    func_800A91DC_jp();
    mPr_SendForeingerAnimalMail(gCommonData.nowPrivate);
    mPr_StartSetCompleteTalkInfo();
    mMsm_SendInformationMail();
    func_8008DCF8_jp();
    func_800A4D10_jp();
    mSN_decide_msg();
    mPr_RenewalMapInfo(gCommonData.nowPrivate->maps, FOREIGN_MAP_COUNT, &gCommonData.save.landInfo);
}

typedef s32 (*mSDI_INIT_PROC)(Game*, s32, s32);

s32 mSDI_StartInitBefore(Game* game, s32 playerNo, s32 init_mode, s32 mallocFlag) {
    static mSDI_INIT_PROC init_proc[mSDI_INIT_MODE_NUM] = {
        mSDI_StartInitNew, mSDI_StartInitNewPlayer, mSDI_StartInitFrom, mSDI_StartInitPak, mSDI_StartInitErr,
    };

    mEv_UnSetGateway();
    return init_proc[init_mode](game, playerNo, mallocFlag);
}

s32 mSDI_StartDataInit(Game* game, s32 playerNo, s32 init_mode) {
    static int renew_reserve_mode_table[mSDI_INIT_MODE_NUM] = {
        TRUE, FALSE, FALSE, FALSE, FALSE,
    };
    s32 res;

    if ((init_mode < mSDI_INIT_MODE_NEW) || (init_mode >= mSDI_INIT_MODE_NUM)) {
        init_mode = mSDI_INIT_MODE_NEW;
    }

    res = mSDI_StartInitBefore(game, playerNo, init_mode, mSDI_MALLOC_FLAG_ZELDA);
    if (res == TRUE) {
        mSDI_StartInitAfter(game, renew_reserve_mode_table[init_mode], mSDI_MALLOC_FLAG_ZELDA);
    }

    return res;
}
