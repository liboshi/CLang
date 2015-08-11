#include <stdio.h>
#include <stdlib.h>

typedef int (*somefunc)(int, int);

int
product(int a, int b)
{
        printf("Sum is: %d\n", a + b);
        return a + b;
}

int
main()
{
        somefunc afunc = &product;
        afunc(4, 5);
        return 0;
}
