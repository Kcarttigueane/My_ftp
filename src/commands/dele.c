/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** delete.c
*/

#include "../../include/server.h"

void dele(int control_socket, char** input_command)
{
    char response[BUFFER_SIZE] = {0};

    if (remove(input_command[1]) == 0) {
        sprintf(response, "250 File %s deleted\r\n", input_command[1]);
        send_resp(control_socket, response);
    } else {
        sprintf(response, "550 File %s not found\r\n", input_command[1]);
        send_resp(control_socket, response);
    }
}
