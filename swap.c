#include <stdio.h>

void swap_int(int *x, int *y)
{
        int tmp = *y;
        *y = *x;
        *x = tmp;
}

void reverse_string(char *str)
{
        char *last_char;
        for(last_char = str; *last_char != '\0'; last_char++)
                ;
        last_char--;
        while(str < last_char)
        {
                char tmp;
                tmp = *str;
                *str++ = *last_char;
                *last_char-- = tmp;
        }
}

int main(int argc, char *argv[])
{
        int i = 1, j = 2;
        swap_int(&i, &j);
        printf("i = %d, j = %d\n", i, j);
        char *str = "string";
        reverse_string(str);
        printf("Reversed string: %s", str);
        return 0;
}
