#include "libc64/sleep.h"

void csleep(OSTime t) {
    OSMesgQueue mq;
    OSMesg msg[1];
    OSTimer timer;

    osCreateMesgQueue(&mq, msg, 1);
    osSetTimer(&timer, t, 0, &mq, NULL);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}

void nsleep(u32 t) {
    csleep(OS_NSEC_TO_CYCLES(t));
}

void usleep(u32 t) {
    csleep(OS_USEC_TO_CYCLES(t));
}

void msleep(u32 t) {
    csleep((t * OS_CPU_COUNTER) / 1000ULL);
}

void sleep(u32 t) {
    csleep(t * OS_CPU_COUNTER);
}
