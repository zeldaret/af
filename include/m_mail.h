#ifndef M_MAIL_H
#define M_MAIL_H

#include "ultra64.h"
#include "unk.h"
#include "m_private_internals.h"
#include "m_npc_base.h"

#define MAIL_HEADER_LEN (16 - PLAYER_NAME_LEN)
#define MAIL_FOOTER_LEN 16 
#define MAIL_BODY_LEN 96

#define MAIL_FOOTER2_LEN 26  
#define MAIL_HEADER2_LEN (MAIL_FOOTER2_LEN - PLAYER_NAME_LEN)

struct struct_func_8085CE18_jp_arg4;
struct AnmPersonalID_c;

// MailName?
typedef struct mMl_unk_00 {
    /* 0x00 */ PersonalID_c personalID;
    /* 0x10 */ u8 type;
} mMl_unk_00; // size = 0x12

typedef struct mMl_unk_2A {
    /* 0x00 */ UNK_TYPE1 unk_00[0x7A];
} mMl_unk_2A; // size = 0x7A

typedef struct MailHeaderCommon {
    /* 0x00 */ s8 unk_00;
    /* 0x00 */ u8 unk_01;
    /* 0x02 */ u8 unk_02[10];
    /* 0x0C */ u8 unk_0C[16];
} MailHeaderCommon; //size = 0x1C

typedef struct MailHeader {
    /* 0x00 */ mMl_unk_00 recipient;
    /* 0x12 */ mMl_unk_00 sender;
} MailHeader; // size = 0x24

typedef struct MailContent {
    /* 0x00 */ u8 font;
    /* 0x01 */ u8 headerBackStart;
    /* 0x02 */ u8 mailType;
    /* 0x03 */ u8 paperType;
    /* 0x04 */ u8 header[MAIL_HEADER_LEN];
    /* 0x1C */ u8 body[MAIL_BODY_LEN];
    /* 0xDC */ u8 footer[MAIL_FOOTER_LEN];
} MailContent; // size = 0x7F

typedef struct Mail_c {
    /* 0x000 */ MailHeader header;
    /* 0x024 */ u16 present;
    /* 0x026 */ MailContent content;
} Mail_c; //size = 0xA4

typedef enum MailNameType {
    /*   0 */ MAIL_NAME_TYPE_PLAYER,
    /*   1 */ MAIL_NAME_TYPE_NPC,
    /*   2 */ MAIL_NAME_NUM,
    /* 255 */ MAIL_NAME_TYPE_CLEAR = 0xFF
} MailNameType;

s32 mMl_strlen(const char* arg0, s32 size, char c);
s32 mMl_strlen2(s32* arg0, const char* arg1, s32 size, char c);
void mMl_strcpy_back(char* dst, const char* src, s32 size);
void mMl_clear_mail_header(Mail_c* mail);
void mMl_clear_mail(Mail_c* mail);
void mMl_clear_mail_box(Mail_c* mail, s32 arg1);
s32 mMl_check_not_used_mail(Mail_c* mail);
void mMl_copy_header_name(mMl_unk_00* arg0, mMl_unk_00* arg1);
void mMl_set_from_name(Mail_c* arg0, Mail_c* arg1);
void mMl_set_to_name(Mail_c* arg0, Mail_c* arg1);
void mMl_set_to_plname(Mail_c* arg0, Mail_c* arg1);
void mMl_set_playername(Mail_c* mail, PersonalID_c* arg1);
void mMl_init_mail(Mail_c* mail, PersonalID_c* arg1);
s32 mMl_chk_mail_free_space(Mail_c mail[], s32 arg1);
s32 mMl_use_mail_space(Mail_c mail[], s32 arg1, PersonalID_c* arg2);
s32 mMl_count_use_mail_space(Mail_c mail[], s32 arg1);
void mMl_copy_mail(Mail_c* dst, Mail_c* src);
void mMl_clear_mail_header_common(MailHeaderCommon* arg0);
void mMl_copy_mail_header_common(MailHeaderCommon* arg0, MailHeaderCommon* arg1);
void mMl_set_mail_name_npcinfo(mMl_unk_00* arg0, AnmPersonalID_c* arg1);
s32 mMl_get_npcinfo_from_mail_name(AnmPersonalID_c* arg0, mMl_unk_00* arg1);
s32 mMl_hunt_for_send_address(Mail_c* mail);
s32 mMl_check_send_mail(struct struct_func_8085CE18_jp_arg4* arg0);
s32 mMl_check_set_present_myself(Mail_c* mail);

#endif
