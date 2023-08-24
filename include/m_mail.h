#ifndef M_MAIL_H
#define M_MAIL_H

#include "ultra64.h"
#include "m_personal_id.h"

#define MAIL_HEADER_LEN (16 - PLAYER_NAME_LEN)
#define MAIL_FOOTER_LEN 16
#define MAIL_BODY_LEN 96

typedef struct Mail_nm_c {
  /* 0x00 */ PersonalID_c personal_ID;
  /* 0x10 */ u8 type;
} Mail_nm_c; // size = 0x12

typedef struct Mail_hdr_c {
  /* 0x00 */ Mail_nm_c recipient;
  /* 0x12 */ Mail_nm_c sender;
} Mail_hdr_c; // size = 0x24

typedef struct Mail_ct_c {
  /* 0x00 */ u8 font;
  /* 0x01 */ u8 header_back_start;
  /* 0x02 */ u8 mail_type;
  /* 0x03 */ u8 paper_type;
  /* 0x04 */ u8 header[MAIL_HEADER_LEN];
  /* 0x0E */ u8 body[MAIL_BODY_LEN];
  /* 0x6E */ u8 footer[MAIL_FOOTER_LEN];
} Mail_ct_c; // size = 0x7E

typedef struct Mail_c {
    /* 0x000 */ Mail_hdr_c header;
    /* 0x024 */ u16 present;
    /* 0x026 */ Mail_ct_c content;
} Mail_c; // size = 0xA4

#endif
