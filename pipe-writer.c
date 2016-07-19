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
        write(fd, "Hello world first", sizeof("Hello world first"));
        close(fd);
        sleep(3);
        fd = open(myfifo, O_WRONLY);
        write(fd, "Hello world second", sizeof("Hello world second"));
        close(fd);
        return 0;
}
