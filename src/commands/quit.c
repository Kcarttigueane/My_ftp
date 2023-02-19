/*
** EPITECH PROJECT, 2022
** Repositery-MyFTP
** File description:
** quit.c
*/

#include "../../include/server.h"

void quit(server_data_t* server_data, int i, char** command)
{
    write(i, FTP_REPLY_221, strlen(FTP_REPLY_221));
    close(i);
    // FD_CLR(i, &server_data.active_fd_set);
}
