#include "m_private.h"
#include "m_lib.h"
#include "m_land.h"
#include "m_name_table.h"
#include "m_time.h"
#include "m_player_lib.h"
#include "6E2300.h"
#include "m_field_info.h"
#include "6E3240.h"
#include "69CB30.h"
#include "m_handbill.h"
#include "m_house.h"
#include "6DA460.h"
#include "6EDD10.h"

PrivateInfo g_foreigner_private;
Mail_c l_mpr_mail;

void mPr_ClearPlayerName(char* buf) {
    mem_clear((u8*)buf, PLAYER_NAME_LEN, ' ');
}

void mPr_CopyPlayerName(char* dst, char* src) {
    mem_copy((u8*)dst, (u8*)src, PLAYER_NAME_LEN);
}

s32 mPr_NullCheckPlayerName(char* name) {
    s32 res = FALSE;
    s32 i;

    for (i = 0; i < PLAYER_NAME_LEN; i++) {
        if (name[0] != ' ') {
            break;
        }
        name++;
    }

    if (i == PLAYER_NAME_LEN) {
        res = TRUE;
    }

    return res;
}

s32 mPr_CheckCmpPlayerName(char* name0, char* name1) {
    s32 res = FALSE;

    if (mPr_NullCheckPlayerName(name0) == FALSE && mPr_NullCheckPlayerName(name1) == FALSE) {
        res = mem_cmp((u8*)name0, (u8*)name1, PLAYER_NAME_LEN);
    }

    return res;
}

s32 mPr_GetPlayerName(char* buf, s32 playerNumber) {
    char* name;
    s32 res = FALSE;

    if (mLd_PlayerManKindCheckNo(playerNumber) == FALSE) {
        if (mPr_NullCheckPersonalID(&common_data.saveFilePrivateInfo[playerNumber].playerId) == FALSE) {
            mPr_CopyPlayerName(buf, common_data.saveFilePrivateInfo[playerNumber].playerId.playerName);
            res = TRUE;
        }
    } else if (mLd_PlayerManKindCheckNo(common_data.playerNumber) == TRUE) {

        name = (common_data.privateInfo)->playerId.playerName;
        mPr_CopyPlayerName(buf, name);
        res = TRUE;
    }

    return res;
}

s32 mPr_NullCheckPersonalID(PersonalID_c* pid) {
    s32 res = FALSE;

    if (pid->landId == 0xFFFF && mPr_NullCheckPlayerName(pid->playerName) == TRUE) {
        res = TRUE;
    }

    return res;
}

void mPr_ClearPersonalID(PersonalID_c* pid) {
    mPr_ClearPlayerName(pid->playerName);
    mLd_ClearLandName(pid->landName);
    pid->landId = 0xFFFF;
    pid->playerId = 0xFFFF;
}

void mPr_ClearAnyPersonalID(PersonalID_c* pid, s32 count) {
    for (; count != 0; count--) {
        mPr_ClearPersonalID(pid);
        pid++;
    }
}

void mPr_CopyPersonalID(PersonalID_c* dst, PersonalID_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(PersonalID_c));
}

s32 mPr_CheckCmpPersonalID(PersonalID_c* pid0, PersonalID_c* pid1) {
    s32 res = FALSE;

    if (pid0->landId == pid1->landId && pid0->playerId == pid1->playerId &&
        mLd_CheckCmpLandName(pid0->landName, pid1->landName) == TRUE &&
        mPr_CheckCmpPlayerName(pid0->playerName, pid1->playerName) == TRUE) {
        res = TRUE;
    }

    return res;
}

void mPr_ClearPrivateBirthday(PrivateBirthday* birthday) {
    birthday->year = 0xFFFF;
    birthday->month = 0xFF;
    birthday->day = 0xFF;
}

void mPr_ClearAnimalMemory(PrivateAnimalMemory* memory) {
    memory->npcId = 0xFFFF;
    mLd_ClearLandName(memory->landName);
}

void mPr_ClearPrivateInfo(PrivateInfo* info) {
    bzero(info, sizeof(PrivateInfo));

    mPr_ClearPersonalID(&info->playerId);
    info->gender = mPr_SEX_MALE;
    mQst_ClearDelivery(info->deliveries, mPr_DELIVERY_QUEST_NUM);
    mQst_ClearErrand(info->errands, mPr_ERRAND_QUEST_NUM);
    mMl_clear_mail_box(info->mail, mPr_INVENTORY_MAIL_COUNT);
    mMl_clear_mail_header_common(&info->savedMailHeader);
    mPlib_change_player_cloth_info_lv2(info, 0x2401);
    mNpc_ClearAnimalPersonalID(&info->storedAnmId);
    mPr_ClearPrivateBirthday(&info->birthday);
    info->backgroundTextureId = 0x24E2;
    mNpc_ClearRemail(&info->remail);
    mPr_ClearAnimalMemory(&info->animalMemory);
    mPr_ClearMapInfo(info->maps, mPr_FOREIGN_MAP_COUNT);
    mMsm_ClearRecord(&info->museumRecord);
}

s32 mPr_GetRandomFace() {
    return fqrand() * (f32)mPr_FACE_TYPE_NUM;
}

s32 mPr_GetRandomOriginalFace() {
    PrivateInfo* priv = common_data.saveFilePrivateInfo;
    PrivateInfo* pr2;
    s32 j;
    PrivateInfo* pr = priv;
    s32 playerExist = 0;
    s32 face;
    s32 i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (pr != NULL && mPr_NullCheckPersonalID(&pr->playerId) == FALSE) {
            playerExist++;
        }
        pr++;
    }

    face = RANDOM(mPr_FACE_TYPE_NUM - playerExist);
    for (; playerExist > 0; playerExist--) {
        pr2 = priv;
        for (j = 0; j < PLAYER_NUM; j++) {
            if (pr2 != NULL && mPr_NullCheckPersonalID(&pr2->playerId) == FALSE && pr2->face == face) {
                face++;

                if (face >= mPr_FACE_TYPE_NUM) {
                    face = mPr_FACE_TYPE0;
                }
                break;
            }

            pr2++;
        }
    }

    return face;
}

u16 mPr_boy_cloth_table[8] = {
    0x2400, 0x2401, 0x2402, 0x2403, 0x2404, 0x2405, 0x2406, 0x2407,
};
u16 mPr_girl_cloth_table[8] = {
    0x2408, 0x2409, 0x240A, 0x240B, 0x240C, 0x240D, 0x240E, 0x240F,
};

u16 mPr_GetRandomCloth(u8 sex) {
    static u16* cloth_table[mPr_SEX_NUM] = { mPr_boy_cloth_table, mPr_girl_cloth_table };
    static s32 cloth_max[mPr_SEX_NUM] = { 8, 8 };

    u16* table;
    s32 idx;
    u16 temp;

    temp = mPr_SEX_NUM;
    if (sex >= temp) {
        sex = mPr_SEX_MALE;
    }

    table = cloth_table[sex];
    idx = RANDOM_F2(cloth_max[sex]);
    temp = table[idx];
    return temp;
}

void mPr_SetNowPrivateCloth() {
    PrivateInfo* priv = common_data.privateInfo;

    if (priv != NULL) {
        mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(priv->gender));
    }
}

void mPr_InitPrivateInfo(PrivateInfo* priv) {
    PrivateInfo* ogPriv;
    u16 pid;
    s32 i;
    s32 face;
    s32 exists;

    exists = FALSE;
    face = mPr_GetRandomOriginalFace();

    priv->playerId.landId = common_data.landInfo.id;
    mLd_CopyLandName(priv->playerId.landName, common_data.landInfo.name);

    pid = RANDOM_F(253);
    ogPriv = common_data.saveFilePrivateInfo;

    for (i = 0; i < PLAYER_NUM - 1; i++, exists = FALSE) {
        s32 j;
        for (j = 0; j < PLAYER_NUM; j++) {

            if (pid == ogPriv[j].playerId.playerId) {
                pid = pid + 1;
                exists = TRUE;
                break;
            }
        }

        if (exists == FALSE) {
            break;
        }
    }

    priv->playerId.playerId = 0xF000 | pid;
    priv->exists = TRUE;
    mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(mPr_SEX_MALE));
    priv->gender = mPr_SEX_MALE;
    priv->inventory.loan = 100;
    priv->face = face;
}

void mPr_InitAnyPrivates(PrivateInfo* info, s32 amount) {

    for (; amount != 0; amount--, info++) {
        mPr_InitPrivateInfo(info);
    }
}

void mPr_CopyPrivateInfo(PrivateInfo* dst, PrivateInfo* src) {
    bcopy(src, dst, sizeof(PrivateInfo));
}

s32 mPr_CheckPrivate(PrivateInfo* priv) {
    s32 res = FALSE;

    if (mLd_CHECK_LAND_ID(priv->playerId.landId)) {
        res = TRUE;
    }

    return res;
}

s32 mPr_CheckCmpPrivate(PrivateInfo* priv0, PrivateInfo* priv1) {
    s32 res = FALSE;

    if (mPr_CheckCmpPersonalID(&priv0->playerId, &priv1->playerId) == TRUE) {
        res = TRUE;
    }

    return res;
}

s32 mPr_GetPrivateIdx(PersonalID_c* pid) {
    PrivateInfo* priv = common_data.saveFilePrivateInfo;
    s32 res = -1;
    s32 i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if ((mPr_NullCheckPersonalID(pid) == FALSE) && (mPr_CheckCmpPersonalID(pid, &priv->playerId) == TRUE)) {
            res = i;
            break;
        }

        priv++;
    }

    return res;
}

s32 mPr_GetPossessionItemIdx(PrivateInfo* priv, u16 item) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

s32 mPr_GetPossessionItemIdxWithCond(PrivateInfo* priv, u16 item, u32 cond) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item && cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

s32 mPr_GetPossessionItemIdxFGTypeWithCond_cancel(PrivateInfo* priv, u16 fg_type, u32 cond) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == fg_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }

            pockets++;
        }
    }

    return idx;
}

s32 mPr_GetPossessionItemIdxItem1Category(PrivateInfo* priv, u8 type) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == 2 && GET_NAME_ITEM_CATEGORY(*pockets) == type) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}

s32 mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(PrivateInfo* priv, u8 itemType, u32 cond) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == 2 && GET_NAME_ITEM_CATEGORY(*pockets) == itemType &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}
s32 mPr_GetPossessionItemIdxKindWithCond(PrivateInfo* priv, u16 kind_start, u16 kind_end, u32 cond) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets >= kind_start && *pockets < kind_end &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                idx = i;
                break;
            }
            pockets++;
        }
    }

    return idx;
}

s32 mPr_GetPossessionItemSum(PrivateInfo* priv, u16 item) {
    s32 sum = 0;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

s32 mPr_GetPossessionItemSumWithCond(PrivateInfo* priv, u16 item, u32 cond) {
    s32 sum = 0;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (*pockets == item && cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

s32 mPr_GetPossessionItemSumFGTypeWithCond_cancel(PrivateInfo* priv, u16 fg_type, u32 cond) {
    s32 sum = 0;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == fg_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

s32 mPr_GetPossessionItemSumItemCategoryWithCond_cancel(PrivateInfo* priv, u8 itemType, u32 cond) {
    s32 sum = 0;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == 2 && GET_NAME_ITEM_CATEGORY(*pockets) == itemType &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

void mPr_SetItemCollectBit(u16 item) {
    u16 furnitureItemNumber = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(item);
    s32 item_type;

    if ((furnitureItemNumber >= 0x1C28 && furnitureItemNumber < 0x1CA8) ||
        (furnitureItemNumber >= 0x1BA8 && furnitureItemNumber < 0x1C28)) {
        return;
    }

    item_type = ACTOR_FGNAME_GET_F000(furnitureItemNumber);

    if (item_type == 1) {

        common_data.privateInfo->catalogFurniture[(furnitureItemNumber - 0x1000) >> 2 >> 5] |=
            (1 << ((furnitureItemNumber - 0x1000) >> 2 & 31));

    } else if (item_type == 2) {
        s32 category = GET_NAME_ITEM_CATEGORY(furnitureItemNumber);
        u16 idx;
        if (category == 0) {
            idx = (furnitureItemNumber - 0x2000);
            common_data.privateInfo->catalogPaper[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 6) {
            idx = furnitureItemNumber - 0x2600;
            common_data.privateInfo->catalogCarpet[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 7) {
            idx = furnitureItemNumber - 0x2700;
            common_data.privateInfo->catalogWallpaper[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 10) {
            idx = furnitureItemNumber - 0x2A00;
            common_data.privateInfo->catalogMusic[idx >> 5] |= (1 << (idx & 31));
        }
    }
}
u16 mPr_DummyPresentToTruePresent() {
    u16 truePresent = 0;

    if (RANDOM(5) != 0) {
        mSP_SelectRandomItem_New(NULL, &truePresent, 1, NULL, 0, 0, 2);
    }

    if (truePresent == 0) {
        truePresent = mFI_GetOtherFruit();
    }

    return truePresent;
}

void mPr_SetPossessionItem(PrivateInfo* priv, s32 idx, u16 item, u32 cond) {

    if (item == 0x251C) {
        item = mPr_DummyPresentToTruePresent();
        cond = mPr_ITEM_COND_PRESENT;
    }

    // FAKEMATCH!!
    priv->inventory.pockets[idx & 0xFFFFFFFF] = item;
    priv->inventory.item_conditions = ((priv->inventory.item_conditions & (~(3 << (idx * 2)))) | (cond << (idx * 2)));

    if (cond == mPr_ITEM_COND_NORMAL) {
        mPr_SetItemCollectBit(item);
    }
}

s32 mPr_SetFreePossessionItem(PrivateInfo* priv, u16 item, u32 cond) {
    s32 idx = mPr_GetPossessionItemIdx(priv, 0);

    if (idx == -1) {
        return 0;
    } else {
        mPr_SetPossessionItem(priv, idx, item, cond);
        return 1;
    }
}

void mPr_AddFirstJobHint(PrivateInfo* priv) {
    u8 hints = priv->hintCount + 1;
    if ((hints & 0x7F) >= 10) {
        hints = 0x80;
    }

    priv->hintCount = hints;
}

s32 mPr_GetFirstJobHintTime(PrivateInfo* priv) {
    s32 hints = priv->hintCount & 0x7F;
    return hints;
}

s32 mPr_CheckFirstJobHint(PrivateInfo* priv) {
    s32 hints = (priv->hintCount >> 7) & 1;

    return hints;
}

s16 mPr_GetMoneyPower() {
    s16 moneyPower = common_data.moneyPower;
    PrivateInfo* priv = common_data.privateInfo;

    if (priv != NULL) {
        switch (priv->destiny.type) {
            case 4: {
                moneyPower += 100;
                break;
            }

            case 3: {
                moneyPower -= 50;
                break;
            }
        }
    }

    if (moneyPower < -80) {
        moneyPower = -80;
    }

    return moneyPower;
}

s16 mPr_GetGoodsPower() {
    s16 goodsPower = common_data.goodsPower;
    s32 type = common_data.privateInfo->destiny.type;

    if (common_data.privateInfo != NULL) {
        type = common_data.privateInfo->destiny.type;

        switch (type) {
            case 5: {
                goodsPower += 30;
                break;
            }

            case 3: {
                goodsPower -= 30;
                break;
            }
        }
    }
    if (goodsPower > 50) {
        goodsPower = 50;
    } else if (goodsPower < -30) {
        goodsPower = -30;
    }
    return goodsPower;
}

s32 mPr_CheckMuseumAddress(PrivateInfo* priv) {
    s32 res = FALSE;

    if (priv != NULL && priv->museumRecord.contacted) {
        res = TRUE;
    }

    return res;
}

s32 mPr_CheckMuseumInfoMail(PrivateInfo* priv) {
    s32 res = FALSE;

    if (priv != NULL && priv->museumRecord.sendInfoMail) {
        res = TRUE;
    }

    return res;
}

s32 mPr_LoadPak_and_SetPrivateInfo2(u8 player, void* pak) {
    PrivateInfo* priv;
    s32 res = FALSE;
    s32 save = func_8007942C_jp(&g_foreigner_private, mNpc_GetInAnimalP(), pak);

    if (save == TRUE) {
        if (player < 4) {
            priv = &common_data.saveFilePrivateInfo[player];
            if (mPr_CheckCmpPrivate(priv, &g_foreigner_private) == TRUE) {
                mPr_CopyPrivateInfo(priv, &g_foreigner_private);
                common_data.privateInfo = priv;
                common_data.playerNumber = player;
                res = TRUE;
            }
        } else {
            s32 i;
            s32 exists;
            priv = common_data.saveFilePrivateInfo;

            for (i = 0; i < PLAYER_NUM; i++, priv++) {
                exists = mPr_CheckCmpPrivate(priv, &g_foreigner_private);
                if (exists == TRUE) {
                    g_foreigner_private.museumRecord.contacted = priv->museumRecord.contacted;
                    mPr_CopyPrivateInfo(priv, &g_foreigner_private);
                    common_data.privateInfo = priv;
                    common_data.playerNumber = i;
                    res = TRUE;
                    break;
                }
            }
            if (exists == FALSE) {
                common_data.privateInfo = &g_foreigner_private;
                common_data.playerNumber = mPR_FOREIGNER_NUMBER;
                res = TRUE;
            }
        }
    }
    return res;
}

void mPr_ClearMotherMailInfo(PrivateMotherMail* motherMail) {
    motherMail->date = mTM_rtcTime_ymd_clear_code;
    bzero(&motherMail->data, sizeof(PrivateMotherMailData));
}

s32 mPr_GetMotherMailPaperType(s32 month, s32 day) {
    static u8 paper_table[lbRTC_MONTHS_MAX] = { 13, 49, 32, 12, 62, 14, 19, 11, 59, 46, 47, 17 };

    PrivateBirthday* birthday = &common_data.privateInfo->birthday;
    s32 paper;

    if (birthday->month == month && birthday->day == day) {
        paper = 1;
    } else if (month == lbRTC_JANUARY && day == 1) {
        paper = 63;
    } else if (month == lbRTC_AUGUST && day == 8) {
        paper = 48;
    } else if (month == lbRTC_DECEMBER && day == 24) {
        paper = 23;
    } else {
        month--;
        paper = paper_table[month];
    }

    return paper - 1;
}

void mPr_GetMotherMail(Mail_c* mail, PersonalID_c* pid, u16 present, s32 stationery, s32 mailNumber) {
    s32 headerBackPos;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom(mail->content.header, &headerBackPos, mail->content.footer, mail->content.body,
                                   mailNumber);
    mail->content.headerBackStart = headerBackPos;
    mail->content.font = 0;
    mail->content.mailType = 4;
    mMl_set_to_plname(mail, pid);
    mail->present = present;
    mail->content.paperType = stationery;
}

s32 mPr_SendMotherMailPost(PersonalID_c* pid, s32 playerNumber, u16 present, s32 stationery, s32 mailNumber) {
    Mail_c* mail;
    mHm_hs_c* home;
    UNUSED s32 pad2;
    s32 mailboxIdx;
    s32 res = FALSE;
    UNUSED s32 pad;

    mail = &l_mpr_mail;
    home = &common_data.homes[mHS_get_arrange_idx(playerNumber)];

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) {
        mailboxIdx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);
        if (mailboxIdx != -1) {
            mPr_GetMotherMail(mail, pid, present, stationery, mailNumber);
            mMl_copy_mail(&home->mailbox[mailboxIdx], mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < 5) {
            mPr_GetMotherMail(mail, pid, present, stationery, mailNumber);
            res = mPO_receipt_proc(mail, 0);
        }
    }

    return res;
}

s32 mPr_SendMotherMailDate(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime) {
    UNUSED s32 pad;
    s32 mailNumber = -1;
    s32 letterNumber;
    u16 present = 0;
    s32 res = FALSE;
    PrivateBirthday* birthday = &common_data.privateInfo->birthday;
    s32 rand;

    if (birthday->month == sendTime->month && birthday->day == sendTime->day) {
        rand = RANDOM2(2.0f);
        mailNumber = 0x184 + rand;
        present = 0x11FC;
    } else if (sendTime->month == sendTime->day) {
        letterNumber = ((sendTime->month) * mPr_MOTHER_MAIL_MONTHLY_NUM) + RANDOM(2.0f);
        mailNumber = 0x162 + letterNumber;
        if (sendTime->month == 1) {
            present = 0x2101;
        } else if (letterNumber == 20) {
            present = 0x2805;
        }
    } else if (sendTime->month == lbRTC_APRIL && sendTime->day == 1) {
        rand = RANDOM2(2.0f);
        mailNumber = rand + 0x180;
    } else {
        if (mEv_check_status(0x1C, 1) == TRUE) {
            rand = RANDOM2(2.0f);
            mailNumber = rand + 0x17C;
        } else if (mEv_check_status(0x1B, 1) == TRUE) {
            rand = RANDOM2(2.0f);
            mailNumber = rand + 0x17E;
        }
    }

    if (mailNumber != -1) {
        if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                   mPr_GetMotherMailPaperType(sendTime->month, sendTime->day), mailNumber) == TRUE) {
            mTM_set_renew_time(&motherMail->date, sendTime);
        }

        res = TRUE;
    }

    return res;
}

s32 mPr_CheckMotherMailMonthly(PrivateMotherMailData* sendData, s32 month, s32 idx) {
    s32 ret;
    if (month == lbRTC_AUGUST) {
        ret = (sendData->august >> (idx)) & 1;
    } else {
        u8 monthlyTemp;
        s32 shift;
        s32 slot;

        month--;
        shift = month * 2;
        slot = shift / 8;
        monthlyTemp = sendData->monthly[slot];
        shift -= slot * 8;

        ret = (monthlyTemp >> (shift + idx)) & 1;
    }

    return ret;
}

s32 mPr_GetMotherMailMonthlyNotSendNum(PrivateMotherMailData* sendData, s32 month) {
    s32 slot;
    s32 notSendNum = 0;
    s32 i;

    if (month == lbRTC_AUGUST) {
        for (i = 0; i < 8; i++) {
            if (((sendData->august >> i) & 1) == 0) {
                notSendNum++;
            }
        }
    } else {
        u8 byte;
        s32 shift;

        month--;
        shift = month * 2;
        slot = shift / 8;
        byte = sendData->monthly[slot];
        shift -= slot * 8;

        for (i = 0; i < 2; i++) {
            if (((byte >> shift) & 1) == 0) {
                notSendNum++;
                shift++;
            }
        }
    }

    return notSendNum;
}

void mPr_SetMotherMailMonthly(PrivateMotherMailData* sendData, s32 month, s32 idx) {
    if (month == lbRTC_AUGUST) {
        sendData->august |= (1 << idx);
    } else {
        s32 slot;
        s32 shift;

        month--;

        shift = month * 2;
        slot = shift / 8;
        shift -= slot * 8;

        sendData->monthly[slot] |= 1 << (shift + idx);
    }
}

void mPr_GetMotherMailMonthlyData(PrivateMotherMailData* sendData, s32* mailNumber, u16* present, s32* eventNumber,
                                  s32 month, s32 notSendNum) {
    s32 mailStartIdx;
    static s32 mail_start_no_table[4] = {
        0x18C,
        0x192,
        0x186,
        0x19E,
    };
    static u16 may_2_item_table[1] = { 0x2469 };
    static u16 december_2_item_table[6] = {
        0x246C, 0x246D, 0x246E, 0x2490, 0x2491, 0x249C,
    };
    s32 selectedEvent;
    s32 i;
    s32 max;

    *present = 0;
    mailStartIdx = 3;

    if (month <= lbRTC_FEBRUARY) {
        mailStartIdx = 3;
    } else if (month <= lbRTC_MAY) {
        mailStartIdx = 0;
    } else if (month <= lbRTC_AUGUST) {
        mailStartIdx = 1;
    } else if (month <= lbRTC_NOVEMBER) {
        mailStartIdx = 2;
    }

    *mailNumber = mail_start_no_table[mailStartIdx];

    selectedEvent = RANDOM(notSendNum);
    max = mPr_MOTHER_MAIL_MONTHLY_NUM;

    max = (month == lbRTC_AUGUST) ? lbRTC_AUGUST : lbRTC_FEBRUARY;

    for (i = 0; i < max; i++) {
        if (mPr_CheckMotherMailMonthly(sendData, month, i) == FALSE) {
            if (selectedEvent <= 0) {
                *eventNumber = i;
                break;
            }

            selectedEvent--;
        }
    }

    *mailNumber += (((month - (mailStartIdx * 3)) * 2) + *eventNumber) - 2;

    if (month == lbRTC_MAY && *eventNumber == 1) {
        *present = may_2_item_table[RANDOM(1.0f)];
    } else if (month == lbRTC_DECEMBER) {
        if (*eventNumber == 0) {
            *present = 0x2800;
        } else {
            *present = december_2_item_table[RANDOM(6)];
        }
    } else if (month == lbRTC_NOVEMBER) {
        *present = 0x2805;
    }
}

s32 mPr_GetMotherMailNormalNotSendNum(PrivateMotherMailData* sendData) {
    u8* shift = &sendData->normal[0];
    s32 notSendNum;
    s32 i;
    s32 j;

    for (i = notSendNum = 0; i < mPr_MOTHER_MAIL_NORMAL_NUM; i++, shift++) {
        for (j = 0; j < 8; j++) {
            if (((*shift >> j) & 1) == 0) {
                notSendNum++;
            }
        }
    }
    return notSendNum;
}

void mPr_SetMotherMailNormal(PrivateMotherMailData* sendData, s32 idx) {
    s32 slot = idx / 8;
    u8* p = &sendData->normal[slot];
    idx -= slot * 8;
    *p |= (1 << idx);
}

s32 mPr_CheckMotherMailNormal(PrivateMotherMailData* sendData, s32 idx) {
    s32 slot = idx / 8;
    u8* p = &sendData->normal[slot];
    s32 ret;
    idx -= slot * 8;
    ret = (*p >> (idx)) & 1;

    return ret;
}

void mPr_GetMotherMailNormalData(PrivateMotherMailData* sendData, s32* mailNumber, u16* present, s32* eventNumber,
                                 s32 noSendNum) {
    s32 selectedEvent;
    s32 i;

    *eventNumber = -1;
    selectedEvent = RANDOM(noSendNum);

    for (i = 0; i < 56; i++) {
        if (mPr_CheckMotherMailNormal(sendData, i) == FALSE) {
            if (selectedEvent <= 0) {
                *eventNumber = i;
                break;
            }

            selectedEvent--;
        }
    }

    *mailNumber = 0x12C + *eventNumber;

    switch (*eventNumber) {
        case 1:
        case 16:
            mSP_SelectRandomItem_New(NULL, present, 1, NULL, 0, 2, 8);
            break;

        case 3:
        case 21:
        case 22:
        case 47:
            *present = mFI_GetOtherFruit();
            break;

        case 12:
            *present = 0x2100;
            break;

        case 37:
            *present = 0x10E8;
            break;

        case 38:
            *present = 0x13B0;
            break;

        case 40:
            mSP_RandomUmbSelect(present, 1);
            break;

        default:
            *present = 0;
            break;
    }
}

void mPr_SendMotherMailNormal(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime) {
    UNUSED s32 pad2;
    s32 monthlyNotSendNum;
    s32 notSendNum;
    UNUSED s32 pad;
    s32 mailNumber;
    s32 eventNumber;
    u16 present;

    mailNumber = -1;
    present = 0;
    monthlyNotSendNum = 0;

    if (RANDOM(100) < 20) {
        notSendNum = mPr_GetMotherMailNormalNotSendNum(&motherMail->data);
        if (notSendNum == 0) {
            bzero(&motherMail->data, sizeof(PrivateMotherMailData));
            monthlyNotSendNum = mPr_GetMotherMailMonthlyNotSendNum(&motherMail->data, sendTime->month);
        }
        if (monthlyNotSendNum > 0) {
            mPr_GetMotherMailMonthlyData(&motherMail->data, &mailNumber, &present, &eventNumber, sendTime->month,
                                         monthlyNotSendNum);

            if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                       mPr_GetMotherMailPaperType(sendTime->month, sendTime->day),
                                       mailNumber) == TRUE) {
                mPr_SetMotherMailMonthly(&motherMail->data, sendTime->month, eventNumber);
            }
        } else {
            mPr_GetMotherMailNormalData(&motherMail->data, &mailNumber, &present, &eventNumber, notSendNum);

            if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                       mPr_GetMotherMailPaperType(sendTime->month, sendTime->day),
                                       mailNumber) == TRUE) {
                mPr_SetMotherMailNormal(&motherMail->data, eventNumber);
            }
        }
    }

    mTM_set_renew_time(&motherMail->date, sendTime);
}

void mPr_SendMotherMail(PrivateMotherMail* motherMail, lbRTC_time_c* sendTime) {
    if (mPr_SendMotherMailDate(motherMail, sendTime) == FALSE) {
        mPr_SendMotherMailNormal(motherMail, sendTime);
    }
}

void mPr_SendMailFromMother() {
    PrivateInfo* priv = common_data.privateInfo;
    UNUSED s32 pad;
    s32 playerNumber = common_data.playerNumber;
    lbRTC_ymd_t* mailDate;
    lbRTC_time_c* rtcTime = &common_data.time.rtcTime;

    if (mLd_PlayerManKindCheckNo(playerNumber) == FALSE && priv != NULL &&
        mPr_NullCheckPersonalID(&priv->playerId) == FALSE) {
        mailDate = &common_data.motherMailInfo[playerNumber].date;

        if (mailDate->year != mTM_rtcTime_ymd_clear_code.year && mailDate->month != mTM_rtcTime_ymd_clear_code.month &&
            mailDate->day != mTM_rtcTime_ymd_clear_code.day) {
            if (mailDate->year != rtcTime->year || mailDate->month != rtcTime->month || mailDate->day != rtcTime->day) {
                mPr_SendMotherMail(&common_data.motherMailInfo[playerNumber], rtcTime);
            }
        } else {
            mTM_set_renew_time(mailDate, rtcTime);
        }
    }
}

void mPr_GetForeingerAnimalMail(Mail_c* mail, PrivateInfo* priv, PrivateAnimalMemory* animalMemory) {
    AnmPersonalID_c pid;
    s32 mailNumber;
    char npcName[6];
    u8 header[20];
    u8 footer[26];
    s32 mailfct;
    u8 looks;
    u16 id;
    s32 headerBackStart;

    looks = mNpc_GetLooks(animalMemory->npcId);
    mailfct = RANDOM(3);
    mailNumber = 0xFC;
    mailfct = mailfct + (looks * 3);
    mailNumber += mailfct;
    mHandbill_Set_free_str(0, priv->playerId.playerName, PLAYER_NAME_LEN);
    id = animalMemory->npcId;
    mNpc_LoadNpcNameString(npcName, (s8)id);
    mHandbill_Set_free_str(1, npcName, ANIMAL_NAME_LEN);
    mHandbill_Set_free_str(2, animalMemory->landName, LAND_NAME_SIZE);
    mHandbill_Set_free_str(3, priv->playerId.landName, LAND_NAME_SIZE);
    mHandbill_Load_HandbillFromRom2(header, 20, &headerBackStart, footer, 26, mail->content.body, mailNumber);
    mem_copy(mail->content.header, header, 10);
    mem_copy(mail->content.footer, footer, 16);

    mail->content.headerBackStart = headerBackStart;
    mail->content.font = 0;
    mail->content.mailType = 0;
    mail->present = 0;
    mail->content.paperType = mNpc_GetPaperType();

    pid.npcId = animalMemory->npcId;
    pid.landId = 0x3000;
    mLd_CopyLandName(pid.landName, animalMemory->landName);
    pid.nameId = animalMemory->npcId & 0xFF;
    pid.looks = looks;

    mMl_set_mail_name_npcinfo(&mail->header.sender, &pid);
    mPr_CopyPersonalID(&mail->header.recipient.personalID, &priv->playerId);
    mail->header.recipient.type = 0;
}

void mPr_SendForeingerAnimalMail(PrivateInfo* priv) {
    Mail_c* mail = &l_mpr_mail;
    PrivateAnimalMemory* animalMemory = &priv->animalMemory;

    if (mLd_PlayerManKindCheck() == FALSE) {
        if (animalMemory->npcId != 0xFFFF && ACTOR_FGNAME_GET_F000(animalMemory->npcId) == 14 &&
            mPO_get_keep_mail_sum() < 5) {
            mMl_clear_mail(mail);
            mPr_GetForeingerAnimalMail(mail, priv, animalMemory);
            mPO_receipt_proc(mail, 0);
            mPr_ClearAnimalMemory(animalMemory);
        }
    }
}

void mPr_StartSetCompleteTalkInfo() {
    if (common_data.privateInfo->completedFish == -1) {
        common_data.privateInfo->completeFishInsectFlags |= (1 << 0);
    }

    if (common_data.privateInfo->completedInsect == -1) {
        common_data.privateInfo->completeFishInsectFlags |= (1 << 2);
    }
}

void mPr_SetCompleteTalk(u8* flags, s32 type) {
    *flags |= (1 << ((type * 2) + 1));
}

s32 mPr_GetCompleteTalk(u8 flags, s32 type) {
    return (flags >> ((type * 2) + 1)) & 1;
}

void mPr_SetFishCompleteTalk() {
    mPr_SetCompleteTalk(&common_data.privateInfo->completeFishInsectFlags, 0);
}

s32 mPr_CheckFishCompleteTalk(u8 playerNumber) {
    s32 res = FALSE;

    if (playerNumber < PLAYER_NUM &&
        mPr_GetCompleteTalk(common_data.saveFilePrivateInfo[playerNumber].completeFishInsectFlags, 0) == TRUE) {
        res = TRUE;
    }

    return res;
}

void mPr_SetInsectCompleteTalk() {
    mPr_SetCompleteTalk(&common_data.privateInfo->completeFishInsectFlags, 1);
}

s32 mPr_CheckInsectCompleteTalk(u8 playerNumber) {
    s32 res = FALSE;

    if (playerNumber < PLAYER_NUM &&
        mPr_GetCompleteTalk(common_data.saveFilePrivateInfo[playerNumber].completeFishInsectFlags, 1) == TRUE) {
        res = TRUE;
    }

    return res;
}

s32 mPr_GetTalkPermission(u8 flags, s32 type) {
    s32 base = type * 2;
    s32 talk = base + 1;

    s32 res = FALSE;
    if (((flags >> base) & 1) == 0 || ((flags >> talk) & 1) == 0) {
        res = TRUE;
    }

    return res;
}

s32 mPr_GetFishCompTalkPermission() {
    s32 res = FALSE;

    if (common_data.privateInfo->completedFish == -1) {
        res = mPr_GetTalkPermission(common_data.privateInfo->completeFishInsectFlags, 0);
    }

    return res;
}

s32 mPr_GetInsectCompTalkPermission() {
    s32 res = FALSE;

    if (common_data.privateInfo->completedInsect == -1) {
        res = mPr_GetTalkPermission(common_data.privateInfo->completeFishInsectFlags, 1);
    }

    return res;
}

void mPr_ClearMapInfo(mPr_map_info_c* mapInfo, s32 max) {
    for (; max != 0; max--) {
        mLd_ClearLandName(mapInfo->landName);
        mapInfo->landId = 0;
        mapInfo++;
    }
}

void mPr_CopyMapInfo(mPr_map_info_c* dst, mPr_map_info_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(mPr_map_info_c));
}

void mPr_SetMapThisLand(mPr_map_info_c* mapInfo) {
    if (mapInfo != NULL) {
        mLd_CopyLandName(mapInfo->landName, common_data.landInfo.name);
        mapInfo->landId = common_data.landInfo.id;
    }
}

s32 mPr_GetMapFreeIdx(mPr_map_info_c* mapInfo, s32 max) {
    s32 res = -1;
    s32 i;

    for (i = 0; i < max; i++) {
        if (!mLd_CheckId(mapInfo->landId) || mLd_NullCheckLandName(mapInfo->landName) == TRUE) {
            res = i;
            break;
        }

        mapInfo++;
    }

    return res;
}

s32 mPr_GetLandMapIdx(mPr_map_info_c* mapInfo, s32 max, LandInfo* landInfo) {
    s32 res = -1;

    if (mapInfo != NULL && landInfo != NULL) {
        s32 i;

        for (i = 0; i < max; i++) {
            if (mLd_CheckCmpLand(mapInfo->landName, mapInfo->landId, landInfo->name, landInfo->id) == TRUE) {
                res = i;
                break;
            }

            mapInfo++;
        }
    }

    return res;
}

s32 mPr_GetThisLandMapIdx(mPr_map_info_c* map_info, s32 max) {
    return mPr_GetLandMapIdx(map_info, max, &common_data.landInfo);
}

void mPr_PushMapInfo(mPr_map_info_c* map_info, s32 max) {
    if (map_info != NULL) {
        max--;

        if (max > 0) {
            for (; max > 0; max--) {
                mPr_CopyMapInfo(map_info, map_info + 1);
                map_info++;
            }
        }

        mPr_ClearMapInfo(map_info, 1);
    }
}

void mPr_SetNewMap(mPr_map_info_c* map_info, s32 max) {
    if (map_info != NULL && mPr_GetThisLandMapIdx(map_info, max) == -1) {
        s32 free_idx = mPr_GetMapFreeIdx(map_info, max);
        if (free_idx != -1) {
            map_info += free_idx;
        } else {
            mPr_PushMapInfo(map_info, max);
            free_idx = max - 1;
            map_info += free_idx;
        }

        if (map_info != NULL) {
            mPr_SetMapThisLand(map_info);
        }
    }
}

void mPr_SetUseMap(mPr_map_info_c* map_info, s32 max) {
    if (mPr_GetThisLandMapIdx(map_info, max) != -1) {
        common_data.unk_10140 = 1;
    }
}

void mPr_RenewalMapInfo(mPr_map_info_c* mapInfo, s32 max, LandInfo* landInfo) {
    mPr_map_info_c map_save;

    s32 map_idx = mPr_GetLandMapIdx(mapInfo, max, landInfo);
    if (map_idx != -1) {
        mPr_CopyMapInfo(&map_save, mapInfo + map_idx);
        mPr_PushMapInfo(mapInfo + map_idx, max - map_idx);

        map_idx = mPr_GetMapFreeIdx(mapInfo, max);
        if (map_idx != -1) {
            mPr_CopyMapInfo(mapInfo + map_idx, &map_save);
        }
    }
}

void mPr_RandomSetPlayerData_title_demo() {
    PrivateInfo* priv = common_data.privateInfo;

    priv->gender = RANDOM(4);
    priv->gender &= 1;
    mPlib_change_player_cloth_info_lv2(priv, mPr_GetRandomCloth(priv->gender));
    priv->face = mPr_GetRandomFace();
}

void mPr_PrintMapInfo_debug(gfxprint* gfxprint) {
    PrivateInfo* priv = common_data.privateInfo;
    mPr_map_info_c* mapInfo;
    int i;

    if (priv != NULL) {
        mapInfo = priv->maps;
        gfxprint_color(gfxprint, 30, 100, 100, 255);
        gfxprint_locate8x8(gfxprint, 3, 21);
        gfxprint_printf(gfxprint, "%04x ", common_data.landInfo.id);

        gfxprint_locate8x8(gfxprint, 3, 22);
        gfxprint_color(gfxprint, 30, 200, 70, 255);

        for (i = 0; i < mPr_FOREIGN_MAP_COUNT; i++) {
            if (i == 4) {
                gfxprint_locate8x8(gfxprint, 3, 23);
            }

            if (mLd_CheckId(mapInfo->landId) == TRUE) {
                gfxprint_printf(gfxprint, "%04x ", mapInfo->landId);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            mapInfo++;
        }
    }
}
