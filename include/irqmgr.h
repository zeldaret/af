#ifndef IRQMGR_H
#define IRQMGR_H

#include "ultra64.h"

#define IRQ_RETRACE_MSG 666
#define IRQ_PRENMI_MSG 669
#define IRQ_PRENMI450_MSG 671
#define IRQ_PRENMI480_MSG 672
#define IRQ_PRENMI500_MSG 673

typedef struct {
  s16 type;
  s8 data[30];
} irqmgr_mesg_t;

typedef struct irqmgr_client_s {
  struct irqmgr_client_s* next;
  OSMesgQueue* msgQueue;
} irqmgr_client_t;

typedef struct {
  irqmgr_mesg_t msgRetrace;
  irqmgr_mesg_t msgPreNMI;
  irqmgr_mesg_t msgDelayPreNMI;
  OSMesgQueue _msgQueue;
  OSMesg msgBuf[8];
  OSThread thread;
  irqmgr_client_t* clients;
  u8 prenmi;
  OSTime prenmiTime;
  OSTimer timer;
  OSTime retraceTime;
} irqmgr_t;

void irqmgr_AddClient(irqmgr_client_t* client, OSMesgQueue* msgQueue);
void irqmgr_RemoveClient(irqmgr_client_t* client);
void irqmgr_SendMesgToClients(irqmgr_t* msg);
void irqmgr_JamMesgForClient(irqmgr_t* msg);
void irqmgr_HandlePreNMI(void);
void IrqMgr_CheckStacks(void);
void irqmgr_HandlePreNMI450(void);
void irqmgr_HandlePreNMI480(void);
void irqmgr_HandlePreNMI500(void);
void IrqMgr_HandleRetrace(void);
void irqmgr_Main(void* arg);
void CreateIRQManager(void* stack, OSPri priority, u8 retracecount);

#endif
