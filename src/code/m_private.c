#include "m_private.h"
#include "m_lib.h"
#include "m_land.h"
#include "m_name_table.h"
#include "m_time.h"
#include "m_player_lib.h"
#include "6E2300.h"
#include "m_field_info.h"
#include "6E30B0.h" 
#include "69CB30.h"
#include "m_handbill.h"
#include "m_house.h"
#include "6DA460.h"
#include "6EDD10.h"

Mail_c l_mpr_mail;
PrivateInfo g_foreigner_private; 

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

        name =(common_data.privateInfo)->playerId.playerName;
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

s32 mPr_GetRandomFace(){
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
    static u16* cloth_table[mPr_SEX_NUM] = {mPr_boy_cloth_table, mPr_girl_cloth_table};
    static s32 cloth_max[mPr_SEX_NUM] = {8, 8};

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
    PrivateInfo* o_priv;
    u16 pid;  
    s32 i;
    s32 face;
    s32 exists;
 

    exists = FALSE;
    face = mPr_GetRandomOriginalFace();

    priv->playerId.landId = common_data.landInfo.id;
    mLd_CopyLandName(priv->playerId.landName, common_data.landInfo.name);

    pid = RANDOM_F(253);
    o_priv = common_data.saveFilePrivateInfo;  
    
    for (i = 0; i < PLAYER_NUM - 1; i++, exists = FALSE) {
        s32 j;
        for (j = 0; j < PLAYER_NUM; j++) {
            
            if (pid == o_priv[j].playerId.playerId) {
                pid = pid +1 ;
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

void mPr_InitAnyPrivates(PrivateInfo* info, s32 amount){
    
    for(; amount != 0; amount--,info++){
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
//
s32 mPr_GetPossessionItemIdx(PrivateInfo* priv, u16 item) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        int i;

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
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) ) {
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

s32 mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(PrivateInfo* priv, u8 item1_type, u32 cond) {
    s32 idx = -1;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == 2 && GET_NAME_ITEM_CATEGORY(*pockets) == item1_type &&
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

s32 mPr_GetPossessionItemSumItemCategoryWithCond_cancel(PrivateInfo* priv, u8 item1_type, u32 cond) {
    s32 sum = 0;

    if (priv != NULL) {
        u16* pockets = priv->inventory.pockets;
        s32 i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ACTOR_FGNAME_GET_F000(*pockets) == 2 && GET_NAME_ITEM_CATEGORY(*pockets) == item1_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

void mPr_SetItemCollectBit(u16 item) {
    u16 ftr_item_no = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(item);
    s32 item_type;

    if ((ftr_item_no >= 0x1C28 && ftr_item_no < 0x1CA8) ||
        (ftr_item_no >= 0x1BA8 && ftr_item_no < 0x1C28)) {
        return;
    }

    item_type = ACTOR_FGNAME_GET_F000(ftr_item_no);

    if (item_type == 1) {

        common_data.privateInfo->catalogFurniture[(ftr_item_no - 0x1000) >> 2 >> 5] |= (1 << ((ftr_item_no - 0x1000) >> 2 & 31));

    } else if (item_type == 2) {
        s32 category = GET_NAME_ITEM_CATEGORY(ftr_item_no);
        u16 idx;
        if (category == 0) {
             idx = (ftr_item_no - 0x2000);
            common_data.privateInfo->catalogPaper[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 5) { 
             idx = ftr_item_no - 0x2600;
            common_data.privateInfo->catalogCarpet[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 6) {
             idx = ftr_item_no - 0x2700;
            common_data.privateInfo->catalogWallpaper[idx >> 5] |= (1 << (idx & 31));
        } else if (category == 9) {
             idx =ftr_item_no - 0x2A00; 
            common_data.privateInfo->catalogMusic[idx >> 5] |= (1 << (idx & 31));
        }
    }
}
u16 mPr_DummyPresentToTruePresent() {
    u16 true_present = 0;

    /* 80% chance of rolling furniture from town's rare list */
    if (RANDOM(5) != 0) {
        mSP_SelectRandomItem_New(NULL, &true_present, 1, NULL, 0, 0, 2);
    }

    /* 20% (and default case) to get random non-native fruit */
    if (true_present == 0) {
        true_present = mFI_GetOtherFruit();
    } 

    return true_present;
}

void mPr_SetPossessionItem(PrivateInfo* priv, s32 idx, u16 item, u32 cond) {

    if(item == 0x251C){
        item = mPr_DummyPresentToTruePresent(); 
        cond = mPr_ITEM_COND_PRESENT;
    }
    // FAKEMATCH!!
    priv->inventory.pockets[idx & 0xFFFFFFFF] = item;
    priv->inventory.item_conditions =
        ((priv->inventory.item_conditions & (~(3 << (idx * 2)))) | (cond << (idx * 2)));

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
        hints = 0x80;  // signal all hints have been given
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
                common_data.playerNumber = 4;
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
    static u8 paper_table[lbRTC_MONTHS_MAX] = {13, 49, 32, 12, 62, 14, 19, 11, 59, 46, 47, 17};

    PrivateBirthday* birthday = &common_data.privateInfo->birthday;
    s32 paper;

    /* TODO: should paper be enums? */
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

void mPr_GetMotherMail(Mail_c* mail, PersonalID_c* pid, u16 present, s32 stationery, s32 mail_no) {
    s32 headerBackPos;

    mMl_clear_mail(mail);
    mHandbill_Load_HandbillFromRom(mail->content.header, &headerBackPos, mail->content.footer, mail->content.body,
                                   mail_no);
    mail->content.headerBackStart = headerBackPos;
    mail->content.font = 0;
    mail->content.mailType = 4;
    mMl_set_to_plname(mail, pid); 
    mail->present = present; 
    mail->content.paperType = stationery;
}

s32 mPr_SendMotherMailPost(PersonalID_c* pid, s32 player_no, u16 present, int stationery, s32 mail_no) {
    Mail_c* mail;
    mHm_hs_c* home; 
    UNUSED s32 pad2;
    s32 mailbox_idx;
    s32 res = FALSE;   
    UNUSED s32 pad; 

    mail = &l_mpr_mail;
    home = &common_data.homes[mHS_get_arrange_idx(player_no)];

    if (mPr_CheckCmpPersonalID(pid, &home->ownerID) == TRUE) { 
         mailbox_idx = mMl_chk_mail_free_space(home->mailbox, HOME_MAILBOX_SIZE);
        if (mailbox_idx != -1) {
            mPr_GetMotherMail(mail, pid, present, stationery, mail_no);
            mMl_copy_mail(&home->mailbox[mailbox_idx], mail);
            res = TRUE;
        } else if (mPO_get_keep_mail_sum() < 5) {
            mPr_GetMotherMail(mail, pid, present, stationery, mail_no);
            res = mPO_receipt_proc(mail, 0);
        }
    }

    return res;
}

s32 mPr_SendMotherMailDate(PrivateMotherMail* mother_mail, lbRTC_time_c* send_time) {
    UNUSED s32 pad;
    s32 mail_no = -1;
    s32 letter_num;
    u16 present = 0;
    s32 res = FALSE; 
    PrivateBirthday* birthday = &common_data.privateInfo->birthday;
    s32 rand;
 
    if (birthday->month == send_time->month &&
        birthday->day == send_time->day) {
        rand = RANDOM2(2.0f);
        mail_no = 0x184 + rand; 
        present = 0x11FC;
    } else if (send_time->month == send_time->day) {
        letter_num = ((send_time->month) * mPr_MOTHER_MAIL_MONTHLY_NUM) + RANDOM(2.0f);
        mail_no = 0x162 + letter_num;
        if (send_time->month == 1) {
            present = 0x2101;
        } else if (letter_num == 20) {
            present = 0x2805;
        }
    } else if (send_time->month == lbRTC_APRIL && send_time->day == 1) {
        rand = RANDOM2(2.0f);
        mail_no = rand + 0x180;
    } else {
        if (mEv_check_status(0x1C, 1) == TRUE) {
            rand = RANDOM2(2.0f);
            mail_no = rand + 0x17C;
        } else if (mEv_check_status(0x1B, 1) == TRUE) {
            rand = RANDOM2(2.0f);
            mail_no = rand + 0x17E;
        }
    }

    if (mail_no != -1) {
        if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                   mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
            mTM_set_renew_time(&mother_mail->date, send_time);
        }

        res = TRUE;
    }

    return res;
}

s32 mPr_CheckMotherMailMonthly(PrivateMotherMailData* send_data, s32 month, s32 idx) {
    s32 ret;
    if (month == lbRTC_AUGUST) {
        ret = (send_data->august >> (idx)) & 1;
    } else {
        u8 monthlyTemp;
        s32 shift;
        s32 slot;
        
        month--;
        shift = month * 2;
        slot = shift / 8;
        monthlyTemp = send_data->monthly[slot];
        shift -= slot * 8;

        ret = (monthlyTemp >> (shift + idx)) & 1;
    }

    return ret;
}

s32 mPr_GetMotherMailMonthlyNotSendNum(PrivateMotherMailData* send_data, s32 month) {
    s32 slot;
    s32 not_send_num = 0;
    s32 i;

    if (month == lbRTC_AUGUST) {
        for (i = 0; i < 8; i++) {
            if (((send_data->august >> i) & 1) == 0) {
                not_send_num++;
            }
        }
    } else {
        u8 byte;
        s32 shift;

        month--;
        shift = month * 2;
        slot = shift / 8;
        byte = send_data->monthly[slot];
        shift -= slot * 8;
        

        for (i = 0; i < 2; i++) {
            if (((byte >> shift) & 1) == 0) {
                not_send_num++;
                shift++;
            }
        }
    }

    return not_send_num;
}

void mPr_SetMotherMailMonthly(PrivateMotherMailData* send_data, s32 month, s32 idx) {
    if (month == lbRTC_AUGUST) {
        send_data->august |= (1 << idx);
    } else {
        s32 slot;
        s32 shift;

        month--;

        shift = month * 2;
        slot = shift / 8;
        shift -= slot * 8;
 
        send_data->monthly[slot] |= 1 << (shift + idx); 
    }
}

void mPr_GetMotherMailMonthlyData(PrivateMotherMailData* send_data, s32* mail_no, u16* present,
                                  s32* event_no, s32 month, s32 not_send_num) {
    s32 mail_start_idx; 
    static s32 mail_start_no_table[4] = {0x18C, 0x192, 0x186, 0x19E};
    static u16 may_2_item_table[1] = {0x2469};  // fortune shirt
    static u16 december_2_item_table[6] = {
        0x246C,  // aurora knit
        0x246E,  // winter sweater
        0x246F,  // go-go shirt
        0x2490,  // deer shirt
        0x2491,  // blue check shirt
        0x249C   // fish knit
    };
    s32 selected_event; 
    s32 i;   
    s32 max;  

 

    *present = 0; 
    mail_start_idx = 3;

    if (month <= lbRTC_FEBRUARY) {
        mail_start_idx = 3;
    } else if (month <= lbRTC_MAY) {
        mail_start_idx = 0;
    } else if (month <= lbRTC_AUGUST) {
        mail_start_idx = 1;
    } else if (month <= lbRTC_NOVEMBER) {
        mail_start_idx = 2;
    }

    *mail_no = mail_start_no_table[mail_start_idx];

    selected_event = RANDOM(not_send_num);
    max = mPr_MOTHER_MAIL_MONTHLY_NUM;
    
    max = (month == lbRTC_AUGUST) ? lbRTC_AUGUST : lbRTC_FEBRUARY;
    

    for (i = 0; i < max; i++) { 
        if (mPr_CheckMotherMailMonthly(send_data, month, i) == FALSE) {
            if (selected_event <= 0) {
                *event_no = i;
                break;
            }

            selected_event--;
        }
    }

    *mail_no += (month - ((mail_start_idx * 3) << 1)) + *event_no - 2;

    if (month == lbRTC_MAY && *event_no == 1) { 
        *present = may_2_item_table[RANDOM(1.0f)];
    } else if (month == lbRTC_DECEMBER) {
        if (*event_no == 0) { 
            *present = 0x2800;
        } else {
            *present = december_2_item_table[RANDOM(6)];
        }
    } else if (month == lbRTC_NOVEMBER) {
        *present = 0x2805;
    }
}

s32 mPr_GetMotherMailNormalNotSendNum(PrivateMotherMailData* send_data) {
    u8* shift = &send_data->normal[0];
    s32 not_send_num;
    s32 i, j;

    for (i = not_send_num = 0; i < mPr_MOTHER_MAIL_NORMAL_NUM; i++, shift++) {
        for (j = 0; j < 8; j++) {
            if (((*shift >> j) & 1) == 0) {
                not_send_num++;
            }
        }
    }
    return not_send_num;
}


void mPr_SetMotherMailNormal(PrivateMotherMailData* send_data, s32 idx) {
    s32 slot = idx / 8;
    u8 *p = &send_data->normal[slot];
    idx -= slot * 8;
    *p |= (1 << idx);
}

s32 mPr_CheckMotherMailNormal(PrivateMotherMailData* send_data, s32 idx) {
    s32 slot = idx / 8;
    u8* p = &send_data->normal[slot];
    s32 ret;
    idx -= slot * 8;  
    ret =(*p >> (idx)) & 1; 
    
    return ret;
}

void mPr_GetMotherMailNormalData(PrivateMotherMailData* send_data, s32* mail_no, u16* present, s32* event_no,
                                 s32 no_send_num) {
    s32 selected_event;
    s32 i;
 
    *event_no = -1;
    selected_event = RANDOM(no_send_num);

    for (i = 0; i < 56; i++) {
        if (mPr_CheckMotherMailNormal(send_data, i) == FALSE) {
            if (selected_event <= 0) {
                *event_no = i;
                break;
            }

            selected_event--;
        }
    }

    *mail_no = 0x12C + *event_no;

    switch (*event_no) {
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

void mPr_SendMotherMailNormal(PrivateMotherMail* mother_mail, lbRTC_time_c* send_time) {
  UNUSED s32 pad2;
  s32 monthly_not_send_num;
  s32 not_send_num;
  UNUSED s32 pad;
  s32 mail_no;
  s32 event_no;
  u16 present;


    mail_no = -1;
    present = 0;
    monthly_not_send_num = 0;  

    if (RANDOM(100) < 20) {
        not_send_num = mPr_GetMotherMailNormalNotSendNum(&mother_mail->data);
        if (not_send_num == 0) {
            bzero(&mother_mail->data, sizeof(PrivateMotherMailData));
            monthly_not_send_num = mPr_GetMotherMailMonthlyNotSendNum(&mother_mail->data, send_time->month);
        }
        if (monthly_not_send_num > 0) {
            mPr_GetMotherMailMonthlyData(&mother_mail->data, &mail_no, &present, &event_no, send_time->month,
                                         monthly_not_send_num);

            if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                       mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
                mPr_SetMotherMailMonthly(&mother_mail->data, send_time->month, event_no);
            }
        } else {
            mPr_GetMotherMailNormalData(&mother_mail->data, &mail_no, &present, &event_no, not_send_num);

            if (mPr_SendMotherMailPost(&common_data.privateInfo->playerId, common_data.playerNumber, present,
                                       mPr_GetMotherMailPaperType(send_time->month, send_time->day), mail_no) == TRUE) {
                mPr_SetMotherMailNormal(&mother_mail->data, event_no);
            }
        }
    }
 
    mTM_set_renew_time(&mother_mail->date, send_time);
}

void mPr_SendMotherMail(PrivateMotherMail* mother_mail, lbRTC_time_c* send_time) {
    if (mPr_SendMotherMailDate(mother_mail, send_time) == FALSE) {
        mPr_SendMotherMailNormal(mother_mail, send_time);
    }
}

void mPr_SendMailFromMother() {
    PrivateInfo* priv = common_data.privateInfo;
    UNUSED s32 pad;  
    s32 player_no = common_data.playerNumber;
    lbRTC_ymd_t* mail_date;
    lbRTC_time_c* rtc_time = &common_data.time.rtcTime; 


    if (mLd_PlayerManKindCheckNo(player_no) == FALSE && priv != NULL &&
        mPr_NullCheckPersonalID(&priv->playerId) == FALSE) {
        mail_date = &common_data.motherMailInfo[player_no].date; 

        if (mail_date->year != mTM_rtcTime_ymd_clear_code.year &&
            mail_date->month != mTM_rtcTime_ymd_clear_code.month && mail_date->day != mTM_rtcTime_ymd_clear_code.day) {
            if (mail_date->year != rtc_time->year || mail_date->month != rtc_time->month ||
                mail_date->day != rtc_time->day) {
                mPr_SendMotherMail(&common_data.motherMailInfo[player_no], rtc_time);
            }
        } else {
            mTM_set_renew_time(mail_date, rtc_time); 
        }
    }
}

void mPr_GetForeingerAnimalMail(Mail_c* mail, PrivateInfo* priv, PrivateAnimalMemory* anm_mem) {
    AnmPersonalID_c pid;
    s32 mailNo;
    char npcName[6];
    u8 header[20];
    u8 footer[26];
    s32 mailfct;
    u8 looks;
    u16 id;
    s32 headerBackStart;

    looks = mNpc_GetLooks(anm_mem->npcId);
    mailfct = RANDOM(3);
    mailNo = 0xFC;
    mailfct = mailfct + (looks * 3);
    mailNo += mailfct;
    mHandbill_Set_free_str(0, priv->playerId.playerName, PLAYER_NAME_LEN);
    id = anm_mem->npcId;
    mNpc_LoadNpcNameString(npcName, (s8)id);
    mHandbill_Set_free_str(1, npcName, ANIMAL_NAME_LEN);
    mHandbill_Set_free_str(2, anm_mem->landName, LAND_NAME_SIZE);
    mHandbill_Set_free_str(3, priv->playerId.landName, LAND_NAME_SIZE);
    mHandbill_Load_HandbillFromRom2(header, 20, &headerBackStart, footer, 26, mail->content.body, mailNo);
    mem_copy(mail->content.header, header, 10);
    mem_copy(mail->content.footer, footer, 16);

    mail->content.headerBackStart = headerBackStart;
    mail->content.font = 0;
    mail->content.mailType = 0;
    mail->present = 0;
    mail->content.paperType = mNpc_GetPaperType();

    pid.npcId = anm_mem->npcId;
    pid.landId = 0x3000;
    mLd_CopyLandName(pid.landName, anm_mem->landName);
    pid.nameId = anm_mem->npcId & 0xFF;
    pid.looks = looks;

    mMl_set_mail_name_npcinfo(&mail->header.sender, &pid);
    mPr_CopyPersonalID(&mail->header.recipient.personalID, &priv->playerId);
    mail->header.recipient.type = 0;
}

void mPr_SendForeingerAnimalMail(PrivateInfo* priv) {
    Mail_c* mail = &l_mpr_mail;
    PrivateAnimalMemory* anm_mem = &priv->animalMemory;

    if (mLd_PlayerManKindCheck() == FALSE) {
        if (anm_mem->npcId != 0xFFFF && ACTOR_FGNAME_GET_F000(anm_mem->npcId) == 14 &&
            mPO_get_keep_mail_sum() < 5) { 
            mMl_clear_mail(mail);
            mPr_GetForeingerAnimalMail(mail, priv, anm_mem);
            mPO_receipt_proc(mail, 0);
            mPr_ClearAnimalMemory(anm_mem);
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

void mPr_SetCompleteTalk(u8* comp_insect_fish_flags, s32 type) { 
    *comp_insect_fish_flags |= (1 << ((type * 2) + 1)); 
}

s32 mPr_GetCompleteTalk(u8 comp_insect_fish_flags, s32 type) {
    return (comp_insect_fish_flags >> ((type * 2) + 1)) & 1;
}

void mPr_SetFishCompleteTalk() { 
    mPr_SetCompleteTalk(&common_data.privateInfo->completeFishInsectFlags, 0); 
}

s32 mPr_CheckFishCompleteTalk(u8 player_no) {
    s32 res = FALSE;

    if (player_no < 4 &&
        mPr_GetCompleteTalk(common_data.saveFilePrivateInfo[player_no].completeFishInsectFlags, 0) == TRUE) {
        res = TRUE;
    }

    return res;
}

void mPr_SetInsectCompleteTalk() {
    mPr_SetCompleteTalk(&common_data.privateInfo->completeFishInsectFlags, 1);
}

s32 mPr_CheckInsectCompleteTalk(u8 player_no) {
    s32 res = FALSE;

    if (player_no < 4 &&
        mPr_GetCompleteTalk(common_data.saveFilePrivateInfo[player_no].completeFishInsectFlags, 1) == TRUE) {
        res = TRUE;
    }

    return res;
}

s32 mPr_GetTalkPermission(u8 comp_insect_fish_flags, s32 type) {
    s32 base = type * 2;
    s32 talk = base + 1;

    s32 res = FALSE;
    if (((comp_insect_fish_flags >> base) & 1) == 0 || ((comp_insect_fish_flags >> talk) & 1) == 0) {
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

void mPr_SetMapThisLand(mPr_map_info_c* map_info) {
    if (map_info != NULL) {
        mLd_CopyLandName(map_info->landName, common_data.landInfo.name);
        map_info->landId = common_data.landInfo.id;
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

s32 mPr_GetLandMapIdx(mPr_map_info_c* map_info, s32 max, LandInfo* land_info) {
    s32 res = -1;

    if (map_info != NULL && land_info != NULL) {
        s32 i;

        for (i = 0; i < max; i++) {
            if (mLd_CheckCmpLand(map_info->landName, map_info->landId, land_info->name, land_info->id) == TRUE) {
                res = i;
                break;
            }

            map_info++;
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

void mPr_SetUseMap(mPr_map_info_c* map_info, s32 max){
    if(mPr_GetThisLandMapIdx(map_info, max) != -1){
        common_data.unk_10140 = 1;
    }
}

void mPr_RenewalMapInfo(mPr_map_info_c* map_info, s32 max, LandInfo* land_info) {
    mPr_map_info_c map_save;

    s32 map_idx = mPr_GetLandMapIdx(map_info, max, land_info);
    if (map_idx != -1) {
        mPr_CopyMapInfo(&map_save, map_info + map_idx);
        mPr_PushMapInfo(map_info + map_idx, max - map_idx);

        map_idx = mPr_GetMapFreeIdx(map_info, max);
        if (map_idx != -1) {
            mPr_CopyMapInfo(map_info + map_idx, &map_save);
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
    mPr_map_info_c* map_info;
    int i;

    if (priv != NULL) {
        map_info = priv->maps;
        gfxprint_color(gfxprint, 30, 100, 100, 255);
        gfxprint_locate8x8(gfxprint, 3, 21);
        gfxprint_printf(gfxprint, "%04x ", common_data.landInfo.id);

        gfxprint_locate8x8(gfxprint, 3, 22);
        gfxprint_color(gfxprint, 30, 200, 70, 255);

        for (i = 0; i < mPr_FOREIGN_MAP_COUNT; i++) {
            if (i == 4) {
                gfxprint_locate8x8(gfxprint, 3, 23);
            }

            if (mLd_CheckId(map_info->landId) == TRUE) {
                gfxprint_printf(gfxprint, "%04x ", map_info->landId);
            } else {
                gfxprint_printf(gfxprint, "**** ");
            }

            map_info++;
        }
    }
}

