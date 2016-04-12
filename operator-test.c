
#include <stdio.h>

int main()
{
        int i = 1;
        for (; i < 10; i++) {
                printf("~%d => %d\n", i, ~i);
        }
        return 0;
}
