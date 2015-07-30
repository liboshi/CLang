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
        char *myfifo = "/tmp/myfifo";
        struct stat sb;

        /* open, read, and display the message from the FIFO */
        printf("%d\n", stat(myfifo, &sb));
        if (stat(myfifo, &sb) == -1) {
                perror("stat");
                return -1;
        }
        while (i) {
                fd = open(myfifo, O_RDONLY);
                char buf[MAX_BUF];
                read(fd, buf, MAX_BUF);
                if (strlen(buf) > 0) {
                        printf("Received: %s\n", buf);
                        close(fd);
                }
                usleep(3000);
        }

        return 0;
}
