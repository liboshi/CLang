#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ 128

/*
 * Declare the message structure.
 */
typedef struct msgbuf {
        long mtype;
        char mtext[MSGSZ];
} msg_buf;

int main()
{
        int msqid;
        int msgflg = IPC_CREAT | 0666;
        key_t key;
        msg_buf sbuf;
        size_t buf_length;

        /*
         * Get the message queue id for the "name" 9527, which was created by
         * by the server.
         */
        key = 9527;
        if ((msqid = msgget(key, msgflg)) < 0) {
                perror("msgget");
                return 1;
        } else {
                (void) fprintf(stderr, "msgget: msgget succeeded: msqid = %d\n",
                               msqid);
        }

        sbuf.mtype = 1;

        (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

        (void) strcpy(sbuf.mtext, "Hello message receiver...");

        (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);

        buf_length = strlen(sbuf.mtext) + 1 ;

        /*
         * Send a message.
         */
        if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
                perror("msgsnd");
                return 1;
        } else {
                printf("Message: \"%s\" Sent\n", sbuf.mtext);
        }

        return 0;
}
