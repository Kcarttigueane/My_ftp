/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** create_temp_socket.c
*/

#include "../include/server.h"

int create_temp_socket(server_data_t* server_data, client_t* clients)
{
    int data_sock_temp;

    if (server_data->data_mode == ACTIVE) {
        if ((data_sock_temp =
            connect(server_data->data_socket_fd,
                (struct sockaddr*)&clients->client_address,
                sizeof(clients->client_address))) == FAILURE)
            handle_error("connect");
    } else if (server_data->data_mode == PASSIVE) {
        if ((data_sock_temp =
            accept(server_data->data_socket_fd, NULL, NULL)) == FAILURE) {
            handle_error("accept for data connection");
        }
    }
    return data_sock_temp;
}
