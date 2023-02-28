/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pasv.c
*/

#include "../../../include/server.h"

void set_socket_options(int socket_fd)
{
    int reuse = 1;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
        0) {
        handle_error("setsockopt");
    }
}

int get_bound_port(int socket_fd, struct sockaddr* address,
socklen_t* address_len)
{
    if (getsockname(socket_fd, address, address_len) < 0)
        handle_error("getsockname");
    return ntohs(((struct sockaddr_in*)address)->sin_port);
}

int create_data_socket(server_data_t* server_data)
{
    int data_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket_fd < 0)
        handle_error("socket");

    set_socket_options(data_socket_fd);

    memset(&server_data->data_address, 0, sizeof(server_data->data_address));
    server_data->data_address.sin_family = AF_INET;
    server_data->data_address.sin_addr.s_addr =
        server_data->server_address.sin_addr.s_addr;
    server_data->data_address.sin_port = 0;

    if (bind(data_socket_fd, (struct sockaddr*)&server_data->data_address,
        sizeof(server_data->data_address)) < 0)
        handle_error("bind pasv");

    if (listen(data_socket_fd, 1) < 0)
        handle_error("listen");

    return data_socket_fd;
}

void ip_to_bytes(const char* ip, int* bytes)
{
    sscanf(ip, "%d.%d.%d.%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
}

void pasv(list_args_t* args)
{
    args->server_data->data_socket_fd = create_data_socket(args->server_data);
    args->server_data->data_len = sizeof(args->server_data->data_address);

    int port = get_bound_port(args->server_data->data_socket_fd,
    (struct sockaddr*)&args->server_data->data_address,
    &args->server_data->data_len);
    int bytes[4];

    ip_to_bytes(inet_ntoa(args->server_data->server_address.sin_addr), bytes);

    dprintf(args->control_socket,
    "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", bytes[0],
    bytes[1], bytes[2], bytes[3], port / 256, port % 256);

    printf("Data socket port: %d\n", (port / 256) * 256 + (port % 256));

    args->server_data->data_mode = PASSIVE;
}
