/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** pwd.c
*/

#include "../../include/server.h"

void pwd(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);
    client_t* clients = get_nth_argument(1, args);
    if (!is_logged(control_socket, clients, &args)) return;

    char pwd_buf[BUFFER_SIZE];
    if (!getcwd(pwd_buf, BUFFER_SIZE)) {
        perror("getcwd");
        send_resp(control_socket, FTP_REPLY_500);
        return;
    }
    char* relative_path =
        strstr(clients[control_socket - 4].current_path, pwd_buf);
    if (!relative_path) {
        send_resp(control_socket, FTP_REPLY_500);
        return;
    }
    dprintf(control_socket, "257 \"%s\" is the current directory.\r\n",
    relative_path);
    va_end(args);
}
