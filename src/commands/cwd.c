/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cwd.c
*/

#include "../../include/server.h"

void handle_chdir_error(int control_socket, int errno_code)
{
    switch (errno_code) {
        case ENOENT:
            send_resp(control_socket, "550 Directory not found\r\n");
            break;
        case EACCES:
            send_resp(control_socket, "550 Permission denied\r\n");
            break;
        default:
            send_resp(control_socket, "550 Failed to change directory\r\n");
            break;
    }
}

void cwd_command(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    char** input_command = get_nth_argument(2, args);

    if (chdir(input_command[1]) < 0) {
        handle_chdir_error(control_socket, errno);
    } else {
        free(clients[control_socket - 4].current_path);
        clients[control_socket - 4].current_path = strdup(input_command[1]);
        send_resp(control_socket, "250 Directory successfully changed\r\n");
    }

    va_end(args);
}
