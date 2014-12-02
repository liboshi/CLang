#include <stdio.h>
#include <string.h>

int memchr_test()
{
        char *pch;
        char str[] = "Example string";
        pch = (char *)memchr(str, 'p', strlen(str));
        if (pch != NULL) {
                printf("'p' found at position: %d...\n", pch - str + 1);
        } else {
                printf("'p' not found...\n");
        }
        return 0;
}

int main()
{
        int ret;
        ret = memchr_test();
        return ret;
}
