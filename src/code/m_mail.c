#include "m_mail.h"
#include "m_lib.h"
#include "m_common_data.h"

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C1C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C284_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/func_8009C2D8_jp.s")

void mMl_clear_mail_header(mMl* arg0) {
    mPr_ClearPersonalID(&arg0->unk_00.unk_00);
    arg0->unk_00.unk_10 = 0xFF;
    mPr_ClearPersonalID(&arg0->unk_12.unk_00);
    arg0->unk_12.unk_10 = 0xFF;
}

void mMl_clear_mail(mMl* arg0) {
    bzero(arg0, sizeof(mMl));
    mMl_clear_mail_header(arg0);
    mem_clear(&arg0->unk_2A, sizeof(mMl_unk_2A), 0x20);
    arg0->unk_26 = 0xFF;
}

void mMl_clear_mail_box(mMl* arg0, s32 arg1) {
    while (arg1 != 0) {
        arg1--;
        mMl_clear_mail(arg0);
        arg0++;
    }
}

s32 mMl_check_not_used_mail(mMl* arg0) {
    s32 ret = 0;

    if (arg0->unk_26 == 0xFF) {
        ret = 1;
    }
    return ret;
}

void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1) {
    arg0->unk_10 = arg1->unk_10;
    mPr_CopyPersonalID(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_from_name(mMl* arg0, mMl* arg1) {
    mMl_copy_header_name(&arg0->unk_12, &arg1->unk_00);
}

void mMl_set_to_name(mMl* arg0, mMl* arg1) {
    mMl_copy_header_name(&arg0->unk_00, &arg1->unk_00);
}

void mMl_set_to_plname(mMl* arg0, mMl* arg1) {
    mPr_CopyPersonalID(&arg0->unk_00.unk_00, &arg1->unk_00.unk_00);
    arg0->unk_00.unk_10 = 0;
}

void mMl_set_playername(mMl* arg0, mPr* arg1) {
    mPr_CopyPersonalID(&arg0->unk_12.unk_00, arg1);
    arg0->unk_12.unk_10 = 0;
}

void mMl_init_mail(mMl* arg0, mPr* arg1) {
    mMl_clear_mail(arg0);
    mMl_set_playername(arg0, arg1);
    arg0->unk_26 = 1;
    arg0->unk_28 = 0;
    arg0->unk_29 = 0;
}

s32 mMl_chk_mail_free_space(mMl arg0[], s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(arg0) == 1) {
            return i;
        }
        arg0++;
    }
    return -1;
}

s32 mMl_use_mail_space(mMl arg0[], s32 arg1, mPr* arg2) {
    s32 index = mMl_chk_mail_free_space(arg0, arg1);

    if (index != -1) {
        mMl_init_mail(&arg0[index], arg2);
    }
    return index;
}

s32 mMl_count_use_mail_space(mMl arg0[], s32 arg1) {
    s32 i;
    s32 ret = 0;

    for (i = 0; i < arg1; i++) {
        if (mMl_check_not_used_mail(arg0) != 1) {
            ret++;
        }
        arg0++;
    }
    return ret;
}

void mMl_copy_mail(mMl* arg0, mMl* arg1) {
    mem_copy(arg0, arg1, sizeof(mMl));
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

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_set_mail_name_npcinfo.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_get_npcinfo_from_mail_name.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_hunt_for_send_address.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_check_send_mail.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_mail/mMl_check_set_present_myself.s")
