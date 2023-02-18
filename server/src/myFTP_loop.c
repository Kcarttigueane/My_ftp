/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** myFTP_loop.c
*/

#include "server.h"

void accept_new_client(server_data_t* server_data, client_t* clients)
{
    if (server_data->nb_clients == FD_SETSIZE) {
        handle_error("Too many clients");
    }
    clients[server_data->nb_clients].client_socked_fd = accept(
        server_data->server_socket_fd,
        (struct sockaddr*)&clients[server_data->nb_clients].client_address,
        &clients[server_data->nb_clients].client_len);
    if (clients[server_data->nb_clients].client_socked_fd < 0)
        handle_error("Accept");
}

void handle_new_client_connection(server_data_t* server_data, client_t* clients)
{
    accept_new_client(server_data, clients);

    send_resp(clients[server_data->nb_clients].client_socked_fd, FTP_REPLY_220);

    FD_SET(
        clients[server_data->nb_clients].client_socked_fd,
        &server_data
             ->fds);  // adds the client file descriptor clients[server_data->nb_clients].client_socked_fd to the set of monitored file descriptors server_data->fds

    if (server_data->fd_max <
        clients[server_data->nb_clients].client_socked_fd) {
        server_data->fd_max = clients[server_data->nb_clients].client_socked_fd;
    }

    server_data->nb_clients++;

    printf("New client connected from %s:%d\n",
           inet_ntoa(clients[server_data->nb_clients].client_address.sin_addr),
           ntohs(clients[server_data->nb_clients].client_address.sin_port));
}

void file_descriptors_loop(server_data_t* server_data, client_t* clients,
                           circular_buffer* cb)
{
    for (int i = 0; i < (server_data->fd_max + 1); i++) {
        if (FD_ISSET(i, &server_data->copy_fds)) {
            if (i == server_data->server_socket_fd) {
                handle_new_client_connection(server_data, clients);
            } else {
                server_data->read_input_len =
                    read(i, server_data->buffer, BUFFER_SIZE);
                server_data->buffer[server_data->read_input_len] = '\0';
                if (server_data->read_input_len == 0) {
                    FD_CLR(i, &server_data->fds);
                    close(i);
                    printf("Close client: %i\n", i);
                } else {
                    write(i, server_data->buffer, server_data->read_input_len);
                    cb_push(&cb, server_data->buffer);
                    parse_command(&cb, server_data, i);
                    printf("Client %i said: %s", i, server_data->buffer);
                }
            }
        }
    }
}

void myFTP_loop(server_data_t* server_data, client_t* clients)
{
    circular_buffer cb;
    cb_init(&cb);
    printf("Server is listening on port %d\n", server_data->server_socket_fd);
    while (true) {
        server_data->copy_fds = server_data->fds;

        if ((server_data->fd_num =
                 select(server_data->fd_max + 1, &server_data->copy_fds, 0, 0,
                        &server_data->timeout)) == FAILURE) {
            break;
        }
        if (server_data->fd_num == STDIN_FILENO)
            continue;
        file_descriptors_loop(server_data, clients, &cb);
    }
}
