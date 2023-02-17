/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** myFTP_loop.c
*/

#include "server.h"

void myFTP_loop(server_data_t* server_data)
{
    circular_buffer cb;
    cb_init(&cb);

    while (true) {
        server_data->copy_fds = server_data->fds;
        server_data->timeout.tv_sec = 5;
        server_data->timeout.tv_usec = 5000;

        if ((server_data->fd_num =
                 select(server_data->fd_max + 1, &server_data->copy_fds, 0, 0,
                        &server_data->timeout)) == FAILURE) {
            break;
        }

        if (server_data->fd_num == 0)
            continue;

        for (int i = 0; i < (server_data->fd_max + 1); i++) {
            if (FD_ISSET(i, &server_data->copy_fds)) {
                if (i == server_data->server_fd) {
                    int client_fd =
                        accept(server_data->server_fd,
                               (struct sockaddr*)&server_data->client_address,
                               &server_data->client_len);
                    if (client_fd < 0)
                        handle_error("Accept");
                    write(client_fd, FTP_REPLY_220, strlen(FTP_REPLY_220));

                    FD_SET(client_fd, &server_data->fds);
                    if (server_data->fd_max < client_fd) {
                        server_data->fd_max = client_fd;
                    }
                    printf("New client connected from %s:%d\n",
                           inet_ntoa(server_data->client_address.sin_addr),
                           ntohs(server_data->client_address.sin_port));
                } else {
                    server_data->str_len =
                        read(i, server_data->buffer, BUFFER_SIZE);
                    server_data->buffer[server_data->str_len] = '\0';
                    if (server_data->str_len == 0) {
                        FD_CLR(i, &server_data->fds);
                        close(i);
                        printf("Close client: %i\n", i);
                    } else {
                        write(i, server_data->buffer, server_data->str_len);
                        cb_push(&cb, server_data->buffer);
                        parse_command(&cb, server_data, i);
                        printf("Client %i said: %s", i, server_data->buffer);
                    }
                }
            }
        }
    }
}
