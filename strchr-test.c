
#include <stdio.h>
#include <string.h>

int main()
{
        char str[] = "This is a sample string";
        char *pch;
        printf("Looking for the 's' character in \"%s\"...\n", str);
        pch = strchr(str, 's');
        while (pch != NULL) {
                printf("found at %ld\n", pch - str + 1);
                pch = strchr(pch + 1, 's');
        }
        return 0;
}
