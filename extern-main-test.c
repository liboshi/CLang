#include <stdio.h>
#include <stdlib.h>

extern int var;
extern int foo();

int
main()
{
        printf("Value of var from foo: %d\n", foo());
        printf("Accessing var directly: %d\n", var);
        return 0;
}

