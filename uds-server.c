#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include "connection.h"

int
main(int argc, char *argv[])
{
        struct sockaddr_un name;
        int down_flag = 0;
        int ret;
        int connection_socket;
        int data_socket;
        int result;
        char buffer[BUFFER_SIZE];

        /* In case the program exited inadvertently on the last run, remove the
         * socket.
         */
        unlink(SOCKET_NAME);

        memset(&name, 0, sizeof(struct sockaddr_un));

        /* Create local socket */
        connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (connection_socket == -1) {
                perror("socket");
                exit(EXIT_FAILURE);
        }

        /* Bind socket to sokcet name */
        name.sun_family = AF_UNIX;
        strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

        ret = bind(connection_socket, (const struct sockaddr *) &name,
                   sizeof(struct sockaddr_un));
        if (ret == -1) {
                perror("bind");
                exit(EXIT_FAILURE);
        }

        ret = listen(connection_socket, 20);
        if (ret == -1) {
                perror("listen");
                exit(EXIT_FAILURE);
        }

        for (;;) {
                /* Wait for incomming connection */
                data_socket = accept(connection_socket, NULL, NULL);
                if (data_socket == -1) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                }

                result = 0;
                for (;;) {
                        /* Wait for next data packet */
                        ret = read(data_socket, buffer, BUFFER_SIZE);
                        if (ret == -1) {
                                perror("read");
                                exit(EXIT_FAILURE);
                        }

                        /* Ensure buffer is 0-terminated */
                        buffer[BUFFER_SIZE - 1] = 0;

                        /* Handle commands */
                        if (!strncmp(buffer, "DOWN", BUFFER_SIZE)) {
                                down_flag = 1;
                                break;
                        }

                        if (!strncmp(buffer, "END", BUFFER_SIZE)) {
                                break;
                        }

                        /* Add received summand. */
                        result += atoi(buffer);
                }

                /* Send result */
                sprintf(buffer, "%d", result);

                ret = write(data_socket, buffer, BUFFER_SIZE);
                if (ret == -1) {
                        perror("write");
                        exit(EXIT_FAILURE);
                }

                /* Close socket */
                close(data_socket);

                /* Quit on DOWN command */
                if (down_flag) {
                        break;
                }
        }

        close(connection_socket);

        /* Unlink the sokcet */
        unlink(SOCKET_NAME);

        exit(EXIT_SUCCESS);
}
