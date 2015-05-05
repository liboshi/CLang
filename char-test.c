
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main() {
        char test_str_1[20] = "LiBoshi";
        char *test_str_2 = "LiBoshi";
        int size = sizeof(test_str_1);
        int size2 = sizeof(test_str_2);
        int str_length = strlen(test_str_1);
        printf("The size of string 1 is %d \n",size);
        printf("The size of string 2 is %d \n",size2);
        printf("The length of string 1 is %d \n", str_length);
        return 0;
}
