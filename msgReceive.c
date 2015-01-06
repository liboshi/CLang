#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#define MSGKEY 1024

struct msgst {
        long msgtype;
        char msgtext[2048];
};

void childproc(){
        struct msgst msgs;
        int msgid,ret;
        char str[512];

        while(1){
                msgid = msgget(MSGKEY, IPC_CREAT | 0660);
                if(msgid < 0) {
                        printf("msq not existed! errno=%d [%s]\n", errno, strerror(errno));
                        sleep(2);
                        continue;
                }

                ret = msgrcv(msgid, &msgs, sizeof(struct msgst), 0, 0);
                printf("text=[%s] pid=[%d]\n", msgs.msgtext, getpid());
        }
        return;
}

int
main() {
        int i, cpid;

        for (i=0; i<5; i++){
                cpid = fork();
                if (cpid < 0)
                        printf("fork failed\n");
                else if (cpid ==0) /*child process*/
                        childproc();
        }
        return 0;
}
