#include <stdio.h>
#include <sys/timeb.h>

int
main() {
        struct timeb ftm;
        ftime(&ftm);
        printf("time: %hu\n", ftm.millitm);
        ftime(&ftm);
        printf("time: %hu\n", ftm.millitm);
        return 0;
}
