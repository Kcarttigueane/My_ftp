/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pwd.c
*/

#include "../../include/server.h"

void pwd(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients)) return;

    if (args->clients[args->control_socket - 4].current_path == NULL) {
        dprintf(args->control_socket, FTP_REPLY_550);
        return;
    }

    dprintf(args->control_socket, "257 \"%s\" is the current directory.\r\n",
    args->clients[args->control_socket - 4].current_path);
}
