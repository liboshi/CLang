#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024

int
main()
{
        int fd;
        char *myfifo = "/tmp/myfifo";
        char buf[MAX_BUF];
        struct stat sb;

        /* open, read, and display the message from the FIFO */
        printf("%d\n", stat(myfifo, &sb));
        if (stat(myfifo, &sb) == -1) {
                perror("stat");
                return -1;
        }
        fd = open(myfifo, O_RDONLY);
        printf("The handle is %d\n", fd);
        read(fd, buf, MAX_BUF);
        printf("Received: %s\n", buf);
        printf("Received size: %lu\n", strlen(buf));
        close(fd);

        return 0;
}
