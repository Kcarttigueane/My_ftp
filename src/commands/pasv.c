/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pasv.c
*/

#include "../../include/server.h"

// void set_socket_options(int socket_fd)
// {
//     int reuse = 1;
//     if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
//         0) {
//         handle_error("setsockopt");
//     }
// }

// int get_bound_port(int socket_fd, struct sockaddr* address,
// socklen_t* address_len)
// {
//     if (getsockname(socket_fd, address, address_len) < 0)
//         handle_error("getsockname");
//     return ntohs(((struct sockaddr_in*)address)->sin_port);
// }


int create_data_socket(server_data_t* server_data)
{
    // ! Create a new socket for passive data transfer
    int data_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket_fd < 0)
        exit(84);

    // ! Set the socket options to reuse the same address as control socket
    int reuse = 1;
    if (setsockopt(data_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse,
                   sizeof(reuse)) < 0) {
        exit(84);
    }

    // ! Bind the socket to a free port on the same interface as control socket
    memset(&server_data->data_address, 0, sizeof(server_data->data_address));
    server_data->data_address.sin_family = AF_INET;
    server_data->data_address.sin_addr.s_addr = server_data->server_address.sin_addr.s_addr;
    server_data->data_address.sin_port = 0;  // 0 to use a free port

    if (bind(data_socket_fd, (struct sockaddr*)&server_data->data_address,
             sizeof(server_data->data_address)) < 0) {
        exit(84);
    }

    if (listen(data_socket_fd, 1) < 0)
        exit(84);

    return data_socket_fd;
}


void pasv(int control_socket, ...)
{
    printf("PASV command called\n");
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t* server_data = get_nth_argument(0, args);

    // ! Create a new socket for passive data transfer
    server_data->data_socket_fd = create_data_socket(server_data);

    // ! Get the bound port number
    socklen_t addr_len = sizeof(server_data->data_address);
    if (getsockname(server_data->data_socket_fd,
                    (struct sockaddr*)&server_data->data_address,
                    &addr_len) < 0) {
        exit(84);
    }

    // ! Convert the IP address to bytes
    char* ip = inet_ntoa(clients[control_socket - 4].client_address.sin_addr);
    int ip1, ip2, ip3, ip4;
    sscanf(ip, "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);

    // Calculate the port number to send to the client
    int port = ntohs(server_data->data_address.sin_port);
    int port1 = port / 256;
    int port2 = port % 256;

    // ! Send the response to the client
    char response[BUFFER_SIZE];
    sprintf(response, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", ip1,
            ip2, ip3, ip4, port1, port2);

    printf("Data socket port: %d\n", (port / 256) * 256 + (port % 256));

    if (write(clients[control_socket - 4].client_socked_fd, response,
              strlen(response)) < 0) {
        exit(84);
    }
}
