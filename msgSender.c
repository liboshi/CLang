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

int
main() {
        struct msgst msgs;
        int msg_type;
        char str[256];
        int ret;
        int msgid;

        msgid = msgget(MSGKEY, IPC_EXCL);
        if (msgid < 0) {
                printf("Failed to create msq\n");
                return -1;
        }

        while (1) {
                printf("Input Message type: ");
                scanf("%d", &msg_type);
                if (msg_type == 0)
                        break;
                printf("Input Message to be sent: ");
                scanf("%s", str);
                msgs.msgtype = msg_type;
                strcpy(msgs.msgtext, str);
                ret = msgsnd(msgid, &msgs, sizeof(struct msgst), IPC_NOWAIT);
                if (ret < 0) {
                        printf("msgsnd() write message failed...\n");
                        return -1;
                }
        }

        msgctl(msgid, IPC_RMID, 0);
        return 0;
}
