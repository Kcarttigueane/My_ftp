/*
** EPITECH PROJECT, 2022
** server
** File description:
** cdup.c
*/

#include "../../include/server.h"

void change_directory(int control_socket, client_t* clients, char* current_path,
server_data_t* server_data)
{
    chdir(clients[control_socket - 4].current_path);

    char* new_path = dirname(current_path);

    if (chdir(new_path) == FAILURE) {
        perror("chdir");
        send_resp(control_socket, FTP_REPLY_550);
    } else {
        send_resp(control_socket, FTP_REPLY_200);
        clients[control_socket - 4].current_path = strdup(new_path);
        chdir(server_data->initial_path);
    }
}

void cdup(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients))
        return;

    char* current_path = args->clients[args->control_socket - 4].current_path;

    if (!strcmp(current_path, args->server_data->initial_path)) {
        send_resp(args->control_socket, FTP_REPLY_550);
        return;
    }
    change_directory(args->control_socket, args->clients, current_path,
    args->server_data);
}
