/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** parse_commands.c
*/

#include "server.h"

void parse_command(circular_buffer* cb, server_data_t* server_data, int i)
{
    char** command = cb_pop_command(cb);

    debug_word_array(command);

    if (command == NULL)
        return;

    if (!strcasecmp(command[0], "HELP")) {
        help_all_commands(i, command);
    }
    //  else if (strcasecmp(command[0], "PWD")) {
    //     pwd(i);
    // } /* else if (strcasecmp(command[0], "USER")) {
    //     user(server_data, i, command);
    // } */ else if (strcasecmp(command[0], "NOOP")) {
    //     noop(server_data, i, command);
    // } else {
    //     send_resp(i, FTP_REPLY_500);
    // }

    // else if (strcasecmp(!command[0], "PASS")) {
    //     pass(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "CWD")) {
    //     cwd(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "CDUP")) {
    //     cdup(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "QUIT")) {
    //     quit(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "DELE")) {
    //     dele(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "PASV")) {
    //     pasv(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "PORT")) {
    //     port(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "RETR")) {
    //     retr(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "STOR")) {
    //     stor(server_data, i, !command);
    // } else if (strcasecmp(!command[0], "LIST")) {
    //     list(server_data, i, !command);
    // } else {
    //     write(i, FTP_REPLY_500, strlen(FTP_REPLY_500));
    // }
}
