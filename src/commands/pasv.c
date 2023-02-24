/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pasv.c
*/

#include "../../include/server.h"

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

void pasv(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t* server_data = get_nth_argument(0, args);

    server_data->data_socket_fd = create_data_socket(server_data);
    int port = get_bound_port(
        server_data->data_socket_fd,
        (struct sockaddr*)&server_data->data_address,
        &server_data->data_len);
    int bytes[4];
    ip_to_bytes(inet_ntoa(server_data->server_address.sin_addr), bytes);

    char response[BUFFER_SIZE];

    sprintf(response, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
            bytes[0], bytes[1], bytes[2], bytes[3], port / 256, port % 256);
    printf("Data socket port: %d\n", (port / 256) * 256 + (port % 256));

    send_resp(clients[control_socket - 4].client_socked_fd, response);
}
