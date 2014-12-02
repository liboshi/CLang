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

int memcmp_test()
{
        char buffer1[] = "DWgaOtP12df0";
        char buffer2[] = "DWGAOTP12DF0";
        int n;
        n=memcmp(buffer1, buffer2, sizeof(buffer1));

        if (n>0) printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
        else if (n<0) printf ("'%s' is less than '%s'.\n",buffer1,buffer2);
        else printf ("'%s' is the same as '%s'.\n",buffer1,buffer2);

        return 0;
}

int main()
{
        int ret;
        //ret = memchr_test();
        ret = memcmp_test();
        return ret;
}
