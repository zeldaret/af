#ifndef C_6BFE60_H
#define C_6BFE60_H

#include "ultra64.h"
#include "6DB420.h"
#include "unk.h"

typedef struct mMl_unk_00 {
    /* 0x00 */ mPr unk_00;
    /* 0x10 */ u8 unk_10;
} mMl_unk_00; // size = 0x11

typedef struct mMl_unk_2A {
    /* 0x00 */ UNK_TYPE1 unk_00[0x7A];
} mMl_unk_2A; // size = 0x7A

typedef struct MailHeaderCommon {
    /* 0x00 */ s8 unk_00;
    /* 0x00 */ u8 unk_01;
    /* 0x02 */ u8 unk_02[10];
    /* 0x0C */ u8 unk_0C[16];
} MailHeaderCommon; //size = 0x1C

// MailBox?
typedef struct mMl {
    /* 0x00 */ mMl_unk_00 unk_00;
    /* 0x11 */ UNK_TYPE1 unk_11[0x1];
    /* 0x12 */ mMl_unk_00 unk_12;
    /* 0x23 */ UNK_TYPE1 unk_23[0x1];
    /* 0x24 */ UNK_TYPE1 unk_24[0x2];
    /* 0x26 */ u8 unk_26;
    /* 0x27 */ UNK_TYPE1 unk_27[0x1];
    /* 0x28 */ u8 unk_28;
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ mMl_unk_2A unk_2A;
} mMl; // size = 0xA4

// void func_8009C1C0_jp();
// void func_8009C284_jp();
// void func_8009C2D8_jp();
void mMl_clear_mail_header(mMl* arg0);
void mMl_clear_mail(mMl* arg0);
void mMl_clear_mail_box(mMl* arg0, s32 arg1);
s32 mMl_check_not_used_mail(mMl* arg0);
void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1);
void mMl_set_from_name(mMl* arg0, mMl* arg1);
void mMl_set_to_name(mMl* arg0, mMl* arg1);
void mMl_set_to_plname(mMl* arg0, mMl* arg1);
void mMl_set_playername(mMl* arg0, mPr* arg1);
void mMl_init_mail(mMl* arg0, mPr* arg1);
s32 mMl_chk_mail_free_space(mMl arg0[], s32 arg1);
s32 mMl_use_mail_space(mMl arg0[], s32 arg1, mPr* arg2);
s32 mMl_count_use_mail_space(mMl arg0[], s32 arg1);
void mMl_copy_mail(mMl* arg0, mMl* arg1);
void mMl_clear_mail_header_common(MailHeaderCommon* arg0);
void mMl_copy_mail_header_common(MailHeaderCommon* arg0, MailHeaderCommon* arg1);
// void mMl_set_mail_name_npcinfo();
// void mMl_get_npcinfo_from_mail_name();
// void mMl_hunt_for_send_address();
// void mMl_check_send_mail();
// void mMl_check_set_present_myself();

#endif
