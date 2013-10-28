#include <stdio.h>

void swap_int(int *x, int *y)
{
        int tmp = *y;
        *y = *x;
        *x = tmp;
}

int main(int argc, char *argv[])
{
        int i = 1, j = 2;
        swap_int(&i, &j);
        printf("i = %d, j = %d\n", i, j);
        return 0;
}
