/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pasv.c
*/

#include "../../include/server.h"

int create_data_socket(server_data_t* server_data)
{
    // ! Create a new socket for passive data transfer
    int data_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (data_socket_fd < 0)
        handle_error("Error creating data socket");

    // ! Set the socket options to reuse the same address as control socket
    int reuse = 1;
    if (setsockopt(data_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse,
                   sizeof(reuse)) < 0) {
        handle_error("Error setting socket options");
    }

    // ! Bind the socket to a free port on the same interface as control socket
    memset(&server_data->data_address, 0, sizeof(server_data->data_address));
    server_data->data_address.sin_family = AF_INET;
    server_data->data_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_data->data_address.sin_port = 0;  // 0 to use a free port

    if (bind(data_socket_fd, (struct sockaddr*)&server_data->data_address,
             sizeof(server_data->data_address)) < 0) {
        handle_error("Error binding data socket");
    }
    return data_socket_fd;
}

void pasv(circular_buffer* cb, server_data_t* server_data, int control_socket,
client_t* clients)
{
    // ! Create a new socket for passive data transfer
    int data_socket_fd = create_data_socket(server_data);

    // ! Get the bound port number
    socklen_t addr_len = sizeof(server_data->data_address);
    if (getsockname(data_socket_fd, (struct sockaddr*)&server_data->data_address, &addr_len) <
        0) {
        handle_error("Error getting socket name");
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

    if (write(clients[control_socket - 4].client_socked_fd, response,
              strlen(response)) < 0) {
        handle_error("Error sending response to client");
    }
}
