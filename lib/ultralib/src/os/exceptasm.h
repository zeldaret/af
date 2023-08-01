#ifndef _EXCEPTASM_H
#define _EXCEPTASM_H

#define MESG(type) (type << 3)

#define MQ_MTQUEUE 0
#define MQ_FULLQUEUE 4
#define MQ_VALIDCOUNT 8
#define MQ_FIRST 12
#define MQ_MSGCOUNT 16
#define MQ_MSG 20

#define OS_EVENTSTATE_MESSAGE_QUEUE 0
#define OS_EVENTSTATE_MESSAGE 4

/* __osHwInt struct member offsets */
#define HWINTR_CALLBACK 0x00
#define HWINTR_SP       0x04

/* __osHwInt struct size */
#define HWINTR_SIZE     0x8

#endif
