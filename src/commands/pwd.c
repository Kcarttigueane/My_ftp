/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pwd.c
*/

#include "../../include/server.h"

void pwd(list_args_t* args)
{
    if (!is_logged(args->control_socket, args->clients)) return;

    char pwd_buf[BUFFER_SIZE];
    if (!getcwd(pwd_buf, BUFFER_SIZE)) {
        perror("getcwd");
        send_resp(args->control_socket, FTP_REPLY_500);
        return;
    }
    char* relative_path =
        strstr(args->clients[args->control_socket - 4].current_path, pwd_buf);
    if (!relative_path) {
        send_resp(args->control_socket, FTP_REPLY_500);
        return;
    }
    dprintf(args->control_socket, "257 \"%s\" is the current directory.\r\n",
    relative_path);
}
