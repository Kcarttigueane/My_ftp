/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** pwd.c
*/

#include "server.h"

void pwd(int control_socket)
{
    char cwd[100];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        send_resp(control_socket, "500 Failed to get current working directory.");
        return;
    }
    char msg[100 + 50];
    sprintf(msg, "257 \"%s\" is the current working directory.", cwd);
    send_resp(control_socket, msg);
}
