// Force the inclusion of unused archive files
EXTERN(osGetIntMask);
ASSERT(DEFINED(osGetIntMask), "Error: osGetIntMask was not linked");

EXTERN(osGetMemSize);
ASSERT(DEFINED(osGetMemSize), "Error: osGetMemSize was not linked");

EXTERN(guPositionF);
ASSERT(DEFINED(guPositionF), "Error: guPositionF was not linked");
