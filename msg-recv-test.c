#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSZ 128


/*
 *Declare the message structure.
 */

typedef struct msgbuf {
        long    mtype;
        char    mtext[MSGSZ];
} message_buf;

int
main()
{
        int msqid;
        key_t key;
        message_buf  rbuf;

        /*
         * Get the message queue id for the
         * "name" 9527, which was created by
         * the server.
         */
        key = 9527;

        if ((msqid = msgget(key, 0666)) < 0) {
                perror("msgget");
                return 1;
        }


        /*
         * Receive an answer of message type 1.
         */
        if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
                perror("msgrcv");
                return 1;
        }

        /*
         * Print the answer.
         */
        printf("%s\n", rbuf.mtext);
        return 0;
}
