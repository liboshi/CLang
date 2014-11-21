#include <stdio.h>

int main(int argc, char *argv[])
{
        FILE *fileToCheck;
        long filesize;
        fileToCheck = fopen(argv[1], "rb");
        fseek(fileToCheck, 0, SEEK_END);
        filesize = ftell(fileToCheck);
        fclose(fileToCheck);
        printf("Size of File: %s is %ld byte\n", argv[1], filesize);
        return 0;
}
