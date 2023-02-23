/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pass.c
*/

#include "../../include/server.h"

void pass(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    char** command = get_nth_argument(2, args);
    client_t* clients = get_nth_argument(1, args);
    char* password = get_size_word_array(command) == 2 ? command[1] : "";
    if (strcmp(clients[control_socket - 4].username, ANONYMOUS_USERNAME) ||
        clients[control_socket - 4].username[0] == '\0') {
        write(control_socket, FTP_REPLY_503, strlen(FTP_REPLY_503));
        return;
    } if (clients[control_socket - 4].is_logged == true) {
        write(control_socket, FTP_REPLY_530, strlen(FTP_REPLY_530));
        return;
    } if ((!strcmp(clients[control_socket - 4].username, ANONYMOUS_USERNAME)) &&
        (!strcmp(password, ANONYMOUS_PASSWORD))) {
        write(control_socket, FTP_REPLY_230, strlen(FTP_REPLY_230));
        clients[control_socket - 4].is_logged = true;
        return;
    }
    write(control_socket, FTP_REPLY_530, strlen(FTP_REPLY_530));
    va_end(args);
}
