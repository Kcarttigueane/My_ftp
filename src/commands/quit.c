/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** quit.c
*/

#include "../../include/server.h"

void quit_client_cleanup(int control_socket, client_t* clients)
{
    if (clients[control_socket - 4].is_logged == true)
        return;

    close(clients[control_socket - 4].client_socked_fd);
    clients[control_socket - 4].client_socked_fd = FAILURE;
    clients[control_socket - 4].is_logged = false;
    if (clients[control_socket - 4].current_path)
        free(clients[control_socket - 4].current_path);
}

void quit(list_args_t* args)
{
    if (args->server_data->data_socket_fd != FAILURE) {
        dprintf(args->control_socket, FTP_REPLY_226);
        close(args->server_data->data_socket_fd);
        args->server_data->data_socket_fd = FAILURE;
    }

    dprintf(args->control_socket, FTP_REPLY_221);
    quit_client_cleanup(args->control_socket, args->clients);
    FD_CLR(args->control_socket, &args->server_data->fds);
}
