#ifndef IRQMGR_H
#define IRQMGR_H

#include "ultra64.h"

#define IRQ_RETRACE_MSG 666
#define IRQ_PRENMI_MSG 669
#define IRQ_PRENMI450_MSG 671
#define IRQ_PRENMI480_MSG 672
#define IRQ_PRENMI500_MSG 673

typedef struct {
    /* 0x00 */ s16 type;
    /* 0x02 */ s8 data[30];
} IrqmgrMsg; //size = 0x20


typedef struct IrqmgrClient {
    /* 0x0 */ struct IrqmgrClient* next;
    /* 0x4 */ OSMesgQueue* msgQueue;
} IrqmgrClient; // size = 0x8

typedef struct {
    /* 0x000 */ IrqmgrMsg msgRetrace;
    /* 0x020 */ IrqmgrMsg msgPreNMI;
    /* 0x040 */ IrqmgrMsg msgDelayPreNMI;
    /* 0x060 */ OSMesgQueue _msgQueue;
    /* 0x078 */ OSMesg msgBuf[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ IrqmgrClient* clients;
    /* 0x24C */ u8 prenmi;
    /* 0x250 */ OSTime prenmiTime;
    /* 0x258 */ OSTimer timer;
    /* 0x278 */ OSTime retraceTime;
} Irqmgr; // size = 0x280

void irqmgr_AddClient(IrqmgrClient* client, OSMesgQueue* msgQueue);
void irqmgr_RemoveClient(IrqmgrClient* client);
void irqmgr_SendMesgToClients(IrqmgrMsg* msg);
void irqmgr_JamMesgForClient(IrqmgrMsg* msg);
void irqmgr_HandlePreNMI(void);
void IrqMgr_CheckStacks(void);
void irqmgr_HandlePreNMI450(void);
void irqmgr_HandlePreNMI480(void);
void irqmgr_HandlePreNMI500(void);
void IrqMgr_HandleRetrace(void);
void irqmgr_Main(void* arg);
void CreateIRQManager(void* stack, OSPri priority, u8 retracecount);

extern vu32 ResetStatus;
extern volatile OSTime ResetTime;
extern volatile OSTime RetraceTime;
extern u32 RetraceCount;

#endif
