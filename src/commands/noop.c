/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** noop.c
*/

#include "../../include/server.h"

void noop(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);

    client_t* clients = get_nth_argument(1, args);

    if (clients[control_socket - 4].is_logged)
        send_resp(control_socket, FTP_REPLY_200);
    else
        send_resp(control_socket, FTP_REPLY_530);

    va_end(args);
}
