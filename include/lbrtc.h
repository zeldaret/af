#ifndef LBRTC_H
#define LBRTC_H

#include "ultra64.h"

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

// docs from: https://n64brew.dev/wiki/Joybus_Protocol

#define RTC_CR_BLOCK_TYPE 0
#define RTC_SRAM_BLOCK_TYPE 1
#define RTC_TIME_BLOCK_TYPE 2
#define RTC_BLOCK_TYPE_3 3

#define CONT_CMD_RTC_INFO 6
#define CONT_CMD_READ_RTC 7
#define CONT_CMD_WRITE_RTC 8

#define CONT_CMD_RTC_INFO_TX 1
#define CONT_CMD_RTC_INFO_RX 3

#define CONT_CMD_READ_RTC_TX 2
#define CONT_CMD_READ_RTC_RX 9

#define CONT_CMD_WRITE_RTC_TX 10
#define CONT_CMD_WRITE_RTC_RX 1

#define RTC_STATUS_STOPPED 0x80
#define RTC_STATUS_CRYSTAL_FAILURE 0x2
#define RTC_STATUS_BATTERY_FAILURE 0x1

#define RTC_ERR_BATTERY 0x11
#define RTC_ERR_CRYSTAL 0x12

#define RTC_STOPPED 0x10

typedef struct __OSContRTCData {
    /* 0x00 */ u8 sec;
    /* 0x01 */ u8 min;
    /* 0x02 */ u8 hour;
    /* 0x03 */ u8 day;
    /* 0x04 */ u8 weekday;
    /* 0x05 */ u8 month;
    /* 0x06 */ u8 yearLo;
    /* 0x07 */ u8 centuriesSince1900; 
} __OSContRTCData; // size = 0x8

typedef struct __OSContRTCRWFormat {
    /* 0x0 */ u8 txsize;
    /* 0x1 */ u8 rxsize;
    /* 0x2 */ u8 cmd; 
    /* 0x3 */ u8 blockType;
    /* 0x4 */ __OSContRTCData data; 
    /* 0xC */ u8 status;
} __OSContRTCRWFormat; // size = 0xD

typedef struct __OSContRTCInfoFormat {
    /* 0x0 */ u8 txsize;
    /* 0x1 */ u8 rxsize;
    /* 0x2 */ u8 cmd;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 status;
} __OSContRTCInfoFormat; // size = 0x6

#define RTC_WRITE_PROTECT_NVRAM_BIT 1
#define RTC_WRITE_PROTECT_RTC_BIT 2
#define RTC_WRITE_STOP_COUNT_BIT 4
#define RTC_WRITE_STOP_COUNT2_BIT 6

typedef struct __OSContRTCControlRegs {
    /* 0x0 */ u8 writeProtectBitfield;
    /* 0x1 */ u8 flagsBitfield;
} __OSContRTCControlRegs; // size = 0x2

extern OSMesgQueue __contRTCMesgQ;
extern OSMesg __contRTCMesg;

//

s32 lbrtc_getTime(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE420_jp(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE480_jp(OSMesgQueue* mq, u8* status);
s32 lbrtc_setTime(OSMesgQueue* mq, OSRTCTime* time);
s32 func_800FE8D0_jp(OSMesgQueue* mq, u8 blockType, u8* data);
s32 func_800FEABC_jp(u8 blockType, u8* data);
s32 func_800FEBE0_jp(OSMesgQueue* mq, OSRTCTime* time);
s32 lbrtc_init(OSMesgQueue* mq);
s32 func_800FEE10_jp(OSMesgQueue* mq, u8 blockType, u8* buf);
void func_800FEF9C_jp(u8 blockType);
s32 lbrtc_GetIntervalMinutes(OSRTCTime* t0, OSRTCTime* t1);

#endif
