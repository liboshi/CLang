#include <stdio.h>
#include <time.h>

int main(void)
{
        time_t current_time;
        time_t start_time;

        printf("About delay 5 seconds\n");

        time(&start_time);

        do {
            time(&current_time);
        } while ((current_time - start_time) < 5);
        
        printf("Done\n");
        return 0;
}
