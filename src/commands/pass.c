/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pass.c
*/

#include "../../include/server.h"

bool test_pass_conditions(client_t* clients, int control_socket, char** command)
{
    char* password = get_size_word_array(command) == 2 ? command[1] : "";

    if (strcmp(clients[control_socket - 4].username, ANONYMOUS_USERNAME) ||
        clients[control_socket - 4].username[0] == '\0') {
        send_resp(control_socket, FTP_REPLY_503);
        return true;
    }
    if (clients[control_socket - 4].is_logged == true) {
        send_resp(control_socket, FTP_REPLY_530);
        return true;
    }
    if ((!strcmp(clients[control_socket - 4].username, ANONYMOUS_USERNAME)) &&
        (!strcmp(password, ANONYMOUS_PASSWORD))) {
        send_resp(control_socket, FTP_REPLY_230);
        clients[control_socket - 4].is_logged = true;
        return true;
    }
    send_resp(control_socket, FTP_REPLY_530);
    return false;
}

void pass(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    char** command = get_nth_argument(2, args);

    if (test_pass_conditions(clients, control_socket, command)) {
        va_end(args);
        return;
    }
    send_resp(control_socket, FTP_REPLY_530);
    va_end(args);
}
