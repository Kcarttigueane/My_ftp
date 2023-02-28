/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** delete.c
*/

#include "../../include/server.h"

void dele(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients))
        return;

    if (remove(args->input_command[1]) == 0) {
        dprintf(args->control_socket, "250 File %s deleted\r\n",
        args->input_command[1]);
    } else {
        dprintf(args->control_socket, "550 File %s not found\r\n",
        args->input_command[1]);
    }
}
