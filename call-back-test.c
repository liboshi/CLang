#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OSHIFN_API

void print_two_numbers(int (*number_source) (void)) {
        printf("%d add %d\n", number_source(), number_source());
}

int over_nine_thousand(void) {
        return (rand() % 1000) + 9001;
}

int meaning_of_life(void) {
        return 29;
}

typedef struct _my_msg {
                int appId;
                char msgbody[32];
} my_msg;

int myfunc(my_msg *msg)
{
        if (strlen(msg->msgbody) > 0 )
                printf("App Id = %d \nMsg = %s \n",msg->appId, msg->msgbody);
        else
                printf("App Id = %d \nMsg = No Msg\n",msg->appId);
        return 0;
}

int foo(int age)
{
        printf("my age is %d\n", age);
        return 0;
}

typedef int (OSHIFN_API *callback)(my_msg *);
typedef int (OSHIFN_API *callback1)(int);

int main(void)
{
        print_two_numbers(&over_nine_thousand);
        print_two_numbers(&meaning_of_life);

        my_msg msg1;
        msg1.appId = 100;
        strcpy(msg1.msgbody, "This is a test");

        callback mycallback = &myfunc;
        callback1 mycallback1 = &foo;

        mycallback(&msg1);
        mycallback1(25);

        return 0;
}
