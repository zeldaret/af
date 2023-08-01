
#include "irqmgr.h"
#include "stackcheck.h"
#include "PR/os_internal.h"

irqmgr_t* this;
irqmgr_t irqmgr_class;

vu32 ResetStatus = 0;
volatile OSTime ResetTime = 0;
volatile OSTime RetraceTime = 0;
u32 RetraceCount = 0;

void irqmgr_AddClient(irqmgr_client_t* client, OSMesgQueue* msgQueue) {
    u32 enable = osSetIntMask(1);

    client->msgQueue = msgQueue;
    client->next = this->clients;
    this->clients = client;

    osSetIntMask(enable);

    if (this->prenmi >= 1) {
        osSendMesg(client->msgQueue, (OSMesg) & this->msgPreNMI, 0);
    }

    if (this->prenmi >= 2) {
        osSendMesg(client->msgQueue, (OSMesg) & this->msgDelayPreNMI, 0);
    }
}

void irqmgr_RemoveClient(irqmgr_client_t* client) {
    irqmgr_client_t* iterClient = this->clients;
    irqmgr_client_t* lastClient = NULL;
    u32 enable = osSetIntMask(1);

    while (iterClient != NULL) {
        if (iterClient == client) {
            if (lastClient != NULL) {
                lastClient->next = client->next;
            } else {
                this->clients = client->next;
            }
            break;
        }
        lastClient = iterClient;
        iterClient = iterClient->next;
    }

    osSetIntMask(enable);
}

void irqmgr_SendMesgToClients(irqmgr_t* msg) {
    irqmgr_client_t* i;
    OSMesgQueue* msgQueue;

    for (i = this->clients; i != NULL; i = i->next) {
        msgQueue = i->msgQueue;
        if (msgQueue->validCount < msgQueue->msgCount) {
            osSendMesg(msgQueue, msg, 0);
        }
    }
}

void irqmgr_JamMesgForClient(irqmgr_t* msg) {
    irqmgr_client_t* i;
    OSMesgQueue* msgQueue;

    for (i = this->clients; i != NULL; i = i->next) {
        msgQueue = i->msgQueue;

        if (msgQueue->validCount < msgQueue->msgCount) {
            osSendMesg(msgQueue, msg, 0);
        }
    }
}
void irqmgr_HandlePreNMI(void) {
    u64 prenmi = 1;

    ResetStatus = prenmi;
    this->prenmi = 1;
    ResetTime = this->prenmiTime = osGetTime();

    osSetTimer(&this->timer, OS_USEC_TO_CYCLES(400000), 0, &this->_msgQueue, (OSMesg)IRQ_PRENMI450_MSG);
    irqmgr_JamMesgForClient((irqmgr_t*)&this->msgPreNMI);
}

void IrqMgr_CheckStacks(void) {
    StackCheck_Check(NULL);
}

void irqmgr_HandlePreNMI450(void) {
    u64 prenmi = 2;
    ResetStatus = prenmi;
    this->prenmi = 2;

    osSetTimer(&this->timer, OS_USEC_TO_CYCLES(50000), 0, &this->_msgQueue, (OSMesg)IRQ_PRENMI480_MSG);
    irqmgr_SendMesgToClients((irqmgr_t*)&this->msgDelayPreNMI);
}

void irqmgr_HandlePreNMI480(void) {
    u32 res;
    osSetTimer(&this->timer, OS_USEC_TO_CYCLES(50000), 0, &this->_msgQueue, (OSMesg)IRQ_PRENMI500_MSG);

    res = osAfterPreNMI();
    if (res != 0) {
        osSetTimer(&this->timer, OS_USEC_TO_CYCLES(1000), 0, &this->_msgQueue, (OSMesg)IRQ_PRENMI480_MSG);
    }
}

void irqmgr_HandlePreNMI500(void) {
    IrqMgr_CheckStacks();
}

void irqmgr_HandleRetrace(void) {
    if (RetraceTime == 0) {
        if (this->retraceTime == 0) {
            this->retraceTime = osGetTime();
        } else {
            RetraceTime = osGetTime() - this->retraceTime;
        }
    }
    RetraceCount++;
    irqmgr_SendMesgToClients(this);
}

void irqmgr_Main(void* arg) {
    OSMesg msg = (OSMesg)0;
    u8 exit = 0;

    while (!exit) {
        osRecvMesg(&this->_msgQueue, &msg, 1);
        switch ((u32)msg) {
            case IRQ_RETRACE_MSG:
                irqmgr_HandleRetrace();
                break;
            case IRQ_PRENMI_MSG:
                irqmgr_HandlePreNMI();
                break;
            case IRQ_PRENMI450_MSG:
                irqmgr_HandlePreNMI450();
                break;
            case IRQ_PRENMI480_MSG:
                irqmgr_HandlePreNMI480();
                break;
            case IRQ_PRENMI500_MSG:
                irqmgr_HandlePreNMI500();
                break;
            default:
                break;
        }
    }
}

void CreateIRQManager(void* stack, OSPri priority, u8 retracecount) {

    this = &irqmgr_class;
    this->clients = NULL;
    this->msgRetrace.type = 1;
    this->msgPreNMI.type = 4;
    this->msgDelayPreNMI.type = 3;
    this->prenmi = 0;
    this->prenmiTime = 0;

    osCreateMesgQueue(&this->_msgQueue, this->msgBuf, 8);
    osSetEventMesg(0xE, &this->_msgQueue, (OSMesg)IRQ_PRENMI_MSG);
    osViSetEvent(&this->_msgQueue, (OSMesg)IRQ_RETRACE_MSG, retracecount);
    osCreateThread(&this->thread, 9, irqmgr_Main, NULL, stack, priority);
    osStartThread(&this->thread);
}
