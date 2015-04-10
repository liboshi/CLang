#include <stdio.h>
#include <stdlib.h>

void printTwoNumbers(int (*numberSource) (void)) {
        printf("%d add %d\n", numberSource(), numberSource());
}

int overNineThousand(void) {
        return (rand() % 1000) + 9001;
}

int meaningOfLife(void) {
        return 29;
}

int main(void) {
        printTwoNumbers(&rand);
        printTwoNumbers(&overNineThousand);
        printTwoNumbers(&meaningOfLife);
        return 0;
}
