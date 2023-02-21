/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** send_resp.c
*/

#include "server.h"

void send_resp(int socket_fd, char *msg)
{
    write(socket_fd, msg, strlen(msg));
}
