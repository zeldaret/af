#include "m_mail.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_npc.h"
#include "6B8A70.h"
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

void mMl_clear_mail_header(Mail* mail) {
    mPr_ClearPersonalID(&mail->unk_00.unk_00);
    mail->unk_00.unk_10 = 0xFF;
    mPr_ClearPersonalID(&mail->unk_12.unk_00);
    mail->unk_12.unk_10 = 0xFF;
}

void mMl_clear_mail(Mail* mail) {
    bzero(mail, sizeof(Mail));
    mMl_clear_mail_header(mail);
    mem_clear(&mail->unk_2A, sizeof(mMl_unk_2A), 0x20);
    mail->unk_26 = 0xFF;
}

void mMl_clear_mail_box(Mail mail[], s32 arg1) {
    while (arg1 != 0) {
        arg1--;
        mMl_clear_mail(mail);
        mail++;
    }
}

s32 mMl_check_not_used_mail(Mail* mail) {
    s32 ret = 0;

    if (mail->unk_26 == 0xFF) {
        ret = 1;
    }
    return ret;
}

void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1) {
    arg0->unk_10 = arg1->unk_10;
    mPr_CopyPersonalID(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_from_name(Mail* arg0, Mail* arg1) {
    mMl_copy_header_name(&arg0->unk_12, &arg1->unk_00);
}

void mMl_set_to_name(Mail* arg0, Mail* arg1) {
    mMl_copy_header_name(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_to_plname(Mail* arg0, Mail* arg1) {
    mPr_CopyPersonalID(&arg0->unk_00.unk_00, &arg1->unk_00.unk_00);
    arg0->unk_00.unk_10 = 0;
}

void mMl_set_playername(Mail* mail, PersonalID* arg1) {
    mPr_CopyPersonalID(&mail->unk_12.unk_00, arg1);
    mail->unk_12.unk_10 = 0;
}

void mMl_init_mail(Mail* mail, PersonalID* arg1) {
    mMl_clear_mail(mail);
    mMl_set_playername(mail, arg1);
    mail->unk_26 = 1;
    mail->unk_28 = 0;
    mail->unk_29 = 0;
}

s32 mMl_chk_mail_free_space(Mail mail[], s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(mail) == 1) {
            return i;
        }
        mail++;
    }
    return -1;
}

s32 mMl_use_mail_space(Mail mail[], s32 arg1, PersonalID* arg2) {
    s32 index = mMl_chk_mail_free_space(mail, arg1);

    if (index != -1) {
        mMl_init_mail(&mail[index], arg2);
    }
    return index;
}

s32 mMl_count_use_mail_space(Mail mail[], s32 arg1) {
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

void mMl_copy_mail(Mail* dst, Mail* src) {
    mem_copy(dst, src, sizeof(Mail));
}

void mMl_clear_mail_header_common(MailHeaderCommon* arg0) {
    arg0->unk_00 = -1;
    arg0->unk_01 = 0;
    mem_clear(arg0->unk_02, 0xA, 0x20);
    mem_clear(arg0->unk_0C, 0x10, 0x20);
}

void mMl_copy_mail_header_common(MailHeaderCommon* arg0, MailHeaderCommon* arg1) {
    mem_copy(arg0, arg1, sizeof(MailHeaderCommon));
}

void mMl_set_mail_name_npcinfo(mMl_unk_00* arg0, mMl_get_npcinfo_from_mail_name_arg0* arg1) {
    PlayerName sp20;

    arg0->unk_10 = 1;
    mNpc_GetNpcWorldNameAnm(&sp20, arg1);
    mPr_CopyPlayerName(&arg0->unk_00.unk_0, &sp20);
    arg0->unk_00.unk_E = arg1->unk_2;
    mLd_CopyLandName(&arg0->unk_00.unk_6, &arg1->unk_4);
    arg0->unk_00.unk_C = ((arg1->unk_0 & 0xFF) << 8) | (arg1->unk_A & 0xFF);
}

s32 mMl_get_npcinfo_from_mail_name(mMl_get_npcinfo_from_mail_name_arg0* arg0, mMl_unk_00* arg1) {
    s32 var_v1 = 0;

    if (arg1->unk_10 == 1) {
        arg0->unk_0 = (((arg1->unk_00.unk_C & 0xFF00) >> 8) | 0xE000);
        arg0->unk_2 = arg1->unk_00.unk_E;
        mLd_CopyLandName(&arg0->unk_4, &arg1->unk_00.unk_6);
        arg0->unk_A = arg1->unk_00.unk_C & 0xFFFF;
        arg0->unk_B = mNpc_GetLooks(arg0->unk_0);
        var_v1 = 1;
    }
    return var_v1;
}

s32 mMl_hunt_for_send_address(Mail* mail) {
    s32 i;

    if (mail->unk_00.unk_10 != 0) {
        return -1;
    }

    for (i = 0; i < ARRAY_COUNT(common_data.homes); i++) {
        if (mPr_CheckCmpPersonalID(&common_data.homes[i].unk_000, &mail->unk_00.unk_00) == 1) {
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

s32 mMl_check_set_present_myself(Mail* mail) {
    switch (mail->unk_26) {
        case 1:
        case 3:
        case 4:
            return 1;

        default:
            return 0;
    }
}
