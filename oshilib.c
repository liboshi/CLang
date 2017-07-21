#include <stdio.h>
#include "oshilib.h"

void
OSHILIB_GetIntf(OshiIntf intf)
{
        OshiIntfV01 *intfCurr = (OshiIntfV01 *)intf;
        // Add some checker here
        //      such as: interface version and etc.
        if (intfCurr->version.major == 0 &&
            intfCurr->version.minor == 1) {
                printf("Version is correct.\n");
        }
        intfCurr->sayHello = OSHILIB_SayHello;
        intfCurr->sayGoodbye = OSHILIB_SayGoodbye;
}

void
OSHILIB_SayHello(char *name)
{
        printf("Hello %s\n", name);
}

void
OSHILIB_SayGoodbye(char *name)
{
        printf("Goodbye %s\n", name);
}

DllExport void
OSHI_Start(OshiIntf intf)
{
        OSHILIB_GetIntf(intf);
}
