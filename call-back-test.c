#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_two_numbers(int (*number_source) (void)) {
        printf("%d add %d\n", number_source(), number_source());
}

int over_nine_thousand(void) {
        return (rand() % 1000) + 9001;
}

int meaning_of_life(void) {
        return 29;
}

typedef struct _MyMsg {
                int appId;
                char msgbody[32];
} MyMsg;

int myfunc(MyMsg *msg)
{
        if (strlen(msg->msgbody) > 0 )
                printf("App Id = %d \nMsg = %s \n",msg->appId, msg->msgbody);
        else
                printf("App Id = %d \nMsg = No Msg\n",msg->appId);
        return 0;
}

typedef int (* callback)(MyMsg *);

int main(void)
{
        print_two_numbers(&over_nine_thousand);
        print_two_numbers(&meaning_of_life);

        MyMsg msg1;
        msg1.appId = 100;
        strcpy(msg1.msgbody, "This is a test\n");

        callback mycallback = &myfunc;

        mycallback(&msg1);

        return 0;
}
