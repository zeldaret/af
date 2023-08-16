#ifndef AC_MAILBOX_H
#define AC_MAILBOX_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct MailBox;

typedef struct MailBox {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x1AC];
} MailBox; // size = 0x320

#endif
