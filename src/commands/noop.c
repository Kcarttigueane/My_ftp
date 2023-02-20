/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** noop.c
*/

#include "server.h"

void noop(int control_socket)
{
    send_resp(control_socket, FTP_REPLY_200);
}
