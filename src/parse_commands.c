/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** parse_commands.c
*/

#include "server.h"

void parse_command(circular_buffer* cb, server_data_t* server_data,
                   int control_socket, client_t* clients)
{
    char** command = cb_pop_command(cb);

    debug_word_array(command);

    if (command == NULL) {
        printf("command is null\n");
        return;
    }

    if (!strcasecmp(command[0], "HELP")) {
        help_command(control_socket, command);
    } else if (!strcasecmp(command[0], "NOOP")) {
        noop(control_socket);
    } else if (!strcasecmp(command[0], "PWD")) {
        pwd(clients, control_socket, server_data);
    } else if (!strcasecmp(command[0], "CWD")) {
        cwd(control_socket, command, clients);
    }


    /* else if (strcasecmp(command[0], "USER")) {
    //     user(server_data, control_socket, command);
    // } */
    // else {
    //     send_resp(control_socket, FTP_REPLY_500);
    // }

    // else if (strcasecmp(!command[0], "PASS")) {
    //     pass(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "CDUP")) {
    //     cdup(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "QUIT")) {
    //     quit(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "DELE")) {
    //     dele(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "PASV")) {
    //     pasv(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "PORT")) {
    //     port(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "RETR")) {
    //     retr(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "STOR")) {
    //     stor(server_data, control_socket, !command);
    // } else if (strcasecmp(!command[0], "LIST")) {
    //     list(server_data, control_socket, !command);
    // } else {
    //     write(control_socket, FTP_REPLY_500, strlen(FTP_REPLY_500));
    // }
}
