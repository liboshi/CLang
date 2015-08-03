#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(void) {
        pid_t cpid;
        cpid = fork();
        if (cpid < 0) {
                printf("Fork successfully.\n");
        }
        if (cpid == 0) {
                printf("Child process.\n");
        }
        if (cpid == 0) {
                printf("Child process.\n");
        }
        return 0;
}
