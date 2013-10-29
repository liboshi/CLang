#include <stdio.h>
#include <stdlib.h>

#define NUL '\0'
#define FALSE 0
#define TRUE 1

int strlen(char *str)
{
        int length = 0;
        while(*str++ != '\0')
        {
                length += 1;
        }
        return length;
}

char *match(char *str, char *want)
{
        while(*want != NUL)
                if(*str++ != *want++)
                        return NULL;
        return str;
}

int del_substr(char *str, char const *substr)
{
        char *next;
        while(*str != NUL)
        {
                next = match(str, substr);
                if(next != NULL)
                        break;
                str++;
        }
        if(*str == NUL)
                return FALSE;

        while(*str++ = *next++)
                ;
        
        return TRUE;        
}

int main(int argc, char *argv[])
{
        char *name = "liboshi";
        int len = strlen(name);
        printf("The length of string %s is: %d\n", name, len);
        char *str = "liboshi";
        char const *substr = "shi";
        del_substr(str, substr);
        printf("The string is: %s\n", str);
}
