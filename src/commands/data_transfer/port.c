/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** port.c
*/

#define PORT_ARGS_FORMAT "%[^,],%d,%d"

#include "../../../include/server.h"

int port_data_socket(char* ip, int port1, int port2)
{
    struct sockaddr_in client_address;
    memset(&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port1 * 256 + port2);
    inet_aton(ip, &client_address.sin_addr);

    int data_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket_fd < 0)
        handle_error("socket");

    if (connect(data_socket_fd, (struct sockaddr*)&client_address,
                sizeof(client_address)) < 0)
        handle_error("connect");

    return data_socket_fd;
}

void handle_port_args(int control_socket, client_t* clients,
server_data_t* server_data, char** port_args)
{
    if (get_size_word_array(port_args) != 2) {
        send_resp(control_socket, FTP_REPLY_501);
        return;
    }
    char ip[BUFFER_SIZE];
    int port1, port2;
    int format_input =
        sscanf(port_args[1], PORT_ARGS_FORMAT, ip, &port1, &port2);
    if (format_input != 3) {
        send_resp(control_socket, FTP_REPLY_501);
        return;
    }
    server_data->data_socket_fd = port_data_socket(ip, port1, port2);
    send_resp(clients[control_socket - 4].client_socked_fd, FTP_REPLY_200);
}

void port(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients))
        return;

    handle_port_args(args->control_socket, args->clients, args->server_data,
    args->input_command);
}
