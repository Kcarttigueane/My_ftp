/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pass.c
*/

#include "server.h"

void pass(server_data_t* server_data, int i, char** command, client_t* clients)
{
    if (get_size_word_array(command) != 2) {
        write(i, FTP_REPLY_501, strlen(FTP_REPLY_501));
    } else if (strcmp(clients[i - 4].username, ANONYMOUS_USERNAME) ||
               clients[i - 4].username[0] == '\0') {
        write(i, FTP_REPLY_503, strlen(FTP_REPLY_503));
    } else if (clients[i - 4].is_logged == true) {
        write(i, FTP_REPLY_530, strlen(FTP_REPLY_530));
    } else if ((!strcmp(clients[i - 4].username, ANONYMOUS_USERNAME)) &&
               (!strcmp(command[1], ANONYMOUS_PASSWORD))) {
        write(i, FTP_REPLY_230, strlen(FTP_REPLY_230));
        clients[i - 4].is_logged = true;
    } else {
        write(i, FTP_REPLY_530, strlen(FTP_REPLY_530));
    }
}
