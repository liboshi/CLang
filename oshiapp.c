#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "oshi.h"

#define OSHI_LIB "/home/boshil/github/clang/liboshi.so"

void* load_library(const char *path);
void* get_proc_address(void *handle, const char *symbol);
void free_library(void *handle);

void*
load_library(const char *path)
{
        void *handle = dlopen(path, RTLD_LAZY);

        if (!handle) {
                printf("Failed to load shared library: %s %s\n",
                       path, dlerror());
                return NULL;
        }
        return handle;
}

void*
get_proc_address(void *handle, const char *symbol)
{
        if (!handle) {
                printf("Invalid shared library handle.\n");
                return NULL;
        }
        return dlsym(handle, symbol);
}

void
free_library(void *handle)
{
        if (!handle) {
                printf("Invalid shared library handle.\n");
        }
}

int
main()
{
        OshiIntfVer intfVer;
        OshiIntfV01 g_intf;
        OshiIntfV01 *g_intfv01;
        void *hinstlib = NULL;

        g_intf.version.major = 0;
        g_intf.version.minor = 1;
        hinstlib = load_library(OSHI_LIB);
        if (hinstlib != NULL) {
                OSHIFN_Start oshi_start = (OSHIFN_Start)get_proc_address(hinstlib, "OSHI_Start");
                if (oshi_start) {
                        oshi_start((OshiIntf)&g_intf);
                }
        }
        g_intfv01 = &g_intf;
        g_intfv01->sayHello("Boush");
        g_intfv01->sayGoodbye("Boush");
        free_library(hinstlib);
        return 0;
}
