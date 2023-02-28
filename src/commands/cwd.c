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
    char* new_path = realpath(input_command[1], NULL);

    if (!new_path) {
        send_resp(control_socket, FTP_REPLY_550);
        return;
    }
    if (strncmp(new_path, server_data->initial_path,
        strlen(server_data->initial_path)) != 0) {
        send_resp(control_socket, FTP_REPLY_550);
        free(new_path);
        return;
    }
    if (chdir(new_path) == FAILURE) {
        perror("chdir");
        send_resp(control_socket, FTP_REPLY_550);
    } else {
        send_resp(control_socket, FTP_REPLY_250);
        clients[control_socket - 4].current_path = strdup(new_path);
    }
    free(new_path);
}

void cwd_command(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args))
        return;

    char** input_command = get_nth_argument(2, args);
    if (!input_command[1]) {
        send_resp(control_socket, FTP_REPLY_501);
        return;
    }

    server_data_t* server_data = get_nth_argument(0, args);

    cwd_execution(control_socket, input_command, clients, server_data);
    va_end(args);
}
