#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int
main(int argc, char *argv[])
{
        int listenfd = 0;
        int connfd = 0;
        struct sockaddr_in svr_addr;

        char sendBuff[1024];
        time_t ticks;

        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&svr_addr, '0', sizeof(svr_addr));
        memset(sendBuff, '0', sizeof(sendBuff));

        svr_addr.sin_family = AF_INET;
        svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        svr_addr.sin_port = htons(50132);

        bind(listenfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));

        listen(listenfd, 10);

        while (1) {
                connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

                ticks = time(NULL);
                snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
                write(connfd, sendBuff, strlen(sendBuff));

                close(connfd);
                sleep(1);
        }
}
