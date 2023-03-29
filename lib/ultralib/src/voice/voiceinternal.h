#ifndef VOICE_INTERNAL_H
#define VOICE_INTERNAL_H

// Various prototypes and externs that don't show up in os_voice.h
extern s32 __osPfsLastChannel;

u8 __osVoiceContDataCrc(u8* data, u32 length);
s32 __osVoiceCheckResult(OSVoiceHandle* hd, u8* stat);

#endif
