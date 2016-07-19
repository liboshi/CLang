#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024

int
main()
{
        int i = 2;
        int fd;
        int timeout = 10 * 1000 * 1000;
        char *myfifo = "/tmp/myfifo";
        struct stat sb;

        /* open, read, and display the message from the FIFO */
        if (stat(myfifo, &sb) == -1) {
                perror("stat");
                return -1;
        }
        while (timeout) {
                fd = open(myfifo, O_RDONLY);
                char buf[MAX_BUF];
                if (read(fd, buf, MAX_BUF) > -1) {
                        if (strlen(buf) > 0) {
                                printf("Received: %s\n", buf);
                                close(fd);
                        }
                }
                usleep(500);
                timeout -= 500;
        }

        return 0;
}
