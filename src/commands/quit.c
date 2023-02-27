/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** quit.c
*/

#include "../../include/server.h"

void quit_client_cleanup(int control_socket, client_t* clients)
{
    if (!clients[control_socket - 4].is_logged) return;

    close(clients[control_socket - 4].client_socked_fd);
    clients[control_socket - 4].is_logged = false;
    clients[control_socket - 4].client_socked_fd = FAILURE;
    free(clients[control_socket - 4].username);
    free(clients[control_socket - 4].password);
    free(clients[control_socket - 4].current_path);
}

void quit(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    server_data_t* server_data = get_nth_argument(0, args);

    if (server_data->data_socket_fd != FAILURE) {
        dprintf(control_socket, FTP_REPLY_226);
        close(server_data->data_socket_fd);
        server_data->data_socket_fd = FAILURE;
    }

    dprintf(control_socket, FTP_REPLY_221);
    quit_client_cleanup(control_socket, clients);
    close(control_socket);
    FD_CLR(control_socket, &server_data->fds);
    va_end(args);
}
