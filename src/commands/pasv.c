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

void bind_data_socket(int socket_fd, struct sockaddr* address,
size_t address_size)
{
    if (bind(socket_fd, address, address_size) < 0)
        exit(84);
}

int get_bound_port(int socket_fd, struct sockaddr* address,
socklen_t* address_len)
{
    if (getsockname(socket_fd, address, address_len) < 0)
        handle_error("getsockname");
    return ntohs(((struct sockaddr_in*)address)->sin_port);
}

int create_data_socket(client_t* clients, int control_socket)
{
    int data_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket_fd < 0)
        handle_error("socket");

    set_socket_options(data_socket_fd);

    memset(&clients[control_socket - 4].data_address, 0,
           sizeof(clients[control_socket - 4].data_address));
    clients[control_socket - 4].data_address.sin_family = AF_INET;
    clients[control_socket - 4].data_address.sin_addr.s_addr =
    htonl(INADDR_ANY);
    clients[control_socket - 4].data_address.sin_port = 0;

    bind_data_socket(
        data_socket_fd,
        (struct sockaddr*)&clients[control_socket - 4].data_address,
        sizeof(clients[control_socket - 4].data_address));

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
    printf("PASV command called\n");
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t *server_data = get_nth_argument(0, args);

    char** command = get_nth_argument(2, args);
    clients[control_socket - 4].data_socket_fd = create_data_socket(clients, control_socket);

    char response[BUFFER_SIZE];
    int port = get_bound_port(
        clients[control_socket - 4].data_socket_fd,
        (struct sockaddr*)&clients[control_socket - 4].data_address,
        &clients[control_socket - 4].data_len);
    int bytes[4];
    ip_to_bytes(inet_ntoa(clients[control_socket - 4].client_address.sin_addr),
                bytes);
    sprintf(response, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n",
            bytes[0], bytes[1], bytes[2], bytes[3], port / 256, port % 256);
    printf("Data socket port: %d\n", (port / 256) * 256 + (port % 256));

    send_resp(clients[control_socket - 4].client_socked_fd, response);
}
