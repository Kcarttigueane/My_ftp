/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#include <stdio.h>
#include "./include/server.h"

int main(int argc, char const* argv[])
{
    if (argc != 2)
        handle_error(SERVER_USAGE);

    server_data_t server_data;
    init_server(&server_data, argv);

    while (true ) {
        server_data.copy_fds = server_data.fds;
        server_data.timeout.tv_sec = 5;
        server_data.timeout.tv_usec = 5000;

        if ((server_data.fd_num =
                 select(server_data.fd_max + 1, &server_data.copy_fds, 0, 0,
                        &server_data.timeout)) == FAILURE) {
            break;
        }

        if (server_data.fd_num == 0)
            continue;

        for (int i = 0; i < (server_data.fd_max + 1); i++) {
            if (FD_ISSET(i, &server_data.copy_fds)) {
                if (i == server_data.server_fd) {
                    int client_fd =
                        accept(server_data.server_fd,
                               (struct sockaddr*)&server_data.client_address,
                               &server_data.client_len);
                    if (client_fd < 0)
                        handle_error("Accept");
                    FD_SET(client_fd, &server_data.fds);
                    if (server_data.fd_max < client_fd) {
                        server_data.fd_max = client_fd;
                    }
                    printf("New client connected from %s:%d\n",
                           inet_ntoa(server_data.client_address.sin_addr),
                           ntohs(server_data.client_address.sin_port));
                } else {
                    server_data.str_len =
                        read(i, server_data.buffer, BUFFER_SIZE);
                    if (server_data.str_len == 0) {
                        FD_CLR(i, &server_data.fds);
                        close(i);
                        printf("Close client: %i\n", i);
                    } else {
                        write(i, server_data.buffer, server_data.str_len);
                    }
                }
            }
        }
    }

    close(server_data.server_fd);
    return 0;
}

// if (strcmp(username, ANONYMOUS_USERNAME) == 0 &&
//     strcmp(password, ANONYMOUS_PASSWORD) == 0) {
//     printf("Access granted.\n");
//     // Accept the connection and proceed with the FTP commands
// } else {
//     printf("Access denied.\n");
//     // Reject the connection and close the socket
// }
