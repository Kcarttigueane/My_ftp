/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** delete.c
*/

#include "../../include/server.h"

void dele(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);

    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args))
        return;

    char** input_command = get_nth_argument(2, args);

    (remove(input_command[1]) == 0)
    ? dprintf(control_socket, "250 File %s deleted\r\n", input_command[1])
    : dprintf(control_socket, "550 File %s not found\r\n",
                input_command[1]);

    va_end(args);
}
