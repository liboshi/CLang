#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
do_at_exit(void)
{
        printf("Program exit\n");
}

int
main()
{
        int flag;
        printf("Function enter\n");

        flag = atexit(do_at_exit);

        if (flag != 0) {
                printf("Cannot set exit function\n");
                return EXIT_FAILURE;
        }

        if (fork() > 0) {
                exit(EXIT_SUCCESS);
        } else {
                _exit(1);
        }
}
