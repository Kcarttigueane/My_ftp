/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** noop.c
*/

#include "server.h"

void noop(int i)
{
    send_resp(i, FTP_REPLY_200);
}
