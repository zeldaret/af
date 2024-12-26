#ifndef M_THREAD_H
#define M_THREAD_H

#define M_THREAD_ID_IDLE      1
#define M_THREAD_ID_FAULT     2
#define M_THREAD_ID_MAIN      3
#define M_THREAD_ID_GRAPH     4
#define M_THREAD_ID_PADMGR    7
#define M_THREAD_ID_DMAMGR    8
#define M_THREAD_ID_IRQMGR    9
#define M_THREAD_ID_AUDIOMGR 10

#define M_PRIORITY_GRAPH         8
#define M_PRIORITY_DMAMGR_LOW   10  // Used when decompressing files
#define M_PRIORITY_AUDIOMGR     11
#define M_PRIORITY_IDLE         12
#define M_PRIORITY_MAIN         12
#define M_PRIORITY_MAIN_HIGH    13
#define M_PRIORITY_PADMGR       15
#define M_PRIORITY_DMAMGR       17
#define M_PRIORITY_SCHED        16
#define M_PRIORITY_IRQMGR       18
#define M_PRIORITY_FAULT_CLIENT (OS_PRIORITY_APPMAX - 1)
#define M_PRIORITY_FAULT        OS_PRIORITY_APPMAX

#endif
