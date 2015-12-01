#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/time.h>

double
get_current_time_ms()
{
        struct timeval tv;
        gettimeofday(&tv, NULL);

        return tv.tv_sec * 1000000 + tv.tv_usec;
}

int
main() {
        struct timeb ftm;
        ftime(&ftm);
        printf("time: %hu\n", ftm.millitm);
        ftime(&ftm);
        printf("time: %hu\n", ftm.millitm);
        printf("%f\n", get_current_time_ms() / 1000);
        return 0;
}
