/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** is_data_con_establish.c
*/

#include "../include/server.h"

bool is_data_con_establish(int control_socket, server_data_t *server_data)
{
    if (server_data->data_socket_fd == FAILURE) {
        dprintf(control_socket, "425 Use PORT or PASV first.\r\n");
        return false;
    }
    return true;
}
