#include <stdio.h>
#include <stdlib.h>

inline void
swap(int m, int n)
{
        printf("%d, %d\n", m, n);
        int temp = m;
        m = n;
        n = temp;
        printf("%d, %d\n", m, n);
}

int
main()
{
        swap(1, 2);
        return 0;
}
