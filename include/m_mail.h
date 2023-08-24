#ifndef C_6BFE60_H
#define C_6BFE60_H

#include "ultra64.h"
#include "unk.h"

typedef struct mMl_unk_2A {
    /* 0x00 */ UNK_TYPE1 unk_00[0x7A];
} mMl_unk_2A; // size = 0x7A

typedef struct mMl {
    /* 0x00 */ UNK_TYPE1 unk_00[0x24];
    /* 0x24 */ UNK_TYPE1 unk_24[0x2];
    /* 0x26 */ u8 unk_26;
    /* 0x27 */ UNK_TYPE1 unk_27[0x1];
    /* 0x28 */ UNK_TYPE1 unk_28[0x2];
    /* 0x2A */ mMl_unk_2A unk_2A;
} mMl; // size = 0xA4

// void func_8009C1C0_jp();
// void func_8009C284_jp();
// void func_8009C2D8_jp();
// void func_8009C344_jp();
void mMl_clear_mail(mMl* arg0);
// void mMl_clear_mail_box();
// void func_8009C414_jp();
// void func_8009C438_jp();
// void func_8009C45C_jp();
// void func_8009C480_jp();
// void func_8009C4A0_jp();
// void func_8009C4C8_jp();
// void func_8009C4F4_jp();
// void func_8009C534_jp();
// void func_8009C5A4_jp();
// void func_8009C608_jp();
// void func_8009C67C_jp();
// void func_8009C69C_jp();
// void func_8009C6EC_jp();
// void mMl_set_mail_name_npcinfo();
// void mMl_get_npcinfo_from_mail_name();
// void mMl_hunt_for_send_address();
// void func_8009C89C_jp();
// void func_8009C8C0_jp();

#endif
