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

void pass(list_args_t* args)
{
    if (test_pass_conditions(args->clients, args->control_socket,
        args->input_command)) {
        return;
    }
    send_resp(args->control_socket, FTP_REPLY_530);
}
