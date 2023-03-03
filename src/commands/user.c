/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** user_command.c
*/

#include "../../include/server.h"

bool test_user_conditions(client_t* clients, char** input_command,
int control_socket)
{
    if (clients[control_socket - 4].is_logged == true) {
        send_resp(control_socket, FTP_REPLY_530);
        return true;
    }
    if (!strcmp(input_command[1], ANONYMOUS_USERNAME)) {
        send_resp(control_socket, FTP_REPLY_331);
        strcpy(clients[control_socket - 4].username, ANONYMOUS_USERNAME);
        return true;
    }
    if (input_command[1]) {
        send_resp(control_socket, FTP_REPLY_331);
        strcpy(clients[control_socket - 4].username, input_command[1]);
        return true;
    }
    return false;
}

void user(list_args_t* args)
{
    if (get_size_word_array(args->input_command) != 2) {
        send_resp(args->control_socket, FTP_REPLY_501);
        return;
    }
    if (test_user_conditions(args->clients, args->input_command,
    args->control_socket))
        return;

    send_resp(args->control_socket, FTP_REPLY_530);
}
