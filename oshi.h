#ifndef _OSHI_H
#define _OSHI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DllExport
#undef DllExport
#endif

#ifdef WIN32
#define DllExport __declspec(dllexport)
#else
#define DllExport __attribute__ ((visibility ("default")))
#endif

#ifdef __cplusplus
}
#endif

typedef unsigned short uint16;

typedef struct _OshiIntfVer
{
    uint16 major;
    uint16 minor;
} OshiIntfVer;

typedef void *OshiIntf;

#define OSHI_MAJOR_VER_0 0
#define OSHI_MAJOR_VER_1 1
#define OSHI_MINOR_VER_0 0
#define OSHI_MINOR_VER_1 1

#define OSHIFN_API

typedef void
(OSHIFN_API *OSHIFN_SayHello)(char *name);

typedef void
(OSHIFN_API *OSHIFN_SayGoodbye)(char *name);

typedef void
(*OSHIFN_GetIntf)(OshiIntf intf);

typedef void
(*OSHIFN_Start)(OshiIntf intf);

#define OSHI_INTF_V01             \
    OshiIntfVer       version;    \
    OSHIFN_SayHello   sayHello;   \
    OSHIFN_SayGoodbye sayGoodbye;

typedef struct _OshiIntfV01
{
    OSHI_INTF_V01
} OshiIntfV01;

#endif
