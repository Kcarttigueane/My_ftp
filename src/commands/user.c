/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** user_command.c
*/

#include "../../include/server.h"

void user(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    char** command = get_nth_argument(2, args);
    client_t* clients = get_nth_argument(1, args);
    if (get_size_word_array(command) != 2) {
        write(control_socket, FTP_REPLY_501, strlen(FTP_REPLY_501));
        return;
    }
    if (clients[control_socket - 4].is_logged == true) {
        write(control_socket, FTP_REPLY_530, strlen(FTP_REPLY_530));
        return;
    }
    if (!strcmp(command[1], ANONYMOUS_USERNAME)) {
        write(control_socket, FTP_REPLY_331, strlen(FTP_REPLY_331));
        strcpy(clients[control_socket - 4].username, ANONYMOUS_USERNAME);
        return;
    }
    write(control_socket, FTP_REPLY_530, strlen(FTP_REPLY_530));
    va_end(args);
}
