
#include <stdio.h>
#include <stdlib.h>

int main() {
        int i;
        int j;
        char buffer[256];
        printf("Enter a number: ");
        fgets(buffer, 256, stdin);
        i = atoi(buffer);
        j = atoi("123456");
        printf("The value entered is %d. Its double is %d\n", i, i * 2);
        printf("The value of j is %d\n", j);
        return 0;
}
