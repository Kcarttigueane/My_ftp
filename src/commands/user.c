/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** user_command.c
*/

#include "server.h"

void user(server_data_t* server_data, int i, char** command, client_t* clients)
{
    if (get_size_word_array(command) != 2) {
        write(i, FTP_REPLY_501, strlen(FTP_REPLY_501));
    } else if (clients[i - 4].is_logged == true) {
        write(i, FTP_REPLY_530, strlen(FTP_REPLY_530));
    } else if (!strcmp(command[1], ANONYMOUS_USERNAME)) {
        write(i, FTP_REPLY_331, strlen(FTP_REPLY_331));
        strcpy(clients[i - 4].username, ANONYMOUS_USERNAME);
    } else {
        write(i, FTP_REPLY_530, strlen(FTP_REPLY_530));
    }
}
