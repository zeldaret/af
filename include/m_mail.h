#ifndef M_MAIL_H
#define M_MAIL_H

#include "ultra64.h"
#include "m_personal_id.h"

#define MAIL_HEADER_LEN (16 - PLAYER_NAME_LEN)
#define MAIL_FOOTER_LEN 16
#define MAIL_BODY_LEN 96

typedef struct MailName {
  /* 0x00 */ PersonalId personalId;
  /* 0x10 */ u8 type;
} MailName; // size = 0x12

typedef struct MailHeader {
  /* 0x00 */ MailName recipient;
  /* 0x12 */ MailName sender;
} MailHeader; // size = 0x24

typedef struct MailContents {
  /* 0x00 */ u8 font;
  /* 0x01 */ u8 headerBackStart;
  /* 0x02 */ u8 mailType;
  /* 0x03 */ u8 paperType;
  /* 0x04 */ u8 header[MAIL_HEADER_LEN];
  /* 0x0E */ u8 body[MAIL_BODY_LEN];
  /* 0x6E */ u8 footer[MAIL_FOOTER_LEN];
} MailContents; // size = 0x7E

typedef struct Mail {
    /* 0x000 */ MailHeader header;
    /* 0x024 */ u16 present;
    /* 0x026 */ MailContents content;
} Mail; // size = 0xA4

#endif
