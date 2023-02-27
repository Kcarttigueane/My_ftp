/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** user_command.c
*/

#include "../../include/server.h"

bool test_user_conditions(client_t* clients, char** command, int control_socket)
{
    if (get_size_word_array(command) != 2) {
        send_resp(control_socket, FTP_REPLY_501);
        return true;
    }
    if (clients[control_socket - 4].is_logged == true) {
        send_resp(control_socket, FTP_REPLY_530);
        return true;
    }
    if (!strcmp(command[1], ANONYMOUS_USERNAME)) {
        send_resp(control_socket, FTP_REPLY_331);
        strcpy(clients[control_socket - 4].username, ANONYMOUS_USERNAME);
        return true;
    }
    if (command[1]) {
        send_resp(control_socket, FTP_REPLY_331);
        strcpy(clients[control_socket - 4].username, command[1]);
        return true;
    }
    return false;
}

void user(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    char** command = get_nth_argument(2, args);

    if (test_user_conditions(clients, command, control_socket)) {
        va_end(args);
        return;
    }
    send_resp(control_socket, FTP_REPLY_530);
    va_end(args);
}
