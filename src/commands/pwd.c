/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pwd.c
*/

#include "../../include/server.h"

void pwd(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);

    client_t* clients = get_nth_argument(1, args);

    char msg[BUFFER_SIZE] = {0};
    int path_len = strlen(clients[control_socket - 4].current_path);

    if (path_len >= BUFFER_SIZE - 30) {
        send_resp(control_socket,
        "550 Current working directory path is too long\r\n");
    } else {
        sprintf(msg, "257 \"%s\" is the current working directory.\r\n",
        clients[control_socket - 4].current_path);
        send_resp(control_socket, msg);
    }

    va_end(args);
}
