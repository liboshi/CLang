#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
main() {
        int fd;
        char *myfifo = "/tmp/myfifo";
        mkfifo(myfifo, 0666);

        fd = open(myfifo, O_WRONLY);
        printf("The handle is %d", fd);
        write(fd, "Hi", sizeof("Hi"));
        close(fd);

        unlink(myfifo);

        return 0;
}
