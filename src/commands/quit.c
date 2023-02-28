/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** quit.c
*/

#include "../../include/server.h"

void quit_client_cleanup(int control_socket, client_t* clients)
{
    if (!clients[control_socket - 4].is_logged)
        return;

    close(clients[control_socket - 4].client_socked_fd);
    clients[control_socket - 4].is_logged = false;
    clients[control_socket - 4].client_socked_fd = FAILURE;
    free(clients[control_socket - 4].username);
    free(clients[control_socket - 4].password);
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
    close(args->control_socket);
    FD_CLR(args->control_socket, &args->server_data->fds);
}
