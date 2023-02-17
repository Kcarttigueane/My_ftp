/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** init_server.c
*/

#include "server.h"

void create_socket(server_data_t* server_data)
{
    server_data->server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_data->server_fd == FAILURE)
        handle_error("Socket creation");
}

void bind_socket(server_data_t* server_data)
{
    if (bind(server_data->server_fd,
             (struct sockaddr*)&server_data->server_address,
             sizeof(server_data->server_address)) < 0)
        handle_error("Bind error");
}

void listen_socket(server_data_t* server_data)
{
    if (listen(server_data->server_fd, QUEUE_LEN) < 0)
        handle_error("Listen");
}

void init_server(server_data_t* server_data, char const* argv[])
{
    server_data->PORT = atoi(argv[1]);

    create_socket(server_data);

    memset(&server_data->server_address, 0,
           sizeof(server_data->server_address));
    server_data->server_address.sin_family = AF_INET;
    server_data->server_address.sin_addr.s_addr = INADDR_ANY;
    server_data->server_address.sin_port = htons(server_data->PORT);

    bind_socket(server_data);

    printf("Server started on port %d\n", server_data->PORT);

    listen_socket(server_data);
    printf("Waiting for a client...\n");

    FD_ZERO(&server_data->fds);
    FD_SET(server_data->server_fd, &server_data->fds);
    server_data->fd_max = server_data->server_fd;
}
