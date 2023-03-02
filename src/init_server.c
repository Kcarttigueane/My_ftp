/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** init_server.c
*/

#include "../include/server.h"

void create_socket(server_data_t* server_data)
{
    server_data->server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_data->server_socket_fd == FAILURE)
        handle_error("Socket creation");
}

void bind_socket(server_data_t* server_data)
{
    if (bind(server_data->server_socket_fd,
    (struct sockaddr*)&server_data->server_address,
    sizeof(server_data->server_address)) < 0)
        handle_error("Bind error");
}

void listen_socket(server_data_t* server_data)
{
    if (listen(server_data->server_socket_fd, QUEUE_LEN) < 0)
        handle_error("Listen");
}

void init_server_data(server_data_t *server_data)
{
    memset(&server_data->server_address, 0,
    sizeof(server_data->server_address));
    server_data->server_address.sin_family = AF_INET;
    server_data->server_address.sin_addr.s_addr = INADDR_ANY;
    server_data->server_address.sin_port = htons(server_data->PORT);
}

void init_server(server_data_t* server_data, char const* argv[])
{
    server_data->PORT = atoi(argv[1]);
    server_data->nb_clients = 0;
    server_data->timeout.tv_sec = 5;
    server_data->timeout.tv_usec = 5000;
    server_data->data_socket_fd = FAILURE;
    server_data->data_mode = NO_MODE;
    create_socket(server_data);
    init_server_data(server_data);
    bind_socket(server_data);
    listen_socket(server_data);
    FD_ZERO(&server_data->fds);
    FD_ZERO(&server_data->copy_fds);
    FD_SET(server_data->server_socket_fd, &server_data->fds);
    server_data->fd_max = server_data->server_socket_fd;
    server_data->initial_path = realpath(argv[2], NULL);
    if (!server_data->initial_path)
        handle_error("realpath");
    if (chdir(server_data->initial_path) == FAILURE)
        handle_error("chdir");
}
