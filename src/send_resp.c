/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** send_resp.c
*/

#include "../include/server.h"

void send_resp(int socket_fd, char *msg)
{
    dprintf(socket_fd, "%s", msg);
}
