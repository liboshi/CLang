#include <stdio.h>
#include <string.h>

struct {
        char name[40];
        int age;
} person, person_copy;

int memchr_test()
{
        char *pch;
        char str[] = "Example string";
        pch = (char *)memchr(str, 'p', strlen(str));
        if (pch != NULL) {
                printf("'p' found at position: %d...\n", pch - str + 1);
        } else {
                printf("'p' not found...\n");
        }
        return 0;
}

int memcmp_test()
{
        char buffer1[] = "DWgaOtP12df0";
        char buffer2[] = "DWGAOTP12DF0";
        int n;
        n=memcmp(buffer1, buffer2, sizeof(buffer1));

        if (n>0) printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
        else if (n<0) printf ("'%s' is less than '%s'.\n",buffer1,buffer2);
        else printf ("'%s' is the same as '%s'.\n",buffer1,buffer2);

        return 0;
}

int memcpy_test()
{
        char myname[] = "Boush Li";
        memcpy(person.name, myname, strlen(myname) + 1);
        person.age = 28;

        memcpy(&person_copy, &person, sizeof(person));

        printf("person_copy: %s, %d\n", person_copy.name, person_copy.age);

        return 0;
}

int memmove_test()
{
        char str[] = "memmove can be very useful......";
        memmove(str + 20, str + 15, 11);
        puts(str);
        return 0;
}

int memset_test()
{
        char str[] = "xxx My Name is Li Boush...";
        memset(str, '>', 3);
        puts(str);
        return 0;
}

int strcat_test()
{
        char str[80];
        strcpy(str, "Thesse ");
        strcat(str, "strings ");
        strcat(str, "are ");
        strcat(str, "concatenated...");
        puts(str);
        return 0;
}

int main()
{
        int ret;
        //ret = memchr_test();
        //ret = memcmp_test();
        //ret = memcpy_test();
        //ret = memmove_test();
        //ret = memset_test();
        ret = strcat_test();
        return ret;
}
