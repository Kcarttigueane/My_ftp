/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** is_logged.c
*/

#include "../include/server.h"

bool is_logged(int control_socket, client_t* clients)
{
    if (clients[control_socket - 4].is_logged == false) {
        send_resp(control_socket, FTP_REPLY_530);
        return false;
    }
    return true;
}
