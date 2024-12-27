#ifndef GRAPH_H
#define GRAPH_H

#include "ultra64.h"

#include "fault.h"

struct GraphicsContext;
extern OSThread graphThread;

void func_800D3E14_jp(struct GraphicsContext *gfxCtx);
void func_800D3E40_jp(struct GraphicsContext *gfxCtx);

void graph_proc(void* arg);

extern FaultClient sGraphFaultClient;
extern FaultAddrConvClient sGraphFaultAddrConvClient;
extern struct GraphicsContext graph_class;

#endif
