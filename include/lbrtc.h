#ifndef LBRTC_H
#define LBRTC_H

#include "ultra64.h"

#define RTC_STATUS_CRASHED 0
#define RTC_STATUS_VALID 1

typedef struct OSRTCTime { // assumed from m_flashrom
    /* 0x00 */ u8 sec;
    /* 0x01 */ u8 min;
    /* 0x02 */ u8 hour;
    /* 0x03 */ u8 day;
    /* 0x04 */ u8 weekday;
    /* 0x05 */ u8 month;
    /* 0x06 */ u16 year;
} OSRTCTime; // size = 0x8

// Internal 

typedef struct __OSRTCTime { // assumed from m_flashrom
    /* 0x00 */ u8 sec;
    /* 0x01 */ u8 min;
    /* 0x02 */ u8 hour;
    /* 0x03 */ u8 day;
    /* 0x04 */ u8 weekday;
    /* 0x05 */ u8 month;
    /* 0x06 */ u8 centuryYear;
    /* 0x07 */ u8 status;
} __OSRTCTime; // size = 0x8

typedef struct __lbrtc_struct_unk {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} __lbrtc_struct_unk; // size = 0x8

typedef struct __lbrtc_struct_unk1 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ __lbrtc_struct_unk unk4;
    /* 0xC */ u8 unkC;
} __lbrtc_struct_unk1; // size = 0xD

typedef struct __lbrtc_struct_unk2 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
} __lbrtc_struct_unk2; // size = 0x6

typedef struct __lbrtc_struct_unk3 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
} __lbrtc_struct_unk3; // size = 0x2

extern OSTimer B_80152480_jp;
extern OSMesgQueue B_801524A0_jp;
extern OSMesg B_801524B8_jp;

//

s32 lbrtc_getTime(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE420_jp(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE480_jp(OSMesgQueue* mq, u8* buf);
s32 lbrtc_setTime(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE8D0_jp(OSMesgQueue* mq, u8 v, u8* buf);
s32 func_800FEABC_jp(u8 v, u8* buf);
s32 func_800FEBE0_jp(OSMesgQueue* mq, OSRTCTime* time);
s32 lbrtc_init(OSMesgQueue* mq);
s32 func_800FEE10_jp(OSMesgQueue* mq, u8 v, u8* buf);
void func_800FEF9C_jp(u8 v);
s32 lbrtc_GetIntervalMinutes(OSRTCTime* t0, OSRTCTime* t1);

#endif
