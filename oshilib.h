#ifndef _OSHI_LIB_H
#define _OSHI_LIB_H
#include "oshi.h"

#ifdef DllExport
#undef DllExport
#endif

#ifdef WIN32
#define DllExport extern "C" __declspec(dllexport)
#else
#define DllExport extern "C" __attribute__ ((visibility ("default")))
#endif

void
OSHILIB_GetIntf(OshiIntf intf);

void
OSHILIB_SayHello(char *name);

void
OSHILIB_SayGoodbye(char *name);

#endif
