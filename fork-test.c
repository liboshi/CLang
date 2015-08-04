#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(int argc, char *argv[]) {
        pid_t cpid, w;
        int status;

        cpid = fork();
        if (-1 == cpid) {
                perror("fork");
                exit(EXIT_FAILURE);
        }

        if (0 == cpid) {
                printf("Child PID is %ld\n", (long)getpid());
                if (argc == 1)
                        pause();
                _exit(atoi(argv[1]));
        } else {
                do {
                        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
                        if (-1 == w) {
                                perror("waitpid");
                                exit(EXIT_FAILURE);
                        }

                        if (WIFEXITED(status)) {
                                printf("exited, status=%d\n", WEXITSTATUS(status));
                        } else if (WIFSIGNALED(status)) {
                                printf("killed by signal %d\n", WTERMSIG(status));
                        } else if (WIFSTOPPED(status)) {
                                printf("stopped by signal %d\n", WSTOPSIG(status));
                        } else if (WIFCONTINUED(status)) {
                                printf("continued\n");
                        }
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                exit(EXIT_SUCCESS);
        }
        return 0;
}
