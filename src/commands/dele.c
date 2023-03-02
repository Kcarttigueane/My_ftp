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

    char* new_path = realpath(args->input_command[1], NULL);

    if (!is_directory_accessible(args->control_socket, args->server_data,
        new_path))
        return;

    if (remove(new_path) == FAILURE) {
        perror("remove");
        dprintf(args->control_socket, "550 File %s not found\r\n",
        args->input_command[1]);
    } else {
        dprintf(args->control_socket, "250 File %s deleted\r\n",
        args->input_command[1]);
    }
}
