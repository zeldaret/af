#include "m_mail.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_npc.h"
#include "m_land.h"
#include "unknown_structs.h"
#include "macros.h"

s32 mMl_strlen(const char* arg0, s32 size, char c) {
    arg0 += size - 1;

    while (size != 0) {
        if (c != *arg0) {
            return size;
        }
        size--;
        arg0--;
    }

    return 0;
}

s32 mMl_strlen2(s32* arg0, const char* arg1, s32 size, char c) {
    s32 count = 0;

    if (arg0 != NULL) {
        *arg0 = false;
    }

    while (size != 0) {
        count++;
        size--;
        if (c == *arg1) {
            if (arg0 != NULL) {
                *arg0 = true;
            }
            break;
        }

        arg1++;
    }

    return count;
}

void mMl_strcpy_back(char* dst, const char* src, s32 size) {
    while (size != 0) {
        *dst-- = *src--;
        size--;
    }
}

void mMl_clear_mail_header(Mail_c* mail) {
    mPr_ClearPersonalID(&mail->header.recipient.personalID);
    mail->header.recipient.type = 0xFF;
    mPr_ClearPersonalID(&mail->header.sender.personalID);
    mail->header.sender.type = 0xFF;
}

void mMl_clear_mail(Mail_c* mail) {
    bzero(mail, sizeof(Mail_c));
    mMl_clear_mail_header(mail);
    mem_clear(mail->content.header, MAIL_HEADER_LEN + MAIL_BODY_LEN + MAIL_FOOTER_LEN, 0x20);
    mail->content.font = 0xFF;
}

void mMl_clear_mail_box(Mail_c mail[], s32 arg1) {
    while (arg1 != 0) {
        arg1--;
        mMl_clear_mail(mail);
        mail++;
    }
}

s32 mMl_check_not_used_mail(Mail_c* mail) {
    s32 ret = 0;

    if (mail->content.font == 0xFF) {
        ret = 1;
    }
    return ret;
}

void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1) {
    arg0->type = arg1->type;
    mPr_CopyPersonalID(&arg0->personalID, &arg1->personalID);
}

void mMl_set_from_name(Mail_c* arg0, Mail_c* arg1) {
    mMl_copy_header_name(&arg0->header.sender, &arg1->header.recipient);
}

void mMl_set_to_name(Mail_c* arg0, Mail_c* arg1) {
    mMl_copy_header_name(&arg0->header.recipient, &arg1->header.recipient);
}

void mMl_set_to_plname(Mail_c* arg0, Mail_c* arg1) {
    mPr_CopyPersonalID(&arg0->header.recipient.personalID, &arg1->header.recipient.personalID);
    arg0->header.recipient.type = 0;
}

void mMl_set_playername(Mail_c* mail, PersonalID_c* arg1) {
    mPr_CopyPersonalID(&mail->header.sender.personalID, arg1);
    mail->header.sender.type = 0;
}

void mMl_init_mail(Mail_c* mail, PersonalID_c* arg1) {
    mMl_clear_mail(mail);
    mMl_set_playername(mail, arg1);
    mail->content.font = 1;
    mail->content.mailType = 0;
    mail->content.paperType = 0;
}

s32 mMl_chk_mail_free_space(Mail_c mail[], s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(mail) == 1) {
            return i;
        }
        mail++;
    }
    return -1;
}

s32 mMl_use_mail_space(Mail_c mail[], s32 arg1, PersonalID_c* arg2) {
    s32 index = mMl_chk_mail_free_space(mail, arg1);

    if (index != -1) {
        mMl_init_mail(&mail[index], arg2);
    }
    return index;
}

s32 mMl_count_use_mail_space(Mail_c mail[], s32 arg1) {
    s32 i;
    s32 ret = 0;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(mail) != 1) {
            ret++;
        }
        mail++;
    }
    return ret;
}

void mMl_copy_mail(Mail_c* dst, Mail_c* src) {
    mem_copy((u8*)dst, (u8*)src, sizeof(Mail_c));
}

void mMl_clear_mail_header_common(MailHeaderCommon* arg0) {
    arg0->unk_00 = -1;
    arg0->unk_01 = 0;
    mem_clear((u8*)arg0->unk_02, 0xA, 0x20);
    mem_clear((u8*)arg0->unk_0C, 0x10, 0x20);
}

void mMl_copy_mail_header_common(MailHeaderCommon* arg0, MailHeaderCommon* arg1) {
    mem_copy((u8*)arg0, (u8*)arg1, sizeof(MailHeaderCommon));
}

void mMl_set_mail_name_npcinfo(mMl_unk_00* arg0, AnmPersonalID_c* arg1) {
    char name[PLAYER_NAME_LEN];

    arg0->type = 1;
    mNpc_GetNpcWorldNameAnm(name, arg1);
    mPr_CopyPlayerName(arg0->personalID.playerName, name);
    arg0->personalID.landId = arg1->landId;
    mLd_CopyLandName(arg0->personalID.landName, arg1->landName);
    arg0->personalID.playerId = ((arg1->npcId & 0xFF) << 8) | (arg1->nameId & 0xFF);
}

s32 mMl_get_npcinfo_from_mail_name(AnmPersonalID_c* arg0, mMl_unk_00* arg1) {
    s32 var_v1 = 0;

    if (arg1->type == 1) {
        arg0->npcId = (((arg1->personalID.playerId & 0xFF00) >> 8) | 0xE000);
        arg0->landId = arg1->personalID.landId;
        mLd_CopyLandName(arg0->landName, arg1->personalID.landName);
        arg0->nameId = arg1->personalID.playerId & 0xFFFF;
        arg0->looks = mNpc_GetLooks(arg0->npcId);
        var_v1 = 1;
    }
    return var_v1;
}

s32 mMl_hunt_for_send_address(Mail_c* mail) {
    s32 i;

    if (mail->header.recipient.type != 0) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(common_data.homes); i++) {
        if (mPr_CheckCmpPersonalID(&common_data.homes[i].ownerID, &mail->header.recipient.personalID) == 1) {
            return i;
        }
    }

    return -1;
}

s32 mMl_check_send_mail(struct_func_8085CE18_jp_arg4* arg0) {
    switch (arg0->unk_26) {
        case 1:
            return 1;

        default:
            return 0;
    }
}

s32 mMl_check_set_present_myself(Mail_c* mail) {
    switch (mail->content.font) {
        case 1:
        case 3:
        case 4:
            return 1;

        default:
            return 0;
    }
}
