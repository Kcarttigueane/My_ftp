/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** handle_new_client.c
*/

#include "../include/server.h"

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

    if (server_data->fd_max <\
        clients[server_data->nb_clients].client_socked_fd) {
        server_data->fd_max = clients[server_data->nb_clients].client_socked_fd;
    }
    clients[server_data->nb_clients].current_path =
        strdup(server_data->initial_path);
    strcpy(clients[server_data->nb_clients].username, ANONYMOUS_USERNAME);
    strcpy(clients[server_data->nb_clients].password, ANONYMOUS_PASSWORD);
    clients[server_data->nb_clients].is_logged = false;
    server_data->nb_clients++;
}
