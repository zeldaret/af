#ifndef FAULT_H
#define FAULT_H

#include "ultra64.h"
#include "attributes.h"

// void Fault_SleepImpl();
// void Fault_ClientProcessThread();
// void Fault_ClientRunTask();
// void Fault_ProcessClient();
// void Fault_AddClient();
// void Fault_RemoveClient();
// void Fault_AddAddrConvClient();
// void Fault_RemoveAddrConvClient();
// void Fault_ConvertAddress();
// void Fault_Sleep();
// void Fault_PadCallback();
// void Fault_UpdatePadImpl();
// void Fault_WaitForInputImpl();
// void Fault_WaitForInput();
// void Fault_DrawRec();
// void Fault_FillScreenBlack();
// void Fault_FillScreenRed();
// void Fault_DrawCornerRec();
// void Fault_PrintFReg();
// void Fault_LogFReg();
// void Fault_PrintFPCSR();
// void Fault_LogFPCSR();
// void Fault_PrintThreadContext();
// void Fault_LogThreadContext();
// void Fault_FindFaultedThread();
// void Fault_Wait5Seconds();
// void Fault_WaitForButtonCombo();
// void Fault_DrawMemDumpContents();
// void Fault_DrawMemDump();
// void Fault_WalkStack();
// void Fault_DrawStackTrace();
// void Fault_LogStackTrace();
// void Fault_ResumeThread();
// void Fault_DisplayFrameBuffer();
// void Fault_ProcessClients();
// void Fault_UpdatePad();
// void Fault_ThreadEntry();
// void Fault_SetFrameBuffer();
// void Fault_Init();
// void Fault_HungupFaultClient();
NORETURN void Fault_AddHungupAndCrashImpl(const char* exp1, const char* exp2);
// NORETURN void Fault_AddHungupAndCrash();

// void FaultDrawer_SetOsSyncPrintfEnabled();
// void FaultDrawer_DrawRecImpl();
// void FaultDrawer_DrawChar();
// void FaultDrawer_ColorToPrintColor();
// void FaultDrawer_UpdatePrintColor();
// void FaultDrawer_SetForeColor();
// void FaultDrawer_SetBackColor();
void FaultDrawer_SetFontColor(u16 color);
// void FaultDrawer_SetCharPad();
// void FaultDrawer_SetCursor();
// void FaultDrawer_FillScreen();
// void FaultDrawer_PrintCallback();
// void FaultDrawer_VPrintf();
void FaultDrawer_Printf(const char* fmt, ...);
// void FaultDrawer_DrawText();
// void FaultDrawer_SetDrawerFB();
// void FaultDrawer_SetInputCallback();
// void FaultDrawer_WritebackFBDCache();
// void FaultDrawer_Init();

#endif
