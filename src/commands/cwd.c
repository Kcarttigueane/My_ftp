/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cwd.c
*/

#include "../../include/server.h"

void cwd_execution(int control_socket, char** input_command, client_t* clients,
server_data_t* server_data)
{
    chdir(clients[control_socket - 4].current_path);

    char* new_path = realpath(input_command[1], NULL);

    if (!is_directory_accessible(control_socket, server_data, new_path))
        return;

    if (chdir(new_path) == FAILURE) {
        perror("chdir");
        send_resp(control_socket, FTP_REPLY_550);
        free(new_path);
    } else {
        send_resp(control_socket, FTP_REPLY_250);
        clients[control_socket - 4].current_path = new_path;
        chdir(server_data->initial_path);
    }
}

void cwd_command(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients))
        return;

    if (!args->input_command[1]) {
        send_resp(args->control_socket, FTP_REPLY_501);
        return;
    }
    cwd_execution(args->control_socket, args->input_command, args->clients,
    args->server_data);
}
