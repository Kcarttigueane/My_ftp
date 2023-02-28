/*
** EPITECH PROJECT, 2022
** server
** File description:
** cdup.c
*/

#include "../../include/server.h"

void change_directory(int control_socket, client_t *clients, char *current_path)
{
    char* new_path = dirname(current_path);
    if (chdir(new_path) == FAILURE) {
        perror("chdir");
        send_resp(control_socket, FTP_REPLY_550);
    } else {
        send_resp(control_socket, FTP_REPLY_250);
        clients[control_socket - 4].current_path = strdup(new_path);
    }
}

void cdup(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args)) return;

    server_data_t* server_data = get_nth_argument(0, args);
    char* current_path = clients[control_socket - 4].current_path;

    if (!strcmp(current_path, server_data->initial_path)) {
        send_resp(control_socket, FTP_REPLY_550);
        return;
    }
    change_directory(control_socket, clients, current_path);
    va_end(args);
}
