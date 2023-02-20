/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** cwd.c
*/

#include "server.h"

void cwd(int control_socket, char** input_command, client_t* clients)
{
    if (chdir(input_command[1]) < 0) {
        if (errno == ENOENT) {
            send_resp(control_socket, "550 Directory not found\r\n");
        } else if (errno == EACCES) {
            send_resp(control_socket, "550 Permission denied\r\n");
        } else {
            send_resp(control_socket, "550 Failed to change directory\r\n");
        }
    } else {
        free(clients[control_socket - 4].current_path);
        clients[control_socket - 4].current_path = strdup(input_command[1]);
        send_resp(control_socket, "250 Directory successfully changed\r\n");
    }
}
