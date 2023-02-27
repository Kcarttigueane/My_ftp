/*
** EPITECH PROJECT, 2022
** server
** File description:
** cdup.c
*/

#include "../../include/server.h"

char* get_current_path(int control_socket, client_t* clients)
{
    char* current_path = strdup(clients[control_socket - 4].current_path);
    char* tmp = NULL;
    int last_slash_pos = 0;

    if (strcmp(current_path, "/") == 0)
        return current_path;

    for (int i = strlen(current_path) - 1; i >= 0; i--) {
        if (current_path[i] == '/') {
            last_slash_pos = i;
            break;
        }
    }
    tmp = strndup(current_path, last_slash_pos);
    free(current_path);
    clients[control_socket - 4].current_path = strdup(tmp);
    return tmp;
}

void cdup(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);

    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args))
        return;

    if (chdir("..") != 0) {
        send_resp(control_socket, FTP_REPLY_550);
    } else {
        send_resp(control_socket, FTP_REPLY_200);
        clients[control_socket - 4].current_path =
        get_current_path(control_socket, clients);
    }
    va_end(args);
}
