/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** noop.c
*/

#include "../../include/server.h"

void noop(list_args_t* args)
{
    (args->clients[args->control_socket - 4].is_logged)
        ? send_resp(args->control_socket, FTP_REPLY_200)
        : send_resp(args->control_socket, FTP_REPLY_530);
}
